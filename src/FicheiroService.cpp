#include "FicheiroService.h"

FicheiroService::FicheiroService(){

}

void FicheiroService::init() {

    if (!SPIFFS.begin(true)) {

        Serial.println("ERRO: SPIFFS nao montou");

        return;
    }

    Serial.println("SPIFFS montado!");

    File raiz = SPIFFS.open("/");

    if (!raiz) {

        Serial.println("ERRO ao abrir raiz do SPIFFS");

        return;
    }

    File arquivo = raiz.openNextFile();

    while (arquivo) {

        Serial.print("Arquivo encontrado: ");
        Serial.print(arquivo.name());
        Serial.print(" | tamanho: ");
        Serial.println(arquivo.size());

        arquivo = raiz.openNextFile();
    }
}

String FicheiroService::buscarArquivo(const char* arquivoNome){
    if (!SPIFFS.exists(arquivoNome)){
        Serial.printf("%s não existe\n",arquivoNome);
        return "";
    }

    File arquivo = SPIFFS.open(arquivoNome,"r");

    if (!arquivo){
        Serial.println("deu ruim ao abrir o arquivo");

        return "";
    }

    String arquivoConteudo = arquivo.readString();

    arquivo.close();
    
    return arquivoConteudo;
} 