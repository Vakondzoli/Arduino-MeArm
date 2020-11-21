#include "DHT.h"
#define DHTPIN 2  
#define DHTTYPE DHT22   
const int AOUTpin=0;
int value;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
Serial.begin(9600);
pinMode(AOUTpin, INPUT);
Serial.println(F("DHTxx test!"));
dht.begin();
}

void loop()
{
delay(2000);
float h = dht.readHumidity();
float t = dht.readTemperature();
float hic = dht.computeHeatIndex(t, h, false);
Serial.print(F("Humidity: "));

Serial.print(h);

Serial.print(F("%  Temperature: "));

Serial.print(t);

Serial.print(F("°C "));


Serial.print(hic);

Serial.print(F("°C "));



value= analogRead(AOUTpin);//reads the analaog value from the alcohol sensor's AOUT pin

Serial.print("Alcohol value: ");
Serial.println(value);

delay(100);

}
