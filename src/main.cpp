#include <Arduino.h>

#include "WifiService.h"
#include "AccessPointService.h"
#include "MqttService.h"
#include "FicheiroService.h"
#include "Buzzer.h"
#include "LedRgb.h"
#include "MemoriaFlashService.h"

#define GPIO_BUZZER 4
#define GPIO_VERMELHO 13
#define GPIO_VERDE 12
#define GPIO_AZUL 14

#define I2C_SCL 22
#define I2C_SDA 21

#define TX 1
#define RX 3

WifiService wifi;
MqttService mqtt;
Buzzer buzzer(GPIO_BUZZER);
LedRgb ledRgb(GPIO_VERMELHO,GPIO_VERDE,GPIO_AZUL);
AccessPointService accessPoint;
FicheiroService ficheiroService;
MemoriaFlashService memoria;

void setup() {
  Serial.begin(115200);

  if (!(memoria.existe("SSID") || memoria.existe("SENHA"))){
    accessPoint.init();
  } else {

    Serial.println("tá indo");
    delay(1000);

    wifi.conectar(
      memoria.lerString("SSID").c_str(),
      memoria.lerString("SENHA").c_str()
    );

    mqtt.init();
    mqtt.sub("teste/fds");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (!(memoria.existe("SSID") || memoria.existe("SENHA"))){
    accessPoint.loop();
  }
  
  // mqtt.loop();

}

void initComponentes(){
  buzzer.init();
  ledRgb.init();
}