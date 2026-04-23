#include <Arduino.h>

// ---------- Motor Pins ----------
int in1 = 9;
int in2 = 10;
int in3 = 6;
int in4 = 5;

// ---------- Sensor Pins ----------
int IR1 = 12;
int IR2 = 7;
int IR3 = 2;
int IR4 = 1;
int L1 = A0;
int L2 = A4;
int push = 8;
int SW1 = A3;
int SW2 = A2;
int SW3 = A1;
int SW4 = 4;
int StartMod = 13;

// ---------- Servo Pins (Timer2) ----------
int SV1 = 11; // OC2A
int SV2 = 3;  // OC2B

// ---------- Servo pulse values for specific positions ----------
int SV1_high = 1250;  // microseconds
int SV1_low  = 2195;
int SV2_high = 2020;
int SV2_low  = 1070;

// ---------- Current target pulses ----------
volatile int SV1_val = SV1_high; // start at high
volatile int SV2_val = SV2_high;

// ---------- Servo Timing ----------
volatile int servoStep = 0;
volatile unsigned long lastMicros = 0;

int lBlack = 0;
int rBlack = 0;

// ---------- Strategy ----------
String strategy = "";
int seen = 0;
int startSeen = 0;
int lastSeen = 0;
unsigned long lastSeenTime = 0;
unsigned long startTime = 0;
int lastSeen1 = 0;
int lastSeen2 = 0;
int lastSeen3 = 0;
int lastSeen4 = 0;
bool accel = false;
unsigned long notSeenTime = 0;
bool notSeen = true;
unsigned long startMove = 0;

// ---------- Setup ----------
void setup() {
//  Serial.begin(9600);
  // Motor pins
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Servo pins
  pinMode(SV1, OUTPUT);
  pinMode(SV2, OUTPUT);

  // Sensor pins
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(StartMod, INPUT);
  pinMode(push, INPUT_PULLUP);
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  pinMode(SW3, INPUT_PULLUP);
  pinMode(SW4, INPUT_PULLUP);

  // Stop motors initially
  coastMotors();

  // Set servos to their high positions
  SV1_val = SV1_high;
  SV2_val = SV2_high;

  // ---------- Configure Timer2 for interrupt ----------
  noInterrupts();
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2 = 0;

  // CTC mode
  TCCR2A |= (1 << WGM21);
  // Prescaler = 8 → 16 MHz / 8 = 2 MHz → 0.5 us per tick
  TCCR2B |= (1 << CS21);
  OCR2A = 32; // interrupt every ~16 us
  TIMSK2 |= (1 << OCIE2A); // enable Timer2 compare interrupt
  interrupts();

  // Give ISR a little time to generate pulses at high positions
  unsigned long start = millis();
  while (millis() - start < 50) {
    // ISR is running; no other action needed
  }

//  delay(1000);
  
  // Wait for push button to start
  while (digitalRead(StartMod) == LOW) {
    // interrupts continue to generate servo pulses
    lBlack = analogRead(L1);
    rBlack = analogRead(L2);
  }
  stopMotors();
  if (digitalRead(SW2) == LOW && digitalRead(SW1) == HIGH) {
    strategy = "L";
  } else if (digitalRead(SW2) == HIGH && digitalRead(SW1) == LOW) {
    strategy = "R";
  } else if (digitalRead(SW1) == LOW && digitalRead(SW2) == LOW) {
    strategy = "F";
  } else {
    strategy = "B";
  }

  if (digitalRead(SW3) == HIGH) {
    accel = true;
  } else if (strategy == "F") {
      strategy = "rush";
  } else if (strategy == "B") {
      strategy = "turt_rush";
  }
//
//  delay(5000);

  if (strategy == "L") {
    SV1_val = SV1_low;
    SV2_val = SV2_low;
    turnLeft(150);
    delay(35);
    moveForward(150);
    delay(50);
  } else if (strategy == "R") {
    SV1_val = SV1_low;
    SV2_val = SV2_low;
    turnRight(150);
    delay(35);
    moveForward(150);
    delay(50);
  } else if (strategy == "B") {
    SV1_val = SV1_low;
    SV2_val = SV2_low;
    stopMotors();
  } else if (strategy == "F") {
    SV1_val = SV1_low;
    SV2_val = SV2_low;
  } else if (strategy == "rush") {
    SV1_val = SV1_low;
    SV2_val = SV2_low;
    moveForward(255);
  } else if (strategy == "turt_rush") {
    SV1_val = SV1_low;
    SV2_val = SV2_low;
    moveForward(255);
    delay(70);
    strategy = "B";
    stopMotors();
//    delay(20);
  }
  
  startTime = millis();
}

