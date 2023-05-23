#include <Servo.h>

// create servo objects to control servos
Servo servo8;
Servo servo9;
Servo servo10;  
bool unfolded = false;

void setup() {
  servo8.attach(8);
  servo9.attach(9);
  servo10.attach(10); 
}

void loop() {
  if (! unfolded) {
    for (int step=0; step<90; step++) {
      servo9.write(step);
      delay(30);
    }
    for (int step=180; step>90; step--) {
      servo8.write(step);
      servo10.write(step);
      delay(30);
    }
    unfolded = true;
  }
}