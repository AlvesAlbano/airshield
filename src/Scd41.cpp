#include "Scd41.h"

Scd41::Scd41(TwoWire& wire):wire(wire){

}

void Scd41::init(){

    scd41.begin(wire,SCD41_I2C_ADDR_62);
    scd41.wakeUp();

    uint16_t erro = scd41.startPeriodicMeasurement();

    if (erro != 0){
        Serial.println("deu ruim iniciar o sensor scd41");
        return;
    }
}

void Scd41::medir(){

    bool dataReady = false;
    uint16_t erro = scd41.getDataReadyStatus(dataReady);

    if (erro != 0){
        Serial.println("deu ruim ao verificar dados do sensor scd41");
        return;
    }

    if (dataReady){

        erro = scd41.readMeasurement(parametros.CO2,parametros.TEMPERATURA,parametros.UMIDADE);

        if (erro == 0){
            Serial.printf("co2: %d\n",parametros.CO2);
            Serial.printf("temperatura: %.2f\n",parametros.TEMPERATURA);
            Serial.printf("umidade: %.2f\n",parametros.UMIDADE);
        }
    }
}

uint32_t Scd41::co2(){
    return parametros.CO2;
}

float Scd41::temperatura(){
    return parametros.TEMPERATURA;
}

float Scd41::umidade(){
    return parametros.UMIDADE;
}