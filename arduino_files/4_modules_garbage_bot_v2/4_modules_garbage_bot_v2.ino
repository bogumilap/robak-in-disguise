#include <Servo.h>

// create servo objects to control servos
Servo servo8;
Servo servo9;  
Servo servo10;

int angle = 45;


void setup() {
  // attaches servoes on pins to the servo objects
  servo8.attach(8);
  servo9.attach(9); 
  servo10.attach(10);
}
// 90, 90, 90
// 0, 0, 90
// 0, 45, 90
// 0, 45, 135
// 90, 90, 135
// 90, 90, 90
void loop() {
  servo8.write(90);  // tell servo to go to given position
  servo9.write(90);
  servo10.write(90);

  double ratio8 = 2;  // 90 / 45
  int delay_value = 30;

  if (angle < 90)
  {
    for (int step=0; step<angle; step++) {
      servo8.write(min(90 - ratio8 * step, 0));
      servo9.write(min(90 - ratio8 * step, 0));
      delay(delay_value);
    }
    for (int step=0; step<angle; step++) {
      servo9.write(max(step, 45));
      delay(delay_value);
    }
    for (int step=0; step<angle; step++) {
      servo10.write(max(90 + step, 135));
    }
  }
}