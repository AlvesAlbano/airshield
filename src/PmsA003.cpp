#include "PmsA003.h"

PmsA003::PmsA003(const int RX,const int TX):Pms(PMSA003,RX,TX){

}

void PmsA003::init(){
    Pms.init();
}

void PmsA003::medir(){
    Pms.read();

    Serial.printf("PM1.0: %d\n",Pms.pm01);
    Serial.printf("PM2.5: %d\n",Pms.pm25);
    Serial.printf("PM10: %d\n",Pms.pm10);
}

uint16_t PmsA003::pm01(){
    return Pms.pm01;
}

uint16_t PmsA003::pm25(){
    return Pms.pm25;
}

uint16_t PmsA003::pm10(){
    return Pms.pm10;
}
