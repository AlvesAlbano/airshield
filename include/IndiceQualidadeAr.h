#pragma once

#include <Arduino.h>
#include "Telemetria.h"
#include "QualidadeAr.h"

struct IndicesQualidadeResultado {
    QualidadeAr QUALIDADE_UMIDADE;
    QualidadeAr QUALIDADE_COV;
    QualidadeAr QUALIDADE_CO2;
    QualidadeAr QUALIDADE_PM01;
    QualidadeAr QUALIDADE_PM25;
    QualidadeAr QUALIDADE_PM10;
};

class IndiceQualidadeAr{
private:
    IndicesQualidadeResultado indicesQualidadeResultado;
public:
    void calcularIndiceUmidade(float UMIDADE);
    void calcularIndiceCov(int32_t INDICE_COV);
    void calcularIndiceCo2(uint16_t CO2);

    void calcularIndicePm01(uint16_t PM01);
    void calcularIndicePm25(uint16_t PM25);
    void calcularIndicePm10(uint16_t PM10);

    IndicesQualidadeResultado getIndicesQualidadeResulado();
};