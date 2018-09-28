// This #include statement was automatically added by the Particle IDE.

#include <Particle.h>

#if !defined(PARTICLE)
#  include <Wire.h>
#endif

SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(MANUAL);

void getAccel();
int curAccel = 0;
LIS3DHSample sample;
Timer timer(100, getAccel);
LIS3DHI2C accel(Wire, 0, WKP);

void getAccel() {
  accel.getSample(sample);
  curAccel = sample.x;
}

//int state;          // movement state of robot

// Accelerometer
void accel_init() {
  Wire.setSpeed(CLOCK_SPEED_100KHZ);  // need to initialize i2c protocol after driving shdn pins low
  Wire.begin();
  delay(500);
	LIS3DHConfig config;
	config.setAccelMode(LIS3DH::RATE_100_HZ);

	bool setupSuccess = accel.setup(config);
	Serial.printlnf("setupSuccess=%d", setupSuccess);
}

void setup()
{
  Serial.begin(9600);

  accel_init();
  timer.start();
  delay(1000);
}

void loop()
{
	Serial.println(curAccel);
}
