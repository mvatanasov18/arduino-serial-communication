#include "DHT.h"

int Trig = 12;
int Echo = 11;

DHT dht(13, DHT11);

void setup() { 
  Serial.begin(9600);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT); 
  dht.begin();
  delay(5000);
}

void retrieveDataFromDHT(float& Humidity, float& Temperature,float& HeatIndex)
{
  
  Humidity = dht.readHumidity();
  
  // Read temperature as Celsius (the default)
  Temperature = dht.readTemperature();
  
  // Compute heat index in Celsius (isFahreheit = false)
  HeatIndex = dht.computeHeatIndex(Temperature, Humidity, false);
}

//USS - UltraSonic Sensor
void retrieveDatafromUSS(int& Distance)
{
  int Time = 0;
  // Transmitting pulse
      digitalWrite(Trig, LOW);
      delayMicroseconds(2);
      digitalWrite(Trig, HIGH);
      delayMicroseconds(10);
      digitalWrite(Trig, LOW);
      
      // Waiting for pulse
      Time = pulseIn(Echo, HIGH);
      
      // Calculating the distance
      Distance = Time * 0.034/2;
      
      if(Distance >5)
      {
        //There is 5cm inaccuracy
        Distance=Distance+5;
      }
}

void loop() {
  
  if(Serial.available())
  {
    //[0] - Humidity
    //[1] - Temperature
    //[2] - HeatIndex
    float DHTData[3];
    int Distance;
    
    retrieveDataFromDHT(DHTData[0],DHTData[1],DHTData[2]);
    retrieveDatafromUSS(Distance);
    
    Serial.print(Distance);
    
    for(int i=0;i<3;i++)
    {
      Serial.print(",");
      Serial.print(DHTData[i]);
    }
    Serial.print("@");
    delay(1000);
  }
}
