void setup() {
  // put your setup code here, to run once:
  pinMode(A21, INPUT);
  analogReadResolution(13);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  double current = analogRead(A21)*.00805664;
  Serial.println(current);
  delay(100);
}
