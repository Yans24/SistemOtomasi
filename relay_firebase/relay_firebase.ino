#include <ESP8266WiFi.h>
#include <OneWire.h>
#include "DHT.h"
#include <LiquidCrystal_I2C.h>
#include <FirebaseArduino.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define relay D4
#define DHT_PIN D3
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

#define FIREBASE_HOST "relay-dht11-2130f-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "qPOVNe0a09NiLUKiSz5T7JZEVyhcrgee2Uw3TuIb"
#define WIFI_SSID "Bos Dian"
#define WIFI_PASS "pakenanya" 



void setup() {
  Serial.begin(115200);
  pinMode(relay, OUTPUT);

  dht.begin();
  lcd.begin();
  lcd.backlight();

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("connecting");
  while (WiFi.status()!= WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("");
  Serial.println("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    
    if (isnan(h) || isnan(t)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }
    
    Firebase.setFloat("Suhu",t);
    Firebase.setFloat("Kelembapan",h);
    // Serial.print("Humidity: ");
    // Serial.print(h);
    // Serial.print("%\t");
    // Serial.print("Temperature: ");
    // Serial.print(t);
    // Serial.println("C");

    lcd.setCursor(0, 0);
    lcd.print("Humidity: ");
    lcd.print(h);
    lcd.print("%");
    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(t);
    lcd.print("C");
    
    if (t > 35) {
        digitalWrite(relay, HIGH);
    } else {
        digitalWrite(relay, LOW);
    }
    
    delay(2000);
}