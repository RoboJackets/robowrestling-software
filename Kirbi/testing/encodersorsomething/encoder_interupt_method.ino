
int counter = 0;
#define outputA 4

void encoderISR() {
  counter++;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(outputA, INPUT);
  attachInterrupt(outputA, encoderISR, RISING);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(counter);
  counter = 0;
  delay(1000);
}
