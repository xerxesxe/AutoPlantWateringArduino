/* DHT Temperature & Humidity Sensor
Moisture Sensor
Lichstsensor
Based on Unified Sensor Library Example
Written by Jonas
Released under no Licence
Sensoren: 

D7 Relay 
D6 Power für Moiture Sensor 
D3 innen DHT11 
D4 aussen DHT11
A1 Moisture Sensor a0 
A0 Lichtsensor D5


int counter =0;

void setup() {
  Serial.begin(9600); 
  delay(50);
}

void loop() {
  counter++;
  Serial.print("Arduino counter 2: ");
  Serial.println(counter);
  delay(500); // wait half a sec
}

*/

#include <DHT.h>
#include <Wire.h>

DHT dht1(3, DHT11);
DHT dht2(4, DHT11);

uint32_t delayMS;

int valMoist = 0;  //value for storing moisture value
int valLight = 0;  //value for lightsensor
int soilPin = A0;  //soil moisture sensor
int soilPower = 6; //Variable for Soil moisture Power
int lightPin = A0; //multiplexing a0
int lightPower = 5; // power LDR
int valTrocken = 0;
int pumpPower = 7;
int humidity;
int temp;

void setup()
{
  Serial.begin(9600);
  // Initialize device.
  pinMode(soilPower, OUTPUT);    //Set D& as an OUTPUT
  pinMode(pumpPower, OUTPUT);    //Set D7 as an OUTPUT
  pinMode(lightPower, OUTPUT);  //SET D% as an OUTPUT
  digitalWrite(soilPower, LOW);  //Set to LOW so no power is flowing through the sensor
  digitalWrite(pumpPower, LOW); //Set to HIGH
  valTrocken = 0;
  dht1.begin();
  dht2.begin();
}

void loop()
{
// Delay between measurements.
  delay(delayMS);
//DHT11 Output
  float T1 = dht1.readTemperature();
  float H1 = dht1.readHumidity();
  float T2 = dht2.readTemperature();
  float H2 = dht2.readHumidity();

//Moistsensor
  valMoist = 250;
  digitalWrite(soilPower, HIGH);  //turn power "On"
  delay(10);                      //wait 10 milliseconds
  valMoist = analogRead(soilPin); //Read the SIG value form sensor

  Serial.println(valTrocken);
  Serial.println(valMoist);
  digitalWrite(soilPower, LOW); //turn D7 "Off"
 
// Lichsensor
 digitalWrite(lightPower, HIGH);
 delay(10);
 valLight = analogRead(lightPin);
 digitalWrite(lightPower, LOW);

  //relaysteuerung
  if (valTrocken == 1)
  {
    digitalWrite(pumpPower, HIGH);
    delay(5000);
    digitalWrite(pumpPower, LOW);
  }
  ESP.deepSleep(5 * 60 * 1000000); // deepSleep time is defined in microseconds
}
