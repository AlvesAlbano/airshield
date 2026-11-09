#pragma once

#include "ArduinoJson.h"
#include "Telemetria.h"
#include "QualidadeAr.h"
#include "MonitorarQualidadeAmbiente.h"

class TelemetriaJsonBuilder{
private:
    Telemetria telemetria;
    IndicesQualidadeResultado indicesQualidadeResultado;
    MonitorarQualidadeAmbiente monitorarQualidadeAmbiente;

    String json = "";
public:
    void setCO2(uint16_t valor);
    void setTemperatura(float valor);
    void setUmidade(float valor);

    void setCOV(int32_t valor);
    
    void setPm01(uint16_t valor);
    void setPm10(uint16_t valor);
    void setPm25(uint16_t valor);

    void setIndiceUmidade(QualidadeAr valor);
    void setIndiceCov(QualidadeAr valor);
    void setIndiceCo2(QualidadeAr valor);
    void setIndicePm01(QualidadeAr valor);
    void setIndicePm25(QualidadeAr valor);
    void setIndicePm10(QualidadeAr valor);
    void setQualidadeGeralDoAr(IndiceQualidadeAr indiceQualidadeAr);

    const char* build();
};