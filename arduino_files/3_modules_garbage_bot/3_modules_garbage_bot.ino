#include <Servo.h>

Servo myservo;  // create servo object to control a servo
Servo second;
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int angle = 45;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  second.attach(8);
}

void loop() {
  // pos = - angle;
  myservo.write(90);              // tell servo to go to position in variable 'pos'

  second.write(90);
  if (angle < 90)
  {
    // for (pos = 90 - angle; pos <= 90 + angle; pos += 1) { // goes from 0 degrees to 180 degrees
    //   // in steps of 1 degree
    //   myservo.write(pos);              // tell servo to go to position in variable 'pos'
    //   second.write(pos);
    //   delay(25);                       // waits 15ms for the servo to reach the position
    // }
    // for (pos = 90 + angle; pos >= 90 - angle; pos -= 1) { // goes from 180 degrees to 0 degrees
    //   myservo.write(pos);              // tell servo to go to position in variable 'pos'
    //   second.write(pos);
    //   delay(25);                       // waits 15ms for the servo to reach the position
    // }
}
}