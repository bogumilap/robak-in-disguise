#include <Servo.h>

// create servo objects to control servos
Servo servo8;
Servo servo9;  

// int angle = 45;


void setup() {
  // attaches servoes on pins to the servo objects
  servo8.attach(8);
  servo9.attach(9); 
}

void loop() {
  servo8.write(90);  // tell servo to go to given position
  servo9.write(90);

  // double ratio8 = 2;  // 90 / 45


}