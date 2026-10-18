#pragma once

#include "Sgp40.h"
#include "Scd41.h"
#include "PmsA003.h"
#include "Telemetria.h"

class ColetorTelemetria{
private:
    Sgp40& sgp40;
    Scd41& scd41;
    PmsA003& pmsa003;
public:
    ColetorTelemetria(Sgp40& sgp40,Scd41& scd41,PmsA003& pmsa003);
    Telemetria coletarDados();
};