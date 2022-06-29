/*
Created by Maureen Sanchez, Andres Zamudio, and Manuel Aboite
Reference Code is cited in the README file of the repository
Purpose: needs to measure heart rate, blood oxygen levels, and recored the ECG/EKG
*/

#include <SPI.h>
#include <nRF24L01.h>
#include "RF24.h"

/*connected to digital pins (pins with a ~)
used for setting module into standby or active mode
switching between transmit or command mode */
RF24 radio(9,10); 

//constants 
const byte address = "00001"; //address 
double msg[4]; //message that is being sent to the Aruino receiver with four different data values

void setup() {
  radio.begin(); //starts the radio module 
  radio.openWritingPipe(address); //looks for reviever module at certain address
}

void loop() {
  //gathers measurements to be sent to other Arduino
  // *MAGIC*
  
  radio.write(msg, 4); //sends data to other Arduino
  delay(1000); //delays gathering new data for one second then it repeats the loop
}
