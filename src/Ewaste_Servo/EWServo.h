#include <Wire.h>
//for now wire is included to use serial print for debug-- this can be removed so there is no library dependencies other than the arduino ones
class EWServo {
  public:
    EWServo(int in1, int in2, int out);
    void calibrate();
    bool write(int pos);
    void stop();
    void setLims(int min, int max);
    void setTolerance(int tol);
    void setFailure(int failure);
    void setSpeed(int speed);
    void setAll(int min = 0, int max = 180, int tol = 15, int failure = 5000, int speed = 300);
    //until calibrate is working these are hardcoded
    int min_analog = 0;
    int max_analog = 400;
  private:
    int input1;
    int input2;
    int feedback;
    int pot_pos;
    int servo_pos;
    int min_servo;
    int max_servo;
    int tolerance;
    int drive;
    int failure;
    void drivePos();
    void driveNeg();
    void driveStop();
    void servoDrivePos(int count);
    void servoDriveNeg(int count);
    bool checkBounds(int pos, int pot_pos);
};
