#include "MemoriaFlashService.h"


MemoriaFlashService::MemoriaFlashService(){

}

void MemoriaFlashService::init(const char* id, bool apenasLeitura){
    memoria.begin(id,apenasLeitura);
}

void MemoriaFlashService::salvarString(const char* chave, const char* valor){
    init("config",false);
    memoria.putString(chave,valor);
    end();
}

String MemoriaFlashService::lerString(const char* chave){
    init("config",false);
    String valor = memoria.getString(chave,"null");
    end();

    return valor;
}

bool MemoriaFlashService::existe(const char* chave){
    init("config",true);

    bool valorExiste = memoria.isKey(chave);
    end();

    return valorExiste;
}

void MemoriaFlashService::end(){
    memoria.end();
}