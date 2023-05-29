int MIN_US = 544;
int MAX_US = 2400;
int DELAY_VALUE = 10;
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
  }
} 