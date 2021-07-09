#include "EWServo.h"

EWServo::EWServo(int in1, int in2, int out) {
  input1 = in1;
  input2 = in2;
  feedback = out;
  pinMode(input1, OUTPUT);
  pinMode(input2, OUTPUT);
  pinMode(feedback, INPUT);
  this->setAll();
}

void EWServo::setLims(int min, int max) {
  min_servo = min;
  max_servo = max;
}

void EWServo::setSpeed(int speed) {
  drive = speed;
}

void EWServo::setTolerance(int tol) {
  tolerance = tol;
}

void EWServo::setAll(int min, int max, int tol, int speed) {
  setLims(min, max);
  setSpeed(speed);
  setTolerance(tol);
}

//sets the gains of the internal PID
void EWServo::setPIDGains(float kp, float ki, float kd) {
  pid = new internalPID(kp, ki, kd);
}

void EWServo::setDrive(int min, int max) {
  pid->setSaturation(min, max);
}

void EWServo::autoCalibrate(){
   int min_d = testMinDriveSignal() + 30; // +30 is a buffer to ensure motion
   int *ex = testAnalogExtremes(min_d + 50);
   max_analog = *(ex);
   min_analog = *(ex+1);
   setDrive(min_d ,min_d + 150);
}


int* EWServo::testAnalogExtremes(int drive) {
  //drive for a little check if the change in pot is meaningful then go the same in the other direction
  bool min_found = false;
  bool max_found = false;
  int extremes[2];
  while (!min_found || !max_found) {
    driveStop();
    float start = micros() / 1000000.0f;
    float current = 0.0f;
    int start_pos = analogRead(feedback);
    //delay(1000);
    while (current - start < 0.5f) {
      pot_pos = analogRead(feedback);
      current = micros() / 1000000.0f;
      if (min_found) {
        drivePos(drive);
      } else {
        driveNeg(drive);
      }
    }
    //from testing a change of 6 is only possible if the servo has moved enough
    if (abs(start_pos - pot_pos) < 6) {
      if (min_found) {
        max_found = true;
        extremes[0] = pot_pos;
      } else {
        delay(1000);
        min_found = true;
        extremes[1] = pot_pos;
      }
    }
  }
  driveStop();
  LOGN("Max pot pos: " + String(max_analog));
  LOGN("Min pot pos: " + String(min_analog));
  return extremes;
}

//There's a weird bug in this where it will not maintain position unless its told to hold it infinitely...
void EWServo::testPositionControl(int pos) {
  int hits = 0;
  while (hits < 100) {
    float current = micros() / 1000000.0f;
    Serial.print(current, 5);
    LOG(",");
    LOGN(analogRead(feedback));
    if (write(pos)) {
      hits++;
    }
  }
  write(pos);
  LOGN("TEST COMPLETE");
}

int EWServo::testMinDriveSignal() {
  int start_pos = analogRead(feedback);
  pot_pos = start_pos;
  int i = 0;
  while (abs(start_pos - pot_pos) < 10) {
    i++;
    pot_pos = analogRead(feedback);
    driveNeg(i);
    delay(100);
  }
  driveStop();
  LOGN("Minimum drive signal of: " + String(i));
  min_drive = i + 20; //plus 20 is a buffer to ensure drive will always move the servo
  return i;
}

float EWServo::testSpeed(int drive) {
  // delay(1000);
  float start = micros() / 1000000.0f;
  float current = 0.0f;
  pot_pos = analogRead(feedback);
  int start_pos = pot_pos;
  while (pot_pos > 5) {
    digitalWrite(input1, LOW);
    pot_pos = analogRead(feedback);
    analogWrite(input2, drive);
    current = micros() / 1000000.0f;
  }
  //  LOGN("From " + String(start_pos));
  //  LOG("Rotation took(seconds): ");
  //  Serial.println(current - start, 9);
  driveStop();
  return current - start;
}

//Takes in a position in degrees
//Position gets mapped to the potentiometer scale and the PID loop runs until the servo reaches the desired position
bool EWServo::write(int pos) {
  pot_pos = analogRead(feedback);
  pos = map(pos, min_servo, max_servo, min_analog + tolerance, max_analog - tolerance);
  if (checkBounds(pos, pot_pos)) {
    return false;
  }
  if (pot_pos < pos + tolerance && pot_pos > pos - tolerance) {
    driveStop();
    pid->clearIntegral();
    return true;
  }
  pid->setSetpoint(pos);
  auto out = pid->update(pot_pos);
  LOGN(out);
  if (out < 0) {
    driveNeg(abs(out));
  }
  if (out > 0) {
    drivePos(abs(out));
  }
  //driveStop();
  return false;
}

//Checks if the position request is within the servos range
bool EWServo::checkBounds(int pos, int pot_pos) {
  if (pos < min_analog + tolerance || pos > max_analog - tolerance) {
    driveStop();
    Serial.println("ERROR: Position request out of bounds");
    return true;
  } else {
    return false;
  }
}

//drives the Servo in the positive direction
void EWServo::drivePos(int power) {
  digitalWrite(input2, LOW);
  analogWrite(input1, power);
}

//drives the Servo in the negative direction
void EWServo::driveStop() {
  digitalWrite(input1, LOW);
  analogWrite(input2, 0);
}

void EWServo::driveNeg(int power) {
  digitalWrite(input1, LOW);
  analogWrite(input2, power);
}
