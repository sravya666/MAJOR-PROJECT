#include <Wire.h> //i2c comm
#include <TimeLib.h> //clock
#include <SPI.h> // memory card
#include <SD.h> // sd card
#include <DS1307RTC.h> //clock

String data;
String info;
const int chipSelect = 10;

void setup() {
  Serial.begin(9600);
  SD.begin(chipSelect);
}

void loop() {

delay(3000);  
File dataFile = SD.open("datalog.txt", FILE_WRITE);

if(Serial.available())
info=Serial.readString(); // read data from primary arduino
else
info="no data"; 

  tmElements_t tm;

  if (RTC.read(tm)) {
    int hr=tm.Hour;
    int mi=tm.Minute;
    int se=tm.Second;
    int da=tm.Day;
    int mo=tm.Month;
    int ye=tmYearToCalendar(tm.Year);
    data=String(hr)+":"+String(mi)+":"+String(se)+"\t"+String(da)+":"+String(mo)+":"+String(ye)+"\t"+info;
  }
  else{
    data="Sensor not found";
  }
  dataFile.println(data);
  dataFile.close();
  Serial.println(data);
  }
  
