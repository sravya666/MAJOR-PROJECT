# MAJOR-PROJECT
We propose a system that is used to measure, monitor, record, and control various atmospheric weather parameters like temperature, pressure, humidity, air quality, sunlight, and altitude. 
This can be implemented by using several sensors like DHT11, BMP280, LDR Module, IR sensor, HC-05, MQ2 Gas sensor, and RTC Module. 
The model is implemented in two parts i.e., the transmitter and receiver.  
The transmitter or the payload has the combination of all these sensors that are connected to the main microcontroller which is the Arduino.
The transmitter also has the SD/memory card that is connected to another Arduino for storing the information. 
The transmitter module is also connected to the primary Arduino. 
In the receiver end, we have the receiver module and the Bluetooth sensors that are connected to another Arduino nano.
The information from the transmitter is received on to the receiver which is displayed on the LCD screen. 
The model operates with two 3.6volts batteries which produce the main power. 
As the power is switched on it gives 5 beeps to indicate that the model is on and the sensing of the values will start soon. 
All the values are displayed on the LCD screen on the receiver with a gap of 3 seconds. 
We can place the transmitter wherever we wish to in a radius of 10mts to 1km and keep the receiver module with us to monitor and view the weather parameters. 
Simultaneously the information is stored on the SD card as well and the information can be viewed on the computer screen as well.
