#include "arduino_secrets.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Configurações de Wi-Fi e MQTT
const char* SSIDName = "WIFI";
const char* SSIDPass = "SENHA";
const char* BrokerURL = "broker.hivemq.com";
const int BrokerPort = 1883;

char Topico_01[] = "SensorPulso";
char MQTTClientName[] = "mqtt-explorer-05a6ff30";

WiFiClient espClient;
PubSubClient clienteMQTT(espClient);

// Pinos e variáveis para o sensor de pulso | HB = HeartBeat
const int PulseSensorHRWire = A0;  // Pino do sensor de pulso
int Threshold = 600; // Limiar para detectar um batimento cardíaco
int cntHB = 0; // Contador de batimentos
boolean ThresholdStat = true; // Flag para detectar picos de batimento
int BPM = 0; // Valor do BPM

unsigned long previousMillisGetHR = 0; // Tempo de leitura do sensor
unsigned long previousMillisHR = 0; // Tempo de cálculo do BPM

const long intervalGetHR = 10; // Intervalo para ler o sensor (10ms)
const long intervalHR = 5000; // Intervalo para calcular BPM (5 segundos)

void setup() {
  // Inicializa a comunicação serial
  Serial.begin(115200);
  delay(500);

  // Configura o pino de leitura do sensor como entrada
  pinMode(PulseSensorHRWire, INPUT);

  // Conexão com Wi-Fi
  WiFi.begin(SSIDName, SSIDPass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("Conectado ao Wi-Fi");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  // Configura o cliente MQTT
  clienteMQTT.setServer(BrokerURL, BrokerPort);
  clienteMQTT.setCallback(mqttCallback);

  // Tenta conectar ao broker MQTT
  while (!clienteMQTT.connected()) {
    Serial.print("Tentando conectar ao broker MQTT...");
    if (clienteMQTT.connect(MQTTClientName)) {
      Serial.println("Conectado ao broker MQTT");
    } else {
      Serial.print("Falha na conexão. Código de erro: ");
      Serial.println(clienteMQTT.state());
      delay(5000);
    }
  }
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  // Função chamada quando uma mensagem é recebida (não faz nada aqui)
}

void GetHeartRate() {
  unsigned long currentMillisGetHR = millis();

  if (currentMillisGetHR - previousMillisGetHR >= intervalGetHR) {
    previousMillisGetHR = currentMillisGetHR;

    int PulseSensorHRVal = analogRead(PulseSensorHRWire); // Lê o valor do sensor de pulso

    // Detecta os picos do batimento cardíaco
    if (PulseSensorHRVal > Threshold && ThresholdStat == true) {
      cntHB++; // Incrementa o contador de batimentos
      ThresholdStat = false; // Impede que o pico seja contado novamente
    }

    if (PulseSensorHRVal < Threshold) {
      ThresholdStat = true; // Reseta a flag quando o sinal está abaixo do limiar
    }
  }

  // Calcula o BPM a cada 5 segundos
  unsigned long currentMillisHR = millis();

  if (currentMillisHR - previousMillisHR >= intervalHR) {
    previousMillisHR = currentMillisHR;

    BPM = cntHB * 12; // Calcula o BPM (batimentos em 5 segundos multiplicados por 12)
    Serial.print("BPM : ");
    Serial.println(BPM); // Exibe o BPM no monitor serial

    // Envia o BPM para o broker MQTT
    String bpmString = String(BPM);
    clienteMQTT.publish(Topico_01, bpmString.c_str()); // Publica o BPM no tópico MQTT

    cntHB = 0; // Reseta o contador de batimentos para o próximo cálculo
  }
}

void loop() {
  if (!clienteMQTT.connected()) {
    // Reconecta ao broker MQTT caso a conexão seja perdida
    while (!clienteMQTT.connected()) {
      Serial.print("Tentando reconectar ao broker MQTT...");
      if (clienteMQTT.connect(MQTTClientName)) {
        Serial.println("Reconectado ao broker MQTT");
      } else {
        Serial.print("Falha na reconexão. Código de erro: ");
        Serial.println(clienteMQTT.state());
        delay(5000);
      }
    }
  }

  clienteMQTT.loop(); // Processa as mensagens MQTT

  GetHeartRate(); // Função para ler o sensor e calcular o BPM
}
