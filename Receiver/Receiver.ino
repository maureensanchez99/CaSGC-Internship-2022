/*
Created by Maureen Sanchez, Andres Zamudio, and Manuel Aboite
Reference Code is cited in the README file of the repository
Purpose: receives data from transmitter Arduino, measures data from attached sensors, displays data onto LCD display 
*/

#include <SPI.h>
#include "RF24.h"
#include <Wire.h>
#include "MAX30105.h"
#include <DHT.h>;

/*connected to digital pins (pins with a ~)
used for setting module into standby or active mode
switching between transmit or command mode */
RF24 radio(9,10); 

//constants and variables
const byte address = "00001"; //address 
double msg[4]; //message that is being sent to the Aruino receiver with four different data values
int msgSize = 4; //size of the message array

#define DHTPIN 7 //pin that DHT22 is connected to
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

float humidity; //stores the humidity value
float temperature; //stores the temperature value

void setup() {
  Serial.begin(9600);
  radio.begin(); //starts the radio module
  radio.openReadingPipe(1, address); //opens connections between the radio modules
  radio.startListening(); //reciever begins waiting for commands from transmitter Arduino   
  dht.begin();
}

void loop() {
  if (radio.available()){ //checks to see if radio is able to connect
      radio.read(msg, msgSize); //start displaying data on LCD display
  }
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
}

double displayValues(){
  Serial.print(humidity);
  Serial.print(temperature);
}
