#include <dht.h>
#define dataPin 8 // Defines pin number to which the sensor is connected

char bt;
int trig_pin = 12;
int echo_pin = 9;
int airquality = A3 ;
dht DHT; // Creats a DHT object
long echotime; //in micro seconds
float distance; //in cm
unsigned long interval=2000;     // the time we need to wait
unsigned long previousMillis=0;  // millis() returns an unsigned long.

void setup() {
  Serial.begin (9600);
  pinMode(2,OUTPUT);   //left motors forward
  pinMode(3,OUTPUT);   //left motors reverse
  pinMode(4,OUTPUT);   //right motors forward
  pinMode(7,OUTPUT);   //right motors reverse
  pinMode(trig_pin, OUTPUT); 
  pinMode(echo_pin, INPUT);
  digitalWrite(trig_pin, LOW); //Start with trigger LOW
}

void loop() {
  if(Serial.available()){
    bt = Serial.read();
    Serial.println(bt);
  }

  if(bt == 'F'){            //move forward(all motors rotate in forward direction)
    digitalWrite(2,HIGH);
    digitalWrite(3,LOW);
    digitalWrite(4,HIGH);
    digitalWrite(7,LOW);
  } else if(bt == 'B'){      //move reverse (all motors rotate in reverse direction)
    digitalWrite(2,LOW);
    digitalWrite(3,HIGH);
    digitalWrite(4,LOW);
    digitalWrite(7,HIGH);
  } else if(bt == 'L'){      //turn right (left side motors rotate in forward direction, right side motors rotate in reverse direction)
    digitalWrite(2,LOW);
    digitalWrite(3,HIGH);
    digitalWrite(4,HIGH);
    digitalWrite(7,LOW);
  } else if(bt == 'R'){      //turn left (right side motors rotate in forward direction, left side motors rotate in reverse direction)
    digitalWrite(2,HIGH);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(7,HIGH);
  } else if (bt == 'S'){      //STOP (all motors stop)
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(7,LOW);
  }

unsigned long currentMillis = millis(); // grab current time
 
 // check if "interval" time has passed (2000 milliseconds)
 if ((unsigned long)(currentMillis - previousMillis) >= interval) {
 
  //trigger a pulse-echo measurement
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  //get the result
  echotime= pulseIn(echo_pin, HIGH);
  distance= (0.0001*((float)echotime*340.0)/2.0);
  
  //send over Bluetooth 
  Serial.print("|");
  Serial.print(distance);

  int readData = DHT.read22(dataPin); // Reads the data from the sensor
  float t = DHT.temperature; // Gets the values of the temperature
  float h = DHT.humidity; // Gets the values of the humidity
  
  // Printing the results on the serial monitor
  Serial.print("|");
  Serial.print(t);
  Serial.print("|");
  Serial.print(h);

  //Read Analog pin 5 for sensor MQ 135 data
  int sensorValueMQ135 = analogRead(A3);

  //send over Bluetooth
  Serial.print("|");
  Serial.print(sensorValueMQ135);

  //Get MQ 5 sensor data
  float sensor_volt;
  float sensorValueMQ5;
  sensorValueMQ5 = analogRead(A4);
  
  
  //send over Bluetooth
  Serial.print("|");
  Serial.print(sensorValueMQ5);
  
  previousMillis = millis();
  }
}
