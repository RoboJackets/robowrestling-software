void setup() {
    Serial.begin(115200);
    pinMode(A22, OUTPUT);
    analogWrite(A22, 128);
    pinMode(18, INPUT);
    pinMode(19, INPUT);
    pinMode(A9, INPUT);
    pinMode(A16, INPUT);
}

void loop() {
    Serial.print(analogRead(A16));
    Serial.print("\t");
    Serial.print(analogRead(A9));
    Serial.print("\t");
    Serial.print(digitalRead(18));
    Serial.print("\t");
    Serial.print(digitalRead(19));
    Serial.print("\n");

    delay(100);
}
