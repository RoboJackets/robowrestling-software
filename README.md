# robowrestling-software

## Setup Guide

### PlatformIO Setup

PlatformIO is the platform that we use to program our bot, using the Arduino library.
It is most well-integrated with VS Code. Therefore, VS Code is the recommended editor for our bot code.
If you don't have VS Code, you can get it from [here](https://code.visualstudio.com/) or through your OS's package manager
(winget for Windows, brew or MacPorts for macOS, or whatever your Linux distro uses).

There is some other support for other editors, but you'll be mostly on your own.
In theory, you could use something like Vim and use the PlatformIO command-line tools, but your code completion and error detection may not work.

The VS Code installation instructions are as follows:

1. Go to the [PlatformIO website](https://platformio.org/platformio-ide)

2. Click the "Get for VS Code" button and follow the install instructions
    - If you wish to use another IDE, you can try looking for instructions [on this page](https://platformio.org/install/integration). However, VS Code will work best (at least from my experience).

3. When you open a folder to work on code, make sure that the folder you open has a `platformio.ini` file directly in it. It has to be directly in the folder.
    - If you're going to make a new project, then
        - Click the PlatformIO icon on the side bar of VS Code and click "Create New Project"
        - In the new tab, click "New Project" on the right
        - Select your board (likely a Teensy 4.1) and the Arudino framework
        - Give it a name and optionally choose a location by unchecking "Use Default Location"
    - Alternatively, you can use `pio init` in a new folder if you have the CLI installed
 

### Git/Github Setup

This is the repository for our code. The other robowrestling repository isn't used for software.
If you haven't used Git before, GitHub has a tutorial [here](https://docs.github.com/en/get-started/getting-started-with-git).
The general workflow is
1. `git pull` (to get the most recent code from GitHub)
2. Write code
3. `git add .` (to add code to the repo)
4. `git commit -m "Short and descriptive message"`
5. `git push` (to send your code to GitHub)

Please be sure to work in your own branch (`git branch <name>` and then `git checkout <branch name>`) unless otherwise working with someone else.
  
1. Linking Accounts
    1. Sign in to your Robojackets Account: [my.robojackets.org](my.robotjackets.org)
    2. Click your name in the top right, click "Profile," scroll down to "Linked Accounts" and link your GitHub and Google account
    
2. Update Identity: [Guide](https://docs.github.com/en/get-started/quickstart/set-up-git)
    1. If you do not have Git installed on your computer, install it from [here](https://git-scm.com/downloads) or with your OS's package manager.

3. Generate a Personal Access Token (PAT) if needed (Make sure to not lose): 
    [Guide](https://docs.github.com/en/authentication/keeping-your-account-and-data-secure/creating-a-personal-access-token)
    1. If you know how to use SSH keys, you may also use those.

4. Download the Github Desktop App (Optional): [Download](https://desktop.github.com/)

5. Clone the robowrestling-software repository using `git clone <url>`: [repo](https://github.com/RoboJackets/robowrestling-software)


## C++ Intro

If you haven't used C++ or Arduino before, don't worry.
There are lots of tutorials on the internet and you can ask the Software STL or other teammates for help.

Here are some basic things to get you started with both C++ and Arduino.

```cpp
// file: main.cpp

#include <Arduino.h>  // adds the Arduino library
// May have other #include statements here to add other things
// For example, if you have classes for things

// Example pins
// #define <name> <value> basically makes an alias
#define LEFT_MOTOR_OUT_PIN 1
#define RIGHT_MOTOR_OUT_PIN 2
#define LIDAR_IN_PIN 3

// Setup function that runs once when the robot first starts up
// Put stuff here for setup, e.g. starting Serial connections and
// setting up pins
void setup() {
    pinMode(LIDAR_IN_PIN, INPUT);  // see how the #define'd LIDAR_IN_PIN is used here?
    pinMode(LEFT_MOTOR_OUT_PIN, OUTPUT);
    pinMode(RIGHT_MOTOR_OUT_PIN, OUTPUT);
}

// This function runs *after* the setup function does and will constantly loop
// while the bot runs
void loop() {
    // This is example code and may not work in an actual bot
    // Highly depends on your hardware
    
    // This code will do the following:
    // If the LIDAR_IN_PIN reads a 1 (sees something), then run the motors at 100%
    // Otherwise, turn in place and check again later if the lidar sees something
    if (digitalRead(LIDAR_IN_PIN) == 1) {
        analogWrite(LEFT_MOTOR_OUT_PIN, 100);
        analogWrite(RIGHT_MOTOR_OUT_PIN, 100);
    } else {
        analogWrite(LEFT_MOTOR_OUT_PIN, -100);
        analogWrite(RIGHT_MOTOR_OUT_PIN, 100);
    }
}
```

## Useful Resources

1. Competition Rules: [All Japan Sumo](https://www.fsi.co.jp/sumo/robot/en/rule.html)
2. Arduino Code Library Documentation: [Reference Page](https://www.arduino.cc/reference/en/)
3. Serial Communication: [Teensy Website](https://www.pjrc.com/teensy/td_uart.html)
4. Teensy 4.1 Documentation (newer bots): [Teensy 4.1](https://www.pjrc.com/store/teensy41.html)
4. Teensy 3.6 Documentation (Kirbi): [Teensy 3.6](https://www.pjrc.com/store/teensy36.html)
5. Teensy Pinout: [Google Drive](https://drive.google.com/drive/folders/1ci8a4ckSqtLVcKN8qR22PUycx4mC5XRj)
