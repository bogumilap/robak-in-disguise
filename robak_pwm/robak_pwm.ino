int MIN_US = 544;
int MAX_US = 2400;
int DELAY_VALUE = 5;
bool FOLDED = false;
bool CRAWLING = false;
float DELAY8 = (MIN_US + MAX_US) / 2;
float DELAY9 = (MIN_US + MAX_US) / 2;
float DELAY10 = (MIN_US + MAX_US) / 2;
int CURRENT_SERVO = 8;


void setDelay(float angle, float* delay_pointer) {
  if (angle > 180 || angle < 0) {
    return;
  }
  *delay_pointer = MIN_US + (angle / 180) * (MAX_US - MIN_US);
  // Serial.print(CURRENT_SERVO);
  // Serial.print("\nCURRENT_SERVO\n");
  // Serial.print((CURRENT_SERVO - 7) % 3);
}


void setup() {
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  cli();//stop interrupts

  //set timer1 interrupt at 50Hz => 20ms
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 311,5;// = (16*10^6) / (50*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei();//allow interrupts

  Serial.begin(9600);

}//end setup

ISR(TIMER1_COMPA_vect){
  float delay = DELAY8;
  if (CURRENT_SERVO == 9){
    delay = DELAY9;
  }
  if (CURRENT_SERVO == 10){
    delay = DELAY10;
  }
  // Serial.print(delay);
  digitalWrite(CURRENT_SERVO, HIGH);
  delayMicroseconds(delay);
  digitalWrite(CURRENT_SERVO, LOW);
  delayMicroseconds(20000 - delay);

  CURRENT_SERVO = 8 + (CURRENT_SERVO - 7) % 3;
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
    setDelay(90, &DELAY8);
    setDelay(90, &DELAY9);
    setDelay(90, &DELAY10);
  }
  CRAWLING = false;
}

void crawl() {
  int angle = 45;

  // 0, 0, 90
  for (int step=0; step<angle; step++) {
    setDelay(90 - 2 * step, &DELAY8);
    setDelay(90 - 2 * step, &DELAY9);
    delay(DELAY_VALUE);
  }

  // 0, 45, 90
  for (int step=0; step<angle; step++) {
    setDelay(step, &DELAY9);
    delay(DELAY_VALUE);
  }

  // 0, 45, 135
  for (int step=0; step<angle; step++) {
    setDelay(90 + step, &DELAY10);
    delay(DELAY_VALUE);
  }

  // 90, 90, 135
  for (int step=0; step<angle; step++) {
    setDelay(2 * step, &DELAY8);
    setDelay(45 + step, &DELAY9);
    delay(DELAY_VALUE);
  }
  
  // 90, 90, 90
  for (int step=0; step<angle; step++) {
    setDelay(135 - step, &DELAY10);
    delay(DELAY_VALUE);
  }
}

void fold() {
  if (! FOLDED) {
    for (int step=90; step<180; step++) {
      setDelay(step, &DELAY8);
      // setDelay(step, &DELAY10);
      delay(DELAY_VALUE);
    }
    for (int step=90; step>0; step--) {
      setDelay(step, &DELAY9);
      delay(DELAY_VALUE);
    }
    for (int step=90; step<180; step++) {
      setDelay(step, &DELAY10);
      delay(DELAY_VALUE);
    }
    FOLDED = true;
  }
}

