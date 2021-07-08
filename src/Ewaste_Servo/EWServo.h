#include <Wire.h>
#include "internalPID.h"

#define LOGN(x) Serial.println(x);
#define LOG(x) Serial.print(x);
#define PLOT(name,x) {Serial.print(String(name) + ":"); Serial.print(x); Serial.print("\t");}
#define ENDPLOT() {Serial.println();}

class EWServo {
  public:
    EWServo(int in1, int in2, int out);
    void testAnalogExtremes(int drive);
    bool write(int pos);
    void stop();
    void setLims(int min, int max);
    void setTolerance(int tol);
    void setFailure(int failure);
    void setSpeed(int speed);
    void setAll(int min = 0, int max = 180, int tol = 10, int speed = 300);
    void drivePos(int power);
    void driveNeg(int power);
    int testMinDriveSignal();
    void testPositionControl(int pos);
    void setPIDGains(float kp = 0.1f, float ki = 0.1f, float kd = 0.1f);
    void setDrive(int min = 170, int max = 400);
    float testSpeed(int drive);
    void driveStop();
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
    int min_drive;
    int max_drive;
    int drive;
    bool checkBounds(int pos, int pot_pos);
    unsigned int count;
    internalPID* pid;
//    
};
