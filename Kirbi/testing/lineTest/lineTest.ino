void setup() {
  // if Ref > sensor, INT is LOW
    int referenceValue = 128;
    Serial.begin(115200);
    pinMode(A22, OUTPUT); // Line RF
    analogWrite(A22, referenceValue);
    pinMode(15, INPUT); // LF INT
    pinMode(16, INPUT); // RF INT
    pinMode(A9, INPUT);  //Line RF analog line sensor signal
    pinMode(A16, INPUT); //Line LF analog 
}

void loop() {
    Serial.print(analogRead(A16)); //Left Line sensor
    Serial.print("\t");
    Serial.print(analogRead(A9));  //Right Line Sensor
    Serial.print("\t");
    Serial.print(digitalRead(15)); //Left Comparator
    Serial.print("\t");
    Serial.print(digitalRead(16)); //Right Comparator
    Serial.print("\n");
    if ((analogRead(A16) > referenceValue) && (digitalRead(15) == HIGH)) {
      Serial.print("Left Sensor Working\t");
    }
    else {
      Serial.print("Left Sensor Failing\t");
    }
    if ((analogRead(A9) > referenceValue) && (digitalRead(16) == HIGH)) {
      Serial.print("Right Sensor Working\n");
    }
    else {
      Serial.print("Right Sensor Failing\n");
    }
    delay(100);
}
