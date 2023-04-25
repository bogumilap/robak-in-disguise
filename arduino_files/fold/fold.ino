#include <Servo.h>

// create servo objects to control servos
Servo servo8;
Servo servo9;
Servo servo10;  

// int angle = 45;


void setup() {
  // attaches servoes on pins to the servo objects
  servo8.attach(8);
  servo9.attach(9);
  servo10.attach(10); 
}

void loop() {
  servo8.write(180);  // tell servo to go to given position
  servo9.write(0);
  servo10.write(180);

  // double ratio8 = 2;  // 90 / 45


}