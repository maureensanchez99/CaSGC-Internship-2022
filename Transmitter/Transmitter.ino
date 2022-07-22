/*
  Created by Maureen Sanchez, Andres Zamudio, and Manuel Aboite
  Reference Code is cited in the README file of the repository
  Purpose: needs to measure heart rate, blood oxygen levels, and recored the ECG/EKG
*/

#include <SPI.h>;
#include "RF24.h"
#include <DHT.h>

/*connected to digital pins (pins with a ~)
  used for setting module into standby or active mode
  switching between transmit or command mode */
RF24 radio(9, 10); //create radio object

//constants 
const byte address = "00001"; //address
double msg[1]; //message that is being sent to the Aruino receiver with four different data values
//double msgSize = 4; //size of the message array
int heartRateMonitorA = 5;
int heartRateMonitorB = 6; 
//A0 is where the heart rate sensors sends the data  
DHT dht(7, DHT22); //creates DHT object 
int temperature;
int humidity;

/*
  Hardware Connections (Breakoutboard to Arduino):
  -5V = 5V (3.3V is allowed)
  -GND = GND
  -SDA = A4 (or SDA)
  -SCL = A5 (or SCL)
  -INT = Not connected
 
  The MAX30105 Breakout can handle 5V or 3.3V I2C logic. We recommend powering the board with 5V
  but it will also run at 3.3V.
*/

void setup() {
  Serial.begin(9600);
  radio.begin(); //starts the radio module
  radio.openWritingPipe(address); //looks for reviever module at certain address

  //sets the pins for which the heart rate monitor is attached to
  pinMode(heartRateMonitorA, INPUT);
  pinMode(heartRateMonitorB, INPUT);
}

void loop() {
  //gathers measurements to be sent to other Arduino
  if((digitalRead(5) == 1)||(digitalRead(6) == 1)){ //collects ECG/EKG data
    msg[0] = '!'; //if value is outside range, sets ! as the value
  } else {
    msg[0] = analogRead(A0); //if value
  }
  //radio.write(msg, msgSize); //sends data to other Arduino
  radio.write(msg,1); //sending it off as a single message to test if receiver is getting data
  delay(2); //Wait for a bit to keep serial data from saturating
}
