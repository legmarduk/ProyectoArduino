#include "DHT.h"

#define PINDHT D7
#define PINHT A0

DHT dht(PINDHT,DHT11);

void setup() {
 Serial.begin(115200);
 dht.begin();
}

void loop() {
  float temperatura = getTemperatura();
  float humedad = getHumedad();
  float humedadTierra= getHumedadTierra();

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println("°C");
  Serial.print("Humedad: ");
  Serial.print(humedad);
  Serial.println("%");
  Serial.print("Humedad Tierra: ");
  Serial.print(humedadTierra);
  Serial.println("%");
  Serial.println("////////////////");
  
  delay(2000);                     
}
float getTemperatura(){ return dht.readTemperature();}
float getHumedad(){return dht.readHumidity(); }
float getHumedadTierra()
{
  float  ht= analogRead(PINHT);
  return((map(ht, 0, 1023, 100, 0)));
}
