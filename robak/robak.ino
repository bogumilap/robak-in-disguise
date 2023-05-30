int MIN_US = 544;
int MAX_US = 2400;
int DELAY_VALUE = 5;
bool FOLDED = false;
bool CRAWLING = false;

void setAngle(float angle, int pinID) {
  if (angle > 180 || angle < 0) {
    return;
  }
  float delay = MIN_US + (angle / 180) * (MAX_US - MIN_US);
  digitalWrite(pinID, HIGH);
  delayMicroseconds(delay);
  digitalWrite(pinID, LOW);
  delayMicroseconds(20000 - delay);
}

void setup() {
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  while (Serial.available() > 0) {
    String inputString = Serial.readStringUntil("\n");
    Serial.println(inputString);
    processInput(inputString);
  }
  if (CRAWLING) {
    crawl();
  }
}

void processInput(String inputString) {
  if (isInputEqual(inputString, "fold")) {
    if (CRAWLING) {
      stop();
    }
    fold();
  }
  if (isInputEqual(inputString, "unfold")) {
    if (CRAWLING) {
      stop();
    }
    unfold();
  }
  if (isInputEqual(inputString, "crawl")) {
    if (FOLDED) {
      unfold();
    }
    CRAWLING = true;
    crawl();
  }
  if (isInputEqual(inputString, "stop")) {
    if (FOLDED) {
      unfold();
    } else {
      stop();
    }
  }
  if (isInputEqual(inputString, "dance")) {
    if (FOLDED) {
      unfold();
    }
    dance();
  }
}

bool isInputEqual(String inputString, String comparedString) {
  return (inputString == comparedString || inputString == comparedString + "\n" 
            || inputString == comparedString + "\r" || inputString == comparedString + "\r\n");
}

void stop() {
  if (FOLDED) {
    unfold();
    FOLDED = false;
  } else {
    setAngle(90, 8);
    setAngle(90, 9);
    setAngle(90, 10);
  }
  CRAWLING = false;
}

void crawl() {
  int angle = 45;

  // 0, 0, 90
  for (int step=0; step<angle; step++) {
    setAngle(90 - 2 * step, 8);
    setAngle(90 - 2 * step, 9);
    delay(DELAY_VALUE);
  }

  // 0, 45, 90
  for (int step=0; step<angle; step++) {
    setAngle(step, 9);
    delay(DELAY_VALUE);
  }

  // 0, 45, 135
  for (int step=0; step<angle; step++) {
    setAngle(90 + step, 10);
    delay(DELAY_VALUE);
  }

  // 90, 90, 135
  for (int step=0; step<angle; step++) {
    setAngle(2 * step, 8);
    setAngle(45 + step, 9);
    delay(DELAY_VALUE);
  }
  
  // 90, 90, 90
  for (int step=0; step<angle; step++) {
    setAngle(135 - step, 10);
    delay(DELAY_VALUE);
  }
}

void fold() {
  if (! FOLDED) {
    for (int step=90; step<180; step++) {
      setAngle(step, 8);
      // setAngle(step, 10);
      delay(DELAY_VALUE);
    }
    for (int step=90; step>0; step--) {
      setAngle(step, 9);
      delay(DELAY_VALUE);
    }
    for (int step=90; step<180; step++) {
      setAngle(step, 10);
      delay(DELAY_VALUE);
    }
    FOLDED = true;
  }
}

void unfold() {
  if (FOLDED) {
    for (int step=0; step<90; step++) {
      setAngle(step, 9);
      delay(DELAY_VALUE);
    }
    for (int step=180; step>90; step--) {
      setAngle(step, 8);
      setAngle(step, 10);
      delay(DELAY_VALUE);
    }
    FOLDED = false;
  } else {
    stop();
  }
} 

