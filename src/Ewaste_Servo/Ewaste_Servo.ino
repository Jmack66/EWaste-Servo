#include "EWServo.h"


EWServo servo = EWServo(23, 22, 21);

void setup() {
  Serial.begin(115200);
  delay(1000);
  servo.setPIDGains(1.231, 4.138, 0.006);
  //Serial.println(servo.testMinDriveSignal());
  //Serial.println(servo.testSpeed(140));
  servo.setDrive(180,400);
  //servo.testPositionControl(90);
  //servo.calibrate(220);

}


//Simple Example that uses W and S keys to move the servo up and down
void loop() {
//  delay(2000);
//  LOGN("---60----");
//  while(!servo.write(90)){}
//  delay(2000);
//  while(!servo.write(0)){}
//  LOGN("---0---");
}
