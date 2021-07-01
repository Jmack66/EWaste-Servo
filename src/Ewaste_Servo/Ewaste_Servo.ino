#include "EWServo.h"

EWServo servo = EWServo(23,22,21);

void setup() {
Serial.begin(115200);
servo.max_analog = 400;
}

//Simple Example that uses W and S keys to move the servo up and down
void loop() {
  int val = 0;
  int spos = 200;
  while (val != 'z') {
    if (Serial.available()) {
      val = Serial.read();// then read the serial value
      if(val == 'w'){
	spos += 60;
      }
      if(val == 's'){
	spos -= 60;
      }
    }
    servo.write(spos);
} 
}
