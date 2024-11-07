# **Servo Control with STM32F429ZI Discovery Board**

## Description
This project controls a servo motor using the STM32F429ZI Discovery board. The board is connected to a computer via UART, allowing commands to be sent directly from the computer to control servo movements. The board decodes incoming commands and adjusts the servo accordingly, making it ideal for applications that require precise and remote motor control.

## Key Components
- **Microcontroller**: STM32F429ZI Discovery Board
- **Servo Motor**: Controlled via PWM signals from the STM32 board
- **UART Connection**: Communication between the STM32 board and computer to receive commands

## Features
- **Command-Based Control**: Control servo actions with commands sent over UART.
- **Real-Time Positioning**: Set specific angles or perform calibration via decoded commands.
- **Responsive Servo Movement**: Commands are processed quickly for real-time adjustments.

## Commands
The STM32 board decodes the following commands:
- **ID**: Responds with the board’s ID (`DISCO_F429ZI`).
- **GOTO <angle>**: Moves the servo to the specified angle (0-180 degrees).
- **CALIB**: Calibrates the servo to a known starting position.
- **STEP <value>**: Moves the servo by a step size of `<value>`.

## Requirements
To compile and run the project, you will need:
- **STM32CubeIDE** or **Keil uVision** for code development and debugging.
- **STM32 HAL Library**: Used for UART and PWM configuration.
- **Servo Motor** compatible with PWM control.
- **Serial Communication**: Terminal program like PuTTY to send commands over UART.

## Setup and Installation
1. **Clone the Repository**:
   ```bash
   git clone https://github.com/krzyslov/DISCO_F429ZI_servo.git
   cd DISCO_F429ZI_servo
   ```

2. **Open the Project**:
   - Load the project files in STM32CubeIDE or Keil uVision.
   - Connect the STM32F429ZI Discovery board to your computer via USB.

3. **Build and Flash the Code**:
   - Compile the project and flash the firmware onto the STM32F429ZI Discovery board.

## Usage
1. **Connecting**: Open a serial terminal (e.g., PuTTY) and connect to the board’s COM port at the specified baud rate.
2. **Sending Commands**: Type commands directly in the terminal to control the servo.

### Example Commands
- **ID**: `id`  
  Returns: `DISCO_F429ZI`

- **Go to specific angle**: `goto 90`  
  Moves the servo to 90 degrees.

- **Calibrate Servo**: `calib`  
  Calibrates the servo to the starting position.

- **Step Movement**: `step 10`  
  Moves the servo by 10 degrees.

## Code Overview
- **Command Decoding**: Located in [dekodowanie.cpp](https://github.com/krzyslov/DISCO_F429ZI_servo/blob/main/dekodowanie.cpp), this module parses incoming strings, identifies keywords (e.g., `id`, `goto`), and translates them into servo control commands.
- **Main Control Loop**: In [main.cpp](https://github.com/krzyslov/DISCO_F429ZI_servo/blob/main/main.cpp), the loop receives UART input, calls `DecodeMsg`, and executes corresponding servo commands based on decoded tokens.
- **Servo Control**: The [servo.cpp](https://github.com/krzyslov/DISCO_F429ZI_servo/blob/main/servo.cpp) file manages the servo’s physical movement. It includes functions to move the servo to a specified angle, calibrate its starting position, and handle incremental steps. Key functions include `ServoCallib()` for calibration, `GoTo()` for setting an exact angle, and `Step()` for moving in defined increments.
- **LED Control**: In [led.cpp](https://github.com/krzyslov/DISCO_F429ZI_servo/blob/main/led.cpp), the LED indicators are managed to reflect the servo’s movement. LEDs light up based on the current servo position, providing visual feedback for the servo’s activity and positioning.
