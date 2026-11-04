#include "WifiService.h"

WifiService::WifiService(){
}

bool WifiService::conectar(const char* nomeRede, const char* senhaRede){

    WiFi.mode(WIFI_STA);
    // WiFi.mode(WIFI_AP_STA);

    WiFi.begin(nomeRede, senhaRede);

    Serial.println("Conectando a rede...");

    unsigned long inicio = millis();

    while (WiFi.status() != WL_CONNECTED){

        if (millis() - inicio >= 15000){
            Serial.println("\nFalha ao conectar!");

            WiFi.disconnect();

            return false;
        }

        Serial.print(".");
        delay(500);
    }

    Serial.printf(
        "\nConectado! IP: %s\n",
        WiFi.localIP().toString().c_str()
    );

    return true;
}

void WifiService::desconectar(){
    WiFi.disconnect();
}

bool WifiService::estaConectado(){
    return WiFi.isConnected();
}

String WifiService::idMac(){
    
    String enderecoMac = WiFi.macAddress();
    // enderecoMac.replace(":","");
    return enderecoMac;
}