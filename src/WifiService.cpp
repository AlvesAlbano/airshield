#include "WifiService.h"

WifiService::WifiService(){

}

void WifiService::init(){

// const uint8_t customMAC[6] = {
//     0x02, 0xAB, 0xCD, 0x11, 0x22, 0x33
// };

// memcpy(mac, customMAC, sizeof(customMAC));
    wifi.setMAC(CPWIFI::MAC_REAL);
}

bool WifiService::conectarWifi(const String& nomeRede){
    return wifi.begin(
        nomeRede.c_str(),
        USUARIO.c_str(),
        SENHA.c_str()
    );
}

void WifiService::manterConexao(){
    wifi.maintain();
}

String WifiService::getEnderecoMac(){
    return WiFi.macAddress();
}