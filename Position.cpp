#include "Position.h"

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#include "pins_arduino.h"
#include "WConstants.h"
#endif
Position::Position()
{
  this->base = 0;
  this->left = 0;
  this->right = 0;
  this->grip = 0;
  this->gripRotate = 0;
}

Position::Position(int _base, int _left, int _right, int _grip, int _gripRotate)
    : base(_base), left(_left), right(_right), grip(_grip), gripRotate(_gripRotate)
{
}

int Position::getBase()
{
  return this->base;
}

int Position::getLeft()
{
  return this->left;
}

int Position::getRight()
{
  return this->right;
}

int Position::getGrip()
{
  return this->grip;
}

int Position::getGripRotate()
{
  return this->gripRotate;
}