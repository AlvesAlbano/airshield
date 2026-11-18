#include <Arduino.h>
#include <Wire.h>

#include "MqttService.h"
#include "ColetorTelemetria.h"
#include "Telemetria.h"
#include "TelemetriaJsonBuilder.h"
#include "IndiceQualidadeAr.h"
#include "MonitorarQualidadeAmbiente.h"
#include "BluetoothService.h"
#include "WifiService.h"

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

MqttService mqtt;
WifiService wifiService;
#define ENDERECO_MAC wifiService.getEnderecoMac()
BluetoothService bluetooth;

LedRgb ledRgb(GPIO_VERMELHO,GPIO_VERDE,GPIO_AZUL);
Buzzer buzzer(GPIO_BUZZER);
Sgp40 sgp40(Wire);
Scd41 scd41(Wire);
Oled displayOled(Wire);
PmsA003 pmsa003(RX,TX);

ColetorTelemetria coletorTelemetria(sgp40,scd41,pmsa003);
IndiceQualidadeAr indiceQualidadeAr;
MonitorarQualidadeAmbiente monitoradorQualidadeAr;

String nomeDispositivo;

volatile bool apertouBotao = false;
bool qualidadeArBoa = true;
bool ApAtivo = false;
bool conectado = false;

QualidadeAr qualidadeArAnterior;
volatile uint32_t ultimaIRQ = 0;

void IRAM_ATTR iqrCallback() {
  uint32_t agora = micros();

  if ((uint32_t)(agora - ultimaIRQ) >= 30000) {
    ultimaIRQ = agora;
    apertouBotao = true;
  }
}

void silenciarBuzzer(){
  if (apertouBotao) {
    noInterrupts();
    apertouBotao = false;
    interrupts();

    buzzer.silenciado = !buzzer.silenciado;
    Serial.println("Botao pressionado");
  }
}

bool timerEnviarTelemetria(){
  static unsigned long tempoAnterior = 0;
  const unsigned long INTERVALO_TELEMETRIA = 1000;

  if ((millis() - tempoAnterior) >= INTERVALO_TELEMETRIA){
    tempoAnterior = millis();

    return true;
  }

  return false;
}

const char* transcreverQualidadeAr(QualidadeAr qualidadeAr){
  switch (qualidadeAr) {
    case BOA:
      return "BOA";
    case MODERADA:
      return "MODERADA";
    case RUIM:
      return "RUIM";
    case MUITO_RUIM:
      return "MUITO RUIM";
    case PESSIMA:
      return "PÉSSIMA";
    default:
      return "N/A";
  }
}

void qualidadeArDisplay(IndicesQualidadeResultado indicesQualidadeResultado){
  static unsigned long tempoAnterior = 0;
  static int pagina = 0;

  const unsigned long INTERVALO_PAGINACAO_DISPLAY = 3000;
  const int TOTAL_PAGINAS_DISPLAY = 2;

  if (millis() - tempoAnterior >= INTERVALO_PAGINACAO_DISPLAY) {
    tempoAnterior = millis();
    pagina = (pagina + 1) % TOTAL_PAGINAS_DISPLAY;
  }

  displayOled.limpar();

  switch (pagina) {

    case 0:
      
      displayOled.texto(
        ("QUALIDADE COV: " + String(transcreverQualidadeAr(indicesQualidadeResultado.QUALIDADE_COV)) + " ppm").c_str(),
        0, 0
      );
    
      displayOled.texto(
        ("QUALIDADE CO2: " + String(transcreverQualidadeAr(indicesQualidadeResultado.QUALIDADE_CO2)) + " ppm").c_str(),
        0, 20
      );

      displayOled.texto(
        ("QUALIDADE UMIDADE: " + String(transcreverQualidadeAr(indicesQualidadeResultado.QUALIDADE_UMIDADE)) + " ppm").c_str(),
        0, 40
      );

      break;

    case 1:
      
      displayOled.texto(
        ("QUALIDADE PM10: " + String(transcreverQualidadeAr(indicesQualidadeResultado.QUALIDADE_PM10)) + " ppm").c_str(),
        0, 0
      );  
    
      displayOled.texto(
        ("QUALIDADE PM2.5: " + String(transcreverQualidadeAr(indicesQualidadeResultado.QUALIDADE_PM25)) + " ppm").c_str(),
        0, 20
      );

      displayOled.texto(
        ("QUALIDADE PM1.0: " + String(transcreverQualidadeAr(indicesQualidadeResultado.QUALIDADE_PM01)) + " ppm").c_str(),
        0, 40
      );
      break;
  }

  displayOled.atualizar();
}

