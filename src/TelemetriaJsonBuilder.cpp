#include "TelemetriaJsonBuilder.h"

void TelemetriaJsonBuilder::setCO2(uint16_t valor){
    telemetria.CO2 = valor;
}

void TelemetriaJsonBuilder::setCOV(int32_t valor){
    telemetria.INDICE_COV = valor;
}

void TelemetriaJsonBuilder::setTemperatura(float valor){
    telemetria.TEMPERATURA = valor;
}

void TelemetriaJsonBuilder::setUmidade(float valor){
    telemetria.UMIDADE = valor;
}

void TelemetriaJsonBuilder::setPm01(uint16_t valor){
    telemetria.PM01 = valor;
}

void TelemetriaJsonBuilder::setPm10(uint16_t valor){
    telemetria.PM10 = valor;
}

void TelemetriaJsonBuilder::setPm25(uint16_t valor){
    telemetria.PM25 = valor;
}

const char* TelemetriaJsonBuilder::build(){
    JsonDocument jsonDocument;

    jsonDocument["co2"] = telemetria.CO2;
    jsonDocument["temperatura"] = telemetria.TEMPERATURA;
    jsonDocument["umidade"] = telemetria.UMIDADE;
    jsonDocument["indice_cov"] = telemetria.INDICE_COV;
    jsonDocument["pm 0.1"] = telemetria.PM01;
    jsonDocument["pm 1.0"] = telemetria.PM10;
    jsonDocument["pm 2.5"] = telemetria.PM25;

    serializeJson(jsonDocument,json);

    return json.c_str();
}