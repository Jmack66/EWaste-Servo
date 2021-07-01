#include "EWServo.h"
#define SPEED 300
#define TOL 15
#define FAILURE 50000

EWServo::EWServo(const int in1, const int in2, const int out) {
  input1 = in1;
  input2 = in2;
  feedback = out;
  pinMode(input1, OUTPUT);
  pinMode(input2, OUTPUT);
  pinMode(feedback, INPUT);

}

void EWServo::setLims(const int min, const int max){
	min_servo = min;
	max_servo = max;
}

void EWServo::calibrate() {
	/*
	pot_pos = analogRead(feedback);
	int err = 0 - pot_pos;
	while(!(ISCLOSE(err,0,TOL))){
		pot_pos = analogRead(feedback);
		err = 0 - pot_pos;
		drivePos();
		Serial.println(pot_pos);
	}
	delay(1000);
	err = 400 - pot_pos;
	while(!(ISCLOSE(err,0,TOL))){
		pot_pos = analogRead(feedback);
		err = 400 - pot_pos;
		driveNeg();
		Serial.println(pot_pos);
	}*/
}
//TO DO: MAP Inputs from pot positions to 0 to 180 deg

bool EWServo::write(int pos){
	if(pos <= min_servo + TOL || pos >= max_servo - TOL){
		driveStop();
		Serial.println("ERROR: Position request out of bounds");
		return false;
	}
	int count = 0;
	bool target = false;
	while(!target){
		count++;
		pot_pos = analogRead(feedback);
		Serial.println(pot_pos);
		if(pot_pos < pos + TOL && pot_pos > pos - TOL){
			target = true;
			Serial.println("TARGET");
			driveStop();
			return target;
		}
	if(pot_pos < pos){
		drivePos();
		if(count % 4 == 0){driveStop();}
	}
	if(pot_pos > pos){
		driveNeg();
		if(count % 4 == 0){driveStop();}		
	}
	if(count > FAILURE){
		write(200);
		//Temporary fix to prevent servo from getting stuck 
		while(1){
			Serial.println("Failed: returning to home");
		}
	}
	}
driveStop();
}


void EWServo::stop(){
driveStop();
}

void EWServo::drivePos() {
  digitalWrite(input2, LOW);
  analogWrite(input1, SPEED);
}

void EWServo::driveStop(){
    digitalWrite(input1, LOW);
  analogWrite(input2, 0);
 }

void EWServo::driveNeg() {
  digitalWrite(input1, LOW);
  analogWrite(input2, SPEED);
}
