//code from https://forum.pjrc.com/threads/17532-Tutorial-on-digital-I-O-ATMega-PIN-PORT-DDR-D-B-registers-vs-ARM-GPIO_PDIR-_PDOR

byte pinTable[] = {2,14,7,8,6,20,21,5}; //pin mappings for cluster D. 2 refers to pin 2 on the teensy, for instance.

void setup() {
  Serial.begin(0);
  for (int i=0; i<8; i++) { 
    pinMode(pinTable[i], INPUT_PULLUP); 
  } 
}

  void loop() {
  byte eight,prev_eight;
  do {
    //TODO: find out what GPIOD_PDIR is. If I set GPIOD_PDIR to something, multimeter should measure that change, right?
    eight = GPIOD_PDIR & 0xFF; //mask all but the last 8 bits
    
    if (eight != prev_eight)
    {
      prev_eight = eight;
      Serial.println(eight,HEX); //print out if any pins (bit vector in GPIO_PDIR) change status
    }
  } while (1==1);
}
