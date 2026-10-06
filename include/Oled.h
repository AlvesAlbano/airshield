#pragma once

#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

class Oled{
private:
    const int LARGURA_TELA = 128;
    const int ALTURA_TELA = 64;
    const int OLED_RESET = -1;
    const int OLED_ADDR = 0x3C;

    TwoWire& wire;
    Adafruit_SSD1306 display;
public:
    Oled(TwoWire& wire);
    void init();
    void texto(const char* texto, int x, int y, int tamanho = 1);
    void atualizar();
    void limpar();
};