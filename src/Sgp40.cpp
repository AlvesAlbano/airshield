#include "Sgp40.h"

// 0x59

Sgp40::Sgp40(TwoWire& wire):wire(wire),sgp40(),covAlgoritmo(0){
}

void Sgp40::init(){
    sgp40.begin(wire);
}

int32_t Sgp40::indiceCOV(float temperatura,float umidade){
    
    uint16_t rawCov;
    uint16_t resultadoCov;

    uint16_t temperatureTicks = temperaturaTicks(temperatura);

    uint16_t humidityTicks = umidadeTicks(umidade);

    uint16_t erro = sgp40.measureRawSignal(humidityTicks,temperatureTicks,rawCov);

    if (erro != 0){
        return 0;
    }

    return covAlgoritmo.process(rawCov);
}

uint16_t Sgp40::temperaturaTicks(float temperatura){
    return (uint16_t) (((temperatura + 45.f) * 65535.f) / 175.f);
}

uint16_t Sgp40::umidadeTicks(float umidade){
    return (uint16_t) ((umidade * 65535.f) / 100.f);
}
