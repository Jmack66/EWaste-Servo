#include "EWServo.h"


//two drive input pins and the feedback pin
EWServo servo = EWServo(23, 22, 21);

void setup() {
  
  Serial.begin(115200);
  delay(1000);
  servo.setPIDGains(1.0, 3.138, 0.006); // this line is needed to define the behaviour of the controller
  servo.autoCalibrate(); //This will automatically determine the minimum drive signal needed and calibrate the limits of the potentiometer
  //to get the servo to start working these are the only two functions that need to be called
  //However, this process can also be done manually to give total control over the servo

  //servo.setDrive(180,400);
  //Serial.println(servo.testMinDriveSignal());
  //Serial.println(servo.testSpeed(140));
  
  //servo.testPositionControl(90);
  //servo.testAnalogExtremes(220);

}


//simple example
void loop() {
  delay(2000);
  while(!servo.write(180)){}
  LOGN("---180---");
  delay(2000);
  LOGN("---90----");
  while(!servo.write(90)){}
  delay(2000);
  while(!servo.write(0)){}
  LOGN("---0---");
}
