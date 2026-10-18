#include <Arduino.h>
#include <Wire.h>
#include <Ticker.h>

#include "WifiService.h"
#include "AccessPointService.h"
#include "MqttService.h"
#include "FicheiroService.h"
#include "MemoriaFlashService.h"
#include "ColetorTelemetria.h"
#include "Telemetria.h"
#include "TelemetriaJsonBuilder.h"

#include "Buzzer.h"
#include "LedRgb.h"
#include "Sgp40.h"
#include "Scd41.h"
#include "PmsA003.h"
#include "Oled.h"

#define GPIO_BUZZER 4
#define GPIO_BOTAO 18
#define GPIO_VERMELHO 13
#define GPIO_VERDE 12
#define GPIO_AZUL 14

#define I2C_SCL 22
#define I2C_SDA 21

#define TX 17
#define RX 16

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

volatile bool coletarTelemetria = false;

volatile bool apertouBotao = false;
volatile uint32_t ultimaIRQ = 0;

void IRAM_ATTR iqrCallback() {
  uint32_t agora = micros();

  if ((uint32_t)(agora - ultimaIRQ) >= 30000) {
    ultimaIRQ = agora;
    apertouBotao = true;
  }
}

void timerCallback(){
  coletarTelemetria = true;
}

void silenciarBuzzer(){
  if (apertouBotao) {
    noInterrupts();
    apertouBotao = false;
    interrupts();

    buzzer.silenciado = !buzzer.silenciado;
    Serial.println(buzzer.silenciado);
    Serial.println("Botao pressionado");
  }
}

void telemetria_display(Telemetria telemetria) {

  static unsigned long tempoAnterior = 0;
  static int pagina = 0;

  const unsigned long intervalo = 3000;

  if (millis() - tempoAnterior >= intervalo) {
    tempoAnterior = millis();
    pagina = (pagina + 1) % 3;
  }

  displayOled.limpar();

  switch (pagina) {

    case 0:
      displayOled.texto(
        ("Temperatura: " + String(telemetria.TEMPERATURA, 1) + " C").c_str(),
          0, 0
        );

      displayOled.texto(
        ("Umidade: " + String(telemetria.UMIDADE, 1) + " %").c_str(),
        0, 20
      );

      displayOled.texto(
        ("Indice COV: " + String(telemetria.INDICE_COV)).c_str(),
        0, 40
      );
      break;

    case 1:
      displayOled.texto(
        ("PM0.1: " + String(telemetria.PM01)).c_str(),
        0, 0
      );
      
      displayOled.texto(
        ("PM2.5: " + String(telemetria.PM25)).c_str(),
        0, 20
      );

      displayOled.texto(
        ("PM10: " + String(telemetria.PM10)).c_str(),
        0, 40
      );
      break;
      
    case 2:
      displayOled.texto(
        ("CO2: " + String(telemetria.CO2) + " ppm").c_str(),
        0, 0
      );
      break;
  }

  displayOled.atualizar();
}

void initComponentes(){
  Wire.begin(I2C_SDA,I2C_SCL);
  pinMode(GPIO_BOTAO,INPUT_PULLUP);

  attachInterrupt(
    digitalPinToInterrupt(GPIO_BOTAO),
    iqrCallback,
    FALLING
  );

  buzzer.init();
  ledRgb.init();
  scd41.init();
  sgp40.init();
  pmsa003.init();
  displayOled.init();
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

    telemetriaTimer.attach(1.0,timerCallback);
    mqtt.init();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (!wifi.estaConectado()){
    accessPoint.init();
  }
  
  if (apertouBotao){
    silenciarBuzzer();
  }

  if (coletarTelemetria && wifi.estaConectado() && mqtt.estaConectado()){
    coletarTelemetria = false;
    Serial.println("foi");
    
    Telemetria telemetria = coletorTelemetria.coletarDados();
    TelemetriaJsonBuilder telemetriaJsonBuilder;

    telemetriaJsonBuilder.setCO2(telemetria.CO2);
    telemetriaJsonBuilder.setTemperatura(telemetria.TEMPERATURA);
    telemetriaJsonBuilder.setUmidade(telemetria.UMIDADE);
    
    telemetriaJsonBuilder.setCOV(telemetria.INDICE_COV);

    telemetriaJsonBuilder.setPm01(telemetria.PM01);
    telemetriaJsonBuilder.setPm10(telemetria.PM10);
    telemetriaJsonBuilder.setPm25(telemetria.PM25);

    const char* json = telemetriaJsonBuilder.build();
    
    telemetria_display(telemetria);

    Serial.println(json);
    Serial.println(wifi.idMac());

    String topico = "airshield/" + wifi.idMac() + "/dados-ambiente";
    Serial.println(topico);
    mqtt.pub(topico.c_str(),json);
    Serial.println("acabou");
  }

  mqtt.loop();
}