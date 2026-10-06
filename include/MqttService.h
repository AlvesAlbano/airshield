#pragma once

#include <PubSubClient.h>
#include <WiFiClient.h>
#include <WiFi.h>

class MqttService {
private:
    WiFiClient wifiClient; 
    PubSubClient pubSubClient;

    const char* MQTT_SERVER = "broker.emqx.io";
    const int MQTT_PORT = 1883;
        
public:
    MqttService();

    void init();
    void conectar();
    void reconectar();
    void loop();
    void pub(const char* topico,const char* payload);
    void sub(const char* topico);

    bool estaConectado();
};