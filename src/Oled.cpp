#include "Oled.h"

Oled::Oled(TwoWire& wire): wire(wire),display(LARGURA_TELA,ALTURA_TELA,&wire,OLED_RESET){

}

void Oled::init() {
    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
    limpar();
    atualizar();
}

void Oled::texto(const char* texto, int x, int y, int tamanho){
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(x,y);
    display.setTextSize(tamanho);
    display.print(texto);
}

void Oled::limpar(){
    display.clearDisplay();
}

void Oled::atualizar(){
    display.display();
}