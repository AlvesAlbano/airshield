#pragma once

#include <Arduino.h>
#include <ESP32_CPWIFI.h>
#include <WiFi.h>

class WifiService {
private:
    String USUARIO = "";
    String SENHA = "";
    CPWIFI wifi;
public:
    WifiService(/* args */);
    void init();
    bool conectarWifi(const String& nomeRede);
    void manterConexao();
    String getEnderecoMac();
};