// ---------- Timer2 ISR for servo PWM ----------
ISR(TIMER2_COMPA_vect) {
  unsigned long now = micros();

  switch (servoStep) {
    case 0: // SV1 HIGH
      digitalWrite(SV1, HIGH);
      lastMicros = now;
      servoStep = 1;
      break;

    case 1: // SV1 LOW
      if (now - lastMicros >= SV1_val) {
        digitalWrite(SV1, LOW);
        lastMicros = now;
        servoStep = 2;
      }
      break;

    case 2: // SV2 HIGH
      if (now - lastMicros >= 300) { // small gap between servos
        digitalWrite(SV2, HIGH);
        lastMicros = now;
        servoStep = 3;
      }
      break;

    case 3: // SV2 LOW
      if (now - lastMicros >= SV2_val) {
        digitalWrite(SV2, LOW);
        lastMicros = now;
        servoStep = 4;
      }
      break;

    case 4: // Wait until 20ms frame completes
      if (now - lastMicros >= 20500UL) {
        servoStep = 0;
      }
      break;
  }
}

// ---------- Main Loop (your original logic) ----------
void loop() {
  if (digitalRead(StartMod) == HIGH) {    
    // Read sensors
    int irVal1 = digitalRead(IR1);
    int irVal2 = digitalRead(IR2);
    int irVal3 = digitalRead(IR3);
    int irVal4 = digitalRead(IR4);
    int lLine = analogRead(L1);
    int rLine = analogRead(L2);

    notSeen = 1;

    if (irVal1) {
      lastSeen1 = millis();
      notSeen = 0;
    }
    if (irVal2) {
      lastSeen2 = millis();
      notSeen = 0;
    }
    if (irVal3) {
      lastSeen3 = millis();
      notSeen = 0;
    }
    if (irVal4) {
      lastSeen4 = millis();
      notSeen = 0;
    }

    if (!notSeen) {
      notSeenTime = millis();
    }
    
    if (irVal2 && irVal3 && strategy == "B") {
      if (seen == 0) {
        startSeen = millis();
      }
      int speed = 0;
      if (millis() - startSeen > 1000) {
        speed = 100 + (millis() - startSeen - 1000) * 0.5;
      } else {
        speed = 0;
        stopMotors();
      }
      if (speed > 150) {
        speed = 0;
        strategy = "F";
      }
      moveForward(speed);
      seen = 1;
    } else if (lLine > 150 && rLine > 150) {
      if (strategy == "rush" && (millis() - startTime) < 200) {
        moveForward(255);
      } else if (irVal2 && irVal3 && strategy != "B") {
          if (seen == 0) {
            startSeen = millis();
          }
          int speed = 50;
          if (millis()- startSeen > 1000) {
            speed = 50 + (millis()-1000 - startSeen) * 0.5;
          } else {
            speed = 50;
          }
          if (speed > 255) {
            speed = 255;
          }
          moveForward(speed);
          if (speed == 0) {
            stopMotors();
          }
          seen = 1;
      } else if (irVal1) {
        lastSeen = 1;
        lastSeenTime = millis();
        if (strategy == "R") {
          if (millis() - startTime >= 150) {
            turnLeft(150);
          }  else {
            moveForward(150);
            seen = 0;
          }
        } else {
          seen = 0;
          turnLeft(150);
        }
      } else if (irVal4) {
        lastSeen = 4;
        lastSeenTime = millis();
        if (strategy == "L") {
          if (millis() - startTime >= 150) {
            turnRight(150);
          }else {
            moveForward(150);
            seen = 0;
          }
        } else {
          seen = 0;
          turnRight(150);
        }
      } else if (irVal2) {
        seen = 0;
        turnLeft(40);
      }  else if (irVal3){
        seen = 0;
        turnRight(40);
      } else if ((millis() - startTime) > 1500 && strategy != "B" &&
                !irVal2 && !irVal3 &&
                lastSeen2 > startTime && lastSeen3 > startTime &&
                abs(lastSeen2 - lastSeen3) <= 20 &&
                (millis() - lastSeen2) < 100 && (millis() - lastSeen3) < 100) {
          seen = 0;
          moveBackward(255);
          delay(100);
          if (lastSeen1 < lastSeen2) {
            turnRight(150);
            delay(50);
            int forwards = millis();
            while (lLine > 150 && rLine > 150 && (millis() - forwards) < 50) {
              moveForward(255);
            }
            
          } else {
            turnLeft(150);
            delay(50);
            int forwards = millis();
            while (lLine > 150 && rLine > 150 && (millis() - forwards) < 50) {
              moveForward(255);
            }
          }
      }else {
        if ((strategy == "R" || strategy == "L") && millis() - startTime <= 70) {
          moveForward(150);
        } else if (strategy == "B") {
//          if (notSeen == 0) {
//            notSeenTime = millis();
//          }
          if (millis() - notSeenTime > 3000 && millis() - startTime > 3000) {
            if (millis() - startMove > 3000) {
              startMove = millis();
            } else if (millis() - startMove <= 50) {
              moveForward(200);
            } else {
              stopMotors();
            }
          } else {
            stopMotors();
          }
        } else {
          moveForward(30);
        }
      }
    } else if (millis() - lastSeenTime < 100) {
      if (lastSeen == 1) {
        turnLeft(150);
      } else if (lastSeen == 4) {
        turnRight(150);
      }
    } else if (lLine <= 150) {
      moveBackward(255);
  //    SV1_val = SV1_low - 100;
      delay(120);
      turnRight(150);
      delay(75);
      if (strategy == "B") {
        strategy = "F";
      }
  //    SV1_val = SV1_low;
    } else if (rLine <= 150) {
      moveBackward(255);
  //    SV2_val = SV2_low + 100;
      delay(120);
      turnLeft(150);
      delay(75);
      if (strategy == "B") {
        strategy = "F";
      }
  //    SV2_val = SV2_low;
    } else {
      moveBackward(255);
    }
  } else {
    stopMotors();
    SV1_val = SV1_high;
    SV2_val = SV2_high;
  }
}

