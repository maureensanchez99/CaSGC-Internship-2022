/*
Created by Maureen Sanchez, Andres Zamudio, and Manuel Aboite
Reference Code is cited in the README file of the repository
Purpose: receives data from transmitter Arduino, measures data from attached sensors, displays data onto LCD display 
*/

#include <SPI.h>
#include "RF24.h"

/*connected to digital pins (pins with a ~)
used for setting module into standby or active mode
switching between transmit or command mode */
RF24 radio(9,10); 

//constants 
const byte address = "00001"; //address 
double msg[4]; //message that is being sent to the Aruino receiver with four different data values
int msgSize = 4; //size of the message array

void setup() {
  radio.begin(); //starts the radio module
  radio.openReadingPipe(1, address); //opens connections between the radio modules
  radio.startListening(); //reciever begins waiting for commands from transmitter Arduino   
}

void loop() {
  if (radio.available()){ //checks to see if radio is able to connect
    for(int i = 0; i < msgSize; i++){
      radio.read(msg, i); //start displaying data on LCD display
    }
  }
}
