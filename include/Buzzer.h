#pragma once

#include <Arduino.h>

class Buzzer{

private:
    unsigned int GPIO;
public:
    volatile bool silenciado = false;

    Buzzer(unsigned int GPIO);

    void init();
    void ligar();
    void desligar();
    void alertar(unsigned int tempoSegundos);
};