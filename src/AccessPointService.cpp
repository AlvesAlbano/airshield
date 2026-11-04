#include "AccessPointService.h"

AccessPointService::AccessPointService(){

}

void AccessPointService::initPortalCativo(String enderecoMac){
    
    String redeAp = REDE_AP + enderecoMac;
    wifiManager.setCaptivePortalEnable(true);
    
    wifiManager.startConfigPortal(
        redeAp.c_str(),
        SENHA_AP
    );
}

bool AccessPointService::conectar(String ssid,String senha){
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
