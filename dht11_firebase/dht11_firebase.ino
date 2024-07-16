#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Wire.h>
#include "DHT.h"

#define FIREBASE_HOST "integrasi-dht11-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "3rs0CnYWP0Vr2nJ0T8yziQV3x8VgeChqPVCanUrn"
#define WIFI_SSID "Yans"
#define WIFI_PASS "sijitekowolu"

#define DHTPIN D2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup(){
    Serial.begin(115200);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    Serial.println("Connecting to WiFi...");
    while (WiFi.status()!= WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected to the WiFi network");
    Serial.println(WiFi.localIP());

    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    dht.begin();
}

void loop(){
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    Firebase.setFloat("humidity", h);
    Firebase.setFloat("temperature", t);
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print("% \t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.println("°C");
    delay(1000);
}
