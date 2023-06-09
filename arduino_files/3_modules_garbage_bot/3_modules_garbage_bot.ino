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

  // these ratios work only for angle = 45
  double ratio8 = 2;  // 90 / 45
  double ratio9 = 3.5;  // (90 + 45 + 22.5) / 45

  if (angle < 90)
  {
    for (int step=0; step<angle; step++) {  // servo8 is going up
      servo8.write(max(90 - ratio8 * step, 0));
      servo9.write(90 - step);
      delay(10);  // waits 25ms for the servos to reach positions
    }
    for (int step=0; step<angle; step++) {  // servo8 is going down
      servo8.write(min(ratio8 * step, 90));
      servo9.write(angle + step);
      delay(10);
    }
    for (int step=0; step<angle; step++) {  // servo9 is going up
      servo8.write(90 + step);
      servo9.write(90 + ratio9 * step); 
      delay(10); 
    }
    for (int step=0; step<angle; step++) {  // servo9 is going down
      servo8.write(90 + angle - step);
      servo9.write(max(90 + angle + 90 + angle / 2 - ratio9 * step, 90)); 
      delay(10);
    }
  }
}