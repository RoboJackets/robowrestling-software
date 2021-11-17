## Simulator Documentation

### Running the Simulator

1. Open a terminal and locate the head of the repo: 

    `user:~/.../robowrestling-software/`

2. Build Cmake (First Time Only): 

    ```
    cmake .
    ```

3. Compile the Source Code:

    ```
    make
    ```

4. (Windows Only) Connect to Xming Display (Run each time a terminal is opened):

    ```
    export DISPLAY=:0
    ```

5. Run the Simulator:

    ```
    ./simulator/src/sim.sw 50 0 0 50 0 0 0
    ```

### Changing Configuration

Execute Command: `./sim.sw r1x r1y r1a r2x r2y r2a dt`

1. r1x: Robot 1 X - Distance left from Origin for Robot 1 in centimeters
2. r1y: Robot 1 Y - Distance up from Origin for Robot 1 in centimeters
3. r1a: Robot 1 Angle - Angle clockwise from 0 radians in PI radians
4. r2x: Robot 2 X - Distance left from Origin for Robot 2 in centimeters
5. r2y: Robot 2 Y - Distance up from Origin for Robot 2 in centimeters
6. r2a: Robot 2 Angle - Angle clockwise from PI radians in PI radians
7. dt: Simulator Timestep - 0 = Realtime Elapsed, >0 Set timestep in seconds

Default Parameters: `./sim.sw 25 25 0.25 0 25 0 0.01`
