#include "DHT.h"
#include <ESP8266WiFi.h>

/*Pines definidos para sensores*/
#define PINDHT D7
#define PINHT A0

/*datos WiFi*/
const char* ssid = "Nelson Daniel";
const char* password ="03Mayo1997";
const char* host = "192.168.43.126"; /*mi ip*/ 

DHT dht(PINDHT,DHT11);

void setup() {
 Serial.begin(115200);
 dht.begin();
 WiFi.begin(ssid,password);

  while(WiFi.status() != WL_CONNECTED)
  {
      Serial.print(".");
      delay(500);
  }
 Serial.println();
 Serial.print("WIFI IP: ");
 Serial.println(WiFi.localIP());
 Serial.println("/////////////");
 Serial.println();
}

void loop() 
{
  WiFiClient client;
  const int port = 80;

  if(!client.connect(host, port))
  {
        Serial.println("Fallo");
        delay(5000);
        return;  
  }
  else
  {
       Serial.println("Conectado");     
       float temperatura = getTemperatura();
       float humedad = getHumedad();
       float humedadTierra= getHumedadTierra();
      
       String url =  "/Arduino/Datos.php";
       String dato1 = "?t=";
       String dato2 = "&h=";
       String dato3 = "&ht=";
       Serial.print("Url: ");
       Serial.println(url);
    
       client.print(String("GET ") + url  +dato1 + temperatura + dato2 +humedad+dato3+humedadTierra+ " HTTP/1.1\r\n"+ "Host: " + host + "\r\n" +"Connection: close\r\n\r\n");
             
       unsigned long timeout = millis();
       while(client.available() == 0)
       {
          if(millis() - timeout >5000)
          {
            Serial.print("Tiempo muerto");
            client.stop();
            return;
          }  
        }
       while(client.available())
       {
        String line = client.readStringUntil('\r');
        Serial.print(line); 
       }  
     Serial.println();
     Serial.println("Conexion cerrada");
  }
  delay(20000);                     
}

/*Recopilar Datos de Los Sensores*/
float getTemperatura(){ return dht.readTemperature();}
float getHumedad(){return dht.readHumidity();}
float getHumedadTierra()
{
  float  ht= analogRead(PINHT);
  return((map(ht, 0, 1023, 100, 0)));
}
