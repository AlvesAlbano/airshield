#pragma once

#include "ArduinoJson.h"
#include "Telemetria.h"

class TelemetriaJsonBuilder{
private:
    Telemetria telemetria;
    String json = "";
public:

    void setCO2(uint16_t valor);
    void setTemperatura(float valor);
    void setUmidade(float valor);

    void setCOV(int32_t valor);
    
    void setPm01(uint16_t valor);
    void setPm10(uint16_t valor);
    void setPm25(uint16_t valor);
    
    const char* build();
};