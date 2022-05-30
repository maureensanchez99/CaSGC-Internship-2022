/*
 *  Track Robot w/ Arduino Mega 2560, motor shield v3, OLED, and Sharp IR sensors
 *  1-19-2020
 *  by My Parts Chest
 *  https://mypartschest.com
 *  https://mypartschest.blogspot.com/
*/

#include <SharpIR.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SHARP_MODEL 1080 

//global vars
bool startup = false;
bool firstLoop = false;
bool motorsOn = false;
int stopTimer = 0;
String heading = "Unstarted";

//declar OLED pins
const int SDA_PIN = 20;
const int SDC_PIN = 21;

//Declare pins for motor control
const int dirA = 13;
const int dirB = 12;
const int speedA = 11;
const int speedB = 3;
const int brakeA = 8;
const int brakeB = 9;
const int highSpeed = 255;
const int lowSpeed = 240;

// Analog pins for distance sensors
const byte frontSensorPin = A0;
const byte driverSensorPin = A1;
const byte passengerSensorPin = A2;
const byte rearSensorPin = A3;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Create an object instance of the SharpDistSensor class
SharpIR frontSensor = SharpIR(frontSensorPin, SHARP_MODEL);
SharpIR driverSensor = SharpIR(driverSensorPin, SHARP_MODEL);
SharpIR passengerSensor = SharpIR(passengerSensorPin, SHARP_MODEL);
SharpIR rearSensor = SharpIR(rearSensorPin, SHARP_MODEL);


void fullStop(int duration)
{
    move("A", "FWD", 0);
    move("B", "FWD", 0);   
    delay(duration);
}

void turnRight(int duration)
{
    move("A", "FWD", highSpeed);
    move("B", "REV", highSpeed);
    delay(duration);
}

void turnLeft(int duration)
{
    move("A", "REV", highSpeed);
    move("B", "FWD", highSpeed);
    delay(duration);
}

void move(String channel, String direction, int speed )
{
  int motor = dirA;
  int pwm = speedA;
  int brake = brakeA;
  bool highLow = HIGH;

  if (motorsOn)
  {
    if (direction == "REV")
      highLow = LOW;
      
    if (channel == "B")
    {
      motor = dirB;
      pwm = speedB;
      brake = brakeB;
      //reverse directions for motor B
      highLow = !highLow;
    }
  
    if (speed == 0) //brake
    {
      digitalWrite(brake, HIGH);
    }
    else
    {
      digitalWrite(motor, highLow);
      digitalWrite(brake, LOW);
      analogWrite(pwm, speed);
    }    
  }
}

void updateDisplay(int fd, int dd, int pd, int rd, String hd)
{
  //write to OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Sensor Readings");
  display.setCursor(0, 5);
  display.print("...............");  
  
  // Display sensor readings
  display.setCursor(0, 16);
  display.print("Front: ");
  display.setCursor(45, 16);
  display.print(fd);
  display.print(" cm");
  
  display.setCursor(0, 26);  
  display.print("Left: ");
  display.setCursor(45, 26);  
  display.print(dd);
  display.print(" cm");
  
  display.setCursor(0, 36);  
  display.print("Right: ");
  display.setCursor(45, 36);  
  display.print(pd);
  display.print(" cm");  
  
  display.setCursor(0, 46);  
  display.print("Rear: ");
  display.setCursor(45, 46);  
  display.print(rd);
  display.print(" cm");  

  display.setCursor(0, 56);  
  display.print("Moving: ");
  display.setCursor(45, 56);  
  display.print(hd);  
  
  display.display(); 
}

void setup() {

  // Setup Channel A & B
  pinMode(dirA, OUTPUT); //Init Motor A (rear-driver's side)
  pinMode(dirB, OUTPUT); //Init Motor B (front-passenger's side)
  pinMode(brakeA, OUTPUT); //Init Brake A
  pinMode(brakeB, OUTPUT); //Init Brake B

  // Init display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  // Display static text
  display.println("Initializing...");
  display.display(); 
  
  delay(1000);
  startup = false;
  firstLoop = true;
  motorsOn = true;
}

void loop() {

  //local vars  
  int frontDistance;
  int driverDistance;
  int passengerDistance;
  int rearDistance;
  
  // Get distance from sensors
  frontDistance = frontSensor.getDistance();
  driverDistance = driverSensor.getDistance();
  passengerDistance = passengerSensor.getDistance();
  rearDistance = rearSensor.getDistance();

  //update OLED
  updateDisplay(frontDistance, driverDistance, passengerDistance, rearDistance, heading);

  if (startup)
  {      
    if (frontSensor.getDistance() > 30)
    {
      firstLoop = false;
      heading = "Forward";

      //forward B (front motor)
      move("B", "FWD", highSpeed);            
      //forward A (rear motor)
      move("A", "FWD", lowSpeed); //rear motor is running a little faster than the front motor; so slow it down

      delay(100);
      stopTimer = 0;
    }
    else //less than 30cm; something is in the way
    {
      if (heading == "Forward" && !firstLoop) //make sure this isn't at startup and I'm not already turning
      {
        fullStop(100); //stop during testing to read sensors

        //back up if too close to something
        if (frontSensor.getDistance() < 10)
        {
          //forward B (front motor)
          move("B", "REV", highSpeed);                
          //forward A (rear motor)
          move("A", "REV", lowSpeed); 
          delay(100);          
        }
                  
        if (passengerSensor.getDistance() > driverSensor.getDistance()) //what has more distance, left or right?
        {
          heading = "Turning Right";
          int lastFront = frontSensor.getDistance();
          
          while (driverSensor.getDistance() != lastFront)
          {
            updateDisplay(frontDistance, driverDistance, passengerDistance, rearDistance, heading);
            turnRight(500);
            if (frontSensor.getDistance() > 30)
            {
              break;      
            }         
          }
        }
        else
        {
          heading = "Turning Left";
          int lastFront = frontSensor.getDistance();
          
          while (passengerSensor.getDistance() != lastFront)
          {
            updateDisplay(frontDistance, driverDistance, passengerDistance, rearDistance, heading);
            turnLeft(500);
            if (frontSensor.getDistance() > 30)
            {
              break;      
            }              
          }
        }                      
      }
      else
      {
        stopTimer++;
        if (stopTimer > 100)
        {
          heading = "Stopped";
          fullStop(100);
          //display stopped
          updateDisplay(frontDistance, driverDistance, passengerDistance, rearDistance, "Stopped!");
          exit(0);
        }        
      }
    }
  }
  else //loop forever until I put my hand in front of the forward sensor
  {
    if (frontDistance < 11)
      {
        delay(1000);
        startup = true;
    }
    else
    {
      delay(20);
    }
  }
}
