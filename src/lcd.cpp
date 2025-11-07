#include "lcd.h"
#include <Wire.h>               
#include <LiquidCrystal_I2C.h>    

#define SDA_PIN    21
#define SCL_PIN    22

LiquidCrystal_I2C lcd(0x27, 16, 2);


void setupLCD() {
    Wire.begin(SDA_PIN, SCL_PIN);

    lcd.init();
    
    lcd.backlight();

    lcd.clear();
    lcd.setCursor(0, 0); 
    lcd.print("Medindo...");
    delay(1000); 
}

void displayData(float temperature, float umidity) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temperatura: ");
    lcd.setCursor(0, 1);
    lcd.print("Umidade: ");

    if (temperature == -999) {
        lcd.setCursor(13, 0);
        lcd.print("Não detectado");
    } else {
        lcd.setCursor(13, 0);
        lcd.print(temperature);

        lcd.setCursor(18, 0);
        lcd.write(0xDF); 
        lcd.print("C");
    }

    if (umidity == -999) {
        lcd.setCursor(9, 1);
        lcd.print("Não detectado");
    } else {
        lcd.setCursor(9, 1);
        lcd.print(umidity);

        lcd.setCursor(13, 1);
        lcd.print("%");
    }
    
}