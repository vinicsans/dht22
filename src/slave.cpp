#include <Arduino.h>
#include <BluetoothSerial.h>
#include "led.h"
#include "slave.h"
#include <Lcd.h>

int mainLedPin = 5;
BluetoothSerial BTSlave;

enum LedState {
    STATE_OFF,
    STATE_ON,
    STATE_BLINKING
};

LedState currentLedState = STATE_OFF;
String prefix = "[TEMPERATURA]";

void setupSlave() {
    setupLED(mainLedPin);
    turnOffLED(mainLedPin);
    currentLedState = STATE_OFF;
    
    Serial.begin(9600);
    Serial.setTimeout(5000);

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

    switch (currentLedState) {
        case STATE_OFF:
            turnOffLED(mainLedPin);
            break;
        case STATE_ON:
            turnOnLED(mainLedPin);
            break;
        case STATE_BLINKING:
            blinkLed(mainLedPin);
            break;
    }

    if (Serial.available())
    {
        String messageToSend = Serial.readStringUntil('\n');
        messageToSend.trim();
        BTSlave.println(messageToSend);
    }
}