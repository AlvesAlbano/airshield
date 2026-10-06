#pragma once

#include "Sgp40.h"
#include "Scd41.h"
#include "PmsA003.h"

typedef struct {
    uint16_t CO2;
    float TEMPERATURA;
    float UMIDADE;

    int32_t INDICE_COV;

    uint16_t PM01;
    uint16_t PM25;
    uint16_t PM10;
} Telemetria;

class ColetorTelemetria{
private:
    Sgp40& sgp40;
    Scd41& scd41;
    PmsA003& pmsa003;
    // Telemetria telemetria;
public:
    ColetorTelemetria(Sgp40& sgp40,Scd41& scd41,PmsA003& pmsa003);
    Telemetria coletarDados();
};