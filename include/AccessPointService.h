#pragma once

#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <ArduinoJson.h>

#include "FicheiroService.h"
#include "MemoriaFlashService.h"

class AccessPointService{
private:
    const char* REDE_AP = "teste";
    const char* SENHA_AP = "12345678";
    const int DNS_PORT = 53;

    WebServer webServer;
    DNSServer dnsServer;
    FicheiroService ficheiroService;
    MemoriaFlashService memoria;

    void carregarPagina();
    void captivePortal();
    
public:
    AccessPointService();
    
    void init();
    void inserirCredenciaisRede();
    void loop();
};