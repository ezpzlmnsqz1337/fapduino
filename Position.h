#ifndef POSITION_H
#define POSITION_H
// This is the content of the .h file, which is where the declarations go

class Position
{
private:
  int base;
  int left;
  int right;
  int grip;
  int gripRotate;

public:
  Position();

  Position(int _base, int _left, int _right, int _grip, int _gripRotate);

  int getBase();

  int getLeft();

  int getRight();

  int getGrip();

  int getGripRotate();
};

// This is the end of the header guard
#endif
