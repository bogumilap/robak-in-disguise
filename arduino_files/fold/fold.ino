#include <Servo.h>

// create servo objects to control servos
Servo servo8;
Servo servo9;
Servo servo10;  
bool folded = false;

void setup() {
  servo8.attach(8);
  servo9.attach(9);
  servo10.attach(10); 
}

void loop() {
  if (! folded) {
    for (int step=90; step<180; step++) {
      servo8.write(step);
      servo10.write(step);
      delay(30);
    }
    for (int step=90; step>0; step--) {
      servo9.write(step);
      delay(30);
    }
    folded = true;
  }
}