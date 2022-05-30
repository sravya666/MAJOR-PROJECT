#include <SPI.h>                        
#include <nRF24L01.h>                           
#include <RF24.h>   
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#define bt1 3

SoftwareSerial MyBlue(5, 6); // RX | TX 
LiquidCrystal_I2C lcd(0x27, 16, 2);
RF24 radio(9, 10); // CE, CSN  

bool startdisplay=false;
bool printdata=false;

int n=0;  // the data to be diaplayed number

const byte address[6] = "00001";

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
  Serial.begin(9600);                          //Serial baud rate set to 9600
  MyBlue.begin(9600);
  radio.begin();                               // nrf24 
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("WELCOME");
  lcd.setCursor(0,1);
  lcd.print("WAITING...");
  Serial.println("WAITING");
  delay(100);
  
  pinMode(bt1,INPUT_PULLUP);

  while(radio.available()==false){}
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("DATA AVAILABLE");
  lcd.setCursor(0,1);
  lcd.print("PRESS THE BUTTON");
  Serial.println("DATA AVAILABLE, PRESS THE BUTTON TO PROCEED");
}

void loop() {
  
  if ( radio.available() ) {
  radio.read(&data, sizeof(MyData));
  Serial.println(data.h);
  Serial.println(data.t);
  Serial.println(data.dn);
  Serial.println(data.gasValue);
  Serial.println(data.tbmp);
  Serial.println(data.pbmp);
  Serial.println(data.abmp);
  Serial.println(data.b);
  String text = String(data.h)+"|"+String((data.t+data.tbmp)/2)+"|"+String(data.gasValue)+"|"+String(data.pbmp)+"|"+String(data.abmp)+"|"+String(data.dn)+"|"+String(data.b)+"|";
  MyBlue.println(text);
  startdisplay=true;
  }
  
  if(startdisplay)
  {    
    
    if(digitalRead(bt1)==LOW)
    { n=n+1;
      delay(500);}    
    if(n==8)            //only 7 datas available, so 8 means go back to 1
    n=1;
    delay(200);
    switch(n){
      case 1: 
      { lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("HUMIDITY : ");
        lcd.setCursor(0,1);
        lcd.print(data.h);
        lcd.print("%");}
        break;
      case 2: 
      { lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("TEMPERATURE : ");
        lcd.setCursor(0,1);
        lcd.print((data.t+data.tbmp)/2);
        lcd.print(" C");}
        break;
      case 3: 
      { lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("PRESUURE : ");
        lcd.setCursor(0,1);
        lcd.print(data.pbmp);
        lcd.print("kPa");}
        break;
      case 4: 
      { lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("ALTITUDE : ");
        lcd.setCursor(0,1);
        lcd.print(data.abmp);
        lcd.print("M ABV SEA LVL");}
        break;
      case 5: 
      { lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("BATTERY : ");
        lcd.setCursor(0,1);
        lcd.print(data.b);
        lcd.print("%");}
        break;
      case 6:
      { lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("DAYLIGHT");
        lcd.setCursor(0,1);
        lcd.print(data.dn);}   
        break;
      case 7:
      { lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("A.Q.I : ");
        lcd.setCursor(0,1);
        if(data.gasValue<30)
        lcd.print("GOOD");
        else if(data.gasValue>30&&data.gasValue<100)
        lcd.print("AVERAGE")  ;
        else if(data.gasValue>100&&data.gasValue<170)
        lcd.print("BAD")  ;
        else
        lcd.print("SENSOR NOT READY");}
        break;
    }

  }
  
}
