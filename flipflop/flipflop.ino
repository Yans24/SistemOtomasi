#define ledHijau D1
#define ledBiru D2
#define ledPutih D3

void setup(){
    Serial.begin(9600);
    pinMode(ledHijau, OUTPUT);
    pinMode(ledBiru, OUTPUT);
    pinMode(ledPutih, OUTPUT);
}

void loop(){
    digitalWrite(ledHijau, HIGH);
    digitalWrite(ledBiru, LOW);
    digitalWrite(ledPutih, LOW);
    delay(1000);
    digitalWrite(ledHijau, LOW);
    digitalWrite(ledBiru, HIGH);
    digitalWrite(ledPutih, LOW);
    delay(1000);
    digitalWrite(ledHijau, LOW);
    digitalWrite(ledBiru, LOW);
    digitalWrite(ledPutih, HIGH);
    delay(1000);
}