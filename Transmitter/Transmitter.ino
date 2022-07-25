/*
  Created by Maureen Sanchez, Andres Zamudio, and Manuel Aboite
  Reference Code is cited in the README file of the repository
  Purpose: needs to measure heart rate, blood oxygen levels, and recored the ECG/EKG
*/

#include <SPI.h>
#include "RH_NRF24.h"
#include <DHT.h>

/*connected to digital pins (pins with a ~)
  used for setting module into standby or active mode
  switching between transmit or command mode */
RH_NRF24 radio(9, 10); //create radio object

//constants 
const uint8_t address = 2; //address

DHT dht(7, DHT22); //creates DHT object at pin 7
int temp; //variable that holds the temperature value
int humid; //variable that holds the humidity value
String stringMsg; //message that is being sent to the Aruino receiver with four different data values
String stringTemp; //string that holds the temperature value
String stringHumid; //string that holds the humidity value

void setup() {
  Serial.begin(9600);
  radio.init(); //starts the radio module
  radio.setChannel(address); //looks for reviever module at certain address

  dht.begin();
  delay(2000);
}

void loop() {
  //gathers measurements to be sent to other Arduino
  temp = dht.readTemperature();
  humid = dht.readHumidity();

  //converts measurements into string data
  stringTemp = String(temp);
  stringHumid = String(humid);
  stringMsg = stringTemp + "," + stringHumid; //adds gathered data into stringMsg
  
  char *msg = stringMsg.c_str(); //converts strinMsg into C language 
  
  radio.send(msg, strlen(msg)); //sending it off as a single message to test if receiver is getting data
  delay(2); //Wait for a bit to keep serial data from saturating
}
