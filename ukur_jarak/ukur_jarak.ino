#define trigPin D1
#define echoPin D2

#define ledMerah D5
#define ledBiru D6
#define ledHijau D7

void setup(){
    Serial.begin(115200);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(ledMerah, OUTPUT);
    pinMode(ledBiru, OUTPUT);
    pinMode(ledHijau, OUTPUT);
}

void loop(){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH);
    long distance = duration / 2 / 28.9;

    Serial.print('Jarak: ');
    Serial.print(distance);
    Serial.println(' Cm');
    delay(500);

    if(distance == 3){
        digitalWrite(ledMerah, HIGH);
        digitalWrite(ledBiru, LOW);
        digitalWrite(ledHijau, LOW);
    }
    else if(distance == 5){
        digitalWrite(ledMerah, LOW);
        digitalWrite(ledBiru, HIGH);
        digitalWrite(ledHijau, LOW);
    }
    else if(distance == 7){
        digitalWrite(ledMerah, LOW);
        digitalWrite(ledBiru, LOW);
        digitalWrite(ledHijau, HIGH);
    }
    else{
        digitalWrite(ledMerah, LOW);
        digitalWrite(ledBiru, LOW);
        digitalWrite(ledHijau, LOW);
    }
}
