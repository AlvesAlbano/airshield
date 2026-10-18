#pragma once

struct Telemetria {
    uint16_t CO2;
    float TEMPERATURA;
    float UMIDADE;

    int32_t INDICE_COV;

    uint16_t PM01;
    uint16_t PM25;
    uint16_t PM10;
};