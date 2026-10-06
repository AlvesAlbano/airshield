#include <Arduino.h>
#include <Wire.h>
#include <Ticker.h>

#include "WifiService.h"
#include "AccessPointService.h"
#include "MqttService.h"
#include "FicheiroService.h"
#include "MemoriaFlashService.h"
#include "ColetorTelemetria.h"

#include "Buzzer.h"
#include "LedRgb.h"
#include "Sgp40.h"
#include "Scd41.h"
#include "PmsA003.h"
#include "Oled.h"

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
AccessPointService accessPoint;
FicheiroService ficheiroService;
MemoriaFlashService memoria;

LedRgb ledRgb(GPIO_VERMELHO,GPIO_VERDE,GPIO_AZUL);
Buzzer buzzer(GPIO_BUZZER);
Sgp40 sgp40(Wire);
Scd41 scd41(Wire);
Oled displayOled(Wire);
PmsA003 pmsa003(RX,TX);

ColetorTelemetria coletorTelemetria(sgp40,scd41,pmsa003);

Ticker telemetriaTimer;

bool coletarTelemetria = false;

void timerCallback(){
  coletarTelemetria = true;
}

void initComponentes(){
  // Wire.begin(I2C_SDA,I2C_SCL);

  // buzzer.init();
  // ledRgb.init();
  // scd41.init();
  // sgp40.init();
  // pmsa003.init();
  // displayOled.init();
}

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

    initComponentes();

    telemetriaTimer.attach(7.0,timerCallback);
    mqtt.init();
    mqtt.sub("teste/fds");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (!(memoria.existe("SSID") && memoria.existe("SENHA"))){
    accessPoint.loop();
  }
  
  if (coletarTelemetria && wifi.estaConectado() && mqtt.estaConectado()){
    coletarTelemetria = false;

    // coletorTelemetria.coletarDados();

    Serial.println("ta indo o timer");
  }
  // mqtt.loop();

  // displayOled.texto("teste",0,0);
  // displayOled.atualizar();
}
