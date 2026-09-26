#pragma once

#include "SPIFFS.h"

class FicheiroService{
public:
    FicheiroService();
    void init();
    String buscarArquivo(const char* arquivo);
};