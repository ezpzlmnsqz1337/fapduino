// This is start of the header guard.  ADD_H can be any unique name.  By convention, we use the name of the header file.
#ifndef MY_SERVO_H
#define MY_SERVO_H
 


#include <Servo.h>

// This is the content of the .h file, which is where the declarations go

class MyServo{
  private:  
    int minimum;
    int maximum;
    int pos;
    int servoPin;
    Servo servo;
    
  public:
    MyServo(int _servoPin, int _minimum, int _maximum, int _pos);

    void init();
  
    void moveBy(int value);
  
    void sweep();
};


// This is the end of the header guard
#endif
