#include <Servo.h>

// create servo objects to control servos
Servo servo8;
Servo servo9;  

int angle = 45;


void setup() {
  // attaches servoes on pins to the servo objects
  servo8.attach(8);
  servo9.attach(9); 
}

void loop() {
  servo8.write(90);  // tell servo to go to given position
  servo9.write(90);

  double ratio8 = 2;  // 90 / 45
  int delay_value = 20;

  if (angle < 90)
  {
    for (int step=0; step<angle; step++) {
      servo8.write(max(90 - ratio8 * step, 0));
      servo9.write(min(90 + ratio8 * step, 180));
      delay(delay_value);
    }
    for (int step=0; step<angle; step++) {
      servo9.write(180 - 2 * step);
      // servo8.write(2 * step);
      delay(delay_value);
    }
    for (int step=0; step<angle; step++) {
      servo8.write(2 * step);
      // servo9.write(180 - 2 * step);
      delay(delay_value);
    }
  }
}