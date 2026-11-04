#pragma once

#include <WiFiManager.h>

#include "MemoriaFlashService.h"

class AccessPointService{
private:
    const char* REDE_AP = "airshield_";
    const char* SENHA_AP = "12345678";

    WiFiManager wifiManager;
    MemoriaFlashService memoria;

public:
    AccessPointService();
    
    bool conectar(String ssid,String senha);
    void initPortalCativo(String enderecoMac);
    void salvarCredenciaisRede();
    void loop();
    bool estaConectado();

    String getEnderecoMac();
};