#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <DHT.h>

#define FIREBASE_HOST "iot24-263f5-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "IVDcjDwevxVFYTzf0ZxoIVc2YGjpLyo3qrtatFVK3"

const char* ssid = "Yans2";
const char* password = "00000000";

#define DHTPIN D8
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define TRIGPIN D5 
#define ECHOPIN D6

FirebaseData firebaseData;
FirebaseAuth firebaseAuth;
FirebaseConfig firebaseConfig;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi with IP: ");
  Serial.println(WiFi.localIP());

  firebaseConfig.host = FIREBASE_HOST;
  firebaseConfig.signer.tokens.legacy_token = FIREBASE_AUTH;

  Firebase.begin(&firebaseConfig, &firebaseAuth);
  Firebase.reconnectWiFi(true);

  dht.begin();
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);

  long duration = pulseIn(ECHOPIN, HIGH);
  float distance = duration / 2 * 0.0343; 
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  if (Firebase.setFloat(firebaseData, "/temperature", temperature)) {
    Serial.println("Temperature updated");
  } else {
    Serial.print("Failed to update temperature: ");
    Serial.println(firebaseData.errorReason());
  }

  if (Firebase.setFloat(firebaseData, "/humidity", humidity)) {
    Serial.println("Humidity updated");
  } else {
    Serial.print("Failed to update humidity: ");
    Serial.println(firebaseData.errorReason());
  }

  if (Firebase.setFloat(firebaseData, "/feed_level", distance)) {
    Serial.println("Feed level updated");
  } else {
    Serial.print("Failed to update feed level: ");
    Serial.println(firebaseData.errorReason());
  }

  delay(2000);
}
