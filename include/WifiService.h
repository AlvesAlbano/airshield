#pragma once

#include <WiFi.h>

class WifiService {
private:
public:
    WifiService();
    bool conectar(const char* nomeRede, const char* senhaRede);
    void desconectar();
    bool estaConectado();
    String idMac();
};
