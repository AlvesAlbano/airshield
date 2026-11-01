#include "IndiceQualidadeAr.h"

void IndiceQualidadeAr::calcularIndiceUmidade(float UMIDADE){
    
    // https://www.terra.com.br/noticias/climatempo/como-a-variacao-da-umidade-no-ar-interfere-na-nossa-saude,0d6b5d0e67cb262a83ea099d4cc40720qfouszs2.html

    if (UMIDADE < 30){
        indicesQualidadeResultado.QUALIDADE_UMIDADE = MUITO_RUIM;
    } else if (UMIDADE < 35){
        indicesQualidadeResultado.QUALIDADE_UMIDADE = RUIM;
    } else if (UMIDADE <= 65) {
        indicesQualidadeResultado.QUALIDADE_UMIDADE = BOA;
    } else if (UMIDADE <= 70) {
        indicesQualidadeResultado.QUALIDADE_UMIDADE = MODERADA;
    } else if (UMIDADE <= 80) {
        indicesQualidadeResultado.QUALIDADE_UMIDADE = RUIM;
    } else {
        indicesQualidadeResultado.QUALIDADE_UMIDADE = MUITO_RUIM;
    }
}

void IndiceQualidadeAr::calcularIndiceCo2(uint16_t CO2) {
    // https://www.co2meter.com/blogs/news/carbon-dioxide-indoor-levels-chart

    if (CO2 <= 1000) {
        indicesQualidadeResultado.QUALIDADE_CO2 = BOA;
    } else if (CO2 <= 2000) {
        indicesQualidadeResultado.QUALIDADE_CO2 = MODERADA;
    } else if (CO2 <= 5000) {
        indicesQualidadeResultado.QUALIDADE_CO2 = RUIM;
    } else {
        indicesQualidadeResultado.QUALIDADE_CO2 = PESSIMA;
    }
}

void IndiceQualidadeAr::calcularIndiceCov(int32_t INDICE_COV) {
    // https://sensirion.com/media/documents/ACD82D45/6294DFC0/Info_Note_Integration_VOC_NOx_Sensor.pdf

    // https://sensirion.com/media/documents/0D0C9129/623B1183/Sensirion_CO2_Sensors_SCD4x_design-in_guide.pdf
    if (INDICE_COV <= 150) {
        indicesQualidadeResultado.QUALIDADE_COV = BOA;
    } else if (INDICE_COV <= 250) {
        indicesQualidadeResultado.QUALIDADE_COV = MODERADA;
    } else if (INDICE_COV <= 400) {
        indicesQualidadeResultado.QUALIDADE_COV = RUIM;
    } else {
        indicesQualidadeResultado.QUALIDADE_COV = MUITO_RUIM;
    }
}

void IndiceQualidadeAr::calcularIndicePm01(uint16_t PM01) {

    // https://breathe-tech.com/blogs/knowledge-hub/understanding-pm1

    if (PM01 <= 5) {
        indicesQualidadeResultado.QUALIDADE_PM01 = BOA;
    } else if (PM01 <= 15) {
        indicesQualidadeResultado.QUALIDADE_PM01 = MODERADA;
    } else if (PM01 <= 35){
        indicesQualidadeResultado.QUALIDADE_PM01 = RUIM;
    } else {
        indicesQualidadeResultado.QUALIDADE_PM01 = MUITO_RUIM;
    }
}

void IndiceQualidadeAr::calcularIndicePm25(uint16_t PM25) {
    // https://www.gov.br/mma/pt-br/assuntos/meio-ambiente-urbano-recursos-hidricos-qualidade-ambiental/qualidade-do-ar/indice-de-qualidade-do-ar-iqar

    if (PM25 <= 15) {
        indicesQualidadeResultado.QUALIDADE_PM25 = BOA;
    } else if (PM25 <= 50) {
        indicesQualidadeResultado.QUALIDADE_PM25 = MODERADA;
    } else if (PM25 <= 75){
        indicesQualidadeResultado.QUALIDADE_PM25 = RUIM;
    } else if (PM25 <= 125){
        indicesQualidadeResultado.QUALIDADE_PM25 = MUITO_RUIM;
    } else {
        indicesQualidadeResultado.QUALIDADE_PM25 = PESSIMA;
    }
}

void IndiceQualidadeAr::calcularIndicePm10(uint16_t PM10) {
    
    // https://www.gov.br/mma/pt-br/assuntos/meio-ambiente-urbano-recursos-hidricos-qualidade-ambiental/qualidade-do-ar/indice-de-qualidade-do-ar-iqar

    if (PM10 <= 45) {
        indicesQualidadeResultado.QUALIDADE_PM10 = BOA;
    } else if (PM10 <= 100) {
        indicesQualidadeResultado.QUALIDADE_PM10 = MODERADA;
    } else if (PM10 <= 150){
        indicesQualidadeResultado.QUALIDADE_PM10 = RUIM;
    } else if (PM10 <= 250){
        indicesQualidadeResultado.QUALIDADE_PM10 = MUITO_RUIM;
    } else {
        indicesQualidadeResultado.QUALIDADE_PM10 = PESSIMA;
    }
}

IndicesQualidadeResultado IndiceQualidadeAr::getIndicesQualidadeResulado(){
    return indicesQualidadeResultado;
}