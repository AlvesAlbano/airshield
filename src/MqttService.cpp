#include "MqttService.h"

void callback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    for (int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
    }
    Serial.println();
    Serial.println("-----------------------");
}

MqttService::MqttService():
    wifiClient(),pubSubClient(wifiClient){
}

void MqttService::init(){
    pubSubClient.setServer(MQTT_SERVER,MQTT_PORT);
    pubSubClient.setCallback(callback);
    pubSubClient.setBufferSize(1024);
    pubSubClient.setSocketTimeout(3);
}

void MqttService::conectar(){

    String client_id = "esp32-airshield-";
    client_id += WiFi.macAddress();

    Serial.println("Tentando conectar ao MQTT...");

    unsigned long inicio = millis();

    if (pubSubClient.connect(client_id.c_str())) {

        Serial.printf("MQTT conectado em %lu ms\n", millis() - inicio);

    } else {

        Serial.printf(
            "Falha MQTT. Estado: %d | Tempo: %lu ms\n",
            pubSubClient.state(),
            millis() - inicio
        );

    }
}

void MqttService::reconectar(){
    if(!pubSubClient.connected()){
        conectar();   
    }
}

bool MqttService::estaConectado(){
    return pubSubClient.connected();
}

void MqttService::loop(){
    if (pubSubClient.connected()) {
        pubSubClient.loop();
    } else {
        reconectar();
    }
}

void MqttService::pub(const char* topico,const char* payload){
    pubSubClient.publish(topico,payload);
}

void MqttService::sub(const char* topico){
    pubSubClient.subscribe(topico);
}