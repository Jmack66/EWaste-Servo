#include "EWServo.h"


EWServo::EWServo(int in1, int in2, int out) {
  input1 = in1;
  input2 = in2;
  feedback = out;
  pinMode(input1, OUTPUT);
  pinMode(input2, OUTPUT);
  pinMode(feedback, INPUT);
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


void EWServo::setFailure(int failure) {
  failure = 50000;
}

void EWServo::setAll(int min, int max, int tol, int failure, int speed) {
  setLims(min, max);
  setSpeed(tol);
  setTolerance(failure);
  setFailure(speed);
}

void EWServo::calibrate() {

}

bool EWServo::write(int pos) {
  pot_pos = analogRead(feedback);
  pos = map(pos, min_servo, max_servo, min_analog, max_analog);
  if (checkBounds(pos, pot_pos)) {
    return false;
  }
  int count = 0;
  while (pot_pos < pos + tolerance && pot_pos > pos - tolerance) {
    count++;
    pot_pos = analogRead(feedback);
    if (pot_pos < pos) {
      servoDrivePos(count);
    } else if (pot_pos > pos) {
      servoDriveNeg(count);
    }
    if (count > failure) {
      write(200);
      //Temporary fix to prevent servo from getting stuck
    }
  }
  driveStop();
  return true;
}

bool EWServo::checkBounds(int pos, int pot_pos) {
  if (pos <= min_servo + tolerance || pos >= max_servo - tolerance || pot_pos + tolerance > max_analog || pot_pos - tolerance < min_analog) {
    driveStop();
    Serial.println("ERROR: Position request out of bounds");
    return false;
  } else {
    return true;
  }
}


void EWServo::stop() {
  driveStop();
}

void EWServo::servoDrivePos(int count) {
  drivePos();
  if (count % 4 == 0) {
    driveStop();
  }
}

void EWServo::servoDriveNeg(int count) {
  driveNeg();
  if (count % 4 == 0) {
    driveStop();
  }
}

void EWServo::drivePos() {
  digitalWrite(input2, LOW);
  analogWrite(input1, drive);
}

void EWServo::driveStop() {
  digitalWrite(input1, LOW);
  analogWrite(input2, 0);
}

void EWServo::driveNeg() {
  digitalWrite(input1, LOW);
  analogWrite(input2, drive);
}