void dance() {
  stop();
  int base_angle = 90;
  int angle = 45;
  // one second - arm 1
  for (int step=0; step<50; step++) {  // servo8 is going up
    setAngle(base_angle + step, 8);
    delay(10); 
  }
  for (int step=49; step>=0; step--) {  // servo8 is going up
    setAngle(base_angle + step, 8);
    delay(10); 
  }

  // 1 s - arm 2
  for (int step=0; step<50; step++) {  // servo8 is going up
    setAngle(base_angle + step, 10);
    delay(10); 
  }
  for (int step=49; step>=0; step--) {  // servo8 is going up
    setAngle(base_angle + step, 10);
    delay(10); 
  }

  // 1 s - /\/\ ...
  for (int step=0; step<angle; step++) {  // servo8 is going up
    setAngle(base_angle - 2 * step, 8);
    setAngle(base_angle - 2 * step, 9);
    setAngle(base_angle - 2 * step, 10);
    delay(11); 
  }
  delay(5);
  for (int step=angle-1; step>=0; step--) {  // servo8 is going up
    setAngle(base_angle - 2 * step, 8);
    setAngle(base_angle - 2 * step, 9);
    setAngle(base_angle - 2 * step, 10);
    delay(11); 
  }
  delay(5);

  // 1 s - \_/
  for (int step=0; step<50; step++) {  // servo8 is going up
    setAngle(base_angle + step, 8);
    setAngle(base_angle + step, 10);
    delay(10); 
  }
  for (int step=49; step>=0; step--) {  // servo8 is going up
    setAngle(base_angle + step, 8);
    setAngle(base_angle + step, 10);
    delay(10); 
  }

  // 4 s - arm 1, 2 up, down
  for (int step=0; step<50; step++) {  // servo8 is going up
    setAngle(base_angle + step, 8);
    delay(20); 
  }
  for (int step=0; step<50; step++) {  // servo8 is going up
    setAngle(base_angle + step, 10);
    delay(20); 
  }
  for (int step=49; step>=0; step--) {  // servo8 is going up
    setAngle(base_angle + step, 10);
    delay(20); 
  }
  for (int step=49; step>=0; step--) {  // servo8 is going up
    setAngle(base_angle + step, 8);
    delay(20); 
  }

  for(int g=0; g<2; g++) {
    // sum = 2s 
    // 0.5s - /\_
    for (int step=0; step<angle; step++) {  // servo8 is going up
      setAngle(base_angle + 2 * step, 8);
      setAngle(base_angle + step, 9);
      delay(11); 
    }
    delay(5);

    // 0.5s - /\/\ ...
    for (int step=0; step<angle; step++) {  // servo8 is going up
      setAngle(base_angle + 2 * step, 10);
      setAngle(base_angle + angle + step, 9);
      delay(11); 
    }
    delay(5);

    // 0.5s - /\_
    for (int step=angle-1; step<=0; step--) {  // servo8 is going up
      setAngle(base_angle - 2 * step, 8);
      setAngle(base_angle + angle - step, 9);
      delay(11); 
    }
    delay(5);
    // 0.5s - ____
    for (int step=angle-1; step<=0; step--) {  // servo8 is going up
      setAngle(base_angle - 2 * step, 8);
      setAngle(base_angle - step, 9);
      delay(11); 
    }
    delay(5);


    // fold - 4s
    for (int step=0; step<angle; step++) {
      setAngle(base_angle + 2 * step, 8);
      setAngle(base_angle + 2 * step, 10);
      delay(44); 
    }
    delay(20);
    for (int step=0; step<angle; step++) {
      setAngle(base_angle - 2 * step, 9);
      delay(44); 
    }
    delay(20);

    // unfold - 4s
    for (int step=0; step<angle; step++) {
      setAngle(base_angle + 2 * (angle - step - 1), 9);
      delay(44); 
    }
    delay(20);
    for (int step=0; step<angle; step++) {
      setAngle(base_angle - 2 * (angle - step - 1), 8);
      setAngle(base_angle - 2 * (angle - step - 1), 10);
      delay(44); 
    }
    delay(20);

    // fala - 6 s
    // /\_ - 1s
    for (int step=0; step<angle; step++) {  // servo8 is going up
      setAngle(base_angle + 2 * step, 8);
      setAngle(base_angle + step, 9);
      delay(22); 
    }
    delay(10);
    for(int i=0; i<2; i++) { // loop - 2s 
    // _/\ - 1 s 
      for (int step=0; step<angle; step++) {  // servo8 is going up
        setAngle(base_angle + 2 * step, 10);
        setAngle(base_angle + 2 * (angle - step - 1), 8);
        delay(22); 
      }
      delay(10);
      for (int step=0; step<angle; step++) {  // servo8 is going up
        setAngle(base_angle + 2 * step, 8);
        setAngle(base_angle + 2 * (angle - step - 1), 10);
        delay(22); 
      }
      delay(10);
    }
    for (int step=0; step<angle; step++) {  // servo8 is going up
      setAngle(base_angle + 2 * (angle - step - 1), 8);
      setAngle(base_angle + (angle - step - 1), 9);
      delay(22); 
    }
    delay(10);
  }

  for (int step=0; step<angle; step++) {  // servo8 is going up
    setAngle(base_angle - 2 * step, 8);
    setAngle(base_angle - min(step, 30), 9);
    setAngle(base_angle - min(step, 15), 10);
    delay(11); 
  }
}
