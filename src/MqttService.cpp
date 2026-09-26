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

    conectar();
}

void MqttService::conectar(){
    String client_id = "esp32-airshield ";
    
    client_id += String(WiFi.macAddress());
    Serial.printf("The client %s connects to the public MQTT broker\n", client_id.c_str());
    
    if (pubSubClient.connect(client_id.c_str(),"", "")) {
        Serial.println("Public EMQX MQTT broker connected");
    } else {
        Serial.print("failed with state ");
        Serial.print(pubSubClient.state());
        delay(2000);
    }
}

void MqttService::reconectar(){
    if(!pubSubClient.connected()){
        conectar();   
    }
}

void MqttService::loop(){
    reconectar();
    pubSubClient.loop();
}

void MqttService::pub(const char* topico,const char* payload){
    pubSubClient.publish(topico,payload);
}

void MqttService::sub(const char* topico){
    pubSubClient.subscribe(topico);
}