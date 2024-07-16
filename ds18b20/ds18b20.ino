#include <DallasTemperature.h>
#include<oneWire.h>

#define ONE_WIRE_BUS D2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup(){
    Serial.begin(115200);
    sensors.begin();
}

void loop(){
    sensors.requestTemperatures();
    Serial.print("Temperature is: ");
    Serial.println(sensors.getTempCByIndex(0));
    delay(500);
}
