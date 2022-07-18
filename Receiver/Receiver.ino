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
double msg[1]; //message that is being sent to the Aruino receiver with four different data values
int msgSize = 4; //size of the message array
double ECG; //ECG value sent from transmitter 

#define DHTPIN 7 //pin that DHT22 is connected to
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE); //initializes the DHT22 sensor

float humidity; //stores the humidity value, value is given in Celcsius 
float temperature; //stores the temperature value

void setup() {
  Serial.begin(9600);
  radio.begin(); //starts the radio module
  radio.openReadingPipe(1, address); //opens connections between the radio modules
  radio.startListening(); //reciever begins waiting for commands from transmitter Arduino   
  dht.begin(); //starts the DHT2 module
}

void loop() {
  if (radio.available()){ //checks to see if radio is able to connect
      radio.read(msg, 1); //start displaying data on LCD display
  }
  ECG = msg[0];
  //Serial.print(ECG);
  humidity = dht.readHumidity(); //takes measurement of humidty
  temperature = dht.readTemperature(); //takes measurement of humidity
  displayValues();
  delay(3000);
}

//displays all the values gathered from the DHT22 sensor
double displayValues(){
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%, Temperature: ");
  Serial.print(temperature);
  Serial.print(" Celcius");
  Serial.print("\n");
}
