#include <Wire.h>
//for now wire is included to use serial print for debug-- this can be removed so there is no library dependencies other than the arduino ones 
class EWServo{
  public:
    EWServo(const int in1, const int in2, const int out);
    void calibrate();
    bool write(int pos);
    void stop();  
    void setLims(const int min, const int max);
  private:
    int input1;
    int input2;
    int feedback;
    int pot_pos;
    int servo_pos;
    int min_servo; 
    int max_servo;
    void drivePos();
    void driveNeg();
    void driveStop();
 
 };
