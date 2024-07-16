#define trigPin D1 
#define echoPin D2
#define relay D3


void loop() {
    long duration, distance;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance < 20) {
        digitalWrite(relay, HIGH);
        Serial.println("Object Detected!");
    } else {
        digitalWrite(relay, LOW);
        Serial.println("No Object Detected.");
    }
    delay(1000);
}