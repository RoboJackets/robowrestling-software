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
    ./simulator/src/sim.sw
    ```


### File Structure

1. `./include/simulator/` : Header files for the Simulator
2. `./res/` : Resource files for the Simulator
3. `./src/` : Source files for the Simulator
4. `./src/simulator/physics/` : Handlers for the physics and collision calculations
5. `./src/simulator/robots/` : Sensor configurations of robots
6. `./src/simulator/sensors/` : Data implementations for sensors



