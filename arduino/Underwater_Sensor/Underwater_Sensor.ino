/*
  Underwater Sensor Datalogger Array
  by Carey McCachern
  
  This sketch controls a module of the underwater sensor datalogger array.
  The module measures temperature and electrical conductivity and records
  the data, along with a time stamp to an SD card.
  
  The module uses a DS18B20 to record temperature, DS1307+ND for a 
  real time clock, and an LC Studios card reader.
  
  This sketch includes code from:
  Temperature probe - http://bildr.org/2011/07/ds18b20-arduino/
  Real time clock - http://bildr.org/2011/03/ds1307-arduino/
  SD card - Arduino example code datalogger
  Jeelib library: http://jeelabs.net/pub/docs/jeelib/
  Check This^  Find necessary drivers
  Find FTDI driver
  
  The circuit:
 * D1:
*/

// Libary code
// OneWire allows communication with temperature probe
// JeeLib allows module to sleep and save power
// SD allows data storage on SD card
// RTClib allows use of the DS1307 RTC
#include <OneWire.h>
#include <JeeLib.h>
#include <SD.h>
#include "RTClib.h"
#include <Wire.h>
#define LOG_INTERVAL 6000 // Time in ms between measurements (1/10 min)

int DS18S20_Pin = 7; //DS18S20 Signal pin on digital 7
ISR(WDT_vect) { Sleepy::watchdogEvent(); } //Setup for low power waiting
RTC_DS1307 RTC;

//Temperature chip i/o
OneWire ds(DS18S20_Pin); // on digital pin 2
// On the Ethernet Shield, CS is pin 4. Note that even if it's not
// used as the CS pin, the hardware CS pin (10 on most Arduino boards,
// 53 on the Mega) must be left as an output or the SD library
// functions will not work.
const int chipSelect = 4;

/*
 * A structure to contain the information from a single reading.
 */
struct Reading{
  float temperature;
  DateTime date;
};

/*
 * convert a float of the form xx.yy to a string containing that value.
 */
void floatToString(float x, char* buffer){
  buffer[3] =  '.';
  x *= 100;
  int intX = (int) x;
  for(int i = 5; i > -1; i--){
    if(i == 3) continue; // skip the decimal point
    buffer[i] = (intX%10) + '0';
    intX /= 10;
  };
};

void setup(void) {
  Serial.begin(9600);
  Wire.begin();
  RTC.begin();
  // Real Time Clock
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
  }
  RTC.adjust(DateTime(__DATE__, __TIME__));
  //SD Card    
  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}

struct Reading currReading;

void loop(void) {
  currReading.temperature = getTemp();
  currReading.date = RTC.now();
  // float temperature = getTemp();
 // Serial.println(currReading.temperature);
 //Serial.println(temperature);
 SDwrite(&currReading);
// SDwrite(temperature);
 delay(20); // Allow time for write before sleep
 Sleepy::loseSomeTime(LOG_INTERVAL - 20);
 
}


/* Functions
***************
* getTemp
*
*/

float getTemp(){
 //returns the temperature from one DS18S20 in DEG Celsius

 byte data[12];
 byte addr[8];

 if ( !ds.search(addr)) {
   //no more sensors on chain, reset search
   ds.reset_search();
   return -1000;
 }

 if ( OneWire::crc8( addr, 7) != addr[7]) {
   Serial.println("CRC is not valid!");
   return -1000;
 }

 if ( addr[0] != 0x10 && addr[0] != 0x28) {
   Serial.print("Device is not recognized");
   return -1000;
 }

 ds.reset();
 ds.select(addr);
 ds.write(0x44,1); // start conversion, with parasite power on at the end

 byte present = ds.reset();
 ds.select(addr);  
 ds.write(0xBE); // Read Scratchpad

 
 for (int i = 0; i < 9; i++) { // we need 9 bytes
  data[i] = ds.read();
 }
 
 ds.reset_search();
 
 byte MSB = data[1];
 byte LSB = data[0];

 float tempRead = ((MSB << 8) | LSB); //using two's compliment
 float TemperatureSum = tempRead / 16;
 
 return TemperatureSum;
 
}

// SD Card

void SDwrite(struct Reading *reading){
  // this needs to do what the other one does, but for a whole READING **TODO**
  /*char buffer[16];
  buffer[6] = ' ';
  buffer[9] = ':';
  buffer[12] = ':';
  buffer[15] = 0;
  
  floatToString(reading->temperature, buffer);
  
  int temp;
  temp = reading->date.hour();
  buffer[7] = (temp/10)%10 + '0';
  buffer[8] = temp%10 + '0';
  
  temp = reading->date.minute();
  buffer[10] = (temp/10)%10 + '0';
  buffer[11] = temp%10 + '0';
  
  temp = reading->date.second();
  buffer[13] = (temp/10)%10 + '0';
  buffer[14] = temp%10 + '0';*/
  
 // Serial.println("Opening SD File");
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  Serial.print(reading->date.hour());
  Serial.println(reading->date.minute());
  if(dataFile){
    dataFile.write((uint8_t*)reading, sizeof(struct Reading));
//    dataFile.println(buffer);
    dataFile.close();
  //  Serial.println(buffer);
  }else{
    Serial.println("error opening SD File!!");
  };
};

/*
void SDwrite(float temperature)
{
  int data = 100 * temperature;
  // make a string for assembling the data to log:
  String dataString = "";
  int sensor = 1;
  dataString += String(data/100);
  dataString += ".";
  dataString += String(data - 100*(data/100));
  
  

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  } 
}
*/

