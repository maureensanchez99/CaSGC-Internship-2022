/*
Created by Maureen Sanchez, Andres Zamudio, and Manuel Aboite
Reference Code is cited in the README file of the repository
Purpose: needs to measure heart rate, blood oxygen levels, and recored the ECG/EKG
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
int heartRateMonitorA = 5;
int heartRateMonitorB = 6;

void setup() {
  radio.begin(); //starts the radio module 
  radio.openWritingPipe(address); //looks for reviever module at certain address
  
  //sets the pins for which the heart rate monitor is attached to
  pinMode(heartRateMonitorA, INPUT);
  pinMode(heartRateMonitorB, INPUT);
}

void loop() {
  //gathers measurements to be sent to other Arduino
  msg[0] = analogRead(A0);
  
  radio.write(msg, msgSize); //sends data to other Arduino
  delay(1000); //delays gathering new data for one second then it repeats the loop
}
