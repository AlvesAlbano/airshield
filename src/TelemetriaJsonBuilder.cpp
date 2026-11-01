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

void TelemetriaJsonBuilder::setIndiceUmidade(QualidadeAr valor){
    indicesQualidadeResultado.QUALIDADE_UMIDADE = valor;
}

void TelemetriaJsonBuilder::setIndiceCov(QualidadeAr valor){
    indicesQualidadeResultado.QUALIDADE_COV = valor;
}

void TelemetriaJsonBuilder::setIndiceCo2(QualidadeAr valor){
    indicesQualidadeResultado.QUALIDADE_CO2 = valor;
}

void TelemetriaJsonBuilder::setIndicePm01(QualidadeAr valor){
    indicesQualidadeResultado.QUALIDADE_PM01 = valor;
}

void TelemetriaJsonBuilder::setIndicePm25(QualidadeAr valor){
    indicesQualidadeResultado.QUALIDADE_PM25 = valor;
}

void TelemetriaJsonBuilder::setIndicePm10(QualidadeAr valor){
    indicesQualidadeResultado.QUALIDADE_PM10 = valor;
}


const char* TelemetriaJsonBuilder::build(){
    JsonDocument jsonDocument;

    JsonObject medidas = jsonDocument["medidas"].to<JsonObject>();

    medidas["co2"] = telemetria.CO2;
    medidas["temperatura"] = telemetria.TEMPERATURA;
    medidas["umidade"] = telemetria.UMIDADE;
    medidas["indice_cov"] = telemetria.INDICE_COV;
    medidas["pm 0.1"] = telemetria.PM01;
    medidas["pm 10"] = telemetria.PM10;
    medidas["pm 2.5"] = telemetria.PM25;

    JsonObject indicesQualidade = jsonDocument["indices_qualidade"].to<JsonObject>();

    indicesQualidade["qualidade_umidade"] = indicesQualidadeResultado.QUALIDADE_UMIDADE; 
    indicesQualidade["qualidade_cov"] = indicesQualidadeResultado.QUALIDADE_COV; 
    indicesQualidade["qualidade_co2"] = indicesQualidadeResultado.QUALIDADE_CO2; 
    indicesQualidade["qualidade_pm01"] = indicesQualidadeResultado.QUALIDADE_PM01; 
    indicesQualidade["qualidade_pm25"] = indicesQualidadeResultado.QUALIDADE_PM25; 
    indicesQualidade["qualidade_pm10"] = indicesQualidadeResultado.QUALIDADE_PM10; 

    serializeJson(jsonDocument,json);

    return json.c_str();
}