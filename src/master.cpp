#include <Arduino.h>
#include <BluetoothSerial.h>
#include <Sensor.h>
#include <Lcd.h>

BluetoothSerial BTSerial;

int buttonPin = 22;
int lastButtonState = HIGH;      
unsigned long pressStartTime = 0; 
bool longPressSent = false;     
const long LONG_PRESS_TIME = 2000; 

float lastHumidity = 0;
float lastTemperature = 0;

u_int8_t slaveAddress[] = {0xF4, 0x65, 0x0B, 0x47, 0x1D, 0x6A};

void setupMaster(){
    Serial.begin(9600);
    Serial.setTimeout(5000);

    pinMode(buttonPin, INPUT_PULLUP);

    if (BTSerial.begin("webvinicDevice", true))
    {
        Serial.println("Bluetooth (Master) iniciado com sucesso");
    } else
    {
        Serial.println("Erro ao iniciar o bluetooth");
    }

    Serial.println("Tentando conectar ao Slave...");
    if (BTSerial.connect(slaveAddress))
    {
        Serial.println("Conectado com sucesso");
    } else {
        Serial.println("Falha ao conectar");
    }

    setupSensor();
    setupLCD();
}

void loopMaster(){

    float temperature = getTemperatureAsFloat();
    float humidity = getRelativeHumidity();

    if (BTSerial.available())
    {
        String receivedMessage = BTSerial.readStringUntil('\n');
        receivedMessage.trim();
        Serial.printf("Mensagem recebida: %s\n", receivedMessage.c_str());
    }

    if (Serial.available())
    {
        String messageToSend = Serial.readStringUntil('\n');
        messageToSend.trim();
        BTSerial.println(messageToSend);
    }

    if (temperature != lastTemperature) {
        String message = "[TEMPERATURA] " + String(temperature, 2);
        BTSerial.println(message);
        Serial.println(message);
    }

    if (humidity != lastHumidity) {
        String message = "[UMIDADE] " + String(humidity, 2);
        BTSerial.println(message);
        Serial.println(message);
    }

    lastTemperature = temperature;
    lastHumidity = humidity;
}