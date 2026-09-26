#pragma once

#include <WiFi.h>

class WifiService {
    private:
    public:
        WifiService();

        void conectar(const char* nomeRede, const char* senhaRede);
        void desconectar();
};