void telemetriaDisplay(Telemetria telemetria,IndicesQualidadeResultado indicesQualidadeResultado) {

  static unsigned long tempoAnterior = 0;
  static int pagina = 0;

  const unsigned long INTERVALO_PAGINACAO_DISPLAY = 3000;
  const int TOTAL_PAGINAS_DISPLAY = 5;

  if (millis() - tempoAnterior >= INTERVALO_PAGINACAO_DISPLAY) {
    tempoAnterior = millis();
    pagina = (pagina + 1) % TOTAL_PAGINAS_DISPLAY;
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

    case 3:
      
      displayOled.texto(
        ("QUALIDADE COV: " + String(transcreverQualidadeAr(indicesQualidadeResultado.QUALIDADE_COV)) + " ppm").c_str(),
        0, 0
      );
    
      displayOled.texto(
        ("QUALIDADE CO2: " + String(transcreverQualidadeAr(indicesQualidadeResultado.QUALIDADE_CO2)) + " ppm").c_str(),
        0, 20
      );

      displayOled.texto(
        ("QUALIDADE UMIDADE: " + String(transcreverQualidadeAr(indicesQualidadeResultado.QUALIDADE_UMIDADE)) + " ppm").c_str(),
        0, 40
      );

      break;

    case 4:
      
      displayOled.texto(
        ("QUALIDADE PM10: " + String(transcreverQualidadeAr(indicesQualidadeResultado.QUALIDADE_PM10)) + " ppm").c_str(),
        0, 0
      );  
    
      displayOled.texto(
        ("QUALIDADE PM2.5: " + String(transcreverQualidadeAr(indicesQualidadeResultado.QUALIDADE_PM25)) + " ppm").c_str(),
        0, 20
      );

      displayOled.texto(
        ("QUALIDADE PM1.0: " + String(transcreverQualidadeAr(indicesQualidadeResultado.QUALIDADE_PM01)) + " ppm").c_str(),
        0, 40
      );
      break;
  }

  displayOled.atualizar();
}

void informacoesAmbienteDisplay(Telemetria telemetria,IndicesQualidadeResultado indicesQualidadeResultado){
  if (qualidadeArBoa){
    telemetriaDisplay(telemetria,indicesQualidadeResultado);
  } else {
    qualidadeArDisplay(indicesQualidadeResultado);
  }
}

void monitorarQualidadeAr(IndicesQualidadeResultado indicesQualidadeResultado){

  QualidadeAr qualidadeArAtual = monitoradorQualidadeAr.obterQualidadeGeral(indicesQualidadeResultado);

  // Serial.println(qualidadeArAtual);
  qualidadeArBoa = (qualidadeArAtual == BOA);

  if (qualidadeArAtual != qualidadeArAnterior){
    Serial.println("apitou ai");
    buzzer.alertar(3);
  }

  qualidadeArAnterior = qualidadeArAtual;

  switch (qualidadeArAtual) {
    case BOA:
      ledRgb.ligar(78, 166, 44);
      break;
    case MODERADA:
      ledRgb.ligar(247, 212, 0);
      break;
    case RUIM:
      ledRgb.ligar(236, 137, 36);
      break;
    case MUITO_RUIM:
      ledRgb.ligar(203, 9, 18);
      break;
    case PESSIMA:
      ledRgb.ligar(149, 0, 96);
      break;
    default:
      ledRgb.ligar(255,255,255);
  }
}

