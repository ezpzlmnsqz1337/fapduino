/**
 * Controling of the robotic eezybot arm via bluetooth
 */
#include "MyServo.h"
#include "Position.h"
#include <SoftwareSerial.h>

#define MAX_SAVED_POSITIONS 5

Position positions[MAX_SAVED_POSITIONS] = {
    Position(0, 0, 0, 0, 0),
    Position(0, 0, 0, 0, 0),
    Position(0, 0, 0, 0, 0),
    Position(0, 0, 0, 0, 0),
    Position(0, 0, 0, 0, 0)};

#define SP2_RX 2
#define SP2_TX 3

SoftwareSerial bluetooth(SP2_RX, SP2_TX); // 2 is RX, 3 is TX

#define servoBasePin 6
#define servoLeftPin 7
#define servoRightPin 8
#define servoGripPin 9
#define servoGripRotatePin 10

#define servoBasePosition 90
#define servoBaseLow 0
#define servoBaseHigh 180

#define servoLeftPosition 30
#define servoLeftLow 20
#define servoLeftHigh 100

#define servoRightPosition 100
#define servoRightLow 90
#define servoRightHigh 160

#define servoGripPosition 95
#define servoGripLow 0
#define servoGripHigh 180

#define servoGripRotatePosition 90
#define servoGripRotateLow 0
#define servoGripRotateHigh 180

MyServo servoBase(servoBasePin, servoBaseLow, servoBaseHigh, servoBasePosition);
MyServo servoLeft(servoLeftPin, servoLeftLow, servoLeftHigh, servoLeftPosition);
MyServo servoRight(servoRightPin, servoRightLow, servoRightHigh, servoRightPosition);
MyServo servoGrip(servoGripPin, servoGripLow, servoGripHigh, servoGripPosition);
MyServo servoGripRotate(servoGripRotatePin, servoGripRotateLow, servoGripRotateHigh, servoGripRotatePosition);

// controls
// 6 axes shit

#define analog1YPin 0
#define analog1XPin 1
#define analog1SWPin 4

#define analog2YPin 2
#define analog2XPin 3
#define analog2SWPin 5

int analog1X = 4;
int analog1Y = 4;
int analog1SW = 1;

int analog2X = 4;
int analog2Y = 4;
int analog2SW = 1;
int analog2SWflag = 0;

int cmd = 0;

// if palying a sequence or not
bool playing = false;
int savedPositions = 0;

void setup()
{
  // BT module
  bluetooth.begin(9600); // Default communication rate of the Bluetooth module

  // servos
  servoBase.init();
  servoLeft.init();
  servoRight.init();
  servoGrip.init();
  servoGripRotate.init();

  // analog controls

  pinMode(analog1SWPin, INPUT);
  digitalWrite(analog1SWPin, HIGH);

  pinMode(analog2SWPin, INPUT);
  digitalWrite(analog2SWPin, HIGH);

  Serial.begin(57600);

  // initialize array
  clearPositions();
}

void loop()
{
  //handle bluetooth
  if (bluetooth.available() > 0)
  {
    Serial.write("Yes");    // Checks whether data is comming from the serial port
    cmd = bluetooth.read(); // Reads the data from the serial port
    handleCommand(cmd);
  }
  if (!playing)
  {

    //show sweep
    // servoBase.sweep();
    // servoLeft.sweep();
    // servoRight.sweep();
    // servoGrip.sweep();
    // servoGripRotate.sweep();

    // handle analog

    analog1X = treatAnalogInputValue(analogRead(analog1XPin), 4);
    analog1Y = treatAnalogInputValue(analogRead(analog1YPin), 4);
    analog1SW = digitalRead(analog1SWPin);

    analog2X = treatAnalogInputValue(analogRead(analog2XPin), 12);
    analog2Y = treatAnalogInputValue(analogRead(analog2YPin), 4);
    analog2SW = digitalRead(analog2SWPin);

    if (analog1X != 0)
    {
      servoBase.moveBy(analog1X);
    }

    if (analog1Y != 0)
    {
      servoLeft.moveBy(analog1Y);
    }

    if (analog2X != 0)
    {
      servoGripRotate.moveBy(analog2X);
    }

    if (analog2Y != 0)
    {
      servoRight.moveBy(analog2Y);
    }

    // grip
    if (analog2SW == LOW)
    {
      if (analog2SWflag == 0)
      {
        servoGrip.moveTo(60);
        analog2SWflag = 1;
      }
      else if (analog2SWflag == 1)
      {
        servoGrip.moveTo(160);
        analog2SWflag = 0;
      }
    }

    delay(60);
  }
}

void handleCommand(char command)
{
  Serial.write("BT command: ");
  Serial.write(command);
  Serial.write("\r\n");
  switch (command)
  {
  case 'l':
    servoBase.moveBy(5);
    break;
  case 'r':
    servoBase.moveBy(-5);
    break;
  case 'f':
    servoRight.moveBy(5);
    break;
  case 'b':
    servoRight.moveBy(-5);
    break;
  case 'u':
    servoLeft.moveBy(5);
    break;
  case 'd':
    servoLeft.moveBy(-5);
    break;
  case 'o':
    servoGrip.moveBy(5);
    break;
  case 'c':
    servoGrip.moveBy(-5);
    break;
  case 'q':
    servoGripRotate.moveBy(5);
    break;
  case 'e':
    servoGripRotate.moveBy(-5);
    break;
  case 'p':
    // play
    play();
    break;
  case 's':
    //save
    savePosition();
    break;
  case 'i':
    //stop plaing
    stop();
    break;
  default:
    Serial.println("Not move!");
  }
}

int treatAnalogInputValue(int data, int speed)
{
  return map(data, 0, 1024, -speed, speed);
}

void savePosition()
{
  positions[savedPositions] = Position(servoBase.getPosition(),
                                       servoLeft.getPosition(),
                                       servoRight.getPosition(),
                                       servoGrip.getPosition(),
                                       servoGripRotate.getPosition());
  savedPositions++;
}

void play()
{
  playing = true;
  for (int i = 0; i < savedPositions; i++)
  {
    Position pos = positions[i];
    servoBase.moveTo(pos.getBase());
    servoLeft.moveTo(pos.getLeft());
    servoRight.moveTo(pos.getRight());
    servoGrip.moveTo(pos.getGrip());
    servoGripRotate.moveTo(pos.getGripRotate());
    Serial.write("Position: ");
    Serial.write(i);
    Serial.write("\r\n");
    delay(1000);
  }
}

void stop()
{
  playing = false;
}

void clearPositions()
{
  for (int i = 0; i < MAX_SAVED_POSITIONS; i++)
  {
    positions[i] = Position(0, 0, 0, 0, 0);
  }
  savedPositions = 0;
}