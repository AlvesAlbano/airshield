#include "Buzzer.h"

Buzzer::Buzzer(unsigned int GPIO): GPIO(GPIO){

}

void Buzzer::init(){
    pinMode(GPIO,OUTPUT);
}

void Buzzer::ligar(){
    if(silenciado){
        digitalWrite(GPIO,LOW);
    } else {
        desligar();
    }
}

void Buzzer::desligar(){
    digitalWrite(GPIO,LOW);
}

void Buzzer::alertar(unsigned int tempoSegundos){

    if (silenciado) {
        desligar();
        return;
    }

    if (!silenciado){
        ligar();
        delay(tempoSegundos);
        desligar();
        delay(tempoSegundos);
    }
}