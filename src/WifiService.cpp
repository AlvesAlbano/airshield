#include "WifiService.h"

WifiService::WifiService() {}

void WifiService::init() {
    WiFi.mode(WIFI_STA);
}

bool WifiService::conectarWifi(const String& nomeRede) {

    Serial.println("Conectando ao Wi-Fi: " + nomeRede);

    WiFi.disconnect(true);
    delay(1000);

    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false);

    WiFi.begin(nomeRede.c_str());

    unsigned long inicio = millis();

    while (millis() - inicio < 30000) {

        wl_status_t status = WiFi.status();

        Serial.print("Status Wi-Fi: ");
        Serial.println(status);

        if (status == WL_CONNECTED) {

            Serial.println("Conectado!");
            Serial.println(WiFi.localIP());
            Serial.println(WiFi.gatewayIP());

            return true;
        }

        delay(1000);
    }

    Serial.println("Falha ao conectar.");
    Serial.print("Status final: ");
    Serial.println(WiFi.status());

    return false;
}

bool WifiService::conectarWifi(const String& nomeRede,const String& senahRede) {

    Serial.println("Conectando ao Wi-Fi: " + nomeRede);

    WiFi.disconnect(true);
    delay(1000);

    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false);

    WiFi.begin(nomeRede.c_str(),senahRede.c_str());

    unsigned long inicio = millis();

    while (millis() - inicio < 30000) {

        wl_status_t status = WiFi.status();

        Serial.print("Status Wi-Fi: ");
        Serial.println(status);

        if (status == WL_CONNECTED) {

            Serial.println("Conectado!");
            Serial.println(WiFi.localIP());
            Serial.println(WiFi.gatewayIP());

            return true;
        }

        delay(1000);
    }

    Serial.println("Falha ao conectar.");
    Serial.print("Status final: ");
    Serial.println(WiFi.status());

    return false;
}

void WifiService::manterConexao() {

    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Wi-Fi desconectado. Reconectando...");

        WiFi.reconnect();
    }
}

String WifiService::getEnderecoMac() {
    return WiFi.macAddress();
}