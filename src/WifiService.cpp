#include "WifiService.h"

WifiService::WifiService(){
}

void WifiService::conectar(const char* nomeRede,const char* senhaRede){
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(nomeRede,senhaRede);
    Serial.println("Conectando a rede");

    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(1000);
    }

    Serial.printf("Conectado! IP:%s\n",WiFi.localIP().toString().c_str());
}

void WifiService::desconectar(){
    WiFi.disconnect();
}