#include "Buzzer.h"

Buzzer::Buzzer(unsigned int GPIO): GPIO(GPIO){

}


void Buzzer::init(){
    pinMode(GPIO,OUTPUT);
}

void Buzzer::ligar(){
    digitalWrite(GPIO,HIGH);
}

void Buzzer::desligar(){
    digitalWrite(GPIO,LOW);
}

void Buzzer::pulsar(unsigned int tempoSegundos){
    ligar();
    delay(tempoSegundos);
    desligar();
    delay(tempoSegundos);
}