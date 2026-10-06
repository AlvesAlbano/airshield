#include "ColetorTelemetria.h"

ColetorTelemetria::ColetorTelemetria(Sgp40& sgp40,Scd41& scd41,PmsA003& pmsa003):sgp40(sgp40),scd41(scd41),pmsa003(pmsa003){

}

Telemetria ColetorTelemetria::coletarDados(){

    Telemetria telemetria;

    scd41.medir();

    telemetria.CO2 = scd41.co2();
    telemetria.TEMPERATURA = scd41.temperatura();
    telemetria.UMIDADE = scd41.umidade();

    telemetria.INDICE_COV = sgp40.indiceCOV(telemetria.TEMPERATURA,telemetria.UMIDADE);

    Serial.printf("CO2: %u\n",telemetria.CO2);
    Serial.printf("Temperatura: %.1f\n",telemetria.TEMPERATURA);
    Serial.printf("Umidade: %.2f\n",telemetria.UMIDADE);

    Serial.printf("Indice COV: %d\n",telemetria.INDICE_COV); 

    pmsa003.medir();    
    
    telemetria.PM01 = pmsa003.pm01();
    telemetria.PM25 = pmsa003.pm25();
    telemetria.PM10 = pmsa003.pm10();

    Serial.printf("PM 1.0: %u\n",telemetria.PM01);
    Serial.printf("PM 2.5: %u\n",telemetria.PM25);
    Serial.printf("PM 10: %u\n",telemetria.PM10);

    return telemetria;
}