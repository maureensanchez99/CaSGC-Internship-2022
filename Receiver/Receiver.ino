/*
Created by Maureen Sanchez, Andres Zamudio, and Manuel Aboite
Reference Code is cited in the README file of the repository
Purpose: receives data from transmitter Arduino, measures data from attached sensors, displays data onto LCD display 
*/

#include <SPI.h>
#include "RH_NRF24.h"
//#include <Wire.h>
//#include "MAX30105.h"


/*connected to digital pins (pins with a ~)
used for setting module into standby or active mode
switching between transmit or command mode */
RH_NRF24 radio(9,10); //create radio object 

//constants 
const uint8_t address = 2; //address
String msg; //message that is being sent to the Aruino receiver with four different data valuesr

String humidity; //stores the humidity value, value is given in Celcsius 
String temperature; //stores the temperature value

void setup() {
  Serial.begin(9600);
  radio.init(); //starts the radio module
  radio.setChannel(address); //opens connections between the radio modules  
}

void loop(){
  //read values from msg
  displayValues();
  delay(3000);
}

//displays all the values gathered from the DHT22 sensor onto the Arduino serial monitor
double displayValues(){
  Serial.print("\nHumidity: ");
  Serial.print(humidity);
  Serial.print("%, Temperature: ");
  Serial.print(temperature);
  Serial.print(" Celcius");
  Serial.print("\n");
}
