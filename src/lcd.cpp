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
    lcd.print("Medindo a temperatura...");
    delay(1000); 
}

void displayTemperature(float temperature) {
	
    lcd.clear();

    lcd.setCursor(0, 0);

    lcd.print("Temperatura: ");

    lcd.setCursor(0, 1);
    
    lcd.print(temperature);
    
	lcd.setCursor(6, 1);
    lcd.write(0xDF); 
    lcd.print("C");
}