// ---------- Motor Functions ----------
void moveForward(int speed) {
  analogWrite(in1, speed);
  digitalWrite(in2, LOW);
  analogWrite(in3, speed);
  digitalWrite(in4, LOW);
}

void moveBackward(int speed) {
  digitalWrite(in1, LOW);
  analogWrite(in2, speed);
  digitalWrite(in3, LOW);
  analogWrite(in4, speed);
}

void stopMotors() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);
}

void turnRight(int speed) {
  analogWrite(in1, speed);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  analogWrite(in4, speed);
}

void turnLeft(int speed) {
  digitalWrite(in1, LOW);
  analogWrite(in2, speed);
  analogWrite(in3, speed);
  analogWrite(in4, LOW);
}

void coastMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
//
//void loop() {
//  // Read your line sensors
//  int lLine = analogRead(L1);
//  int rLine = analogRead(L2);
//  int irVal1 = digitalRead(IR1);
//  int irVal2 = digitalRead(IR2);
//  int irVal3 = digitalRead(IR3);
//  int s1 = digitalRead(SW1);
//  int s2 = digitalRead(SW2);
//
//  // Print values to Serial Monitor
////  Serial.print("L1: ");
////  Serial.print(lLine);
////  Serial.print("\tR1: ");
////  Serial.println(rLine);
////  Serial.print("SW1: ");
////  if (digitalRead(SW1) == HIGH) {
////    Serial.print("OFF");
////  } else {
////    Serial.print("ON");
////  }
////  Serial.print("\tSW2: ");
////  if (digitalRead(SW2) == HIGH) {
////    Serial.println("OFF");
////  } else {
////    Serial.println("ON");
////  }
//    Serial.print("\tIR1: ");
//    if (irVal1) {
//      Serial.println("Detected");
//    } else {
//      Serial.println("Nothing");
//    }
////    Serial.print("\tIR2: ");
////    if (irVal2) {
////      Serial.println("Detected");
////    } else {
////      Serial.println("Nothing");
////    }
////    Serial.print("\tIR3: ");
////    if (irVal3) {
////      Serial.println("Detected");
////    } else {
////      Serial.println("Nothing");
////    }
//
//  delay(100); // small delay to make output readable (adjust as needed)
//}
