#include <Arduino.h>
#include <world_state.hpp>
#include <robot_actions.hpp>
#include <algorithms.hpp>

const int leftSensor = 2;
const int middleSensor = 3;
const int rightSensor = 4;

const int rightPWM = 6;
const int rightDIR = 5;
const int leftPWM = 8;
const int leftDIR = 7;

const int LEFT_LINE = 23;
const int RIGHT_LINE = 22;

const int START_PIN = 0;

const char* lineStateToString(line_states state) {
  switch (state) {
    case LINE_BOTH_BLACK: return "LINE_BOTH_BLACK";
    case LINE_LEFT_WHITE: return "LINE_LEFT_WHITE";
    case LINE_RIGHT_WHITE: return "LINE_RIGHT_WHITE";
    case LINE_BOTH_WHITE: return "LINE_BOTH_WHITE";
    default: return "UNKNOWN_LINE";
  }
}

const char* enemyStateToString(enemy_states state) {
  switch (state) {
    case ENEMY_NONE: return "ENEMY_NONE";
    case ENEMY_LEFT: return "ENEMY_LEFT";
    case ENEMY_CENTER: return "ENEMY_CENTER";
    case ENEMY_RIGHT: return "ENEMY_RIGHT";
    case ENEMY_LEFT_CENTER: return "ENEMY_LEFT_CENTER";
    case ENEMY_CENTER_RIGHT: return "ENEMY_CENTER_RIGHT";
    case ENEMY_LEFT_RIGHT: return "ENEMY_LEFT_RIGHT";
    case ENEMY_ALL: return "ENEMY_ALL";
    default: return "UNKNOWN_ENEMY";
  }
}

int motors[2] = {255, 255};
int line_sensors[2] = {32, 790};
int ir_sensors[3] = {1, 1, 1};
int i = 0;

world_state state(ir_sensors, line_sensors);
robot_actions robot(motors);

void pullSensors();
void updateMotors();
void updateState();
void debug();

void setup() {
  pinMode(leftSensor, INPUT);
  pinMode(middleSensor, INPUT);
  pinMode(rightSensor, INPUT);

  pinMode(rightPWM, OUTPUT);
  pinMode(rightDIR, OUTPUT);
  pinMode(leftPWM, OUTPUT);
  pinMode(leftDIR, OUTPUT);

  pinMode(START_PIN, INPUT);

  Serial.begin(9600);
  Serial.println("Setup complete");
  
  // while (digitalRead(START_PIN) == 0 && i % 100 == 0) {
  //   Serial.println("Waiting");
  //   i++;
  // }
}

void loop() {
  // if (digitalRead(START_PIN) == 1 or true) {
  if (true) {
    pullSensors();
    updateMotors();
    updateState();
    debug();
  } else {
    motors[0] = 0;
    motors[1] = 0;
    updateMotors();
  }
  
}

void pullSensors() {
  ir_sensors[0] = digitalRead(leftSensor);
  ir_sensors[1] = digitalRead(middleSensor);
  ir_sensors[2] = digitalRead(rightSensor);

  line_sensors[0] = analogRead(LEFT_LINE);
  line_sensors[1] = analogRead(RIGHT_LINE);
}

void updateMotors() {
  robot.applyMotors();
}

void updateState() {
  line_states line = state.line_check();
  enemy_states enemy = state.enemy_pos();

  if (line == LINE_BOTH_BLACK) {
    robot.drive_backward(150);
  } else if (line == LINE_LEFT_WHITE) {
    robot.drive_right(150);
  } else if (line == LINE_RIGHT_WHITE) {
    robot.drive_left(200);
  } else {
    switch (enemy) {
      case ENEMY_CENTER:
        robot.drive_forward(100);
        break;

      case ENEMY_LEFT:
      case ENEMY_LEFT_CENTER:
        robot.drive_left(100);
        break;

      case ENEMY_RIGHT:
      case ENEMY_CENTER_RIGHT:
        robot.drive_right(100);
        break;

      case ENEMY_ALL:
        robot.drive_forward(150);
        break;

      case ENEMY_NONE:
      default:
        robot.drive_left(50);
        break;
    }
  }

}

void debug() {
  i ++;
  if (i % 513 == 0) {
    Serial.print(sizeof(int));
    Serial.print("IR: ");
    Serial.print(ir_sensors[0]);
    Serial.print(" ");
    Serial.print(ir_sensors[1]);
    Serial.print(" ");
    Serial.print(ir_sensors[2]);

    Serial.print(" | Line: ");
    Serial.print(line_sensors[0]);
    Serial.print(" ");
    Serial.println(line_sensors[1]);

    Serial.print(" | Motors: ");
    Serial.print(motors[0]);
    Serial.print(" ");
    Serial.println(motors[1]);

    line_states line = state.line_check();
    enemy_states enemy = state.enemy_pos();
    
    Serial.print("Line State: ");
    Serial.println(lineStateToString(line));

    Serial.print("Enemy State: ");
    Serial.println(enemyStateToString(enemy));
  }
}