void enviarTelemetria(Telemetria telemetria,IndicesQualidadeResultado indicesQualidadeResultado){
  Serial.println("foi");
  
  TelemetriaJsonBuilder telemetriaJsonBuilder;

  telemetriaJsonBuilder.setCO2(telemetria.CO2);
  telemetriaJsonBuilder.setTemperatura(telemetria.TEMPERATURA);
  telemetriaJsonBuilder.setUmidade(telemetria.UMIDADE);
    
  telemetriaJsonBuilder.setCOV(telemetria.INDICE_COV);

  telemetriaJsonBuilder.setPm01(telemetria.PM01);
  telemetriaJsonBuilder.setPm10(telemetria.PM10);
  telemetriaJsonBuilder.setPm25(telemetria.PM25);

  indiceQualidadeAr.calcularIndiceUmidade(telemetria.UMIDADE);
  indiceQualidadeAr.calcularIndiceCov(telemetria.INDICE_COV);
  indiceQualidadeAr.calcularIndiceCo2(telemetria.CO2);
  indiceQualidadeAr.calcularIndicePm01(telemetria.PM01);
  indiceQualidadeAr.calcularIndicePm25(telemetria.PM25);
  indiceQualidadeAr.calcularIndicePm10(telemetria.PM10);

  telemetriaJsonBuilder.setIndiceUmidade(indicesQualidadeResultado.QUALIDADE_UMIDADE);
  telemetriaJsonBuilder.setIndiceCov(indicesQualidadeResultado.QUALIDADE_COV);
  telemetriaJsonBuilder.setIndiceCo2(indicesQualidadeResultado.QUALIDADE_CO2);
  telemetriaJsonBuilder.setIndicePm01(indicesQualidadeResultado.QUALIDADE_PM01);
  telemetriaJsonBuilder.setIndicePm25(indicesQualidadeResultado.QUALIDADE_PM25);
  telemetriaJsonBuilder.setIndicePm10(indicesQualidadeResultado.QUALIDADE_PM10);

  const char* json = telemetriaJsonBuilder.build();
    
  Serial.println(json);
  // Serial.println(wifi.idMac());

  String topico = "airshield/" + String(ENDERECO_MAC) + "/dados-ambiente";
  Serial.println(topico);
  mqtt.pub(topico.c_str(),json);
}

void initComponentes(){
  Wire.begin(I2C_SDA,I2C_SCL);

  // Wire.setClock(100000);
  // Serial.printf("SDA: %d\n", digitalRead(21));
  // Serial.printf("SCL: %d\n", digitalRead(22));
  // Serial.println("I2C iniciado!");

  // pinMode(21, INPUT_PULLUP);
  // pinMode(22, INPUT_PULLUP);
  // delay(100);
  // Serial.printf("SDA com pull-up: %d\n", digitalRead(21));
  // Serial.printf("SCL com pull-up: %d\n", digitalRead(22));


  delay(1000);

  // scannerI2C();
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

  wifiService.init();
  bool conectado = wifiService.conectarWifi("UNIFOR");
  // bool conectado = wifiService.conectarWifi("Somanex Casa 11","23280915");

  nomeDispositivo = "airshield-" + ENDERECO_MAC;

  bluetooth.init(nomeDispositivo);

  initComponentes();

  // Serial.println("==============================");
  // Serial.println("IDENTIFICACAO AIRSHIELD");
  // Serial.println("MAC WIFI: " + wifiService.getEnderecoMac());
  // Serial.println("MAC BLE: " + bluetooth.getBluetoothMAC());
  // Serial.println("NOME BLE: " + nomeDispositivo);
  // Serial.println("==============================");
  // WiFiClient teste;

  // Serial.println("Testando TCP com broker.emqx.io...");

  // if (teste.connect("broker.emqx.io", 1883)) {
  //     Serial.println("TCP conectado ao broker!");
  //     teste.stop();
  // } else {
  //     Serial.println("Falha na conexao TCP com broker!");
  // }

  if (conectado) {

    Serial.println("Wi-Fi conectado!");

    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    Serial.print("RSSI: ");
    Serial.println(WiFi.RSSI());

    mqtt.init();
    mqtt.conectar();

  } else {

    Serial.println("Falha no Wi-Fi!");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  // if (apertouBotao){
  //   silenciarBuzzer();
  // }
  Telemetria telemetria = coletorTelemetria.coletarDados();
  IndicesQualidadeResultado indicesQualidadeResultado = indiceQualidadeAr.getIndicesQualidadeResulado();
  
  monitorarQualidadeAr(indicesQualidadeResultado);
  
  informacoesAmbienteDisplay(telemetria,indicesQualidadeResultado);
  
  if (timerEnviarTelemetria() && mqtt.estaConectado()){
    enviarTelemetria(telemetria,indicesQualidadeResultado);
  }

  if (bluetooth.taConectado()){

    bluetooth.enviarMensagem(nomeDispositivo);
    Serial.println(nomeDispositivo);
    Serial.println("ta indo o ble");
  }

  mqtt.loop();
  wifiService.manterConexao();
}

// #include <Arduino.h>

// void setup() {
//     Serial.begin(115200);
//     delay(1000);

//     pinMode(21, INPUT_PULLUP);
//     delay(100);

//     Serial.println("TESTE SDA");

//     for (int i = 0; i < 10; i++) {
//         Serial.println(digitalRead(21));
//         delay(500);
//     }

//     pinMode(22, INPUT_PULLUP);
//     delay(100);

//     Serial.println("TESTE SCL");

//     for (int i = 0; i < 10; i++) {
//         Serial.println(digitalRead(22));
//         delay(500);
//     }
// }

// void loop() {}