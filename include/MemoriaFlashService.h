#pragma once

#include <Preferences.h>

class MemoriaFlashService{
private:
    Preferences memoria;
    void init(const char* id, bool apenasLeitura);
    void end();
public:

    MemoriaFlashService();
    void salvarString(const char* chave, const char* valor);
    String lerString(const char* chave);
    bool existe(const char* chave);
};