void unfold() {
  if (FOLDED) {
    for (int step=0; step<90; step++) {
      setDelay(step, &DELAY9);
      delay(DELAY_VALUE);
    }
    for (int step=180; step>90; step--) {
      setDelay(step, &DELAY8);
      setDelay(step, &DELAY10);
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
    setDelay(base_angle + step, &DELAY8);
    delay(10); 
  }
  for (int step=49; step>=0; step--) {  // servo8 is going up
    setDelay(base_angle + step, &DELAY8);
    delay(10); 
  }

  // 1 s - arm 2
  for (int step=0; step<50; step++) {  // servo8 is going up
    setDelay(base_angle + step, &DELAY10);
    delay(10); 
  }
  for (int step=49; step>=0; step--) {  // servo8 is going up
    setDelay(base_angle + step, &DELAY10);
    delay(10); 
  }

  // 1 s - /\/\ ...
  for (int step=0; step<angle; step++) {  // servo8 is going up
    setDelay(base_angle - 2 * step, &DELAY8);
    setDelay(base_angle - 2 * step, &DELAY9);
    setDelay(base_angle - 2 * step, &DELAY10);
    delay(11); 
  }
  delay(5);
  for (int step=angle-1; step>=0; step--) {  // servo8 is going up
    setDelay(base_angle - 2 * step, &DELAY8);
    setDelay(base_angle - 2 * step, &DELAY9);
    setDelay(base_angle - 2 * step, &DELAY10);
    delay(11); 
  }
  delay(5);

  // 1 s - \_/
  for (int step=0; step<50; step++) {  // servo8 is going up
    setDelay(base_angle + step, &DELAY8);
    setDelay(base_angle + step, &DELAY10);
    delay(10); 
  }
  for (int step=49; step>=0; step--) {  // servo8 is going up
    setDelay(base_angle + step, &DELAY8);
    setDelay(base_angle + step, &DELAY10);
    delay(10); 
  }

  // 4 s - arm 1, 2 up, down
  for (int step=0; step<50; step++) {  // servo8 is going up
    setDelay(base_angle + step, &DELAY8);
    delay(20); 
  }
  for (int step=0; step<50; step++) {  // servo8 is going up
    setDelay(base_angle + step, &DELAY10);
    delay(20); 
  }
  for (int step=49; step>=0; step--) {  // servo8 is going up
    setDelay(base_angle + step, &DELAY10);
    delay(20); 
  }
  for (int step=49; step>=0; step--) {  // servo8 is going up
    setDelay(base_angle + step, &DELAY8);
    delay(20); 
  }

  for(int g=0; g<2; g++) {
    // sum = 2s 
    // 0.5s - /\_
    for (int step=0; step<angle; step++) {  // servo8 is going up
      setDelay(base_angle + 2 * step, &DELAY8);
      setDelay(base_angle + step, &DELAY9);
      delay(11); 
    }
    delay(5);

    // 0.5s - /\/\ ...
    for (int step=0; step<angle; step++) {  // servo8 is going up
      setDelay(base_angle + 2 * step, &DELAY10);
      setDelay(base_angle + angle + step, &DELAY9);
      delay(11); 
    }
    delay(5);

    // 0.5s - /\_
    for (int step=angle-1; step<=0; step--) {  // servo8 is going up
      setDelay(base_angle - 2 * step, &DELAY8);
      setDelay(base_angle + angle - step, &DELAY9);
      delay(11); 
    }
    delay(5);
    // 0.5s - ____
    for (int step=angle-1; step<=0; step--) {  // servo8 is going up
      setDelay(base_angle - 2 * step, &DELAY8);
      setDelay(base_angle - step, &DELAY9);
      delay(11); 
    }
    delay(5);


    // fold - 4s
    for (int step=0; step<angle; step++) {
      setDelay(base_angle + 2 * step, &DELAY8);
      setDelay(base_angle + 2 * step, &DELAY10);
      delay(44); 
    }
    delay(20);
    for (int step=0; step<angle; step++) {
      setDelay(base_angle - 2 * step, &DELAY9);
      delay(44); 
    }
    delay(20);

    // unfold - 4s
    for (int step=0; step<angle; step++) {
      setDelay(base_angle + 2 * (angle - step - 1), &DELAY9);
      delay(44); 
    }
    delay(20);
    for (int step=0; step<angle; step++) {
      setDelay(base_angle - 2 * (angle - step - 1), &DELAY8);
      setDelay(base_angle - 2 * (angle - step - 1), &DELAY10);
      delay(44); 
    }
    delay(20);

    // fala - 6 s
    // /\_ - 1s
    for (int step=0; step<angle; step++) {  // servo8 is going up
      setDelay(base_angle + 2 * step, &DELAY8);
      setDelay(base_angle + step, &DELAY9);
      delay(22); 
    }
    delay(10);
    for(int i=0; i<2; i++) { // loop - 2s 
    // _/\ - 1 s 
      for (int step=0; step<angle; step++) {  // servo8 is going up
        setDelay(base_angle + 2 * step, &DELAY10);
        setDelay(base_angle + 2 * (angle - step - 1), &DELAY8);
        delay(22); 
      }
      delay(10);
      for (int step=0; step<angle; step++) {  // servo8 is going up
        setDelay(base_angle + 2 * step, &DELAY8);
        setDelay(base_angle + 2 * (angle - step - 1), &DELAY10);
        delay(22); 
      }
      delay(10);
    }
    for (int step=0; step<angle; step++) {  // servo8 is going up
      setDelay(base_angle + 2 * (angle - step - 1), &DELAY8);
      setDelay(base_angle + (angle - step - 1), &DELAY9);
      delay(22); 
    }
    delay(10);
  }

  for (int step=0; step<angle; step++) {  // servo8 is going up
    setDelay(base_angle - 2 * step, &DELAY8);
    setDelay(base_angle - min(step, 30), &DELAY9);
    setDelay(base_angle - min(step, 15), &DELAY10);
    delay(11); 
  }
}
