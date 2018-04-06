// A test of the eFLL fuzzy library
// Utilizes the VL53L0X sensor and Car ESCs

#include <Particle.h>

#include <FuzzyRule.h>
#include <FuzzyComposition.h>
#include <Fuzzy.h>
#include <FuzzyRuleConsequent.h>
#include <FuzzyOutput.h>
#include <FuzzyInput.h>
#include <FuzzyIO.h>
#include <FuzzySet.h>
#include <FuzzyRuleAntecedent.h>

#include <thresholds.h>

#include <VL53L0X.h>
#include <LIS3DH.h>

#if !defined(PARTICLE)
#  include <Wire.h>
#endif

VL53L0X sensor0;
VL53L0X sensor1;
VL53L0X sensor2;
VL53L0X sensor3;

int FL = D7;    // AUX BOARD SWITCHED FL and FR up
int FR = A4;    // A5 does not support attachInterrupt, so jump A5 to D7 on the board, also cut INT line
int BL = D5;
int BR = D6;

int RS = D4;

Servo LESC;
Servo RESC;
int Lmotor = D2;
int Rmotor = D3;

boolean FLflag = true; // active low
boolean FRflag = true;
boolean BLflag = true;
boolean BRflag = true;

boolean RSflag = false;

SYSTEM_THREAD(ENABLED);

// Try to print on web console**************************
//SYSTEM_MODE(MANUAL);

// Accelerometer
const unsigned long PRINT_SAMPLE_PERIOD = 100;
LIS3DHI2C accel(Wire, 0, WKP);
unsigned long lastPrintSample = 0;

void FLISR() {
    FLflag = digitalRead(FL);
}

void FRISR() {
    FRflag = digitalRead(FR);
}

void BLISR() {
    BLflag = digitalRead(BL);
}

void BRISR() {
    BRflag = digitalRead(BR);
}

void RSISR() {
    RSflag = digitalRead(RS);
}

void tof_init() {
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);
    digitalWrite(A0, LOW);
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);
    digitalWrite(A3, LOW);
    delay(500);

    Wire.setSpeed(CLOCK_SPEED_100KHZ);  // need to initialize i2c protocol after driving shdn pins low
    Wire.begin();

    delay(10);
    digitalWrite(A0, HIGH);
    digitalWrite(A1, HIGH);
    digitalWrite(A2, HIGH);
    digitalWrite(A3, HIGH);
    delay(10);
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);
    digitalWrite(A3, LOW);
    sensor0.init();
    sensor0.setAddress(0x30);
    sensor0.setTimeout(1000);
    delay(10);
    digitalWrite(A1, HIGH);
    sensor1.init();
    sensor1.setAddress(0x31);
    sensor1.setTimeout(1000);
    delay(10);
    digitalWrite(A2, HIGH);
    sensor2.init();
    sensor2.setAddress(0x32);
    sensor2.setTimeout(1000);
    delay(10);
    digitalWrite(A3, HIGH);
    sensor3.init();
    sensor3.setAddress(0x33);
    sensor3.setTimeout(1000);
    delay(10);

    // Start continuous back-to-back mode (take readings as
    // fast as possible).  To use continuous timed mode
    // instead, provide a desired inter-measurement period in
    // ms (e.g. sensor.startContinuous(100)).
    sensor0.startContinuous(10);
    sensor1.startContinuous(10);
    sensor2.startContinuous(10);
    sensor3.startContinuous(10);			
}

void accel_init() {
  LIS3DHConfig config;
  config.setAccelMode(LIS3DH::RATE_400_HZ);

  bool setupSuccess = accel.setup(config);
  Serial.printlnf("setupSuccess=%d", setupSuccess);
}

void others_init() {
	// Line sensors
  	pinMode(FL, INPUT);
  	pinMode(FR, INPUT);
  	pinMode(BL, INPUT);
  	pinMode(BR, INPUT);
  	// Remote switch
  	pinMode(RS, INPUT);
  	// Car ESCs
  	pinMode(Lmotor, OUTPUT);
  	pinMode(Rmotor, OUTPUT);

  	// ***Remove for competition***
  	// ***Serial monitor***
  	Serial.begin(9600);	// *** need to modify before comp ***
}

