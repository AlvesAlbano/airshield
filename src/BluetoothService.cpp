#include "BluetoothService.h"

BluetoothService::BluetoothService() {
    server = nullptr;
    service = nullptr;
    characteristic = nullptr;

    connected = false;
}

// Callbacks de conexão
class BluetoothCallbacks : public BLEServerCallbacks {
private:
    BluetoothService* bluetooth;

public:
    BluetoothCallbacks(BluetoothService* service) {
        bluetooth = service;
    }

    void onConnect(BLEServer* server) override {
        bluetooth->setConnected(true);
    }

    void onDisconnect(BLEServer* server) override {
        bluetooth->setConnected(false);
        server->getAdvertising()->start();
    }
};

void BluetoothService::init(String nomeDispositivo) {

    BLEDevice::init(nomeDispositivo.c_str());

    server = BLEDevice::createServer();

    server->setCallbacks(new BluetoothCallbacks(this));

    service = server->createService(SERVICE_UUID);

    characteristic = service->createCharacteristic(
        CHAR_UUID,
        BLECharacteristic::PROPERTY_READ |
        BLECharacteristic::PROPERTY_NOTIFY
    );

    characteristic->addDescriptor(new BLE2902());

    service->start();

    server->getAdvertising()->start();

    Serial.println("Bluetooth iniciado!");
}

String BluetoothService::getBluetoothMAC() {
    return BLEDevice::getAddress().toString().c_str();
}

void BluetoothService::enviarMensagem(String message) {

    if (!connected || characteristic == nullptr)
        return;

    characteristic->setValue(message.c_str());
    characteristic->notify();
}

bool BluetoothService::taConectado() {
    return connected;
}

void BluetoothService::setConnected(bool state) {
    connected = state;
}