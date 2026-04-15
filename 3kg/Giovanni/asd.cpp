
#include <Arduino.h>

/*
 Teensy 4.1 + Cytron MD25HV (2 drivers) + TMCS1126 current sensor
 STEP & HOLD TEST for DMM comparison
 Motor1: PWM=37, DIR=38
 Motor2: PWM=36, DIR=40
 TMCS1126 VOUT -> Teensy pin 23 (A9)

 Behavior:
 - Calibrate zero-current at startup (motors off)
 - Forward pass: hold each duty in speedSteps[] for 5 s
 - Pause, then Reverse pass: same sequence
 - Print current every 100 ms for DMM comparison
*/

//////////////////// Pins ////////////////////
const int pwm1Pin = 37;
const int dir1Pin = 38;
const int pwm2Pin = 36;
const int dir2Pin = 40;
const int curPin = 23; // TMCS1126 VOUT -> Teensy pin 23 (A9)

////////////// User Tunables ///////////////
// PWM setup
const int pwmResolutionBits = 8; // 0..255
const int pwmMax = 255;
const uint32_t pwmHz = 20000; // 20 kHz (quiet)

// Step test
const uint32_t holdMs = 5000; // hold each step for 5 seconds
const uint32_t betweenStepsMs = 500; // short settle between steps

// Duty cycles to test (edit as needed)
int speedSteps[] = {0, 64, 128, 192, 255};
const size_t NUM_STEPS = sizeof(speedSteps) / sizeof(speedSteps[0]);

// Current sensor (TMCS1126 A8A typical)
const float SENS_V_PER_A = 0.040f; // 40 mV/A (adjust if your variant differs)

// ADC (Teensy 4.1)
const int adcBits = 12; // use full 12-bit resolution
const float vRef_ADC = 3.3f; // Teensy analog reference (approx.)
const int adcAvgSamples = 16; // internal averaging

// Print rate during holds
const uint32_t printEveryMs = 100;

////////////// Internals /////////////////
float vZero = 0.0f; // learned zero-current voltage at startup
float lastVoltageV = 0.0f; // cached latest sensor voltage

// Forward declarations
float measureVoltage(int pin, int samples);
float readCurrentA();
void setDirection(bool forward);
void runStepSequence(const char* label);

void setup() {
  // IO
  pinMode(pwm1Pin, OUTPUT);
  pinMode(dir1Pin, OUTPUT);
  pinMode(pwm2Pin, OUTPUT);
  pinMode(dir2Pin, OUTPUT);

  // PWM
  analogWriteResolution(pwmResolutionBits);
  analogWriteFrequency(pwm1Pin, pwmHz);
  analogWriteFrequency(pwm2Pin, pwmHz);

  // Ensure motors OFF for calibration
  digitalWrite(dir1Pin, LOW);
  digitalWrite(dir2Pin, LOW);
  analogWrite(pwm1Pin, 0);
  analogWrite(pwm2Pin, 0);

  // ADC config
  analogReadResolution(adcBits);
  analogReadAveraging(adcAvgSamples);

  Serial.begin(115200);
  while (!Serial && millis() < 2000) {
  }

  Serial.println("\n=== Teensy 4.1 MD25HV STEP & HOLD + TMCS1126 ===");
  Serial.println("Calibrating zero-current offset (motors OFF)...");
  vZero = measureVoltage(curPin, 200);
  Serial.print("Zero-current Vout = ");
  Serial.print(vZero, 4);
  Serial.println(" V");
  Serial.println("\nForward pass starts in 1 s...");
  delay(1000);
}

void loop() {
  // Forward pass
  setDirection(true);
  runStepSequence("FORWARD");
  delay(1000);

  // Reverse pass
  setDirection(false);
  runStepSequence("REVERSE");
  delay(1000);
}

void setDirection(bool forward) {
  digitalWrite(dir1Pin, forward ? HIGH : LOW);
  digitalWrite(dir2Pin, forward ? HIGH : LOW);
}

void runStepSequence(const char* label) {
  Serial.print("\n--- ");
  Serial.print(label);
  Serial.println(" ---");

  for (size_t i = 0; i < NUM_STEPS; ++i) {
    int duty = constrain(speedSteps[i], 0, pwmMax);

    // Apply duty to both motors
    analogWrite(pwm1Pin, duty);
    analogWrite(pwm2Pin, duty);

    Serial.print("STEP ");
    Serial.print(i + 1);
    Serial.print("/");
    Serial.print(NUM_STEPS);
    Serial.print(": PWM=");
    Serial.print(duty);
    Serial.println(" (Hold 5 s)");

    // Hold and print current periodically
    uint32_t t0 = millis();
    uint32_t lastPrint = 0;
    while (millis() - t0 < holdMs) {
      if (millis() - lastPrint >= printEveryMs) {
        lastPrint = millis();
        float amps = readCurrentA();
        float vout = lastVoltageV;

        Serial.print(" t=");
        Serial.print((millis() - t0) / 1000.0f, 1);
        Serial.print(" s Vout=");
        Serial.print(vout, 4);
        Serial.print(" V I=");
        Serial.print(amps, 3);
        Serial.println(" A");
      }
      delay(5);
    }

    // Optional short idle between steps for stability
    analogWrite(pwm1Pin, 0);
    analogWrite(pwm2Pin, 0);
    delay(betweenStepsMs);
  }
}

float readCurrentA() {
  // Average a few samples quickly for a steadier number
  const int n = 8;
  float v = measureVoltage(curPin, n);
  lastVoltageV = v;

  // Convert to current using calibrated zero
  float amps = (v - vZero) / SENS_V_PER_A;
  if (fabsf(amps) < 0.02f) {
    amps = 0.0f;
  }
  return amps;
}

// Average N analogRead() values and convert to volts (correct scaling)
float measureVoltage(int pin, int samples) {
  uint32_t acc = 0;
  for (int i = 0; i < samples; ++i) {
    acc += analogRead(pin);
  }

  float counts = float(acc) / float(samples);
  float volts = counts * (vRef_ADC / float((1 << adcBits) - 1));
  return volts;
}