void interrupt_init() {
	// Line sensors
	attachInterrupt(FL,FLISR,CHANGE);
  	attachInterrupt(FR,FRISR,CHANGE);
  	attachInterrupt(BL,BLISR,CHANGE);
  	attachInterrupt(BR,BRISR,CHANGE);
  	// Remote switch
  	attachInterrupt(RS,RSISR,CHANGE);
}

void ESC_init() {
	// Necessary for Servo objects
  	LESC.attach(Lmotor);
  	RESC.attach(Rmotor);
  	// Write stop command
  	LESC.writeMicroseconds(1500);
  	RESC.writeMicroseconds(1500);
}

void fuzzy_init() {
  Fuzzy* fuzzy = new Fuzzy();

  // Criando o FuzzyInput distancia
  FuzzyInput* distance = new FuzzyInput(1);
  // Criando os FuzzySet que compoem o FuzzyInput distancia 
  FuzzySet* small = new FuzzySet(0, 20, 20, 40); // Distancia pequena
  distance->addFuzzySet(small); // Adicionando o FuzzySet small em distance
  FuzzySet* safe = new FuzzySet(30, 50, 50, 70); // Distancia segura
  distance->addFuzzySet(safe); // Adicionando o FuzzySet safe em distance
  FuzzySet* big = new FuzzySet(60, 80, 80, 80); // Distancia grande
  distance->addFuzzySet(big); // Adicionando o FuzzySet big em distance
  
  fuzzy->addFuzzyInput(distance); // Adicionando o FuzzyInput no objeto Fuzzy
  
  // Criando o FuzzyOutput velocidade
  FuzzyOutput* velocity = new FuzzyOutput(1);
  // Criando os FuzzySet que compoem o FuzzyOutput velocidade 
  FuzzySet* slow = new FuzzySet(0, 10, 10, 20); // Velocidade lenta
  velocity->addFuzzySet(slow); // Adicionando o FuzzySet slow em velocity
  FuzzySet* average = new FuzzySet(10, 20, 30, 40); // Velocidade normal
  velocity->addFuzzySet(average); // Adicionando o FuzzySet average em velocity
  FuzzySet* fast = new FuzzySet(30, 40, 40, 50); // Velocidade alta
  velocity->addFuzzySet(fast); // Adicionando o FuzzySet fast em velocity
  
  fuzzy->addFuzzyOutput(velocity); // Adicionando o FuzzyOutput no objeto Fuzzy
  
  //-------------------- Montando as regras Fuzzy
  // FuzzyRule "SE distancia = pequena ENTAO velocidade = lenta"
  FuzzyRuleAntecedent* ifDistanceSmall = new FuzzyRuleAntecedent(); // Instanciando um Antecedente para a expresso
  ifDistanceSmall->joinSingle(small); // Adicionando o FuzzySet correspondente ao objeto Antecedente
  FuzzyRuleConsequent* thenVelocitySlow = new FuzzyRuleConsequent(); // Instancinado um Consequente para a expressao
  thenVelocitySlow->addOutput(slow);// Adicionando o FuzzySet correspondente ao objeto Consequente
  // Instanciando um objeto FuzzyRule
  FuzzyRule* fuzzyRule01 = new FuzzyRule(1, ifDistanceSmall, thenVelocitySlow); // Passando o Antecedente e o Consequente da expressao
  fuzzy->addFuzzyRule(fuzzyRule01); // Adicionando o FuzzyRule ao objeto Fuzzy
  
  // FuzzyRule "SE distancia = segura ENTAO velocidade = normal"
  FuzzyRuleAntecedent* ifDistanceSafe = new FuzzyRuleAntecedent(); // Instanciando um Antecedente para a expresso
  ifDistanceSafe->joinSingle(safe); // Adicionando o FuzzySet correspondente ao objeto Antecedente
  FuzzyRuleConsequent* thenVelocityAverage = new FuzzyRuleConsequent(); // Instancinado um Consequente para a expressao
  thenVelocityAverage->addOutput(average);// Adicionando o FuzzySet correspondente ao objeto Consequente
  // Instanciando um objeto FuzzyRule
  FuzzyRule* fuzzyRule02 = new FuzzyRule(2, ifDistanceSafe, thenVelocityAverage); // Passando o Antecedente e o Consequente da expressao
  fuzzy->addFuzzyRule(fuzzyRule02); // Adicionando o FuzzyRule ao objeto Fuzzy
  
  // FuzzyRule "SE distancia = grande ENTAO velocidade = alta"
  FuzzyRuleAntecedent* ifDistanceBig = new FuzzyRuleAntecedent(); // Instanciando um Antecedente para a expresso
  ifDistanceBig->joinSingle(big); // Adicionando o FuzzySet correspondente ao objeto Antecedente
  FuzzyRuleConsequent* thenVelocityFast = new FuzzyRuleConsequent(); // Instancinado um Consequente para a expressao
  thenVelocityFast->addOutput(fast);// Adicionando o FuzzySet correspondente ao objeto Consequente
  // Instanciando um objeto FuzzyRule
  FuzzyRule* fuzzyRule03 = new FuzzyRule(3, ifDistanceBig, thenVelocityFast); // Passando o Antecedente e o Consequente da expressao
  fuzzy->addFuzzyRule(fuzzyRule03); // Adicionando o FuzzyRule ao objeto Fuzzy
}

