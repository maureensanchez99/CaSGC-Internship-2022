/*
Created by Maureen Sanchez, Andres Zamudio, and Manuel Aboite
Reference Code is cited in the README file of the repository. 
*/

// needs to measure heart rate, blood oxygen levels, and recored the ECG/EKG

#include <SPI.h>
#include "RF24.h"
RF24 radio(9,10);

//constants 
const uint64_t address = 0xF0F0F0F000LL; //address 
double msg[4]; //message that is being sent to the Aruino receiver with four different data values

void setup() {
  radio.begin(); //starts the radio module 
  radio.openWritingPipe(address); //looks for reviever module at certain address
}

void loop() {
  radio.write(msg, 4);
}
