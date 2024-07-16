#include <OneWire.h>
#include "DHT.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define relay D4
#define DHT_PIN D3
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);



void setup() {
  Serial.begin(115200);
  dht.begin();
  lcd.begin();
  lcd.backlight();
  pinMode(relay, OUTPUT);
}

void loop() {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    
    if (isnan(h) || isnan(t)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }
    
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print("%\t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.println("C");

    lcd.setCursor(0, 0);
    lcd.print("Humidity: ");
    lcd.print(h);
    lcd.print("%");
    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(t);
    lcd.print("C");
    
    if (t > 34) {
        digitalWrite(relay, HIGH);
    } else {
        digitalWrite(relay, LOW);
    }
    
    delay(2000);
}