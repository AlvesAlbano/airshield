#include "AccessPointService.h"

AccessPointService::AccessPointService():webServer(80){

}

void AccessPointService::init(String idMac){

    ficheiroService.init();

    WiFi.mode(WIFI_AP);
    // WiFi.mode(WIFI_AP_STA);

    String redeAp = REDE_AP + idMac;
    Serial.println(redeAp);
    Serial.println(redeAp.length());

    bool iniciado = WiFi.softAP(redeAp, SENHA_AP);

    if (!iniciado) {
        Serial.println("Erro ao iniciar Access Point");
        return;
    }

    Serial.println("AP iniciado!");

    Serial.printf(
        "Endereco IP: %s\n",
        WiFi.softAPIP().toString().c_str()
    );

    dnsServer.start(
        DNS_PORT,
        "*",
        WiFi.softAPIP()
    );

    carregarPagina();

    webServer.on("/salvar", HTTP_POST, [this](){
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
        Serial.println("deu ruim iniciar AP");

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

    Serial.println("Reiniciando....");
    delay(3000);
    ESP.restart();
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

    auto redirectToRoot = [this]() {

        Serial.printf(
            "[CAPTIVE] Requisicao: %s\n",
            webServer.uri().c_str()
        );

        webServer.sendHeader(
            "Location",
            "http://192.168.4.1/",
            true
        );

        webServer.sendHeader(
            "Cache-Control",
            "no-cache, no-store, must-revalidate"
        );

        webServer.send(
            302,
            "text/plain",
            ""
        );
    };

    // Android
    webServer.on("/generate_204", HTTP_GET, redirectToRoot);
    webServer.on("/gen_204", HTTP_GET, redirectToRoot);

    // Apple
    webServer.on("/hotspot-detect.html", HTTP_GET, redirectToRoot);
    webServer.on("/library/test/success.html", HTTP_GET, redirectToRoot);

    // Windows
    webServer.on("/connecttest.txt", HTTP_GET, redirectToRoot);
    webServer.on("/ncsi.txt", HTTP_GET, redirectToRoot);

    // Favicon
    webServer.on(
        "/favicon.ico",
        HTTP_GET,
        [this]() {
            webServer.send(204, "text/plain", "");
        }
    );

    // Qualquer outra URL
    webServer.onNotFound([this]() {

        Serial.println("\n========== CAPTIVE PORTAL ==========");

        Serial.printf(
            "URI: %s\n",
            webServer.uri().c_str()
        );

        Serial.printf(
            "IP: %s\n",
            webServer.client().remoteIP().toString().c_str()
        );

        Serial.println("====================================");

        // Evita responder HTML para requisicoes POST desconhecidas
        if (webServer.method() != HTTP_GET) {

            webServer.send(
                404,
                "text/plain",
                "Not Found"
            );

            return;
        }

        String index = ficheiroService.buscarArquivo("/index.html");

        if (index.isEmpty()) {

            webServer.send(
                404,
                "text/plain",
                "index.html nao encontrado"
            );

            return;
        }

        webServer.sendHeader(
            "Cache-Control",
            "no-cache, no-store, must-revalidate"
        );

        webServer.send(
            200,
            "text/html; charset=utf-8",
            index
        );
    });
}

void AccessPointService::loop(){
    dnsServer.processNextRequest();
    webServer.handleClient();
    delay(2);
}