# robowrestling-software

## Installation Guide

### C++ Setup

1. For Mac
    1. Install XCode

1. For Windows
    1. Install Linux Terminal: [Guide](https://www.windowscentral.com/install-windows-subsystem-linux-windows-10)
    2. Use your preferred code editor
    3. Follow the **For Linux** setup
    
1. For Linux
    1. Open a terminal and run the following commands:

        ```
        <sudo apt-get update>
        <sudo apt-get install c++>
        ```
    
    2. Use your preferred code editor
  
### Git/Github Setup
  
1. Linking Accounts
    1. Sign in to your Robojackets Account: [my.robojackets.org](my.robotjackets.org)
    2. Go to profile and add accounts for both github and google
    
2. Update Identity: [Guide](https://docs.github.com/en/get-started/quickstart/set-up-git)
    1. Follow the **Setting Up Git** section

3. Generate a PAT if needed (Make sure to not lose): 
    [Guide](https://docs.github.com/en/authentication/keeping-your-account-and-data-secure/creating-a-personal-access-token)

4. Download the Github Desktop App (Optional): [Download](https://desktop.github.com/)

5. Clone the robowrestling-software repository: [repo](https://github.com/RoboJackets/robowrestling-software)

### Dependencies Installation

1. For Linux/Windows
    1. Open a terminal and run the following commands:
    
        ```
        <sudo apt-get update>
        <sudo apt-get install cmake libsfml-dev>
        ```
    
    2. (Windows Only) Install Xming: [Download](https://sourceforge.net/projects/xming/)

2. For Mac
    1. Install XCode extensions for Cmake and SFML

### Arduino IDE Setup

1. Install Arduino IDE: [Download](https://www.arduino.cc/en/software)

2. Install Teensyduino: [Download](https://www.pjrc.com/teensy/td_download.html)

## Running the Simulator

1. For Linux
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
    
2. For Mac
    1. **TODO**

### Changing Configuration

## Strategies

### Making a new Strategy

1. Develop a state machine diagram to reference. Example:

    ![state_strategy](/strategy/diagrams/state_strategy.png)
    
2. Create a new header and cpp file in the `/strategy/include/` and `/strategy/src/` folders respectively

3. Use the following templates:
    1. Header:
    
        ``` 
        Code
            Here
        ```
        
    2. Cpp:
    
        ``` 
        Code
            Here
        ```
    
4. Add the Strategy to the build path
    1. Locate `/strategy/CMakeLists.txt`
    2. Add the Strategy to the list `<add_library(Strategies src/**STRATEGY_NAME_HERE**.cpp ...`
    
5. Select the Strategy to run on a compatible Robot
    1. Locate `/simulator/include/simulator/sim.h`
    2. Include the Strategy for Selection
    
        ```
        #include <strategy/**STRATEGY_NAME_HERE**.h>
        ```
        
    3. Change a Robot's selection `<#define STRATEGY_1 **STRATEGY_NAME_HERE**>`
