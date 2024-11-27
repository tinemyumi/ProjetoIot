# Projeto IoT: Monitoramento e Redução do Estresse com Música 🎵

## Descrição 📑

Este projeto utiliza **IoT (Internet das Coisas)** para monitorar o estresse de uma pessoa por meio de um **sensor de pulso cardíaco** e **ESP8266 NodeMCU**. Quando detectado um nível elevado de estresse, o sistema recomenda uma playlist de músicas relaxantes via **Spotify** e envia notificações via **WhatsApp**. Os dados do sensor são armazenados no **InfluxDB** e visualizados no **Grafana**.

## Componentes ⚒️

- **ESP8266 NodeMCU**: Microcontrolador que coleta dados do sensor e se conecta à nuvem.
- **Sensor de Pulso Cardíaco**: Monitora a frequência cardíaca do usuário.
- **Arduino IoT Cloud**: Plataforma para gerenciar o dispositivo e os dados coletados.
- **Node-RED**: Orquestra os dados entre o sensor, Spotify, WhatsApp, InfluxDB e Grafana.
- **API do Spotify**: Controla a reprodução de músicas baseadas no nível de estresse.
- **WhatsApp API**: Envia alertas e recomendações ao usuário.
- **InfluxDB**: Armazena os dados coletados do sensor.
- **Grafana**: Exibe os dados de forma interativa.

## Objetivo 🎯

Monitorar e reduzir o estresse do usuário, utilizando música como método de alívio. O sistema detecta a frequência cardíaca, analisa os dados e escolhe músicas do Spotify para ajudar no relaxamento, além de fornecer feedback ao usuário via WhatsApp. Os dados são armazenados e pode-se visualizar os dados de forma interativa através de dashboard. 

## Tecnologias Utilizadas 💻

- **ESP8266 NodeMCU**: Para conectar o sensor à rede e à nuvem.
- **Node-RED**: Para integrar as diferentes plataformas (Spotify, WhatsApp, InfluxDB).
- **API do Spotify**: Para reproduzir músicas personalizadas.
- **WhatsApp API**: Para enviar notificações sobre o nível de estresse.
- **InfluxDB e Grafana**: Para armazenamento e visualização dos dados em tempo real.

## Conclusão 💯

O projeto oferece uma solução inovadora para o monitoramento e controle do estresse, utilizando IoT e integração de múltiplas plataformas, proporcionando uma experiência personalizada de bem-estar.
