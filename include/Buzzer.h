#pragma once

#include <Arduino.h>

class Buzzer{

private:
    unsigned int GPIO;
public:
    Buzzer(unsigned int GPIO);

    void init();
    void ligar();
    void desligar();
    void pulsar(unsigned int tempoSegundos);
};