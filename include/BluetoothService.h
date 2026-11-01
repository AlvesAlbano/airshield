#pragma once

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define SERVICE_UUID "12345678-1234-1234-1234-123456789000"
#define CHAR_UUID    "12345678-1234-1234-1234-123456789001"

class BluetoothService {
private:
    BLEServer* server;
    BLEService* service;
    BLECharacteristic* characteristic;

    bool connected;

    String getBluetoothMAC();

public:
    BluetoothService();

    void init(String nomeDispositivo);
    void enviarMensagem(String message);
    bool taConectado();
    void setConnected(bool state);
};