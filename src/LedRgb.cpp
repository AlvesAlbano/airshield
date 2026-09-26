#include "LedRgb.h"

// Anodo <------------------------------------------
LedRgb::LedRgb(unsigned int gpio_vermelho,unsigned int gpio_verde,unsigned int gpio_azul):GPIO_VERMELHO(gpio_vermelho),GPIO_VERDE(gpio_verde),GPIO_AZUL(gpio_azul){

}

void LedRgb::init(){
    pinMode(GPIO_VERMELHO,OUTPUT);
    pinMode(GPIO_VERDE,OUTPUT);
    pinMode(GPIO_AZUL,OUTPUT);
}

void LedRgb::ligar(uint8_t valorVermelho,uint8_t valorVerde,uint8_t valorAzul){
    analogWrite(GPIO_VERMELHO,255 - valorVermelho);
    analogWrite(GPIO_VERDE,255 - valorVerde);
    analogWrite(GPIO_AZUL,255 - valorAzul);
}

void LedRgb::desligar(){
    analogWrite(GPIO_VERMELHO,0);
    analogWrite(GPIO_VERDE,0);
    analogWrite(GPIO_AZUL,0);
}