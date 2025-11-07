#include <Arduino.h>
#include <BluetoothSerial.h>
#include "led.h"
#include "slave.h"
#include <Lcd.h>

BluetoothSerial BTSlave;

String prefix = "[TEMPERATURA]";

void setupSlave() {
    Serial.begin(9600);
    Serial.setTimeout(5000);

    setupLCD();

    if (BTSlave.begin("webvinicDevice"))
    {
        Serial.println("Bluetooth iniciado com sucesso");
        Serial.print("ESP MAC Address: ");
        Serial.println(BTSlave.getBtAddressString());
    } else
    {
        Serial.println("Error para iniciar o Bluetooth");
    }
}

void loopSlave() {
    if (BTSlave.available())
    {
        String receivedMessage = BTSlave.readStringUntil('\n');
        receivedMessage.trim();
        Serial.printf("Evento Recebido: %s\n", receivedMessage.c_str());

        if (receivedMessage.startsWith("[TEMPERATURA]")) {
            int prefixLength = prefix.length();
            String numberString = receivedMessage.substring(prefixLength);
            numberString.trim();
            float temperature = numberString.toFloat();

            displayTemperature(temperature);
        }
    }

}