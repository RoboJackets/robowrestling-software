main:
    - sensors:
        - inputs: arduino outputs as analog/digital values
        - outputs: 0/1 sensor values in line / distance sensor arrays
world_state:
    - input: sensor array updates
    - output: enum decision on position of robot and enemy
algorithms:
    - input: enum positions of robot and enemy
    - output: macro decisions of motors (set go forward, go back)
robot_action:
    - input: macro movements
    - output: -256/256 power levels for motors in form of motor array
main: 
    - motors:
        - inputs: -256/256 power levels for motors in form of motor array
        - outputs: direct writes to arduino