#include <Servo.h>

// create servo objects to control servos
Servo servo8;
Servo servo9;
Servo servo10; 

int angle = 45;
int move_max = 5;
int moves = 0; 
int base_angle = 90;


void setup() {
  // attaches servoes on pins to the servo objects
  servo8.attach(8);
  servo9.attach(9);
  servo10.attach(10);  
}

void loop() {
  servo8.write(90);  // tell servo to go to given position
  servo9.write(90);

  // these ratios work only for angle = 45
  double ratio8 = 2;  // 90 / 45
  double ratio9 = 3.5;  // (90 + 45 + 22.5) / 45

  if (angle < 90)
  {

      // one second - arm 1
      for (int step=0; step<50; step++) {  // servo8 is going up
        servo8.write(base_angle + step);
        delay(10); 
      }
      for (int step=49; step>=0; step--) {  // servo8 is going up
        servo8.write(base_angle + step);
        delay(10); 
      }

      // 1 s - arm 2
      for (int step=0; step<50; step++) {  // servo8 is going up
        servo10.write(base_angle + step);
        delay(10); 
      }
      for (int step=49; step>=0; step--) {  // servo8 is going up
        servo10.write(base_angle + step);
        delay(10); 
      }

      // 1 s - /\/\ ...
      for (int step=0; step<angle; step++) {  // servo8 is going up
        servo8.write(base_angle - 2 * step);
        servo9.write(base_angle - 2 * step);
        servo10.write(base_angle - 2 * step);
        delay(11); 
      }
      delay(5);
      for (int step=angle - 1; step>=0; step--) {  // servo8 is going up
        servo8.write(base_angle - 2 * step);
        servo9.write(base_angle - 2 * step);
        servo10.write(base_angle - 2 * step);
        delay(11); 
      }
      delay(5);

      // 1 s - \_/
      for (int step=0; step<50; step++) {  // servo8 is going up
        servo8.write(base_angle + step);
        servo10.write(base_angle + step);
        delay(10); 
      }
      for (int step=49; step>=0; step--) {  // servo8 is going up
        servo8.write(base_angle + step);
        servo10.write(base_angle + step);
        delay(10); 
      }

      // 4 s - arm 1, 2 up, down
      for (int step=0; step<50; step++) {  // servo8 is going up
        servo8.write(base_angle + step);
        delay(20); 
      }
      for (int step=0; step<50; step++) {  // servo8 is going up
        servo10.write(base_angle + step);
        delay(20); 
      }
      for (int step=49; step>=0; step--) {  // servo8 is going up
        servo10.write(base_angle + step);
        delay(20); 
      }
      for (int step=49; step>=0; step--) {  // servo8 is going up
        servo8.write(base_angle + step);
        delay(20); 
      }

      for(int g = 0; g < 2; g++){
        // sum = 2s 
        // 0.5s - /\_
        for (int step=0; step<angle; step++) {  // servo8 is going up
          servo8.write(base_angle + 2 * step);
          servo9.write(base_angle + step);
          delay(11); 
        }
        delay(5);

        // 0.5s - /\/\ ...
        for (int step=0; step<angle; step++) {  // servo8 is going up
          servo10.write(base_angle + 2 * step);
          servo9.write(base_angle + angle + step);
          delay(11); 
        }
        delay(5);

        // 0.5s - /\_
        for (int step=angle - 1; step<=0; step--) {  // servo8 is going up
          servo8.write(base_angle - 2 * step);
          servo9.write(base_angle + angle - step);
          delay(11); 
        }
        delay(5);
        // 0.5s - ____
        for (int step=angle - 1; step<=0; step--) {  // servo8 is going up
          servo8.write(base_angle - 2 * step);
          servo9.write(base_angle - step);
          delay(11); 
        }
        delay(5);


        // fold - 4s
        for (int step = 0; step < angle; step++){
          servo8.write(base_angle + 2 * step);
          servo10.write(base_angle + 2 * step);
          delay(44); 
        }
        delay(20);
        for (int step = 0; step < angle; step++){
          servo9.write(base_angle - 2 * step);
          delay(44); 
        }
        delay(20);

        // unfold - 4s
        for (int step = 0; step < angle; step++){
          servo9.write(base_angle + 2 * (angle - step - 1));
          delay(44); 
        }
        delay(20);
        for (int step = 0; step < angle; step++){
          servo8.write(base_angle - 2 * (angle - step - 1));
          servo10.write(base_angle - 2 * (angle - step - 1));
          delay(44); 
        }
        delay(20);


        // fala - 6 s

        // /\_ - 1s
        for (int step=0; step<angle; step++) {  // servo8 is going up
          servo8.write(base_angle + 2 * step);
          servo9.write(base_angle + step);
          delay(22); 
        }
        delay(10);
        for(int i = 0; i < 2; i++){ // loop - 2s 
        // _/\ - 1 s 
          for (int step=0; step<angle; step++) {  // servo8 is going up
            servo10.write(base_angle + 2 * step);
            servo8.write(base_angle + 2 * (angle - step - 1));
            delay(22); 
          }
          delay(10);
          for (int step=0; step<angle; step++) {  // servo8 is going up
            servo8.write(base_angle + 2 * step);
            servo10.write(base_angle + 2 * (angle - step - 1));
            delay(22); 
          }
          delay(10);
        }
        for (int step=0; step<angle; step++) {  // servo8 is going up
            servo8.write(base_angle + 2 * (angle - step - 1));
          servo9.write(base_angle + (angle - step - 1));
            delay(22); 
        }
        delay(10);
      }

      for (int step=0; step<angle; step++) {  // servo8 is going up
        servo8.write(base_angle - 2 * step);
        servo9.write(base_angle - min(step, 30));
        servo10.write(base_angle - min(step, 15));
        delay(11); 
      }
      while(true);


    
  }
}