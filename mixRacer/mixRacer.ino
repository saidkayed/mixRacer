// ConstantSpeed.pde
// -*- mode: C++ -*-
//
// Shows how to run AccelStepper in the simplest,
// fixed speed mode with no accelerations
/// \author  Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2009 Mike McCauley
// $Id: ConstantSpeed.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $

#include <AccelStepper.h>
#include <Servo.h>

//NodeMcu Rx Tx
#include <SoftwareSerial.h>

SoftwareSerial s(1,0);
//Servo
Servo servo;
int servoAngle;
String line = "";
boolean isRight;
boolean isLeft;
boolean isStraight = true;

//Stepper
AccelStepper stepper1(4, 2, 3, 4, 5); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
AccelStepper stepper2(4, 10, 11, 12, 13);
boolean isForward;
boolean isReverse;
int speed = 300;

//Sensor
const int trigPin = 8;
const int echoPin = 9;

long duration;
int distance;

bool dist = false;


void setup()
{
  s.begin(9600);

 //Servo
  servo.attach(7);
  delay(2000);

  //Stepper
  //Serial.begin(9600);

  //Sensor
  pinMode(trigPin, OUTPUT); //Sets trigPin as output
  pinMode(echoPin, INPUT); //Sets echoPin as input
  
}

void loop()
{
  while (true) {
    
    if (s.available() > 0) {
      char c = s.read();
      if (c == '\n') break;
      line += c;
      s.println("loop " + line);
    }

  sensorDistance();

    //Get action
    if (line == "ON"|| line == "o") {
      line = "";
      isForward = true;
      isReverse = false;
    }

    if (line == "OFF" || line == "f") {
      line = "";
      isForward = false;
      isReverse = false;
    }

    if (line == "BACK" || line == "b") {
      line = "";
      isForward = false;
      isReverse = true;
    }
    //servo
    if (line == "RIGHT" || line == "r") {
      line = "";
      isRight = true;
      isLeft = false;
       isStraight = false;
    
    }
    if (line == "LEFT" || line == "l") {
      line = "";
      isRight = false;
      isLeft = true;
       isStraight = false;
    }
    if(line == "STRAIGHT"|| line == "s"){
      line = "";
      isRight = false;
      isLeft = false;
      isStraight = true;
    }


    //Perform action
    if (isForward && !isReverse) 
    {
      runMotor();
    }
    if (!isForward  && !isReverse)
    {
      stopMotor();
    }
    if (isReverse) {
      reverse();
    }
    if (!isRight && isLeft) 
    {
      turnLeft();
    }
    if(isRight && !isLeft)
    {
      turnRight();
    }
    if(isStraight)
    {
      goStraight();
    }
    
  }
  
}

//Methods
void runMotor()
{
  stepper1.setMaxSpeed(1000);
  stepper1.setSpeed(-speed);
  stepper1.runSpeed();

  stepper2.setMaxSpeed(1000);
  stepper2.setSpeed(speed);
  stepper2.runSpeed();
}

void stopMotor() {
  stepper1.stop();
  stepper2.stop();
}

void reverse() {
  stepper2.setMaxSpeed(1000);
  stepper2.setSpeed(-speed);
  stepper2.runSpeed();

  stepper1.setMaxSpeed(1000);
  stepper1.setSpeed(speed);
  stepper1.runSpeed();
}

void turnLeft() {
  servo.write(0);
}

void turnRight(){
  servo.write(40);
}

void goStraight(){
  servo.write(20);
}

void sensorDistance(){
  if(dist){
    //Sensor
  //Clears trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance = duration*0.034/2;
// Prints the distance on the Serial Monitor
//Serial.print("Distance: ");
//Serial.println(distance);
}
}