int distance = 8192;
int L_command = 1500;
int R_command = 1500;

void setup() {
	others_init();		// line, remote, esc, ***printing***
	tof_init();			// ToF and I2C
	accel_init();		// accelerometer
	interrupt_init();	// interrupts for lines and remote
	ESC_init();			// Car ESCs

	fuzzy_init();		// Fuzzy library************

  	// ***Set up web*** ****************************
  	// register cloud variables
	Particle.variable("distance", distance);
	Particle.variable("Left_ESC", L_command);
	Particle.variable("Right_ESC", R_command);
	// *********************************************

    while(!RSflag) {  // initial LOW
    	// Serial.println("Waiting for Start");**************
    	Particle.publish("Waiting for Start");
  	}
  	// Serial.println("Starting in 5 seconds...");***********
  	Particle.publish("Starting in 5 seconds...");
  	delay(5000);
  	// Serial.println("GO!");********************************
  	Particle.publish("GO!");
}

void loop(){
	// try acting on every input to stress test the ESCs

	// ******************************************
	// TODO:
	// 1. add thresholds for I/O
	// 2. Modify fuzzy function
	// 3. modify loop function
	// TEST
	// ******************************************

	// sensorx.readRangeContinuousMillimeters();
	if (sensor0.timeoutOccurred() || sensor1.timeoutOccurred() || sensor2.timeoutOccurred() || sensor3.timeoutOccurred()) { Serial.print(" SENSOR TIMEOUT"); }
	// xESC.writeMicroseconds(yyyy);
  
  	// **************************************************
  	// fuzzy->setInput(1, averageDistance);
  
  	// fuzzy->fuzzify();

  	// float output = fuzzy->defuzzify(1);
  
  	// // Serial.print("Distancia: ");
  	// // Serial.print(averageDistance);
  	// // Serial.print("Velocidade: ");
  	// // Serial.println(output);
  	// // wait 100 milli seconds before looping again
  	// delay(100);

  	// publish something
  	//***********************************************


  	// obligatory sampling from accelerometer
  	LIS3DHSample sample;
  	if(!accel.getSample(sample)) {
  		//Serial.println("no sample"); // ********************************
  		Particle.publish("no sample");
  	}

  	if(RSflag == HIGH) {
  		L_command = 1500;
    	R_command = 1500;
  	}

  	LESC.writeMicroseconds(L_command);
  	RESC.writeMicroseconds(R_command);
}