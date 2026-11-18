#pragma once

#include <Arduino.h>
#include <WiFi.h>

class WifiService {
private:
public:
    WifiService();

    void init();
    bool conectarWifi(const String& nomeRede);
    bool conectarWifi(const String& nomeRede,const String& senhaRede);
    void manterConexao();
    String getEnderecoMac();
};