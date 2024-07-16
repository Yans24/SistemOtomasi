#define btnHijau D5
#define btnBiru D6

#define ledHijau D1 
#define ledBiru D2  
#define ledPutih D3 

void setup() {
    Serial.begin(9600);
    pinMode(btnHijau, INPUT);
    pinMode(btnBiru, INPUT);
    pinMode(ledHijau, OUTPUT);
    pinMode(ledBiru, OUTPUT);
    pinMode(ledPutih, OUTPUT);
}

void loop() {
    //definisi button sebagai indikator input
    if(digitalRead(btnHijau) == 1){
        digitalWrite(ledHijau, HIGH);
    }else {
        digitalWrite(ledHijau, LOW);
        }
    if(digitalRead(btnBiru) == 1){
        digitalWrite(ledBiru, HIGH);
    }else{
        digitalWrite(ledBiru, LOW);
    }
    
    //Logic XOR : jika salah satu kondisi terpenuhi 
    if((digitalRead(btnHijau) == 1 && digitalRead(btnBiru) == 0) || (digitalRead(btnHijau) == 0 && digitalRead(btnBiru) == 1)) {
        digitalWrite(ledPutih, HIGH);
    } else {
        digitalWrite(ledPutih, LOW);
    }
}
