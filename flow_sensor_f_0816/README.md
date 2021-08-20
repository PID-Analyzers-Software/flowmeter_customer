# flowmeter

Wiring:

--------
ADS1115 - SDA  <--> ESP32 5 

ADS1115 - SCL  <--> ESP32 4 

ADS1115 - VDD  <--> ESP32 5V 

ADS1115 - GND  <--> ESP32 GND 

ADS1115 - A0   <--> F1022 VOUT 

ADS1115 - A1   <--> ESP32 GND 

ADS1115 - A2   <--> ESP32 GND 

ADS1115 - A3   <--> ESP32 GND 


--------

DS3231M - SDA  <--> ESP32 5

DS3231M - SCL  <--> ESP32 4

DS3231M - VDD  <--> ESP32 3.3V

DS3231M - GND  <--> ESP32 GND


--------

F1022   - VCC  <--> BOOST CONVERTER 12V OUT 

F1022   - GND  <--> ESP32 GND 

F1022	- VOUT <--> ADS1115 A0 

--------

BOOST CONVERTER VIN  <--> ESP32 3.3V

BOOST CONVERTER GND  <--> ESP32 GND

BOOST CONVERTER VOUT <--> F1022 VCC(12V)


--------

BUTTON DOWN  <--> ESP32 2

BUTTON S     <--> ESP32 0

BUTTON RIGHT <--> ESP32 15


Calibration mode:

Hold buttons DOWN and RIGHT for 3 or more seconds and then release to enter CALIBRATION MODE. While in calibration, connect to esp32's wifi network and open url on screen in browser and set parameters as needed.
