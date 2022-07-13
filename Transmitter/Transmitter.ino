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
RF24 radio(9, 10);

//constants 
/*const byte address = "00001"; //address
double msg[4]; //message that is being sent to the Aruino receiver with four different data values
int msgSize = 4; //size of the message array*/
int heartRateMonitorA = 5;
int heartRateMonitorB = 6; 
//A0 is where the heart rate sensors sends the data  

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
  //radio.begin(); //starts the radio module
  //radio.openWritingPipe(address); //looks for reviever module at certain address

  //sets the pins for which the heart rate monitor is attached to
  pinMode(heartRateMonitorA, INPUT);
  pinMode(heartRateMonitorB, INPUT);
}

void loop() {
  //gathers measurements to be sent to other Arduino
  //msg[0] = analogRead(A0);
  Serial.println(analogRead(A0)); //testing heart rate monitor
  //radio.write(msg, msgSize); //sends data to other Arduino
  delay(1000); //delays gathering new data for one second then it repeats the loop
}
