#pragma once

#include <Arduino.h>
// #include <cstdint>

class LedRgb{

private:
    const unsigned int GPIO_VERMELHO;
    const unsigned int GPIO_VERDE;
    const unsigned int GPIO_AZUL;

public:
    LedRgb(unsigned int gpio_vermelho,unsigned int gpio_verde,unsigned int gpio_azul);

    void init();
    void ligar(uint8_t valorVermelho,uint8_t valorVerde,uint8_t valorAzul);
    void desligar();
};