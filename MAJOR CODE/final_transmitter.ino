#include "DHT.h" 
#include <Adafruit_BMP280.h>
#include <SPI.h>                              
#include <nRF24L01.h>
#include <RF24.h>

#define DHTTYPE DHT11

#define DHTPIN 7
#define gasPin A3
#define batPin A2
#define lightPin A1
#define buzzer 6

DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP280 bmp;
RF24 radio(9, 10);                              
const byte address[6] = "00001";             

void beep(){
  tone(buzzer,1000);
  delay(250);
  noTone(buzzer);
  delay(250);
}

struct MyData {
  byte gasValue;
  byte dn;
  byte tbmp;
  byte pbmp;
  byte abmp;
  byte h;
  byte t;
  byte b;
};
MyData data;
void setup() {
  dht.begin();
  bmp.begin();
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
  radio.begin();                              
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  
  pinMode(6,OUTPUT);
  
  Serial.begin(9600);
  beep();
  beep();
  beep();
  beep();
  beep();
  
}

void loop() {
  data.gasValue = analogRead(gasPin);
  data.h = dht.readHumidity();
  data.t = dht.readTemperature();
  data.tbmp = bmp.readTemperature();
  data.pbmp = bmp.readPressure();
  data.abmp = bmp.readAltitude(1019.66);
  data.dn = map(analogRead(lightPin),0,1000,0,100); //LDR
  data.b = map(analogRead(batPin),125,155,0,100); // BATTERY
  
  radio.write(&data,sizeof(MyData)); // sent to reciever 
  String text =String(data.h)+"|"+String((data.t+data.tbmp)/2)+"|"+String(data.gasValue)+"|"+String(data.pbmp)+"|"+String(data.abmp)+"|"+String(data.dn)+"|"+String(data.b);
  Serial.println(text);
  beep();
  delay(2500);
 

}
