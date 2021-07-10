#include <Wire.h>
#include "internalPID.h"

//These are just used internally because typing out serial.println takes forever
#define LOGN(x) Serial.println(x);
#define LOG(x) Serial.print(x);
#define PLOT(name,x) {Serial.print(String(name) + ":"); Serial.print(x); Serial.print("\t");}
#define ENDPLOT() {Serial.println();}

class EWServo {
  public:
    EWServo(int in1, int in2, int out); //sets the pins 
    int* testAnalogExtremes(int drive); // automatically finds the max and min potentiometer positions
    bool write(int pos); //input is a position in degrees
    void setLims(int min, int max); //sets servo limits (defaults to 0 and 180 like most servos, but if the potentiometer 
    void setTolerance(int tol); //determines the acceptable range for a desired position
    void setAll(int min = 0, int max = 180, int tol = 8); //sets all the values in one function defaults to these values
    void drivePos(int power); //drives servo in the positive direction
    void driveNeg(int power); //drives servo in the negative direction
    int testMinDriveSignal(); //finds the minimum signal to overcome friction etc 
    void testPositionControl(int pos); //There's a weird bug in this where it will not maintain position unless its told to hold it infinitely...
    void setPIDGains(float kp = 0.1f, float ki = 0.1f, float kd = 0.1f);
    void setDriveLims(int min, int max); //sets the min and max drive signal allowed for the servo, varies dramatically based on the driver used 
    void setAnalogLims(int min, int max);
    float testSpeed(int drive); //times servo motion from a starting position to near the minimum analog
    void autoCalibrate(); //Automatically finds the minimum driving force and the potentiometer limits
    void driveStop(); //stops driving the servo
    int min_analog;
    int max_analog;
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
};
