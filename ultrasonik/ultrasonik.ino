#define trigPin D1
#define echoPin D2

long durasi, jarak;


void setup(){
    Serial.begin(115200);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void loop(){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    durasi = pulseIn(echoPin, HIGH);
    jarak = durasi / 2 / 28.9;

    Serial.print('Jarak: ');
    Serial.print(jarak);
    Serial.println(' Cm');
    delay(1000);
}