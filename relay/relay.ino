#define relay D5 
void setup(){
    pinMode(D5, OUTPUT);

}
void loop(){
    digitalWrite(D5, HIGH);
    delay(100);
    digitalWrite(D5, LOW);
    delay(100);
}