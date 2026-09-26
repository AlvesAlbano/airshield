#pragma once

#include "SensirionI2CSgp40.h"
#include "SensirionGasIndexAlgorithm.h"
#include <Wire.h>

class Sgp40{

private:
    SensirionI2CSgp40 sgp40;
    SensirionGasIndexAlgorithm covAlgoritmo;
    TwoWire& wire;

    uint16_t temperaturaTicks(float temperatura);
    uint16_t umidadeTicks(float umidade);
public:
    Sgp40(TwoWire& wire);
    void init();
    int32_t indiceCOV(float temperatura,float umidade);
};
