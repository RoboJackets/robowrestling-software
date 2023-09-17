# robowrestling-software

## Installation Guide

### C++ Setup

1. For Windows
    1. Install Windows Subsystem for Linux (WSL): [Guide](https://www.windowscentral.com/install-windows-subsystem-linux-windows-10) (Ubuntu is fine unless you want to use another distribution)
    2. Use your preferred code editor (though VS Code is highly recommended)
    3. Follow the **For Linux** setup
    
1. For Linux
    1. Open a terminal and run the following commands:

        ```
        sudo apt-get update
        sudo apt-get install c++
        ```
    
    2. Use your preferred code editor (though VS Code is highly recommended)
 
1. For Mac
    1. Install the XCode command line tools with `xcode-select --install`
 
### Git/Github Setup
  
1. Linking Accounts
    1. Sign in to your Robojackets Account: [my.robojackets.org](my.robotjackets.org)
    2. Click your name in the top right, click "Profile," scroll down to "Linked Accounts" and link your GitHub and Google account
    
2. Update Identity: [Guide](https://docs.github.com/en/get-started/quickstart/set-up-git)
    1. Follow the **Setting Up Git** section if you do not already have Git set up

3. Generate a Personal Access Token (PAT) if needed (Make sure to not lose): 
    [Guide](https://docs.github.com/en/authentication/keeping-your-account-and-data-secure/creating-a-personal-access-token)

4. Download the Github Desktop App (Optional): [Download](https://desktop.github.com/)

5. Clone the robowrestling-software repository: [repo](https://github.com/RoboJackets/robowrestling-software)

### Dependencies Installation

1. For Linux/Windows with WSL
    1. Open a terminal and run the following commands:
    
        ```
        sudo apt-get update
        sudo apt-get install cmake libsfml-dev
        ```
    
    2. (Windows only *without* WSL) Install Xming: [Download](https://sourceforge.net/projects/xming/)

2. For Mac
    1. Open a terminal and run the following commands:
        1. Install Homebrew

            ```
            /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
            ```
            
        2. Install Dependencies
            ```
            brew install cmake
            brew install sfml
            ```

### PlatformIO Setup

1. Go to the [PlatformIO website](https://platformio.org/platformio-ide)

2. Click the "Get for VS Code" button and follow the install instructions
    - If you wish to use another IDE, you can try looking for instructions [on this page](https://platformio.org/install/integration). However, VS Code will work best (at least from my experience).

3. If you need to include common firmware modules and they aren't already included, you can open the platformio.ini file within each robot's folder (i.e. `firmware/3kg/Kirbi/platformio.ini` and add a build flag to `build_flags` in the format `-Ipath` (i.e. `-I../../CommonFirmware/src/3kg`.

## Useful Resources

1. Competition Rules: [All Japan Sumo](https://www.fsi.co.jp/sumo/robot/en/rule.html)
2. Arduino Code Library Documentation: [Reference Page](https://www.arduino.cc/reference/en/)
3. Serial Communication: [Teensy Website](https://www.pjrc.com/teensy/td_uart.html)
4. Teensy 4.1 Documentation (newer bots): [Teensy 4.1](https://www.pjrc.com/store/teensy41.html)
4. Teensy 3.6 Documentation (Kirbi): [Teensy 3.6](https://www.pjrc.com/store/teensy36.html)
5. Teensy Pinout: [Google Drive](https://drive.google.com/drive/folders/1ci8a4ckSqtLVcKN8qR22PUycx4mC5XRj)
