#include <Arduino.h>
void setup() {
    Serial.begin(9600);
    while (!Serial); // Wait for Serial Monitor to open
    loop();
}

void loop() {
    for (int pin = 2; pin <= 13; pin++) { // Loop through digital pins 2 to 13
        pinMode(pin, INPUT);
        int state = digitalRead(pin);

        Serial.print("Pin ");
        Serial.print(pin);
        Serial.print(": ");

        if (state == HIGH) {
            Serial.println("HIGH (connected to 5V)");
        } else {
            Serial.println("LOW (not connected to 5V)");
        }

        delay(1000); // Delay for readability
    }
}