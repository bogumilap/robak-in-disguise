int MIN_US = 544;
int MAX_US = 2400;

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
}

void loop() {
  int ratio8 = 2;
  int delay_value = 50;
  int angle = 45;
  setAngle(90, 8);
  setAngle(90, 9);
  setAngle(90, 10);

  // 0, 0, 90
  for (int step=0; step<angle; step++) {
    setAngle(90 - ratio8 * step, 8);
    setAngle(90 - ratio8 * step, 9);
    delay(delay_value);
  }

  // 0, 45, 90
  for (int step=0; step<angle; step++) {
    setAngle(step, 9);
    delay(delay_value);
  }

  // 0, 45, 135
  for (int step=0; step<angle; step++) {
    setAngle(90 + step, 10);
    delay(delay_value);
  }

  // 90, 90, 135
  for (int step=0; step<angle; step++) {
    setAngle(ratio8 * step, 8);
    setAngle(45 + step, 9);
    delay(delay_value);
  }
  
  // 90, 90, 90
  for (int step=0; step<angle; step++) {
    setAngle(135 - step, 10);
    delay(delay_value);
  }
}