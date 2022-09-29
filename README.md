# robowrestling-software

## Installation Guide

### C++ Setup

1. For Windows
    1. Install Linux Terminal: [Guide](https://www.windowscentral.com/install-windows-subsystem-linux-windows-10)
    2. Use your preferred code editor
    3. Follow the **For Linux** setup
    
1. For Linux
    1. Open a terminal and run the following commands:

        ```
        <sudo apt-get update>
        <sudo apt-get install c++>
        
        curl -fsSL https://cli.github.com/packages/githubcli-archive-keyring.gpg | sudo dd of=/usr/share/keyrings/githubcli-archive-keyring.gpg \
        && sudo chmod go+r /usr/share/keyrings/githubcli-archive-keyring.gpg \
        && echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/githubcli-archive-keyring.gpg] https://cli.github.com/packages stable main" |
        sudo tee /etc/apt/sources.list.d/github-cli.list > /dev/null \
        && sudo apt update \
        && sudo apt install gh -y

        ```
    
    2. Use your preferred code editor
 
1. For Mac
    1. Install Homebrew

            ```
            /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
            ```
    2. Install github cli
            ```
            brew install gh
            ```
 
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

6. If you did not install the Github Desktop App, authenticate with Github cli:
    1. run `gh auth login`
    2. pick the non-enterprise option 
    3. use https as preferred method (unless you want to make a ssh-key) 
    4. follow steps to login to github 

### Dependencies Installation

1. For Linux/Windows
    1. Open a terminal and run the following commands:
    
        ```
        sudo apt-get update
        sudo apt-get install cmake libsfml-dev
        ```
    
    2. (Windows Only) Install Xming: [Download](https://sourceforge.net/projects/xming/)

2. For Mac
    1. Open a terminal and run the following commands:
            
        1. Install Dependencies
            ```
            brew install cmake
            brew install sfml
            ```

### Platform IO Setup

1. Install VSCode: [Download](https://code.visualstudio.com/)

2. Install PlatformIO: [PlatformIO](https://platformio.org/) 
    1. Go to the extension tab in VSCode 
    2. Search for PlatformIO as install it

## [Simulator Documentation](simulator/SIMULATOR.md)

## [Strategy Documentation](strategy/STRATEGY.md)

## Useful Resources

1. Competition Rules: [All Japan Sumo](https://www.fsi.co.jp/sumo/robot/en/rule.html)
2. Arduino Code Library Documentation: [Reference Page](https://www.arduino.cc/reference/en/)
3. Serial Communication: [Teensy 3.6](https://www.pjrc.com/teensy/td_uart.html)
4. Teensy 3.6 Documentation: [Teensy 3.6](https://www.pjrc.com/store/teensy36.html)
5. Teensy Pinout: [Google Drive](https://drive.google.com/drive/folders/1ci8a4ckSqtLVcKN8qR22PUycx4mC5XRj)
