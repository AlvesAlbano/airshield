#pragma once

#include <Wire.h>

#include "SensirionI2cScd4x.h"

struct Parametros{
    uint16_t CO2;
    float TEMPERATURA;
    float UMIDADE;
};

class Scd41{
private:
    SensirionI2cScd4x scd41;
    Parametros parametros;
    TwoWire& wire;
    
public:
    Scd41(TwoWire& wire);
    void init();
    void medir();

    uint32_t co2();
    float temperatura();
    float umidade();
};