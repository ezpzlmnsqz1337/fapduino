#include "MyServo.h"

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#include "pins_arduino.h"
#include "WConstants.h"
#endif
MyServo::MyServo(int _servoPin, int _minimum, int _maximum, int _pos)
    : servoPin(_servoPin), minimum(_minimum), maximum(_maximum), pos(_pos)
{
}

void MyServo::init()
{
  servo.attach(this->servoPin);
  servo.write(this->pos);
}

int MyServo::getPosition()
{
  return this->pos;
}

void MyServo::moveBy(int value)
{
  int newValue = constrain(this->pos + value, this->minimum, this->maximum);
  servo.write(newValue);
  this->pos = newValue;
}

void MyServo::moveTo(int value)
{
  // if already there, return
  if (this->pos == value)
  {
    return;
  }

  // get value in between the servo limits
  int newValue = constrain(value, this->minimum, this->maximum);

  // increment with delay to slow down the servo movement
  int increment = newValue > this->pos ? +1 : -1;
  while (this->pos != newValue)
  {
    this->moveBy(increment);
    delay(15);
  }
  this->pos = newValue;
}

void MyServo::sweep()
{
  for (this->pos = this->minimum; this->pos <= this->maximum; this->pos += 1)
  { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo.write(this->pos); // tell servo to go to position in variable 'pos'
    delay(15);              // waits 15ms for the servo to reach the position
  }
  for (this->pos = this->maximum; this->pos >= this->minimum; this->pos -= 1)
  {                         // goes from 180 degrees to 0 degrees
    servo.write(this->pos); // tell servo to go to pos in variable 'pos'
    delay(15);              // waits 15ms for the servo to reach the pos
  }
}
