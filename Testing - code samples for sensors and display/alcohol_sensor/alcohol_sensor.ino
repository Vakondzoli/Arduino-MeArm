/* MQ-3 Alcohol Sensor Circuit with Arduino */


const int AOUTpin=0;
int value;


void setup() {
Serial.begin(9600);
pinMode(AOUTpin, INPUT);

}

void loop()
{
value= analogRead(AOUTpin);//reads the analaog value from the alcohol sensor's AOUT pin

Serial.print("Alcohol value: ");
Serial.println(value);

delay(100);

}
