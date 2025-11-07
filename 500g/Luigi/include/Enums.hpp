#ifndef ENUMS_HPP
#define ENUMS_HPP

// Put all shared enums here:

enum LinePosition { OFF_LINE, LEFT_LINE, RIGHT_LINE, CENTER_LINE };
enum EnemyPosition { NONE, LEFT, MIDLEFT, FRONT, FARFRONT, RIGHT, MIDRIGHT };
enum RobotMode { AVOID_LEFT, AVOID_RIGHT, ATTACK };
enum Behavior { NO, TURN_AROUND, TURN_LEFT, TURN_RIGHT };
// (later) enum RobotState { IDLE, FOLLOW_LINE, AVOID_OBSTACLE, PATROL, ATTACK };

#endif