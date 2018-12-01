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

void MyServo::moveBy(int value)
{
  int newValue = constrain(this->pos + value, this->minimum, this->maximum);
  servo.write(newValue);
  this->pos = newValue;
}

void MyServo::moveTo(int value)
{
  servo.write(value);
  this->pos = value;
}

void MyServo::sweep()
{
  for (this->pos = minimum; this->pos <= this->maximum; this->pos += 1)
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
