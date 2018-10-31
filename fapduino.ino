/**
 * Controling of the robotic eezybot arm via bluetooth
 */
#include "MyServo.h"
#include <SoftwareSerial.h>

#define SP2_RX 2
#define SP2_TX 3

SoftwareSerial bluetooth(SP2_RX, SP2_TX); // 2 is RX, 3 is TX

#define servoBasePin 6
#define servoLeftPin 7
#define servoRightPin 8
#define servoGripPin 9

#define servoBasePosition 90
#define servoBaseLow 0
#define servoBaseHigh 180

#define servoLeftPosition 30
#define servoLeftLow 20
#define servoLeftHigh 80

#define servoRightPosition 100
#define servoRightLow 90
#define servoRightHigh 160

#define servoGripPosition 95
#define servoGripLow 90
#define servoGripHigh 100

MyServo servoBase(servoBasePin, servoBaseLow, servoBaseHigh, servoBasePosition);
//MyServo servoLeft(servoLeftPin, servoLeftLow, servoLeftHigh, servoLeftPosition);
//MyServo servoRight(servoRightPin, servoRightLow, servoRightHigh, servoRightPosition);
//MyServo servoGrip(servoGripPin, servoGripLow, servoGripHigh, servoGripPosition);

// controls
// 6 axes shit
#define analogXPin 0
#define analogYPin 1
#define analogSWPin 2

int analogX = 4;
int analogY = 4;
int analogSW = 1;


//rotary encoder
#define rotaryCLK 9
#define rotaryDT 11
#define rotarySW 10

volatile unsigned int rotaryPos = 0;


int pos = 0;    // variable to store the servo position
char cmd = 0;

void setup() {
  // BT module
  bluetooth.begin(9600); // Default communication rate of the Bluetooth module

  // servos

  // analog controls
  
  pinMode(analogSW, INPUT);
  digitalWrite(analogSW, HIGH);

//  //rotary
//  pinMode(rotaryCLK, INPUT); 
//  digitalWrite(rotaryCLK, HIGH);       // turn on pullup resistor
//  pinMode(rotaryDT, INPUT); 
//  digitalWrite(rotaryDT, HIGH);       // turn on pullup resistor
//  attachInterrupt(0, doEncoder, RISING); // encoder pin on interrupt 0 - pin2
  
  Serial.begin(115200);
}

void loop() {    
  //handle bluetooth
  if(bluetooth.available() > 0){ // Checks whether data is comming from the serial port
    cmd = bluetooth.read(); // Reads the data from the serial port
    handleCommand(cmd);
  }


   //show sweep 
   servoBase.sweep();
   //servoLeft.sweep();
   //servoRight.sweep();
   //servoGrip.sweep();


  // handle analog
   
  analogX = treatAnalogInputValue(analogRead(analogXPin));
  analogY = treatAnalogInputValue(analogRead(analogYPin));
  analogSW = treatAnalogInputValue(analogRead(analogSWPin)); 
  
  Serial.print("Switch:  ");
  Serial.print(analogSW);
  Serial.print("\n");
  Serial.print("X-axis: ");
  Serial.print(analogX);
  Serial.print("\n");
  Serial.print("Y-axis: ");
  Serial.println(analogY);
  Serial.print("\n\n");


  if(analogX-4 != 0){
    Serial.println("Servo: ");
    servoBase.moveBy(analogX-4);
  }

  if(analogY-4 != 0){
    //servoRight.moveBy(analogY-4);   
  }

//  // handleRotary
//  Serial.print("Position:");
//  Serial.println (rotaryPos, DEC);  //Angle = (360 / Encoder_Resolution) * rotaryPos

  delay(60);
}

void doEncoder() {
  if (digitalRead(rotaryDT)==HIGH) {
    rotaryPos++;
  } else {
    rotaryPos--;
  }
}

void handleCommand(char command){
  Serial.println(command);
  switch(command){
    case 'l':
      servoBase.moveBy(5);
      break;
    case 'r':
      servoBase.moveBy(-5);
      break;
    case 'f':
      //servoRight.moveBy(5);
      break;
    case 'b':
      //servoRight.moveBy(-5);
      break;
    case 'u':
      //servoLeft.moveBy(5);
      break;
    case 'd':
      //servoLeft.moveBy(-5);
      break;
    default:
      Serial.println("Not move!");
  }  
}

int treatAnalogInputValue(int data) {
  return (data * 9 / 1024);
}
