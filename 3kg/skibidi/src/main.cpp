#include "Strategies/Strategy.hpp"
#include "Strategies/Defense.hpp"
#include "Strategies/Matador.hpp"
#include "Strategies/SlammyWhammyImproved.hpp"
#include "Strategies/Track.hpp"
#include "Skibidi.hpp"

#define DIP_HI 26
#define DIP_MID 27
#define DIP_LO 33

Skibidi *skibidi;
State state;
Strategy *strategy;
Strategy *strategies[8];

unsigned short selected_strategy = 0;

Adafruit_SSD1306 disp(128, 64, &Wire2, -1);
void display_debug_info(State* state, bool running);

void setup(void) {
    // Serial initialization (for debugging)
    Serial.begin(9600);
    Serial.println("Init");
    // Pin initialization -- handled by the things that use them
    // State initialization
    skibidi = new Skibidi();
    state = {
        .active_line_sensors = {
            {Position::FRONT_LEFT,  false},
            {Position::FRONT_RIGHT, false},
            {Position::BACK_LEFT,   false},
            {Position::BACK_RIGHT,  false},
        },
        .active_ir_sensors = {
            {IrDirection::RIGHT,        false},
            {IrDirection::MID_RIGHT,    false},
            {IrDirection::CENTER_RIGHT, false},
            {IrDirection::CENTER,       false},
            {IrDirection::CENTER_LEFT,  false},
            {IrDirection::MID_LEFT,     false},
            {IrDirection::LEFT,         false},
        },
    };
    strategies[0] = new SlammyWhammy(35, 25);
    strategies[1] = new Matador(50, 30);
    strategies[2] = new Defense();
    strategies[3] = new Track(50, 30);
    //strategy = new SlammyWhammy(50, 30);

    // Sensor initialization
    skibidi->initialize_sensors();

    if (!disp.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("Failed to init display\n");
        while (true) { delay(5000); }
    }
}

char* linetos(Position ir) {
    switch (ir) {
        case Position::FRONT_LEFT:  return (char*)"FRONT_LEFT\0";
        case Position::FRONT_RIGHT: return (char*)"FRONT_RIGHT\0";
        case Position::BACK_LEFT:   return (char*)"BACK_LEFT\0";
        case Position::BACK_RIGHT:  return (char*)"BACK_RIGHT\0";
        case Position::NONE:        return (char*)"NONE\0";
    }
    return (char*)"NONE";
}

void loop(void) {
    // TODO: move into update_state
    StartModule* start_module = skibidi->get_start_module();

    // Update sensors
    skibidi->update_state(&state);
    display_debug_info(&state, start_module->is_started());

    if (!start_module->is_started()) {
        selected_strategy = (digitalRead(DIP_HI) << 2) | (digitalRead(DIP_MID) << 1) | digitalRead(DIP_LO);
        strategy = strategies[selected_strategy > 3 ? 3 : selected_strategy];

        state.driving_state = DrivingState::MBRAKE;
        state.motor_speed = 0;
        state.tank_drive = false;
        skibidi->execute_action(&state);
        return;
    }

    // Checking if we hit the border somewhere
    if (state.emergency_mvmt && millis() - state.emerg_started_millis < EMERG_MVMT_MILLIS) {
        // do nothing, continue backing up
    } else if (state.active_line_sensors[Position::FRONT_LEFT] || state.active_line_sensors[Position::FRONT_RIGHT]) {
        // Emergency reverse
        state.emergency_mvmt = true;
        state.emerg_started_millis = millis();
        state.driving_state = DrivingState::MBACKWARD;
        state.motor_speed = 25;
    } else {
        // Make decision
        state.emergency_mvmt = false;
        strategy->make_decision(&state);
    }

    // Execute decision
    skibidi->execute_action(&state);
}

void display_debug_info(State* state, bool started) {
    char* motorDir;
    switch (state->driving_state) {
        case MFORWARD:
            motorDir = "FWD\0";
            break;
        case MBACKWARD:
            motorDir = "BWD\0";
            break;
        case MTURN_LEFT:
            motorDir = "TUL\0";
            break;
        case MTURN_RIGHT:
            motorDir = "TUR\0";
            break;
        case MBRAKE:
            motorDir = "BRK\0";
            break;
        case MCOAST:
            motorDir = "CST\0";
            break;
    }
    disp.clearDisplay();
    disp.setTextSize(1);
    disp.setTextColor(WHITE);
    disp.setCursor(0, 0);

    disp.println("------ SKIBIDI ------");
    disp.printf("%s         STRAT: %hu\n", started ? "STRT" : "HALT", selected_strategy);
    disp.printf("  L %d %d %d %d %d %d %d R\n",
        state->active_ir_sensors[IrDirection::LEFT],
        state->active_ir_sensors[IrDirection::MID_LEFT],
        state->active_ir_sensors[IrDirection::CENTER_LEFT],
        state->active_ir_sensors[IrDirection::CENTER],
        state->active_ir_sensors[IrDirection::CENTER_RIGHT],
        state->active_ir_sensors[IrDirection::MID_RIGHT],
        state->active_ir_sensors[IrDirection::RIGHT]
    );
    disp.printf("EBK:%s  LL:%s  LR:%s\n", state->emergency_mvmt ? "T" : "F", state->active_line_sensors[Position::FRONT_LEFT] ? "1" : "0", state->active_line_sensors[Position::FRONT_RIGHT] ? "1" : "0");
    disp.printf("DST: %s\n", motorDir);
    disp.println("6");
    disp.println("7");
    disp.println("8");
    disp.display();
}
