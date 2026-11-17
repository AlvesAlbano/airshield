#include "AccessPointService.h"

AccessPointService::AccessPointService(){

}

void AccessPointService::initPortalCativo(String enderecoMac) {

    String redeAp = REDE_AP + enderecoMac;

    wifiManager.setConfigPortalBlocking(true);
    wifiManager.setCaptivePortalEnable(true);

    // Inicia o AP e o portal de configuração
    bool sucesso = wifiManager.startConfigPortal(
        redeAp.c_str(),
        SENHA_AP
    );

    if (sucesso) {
        Serial.println("Wi-Fi configurado com sucesso!");

        salvarCredenciaisRede();
    } else {
        Serial.println("Falha ao configurar Wi-Fi!");
    }
}

bool AccessPointService::conectar(String ssid, String senha) {

    WiFi.mode(WIFI_STA);

    // return wifiManager.connectWifi(
    //     ssid.c_str(),
    //     senha.c_str()
    // );

    return wifiManager.autoConnect(
        ssid.c_str(),
        senha.c_str()
    );
}

void AccessPointService::salvarCredenciaisRede(){
    
    memoria.salvarString("SSID",WiFi.SSID().c_str());
    memoria.salvarString("SENHA",WiFi.psk().c_str());
    
    Serial.println("credencias salvas na memoria flash");
    Serial.printf("ssid: %s \n",WiFi.SSID());
    Serial.printf("senha: %s \n",WiFi.psk());
}

bool AccessPointService::estaConectado(){
    return WiFi.status() == WL_CONNECTED;
}

String AccessPointService::getEnderecoMac(){
    return WiFi.macAddress();
}
