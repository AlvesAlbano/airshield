#include "AccessPointService.h"

AccessPointService::AccessPointService():webServer(80){

}

void AccessPointService::init(){

    ficheiroService.init();
    WiFi.softAP(REDE_AP,SENHA_AP);

    Serial.println("AP Iniciado");

    Serial.printf("endereço IP: %s\n",WiFi.softAPIP().toString());
    
    dnsServer.start(DNS_PORT,"*",WiFi.softAPIP());
    
    carregarPagina();
    
    webServer.on("/salvar",HTTP_POST,[this](){
        inserirCredenciaisRede();
    });

    captivePortal();

    webServer.begin();
    Serial.println("Servidor HTTP iniciado");
}

void AccessPointService::inserirCredenciaisRede(){
    if (!webServer.hasArg("plain")){
        webServer.send(
            400,
            "application/javascript",
            "deu ruim"
        );

        return;
    }

    String corpo = webServer.arg("plain");

    JsonDocument jsonDocument;

    DeserializationError deserializationError = deserializeJson(jsonDocument,corpo);

    if (deserializationError){
        Serial.println("deu ruim");

        return;
    }

    const char* ssid = jsonDocument["ssid"];
    const char* senha = jsonDocument["senha"];

    if (ssid == nullptr || senha == nullptr){
        webServer.send(
            400,
            "application/json",
            "deu ruim ai"
        );

        return;
    }

    memoria.salvarString("SSID",ssid);
    memoria.salvarString("SENHA",senha);
    
    Serial.println("credencias salvas na memoria flash");
    Serial.printf("ssid: %s \n",ssid);
    Serial.printf("senha: %s \n",senha);

    webServer.send(
        200,
        "application/json",
        "deu bom"
    );

}

void AccessPointService::carregarPagina(){
    webServer.on("/",HTTP_GET,[this](){
        String index = ficheiroService.buscarArquivo("/index.html");

        if (index.length() == 0){

            webServer.send(
                404,
                "text/plain",
                "index.html não encontrado"
            );

            return;
        }

        webServer.send(
            200,
            "text/html",
            index
        );
    });

    webServer.on("/style.css",HTTP_GET,[this](){
        String style = ficheiroService.buscarArquivo("/style.css");

        if (style.length() == 0){

            webServer.send(
                404,
                "text/plain",
                "style.css não encontrado"
            );

            return;
        }

        webServer.send(
            200,
            "text/css",
            style
        );
    });

    webServer.on("/script.js",HTTP_GET,[this](){
        String script = ficheiroService.buscarArquivo("/script.js");

        if (script.length() == 0){

            webServer.send(
                404,
                "text/plain",
                "script.js não encontrado"
            );

            return;
        }

        webServer.send(
            200,
            "application/javascript",
            script
        );
    });
}

void AccessPointService::captivePortal() {

    // Android
    webServer.on(
        "/generate_204",
        HTTP_GET,
        [this]() {

            webServer.sendHeader(
                "Location",
                "/",
                true
            );

            webServer.send(
                302,
                "text/plain",
                ""
            );
        }
    );


    // Apple
    webServer.on(
        "/hotspot-detect.html",
        HTTP_GET,
        [this]() {

            webServer.sendHeader(
                "Location",
                "/",
                true
            );

            webServer.send(
                302,
                "text/plain",
                ""
            );
        }
    );

    // Windows
    webServer.on(
        "/connecttest.txt",
        HTTP_GET,
        [this]() {

            webServer.sendHeader(
                "Location",
                "/",
                true
            );

            webServer.send(
                302,
                "text/plain",
                ""
            );
        }
    );


    webServer.on(
        "/ncsi.txt",
        HTTP_GET,
        [this]() {

            webServer.sendHeader(
                "Location",
                "/",
                true
            );

            webServer.send(
                302,
                "text/plain",
                ""
            );
        }
    );

    // Favicon
    webServer.on(
        "/favicon.ico",
        HTTP_GET,
        [this]() {

            webServer.send(
                204,
                "text/plain",
                ""
            );
        }
    );

    // Qualquer outra URL
    webServer.onNotFound(
        [this]() {

            Serial.println();
            Serial.println("REQUISICAO NAO ENCONTRADA:");
            Serial.print("URI: ");
            Serial.println(webServer.uri());

            webServer.sendHeader(
                "Location",
                "/",
                true
            );

            webServer.send(
                302,
                "text/plain",
                ""
            );
        }
    );
}

void AccessPointService::loop(){
    dnsServer.processNextRequest();
    webServer.handleClient();
}