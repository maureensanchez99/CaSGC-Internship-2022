/*
Created by Maureen Sanchez, Andres Zamudio, and Manuel Aboite
Reference Code is cited in the README file of the repository. 
*/

#include <SPI.h>
#include "RF24.h"
RF24 radio(9,10);

//constants 
const uint64_t address = 0xF0F0F0F000LL; //address 
double msg[4]; 

void setup() {
  radio.begin(); //starts the radio module
  radio.openReadingPipe(1, address); //opens connections between the radio modules
  radio.startListening(); //reciever begins waiting for commands from transmitter Arduino   
}

void loop() {
  if (radio.available()){ //checks to see if radio is able to connect
    radio.read(msg,4); //if so start recieving messages to perform
  }
}
