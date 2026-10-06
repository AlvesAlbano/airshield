#pragma once

#include "PMserial.h"

class PmsA003{
private:
    SerialPM Pms;
public:
    PmsA003(const int RX,const int TX);

    void init();
    void medir();
    uint16_t pm01();
    uint16_t pm25();
    uint16_t pm10();
};