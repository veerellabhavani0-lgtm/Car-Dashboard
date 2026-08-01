# CAN Node Communication Automotive

**Author:** V.BHAVANISANKAR  
**Date:** 13/07/2026

## Overview
This project contains the firmware and configuration for three Electronic Control Units (ECU1, ECU2, and ECU3) in the CAN node communication automotive system.

## Description
ECU1, ECU2, and ECU3 are electronic control units that communicate via the CAN (Controller Area Network) protocol in this automotive application. Each ECU has its own dedicated project folder with specific firmware and configuration files.

## ECU Functions

### ECU1 - Speed and Gear Transmission
- Reads vehicle speed from sensors using ADC
- Reads gear position from digital keypad
- Transmits speed data (2 bytes) over CAN with message ID: SPEED_MSG_ID
- Transmits gear position data (2 bytes) over CAN with message ID: GEAR_MSG_ID
- Supports gear positions: N, 1, 2, 3, 4, 5, R, C

### ECU2 - RPM and Indicator Transmission
- Reads engine RPM from sensors using ADC
- Reads indicator status (turn signals) from digital keypad
- Transmits RPM data (4 bytes) over CAN with message ID: RPM_MSG_ID
- Transmits indicator status (1 byte) over CAN with message ID: INDICATOR_MSG_ID

### ECU3 - Display and Data Reception
- Receives CAN messages from ECU1 and ECU2
- Displays vehicle data on Character LCD (CLCD)
- Shows: Speed (SP), Gear (G), RPM, and Indicator (IND) status
- Includes indicator blink functionality
- Processes CAN bus data using message handler

## Technical Specifications
- **Microcontroller:** PIC18F4580 (based on xc.h)
- **Clock Frequency:** 200 MHz
- **Communication Protocol:** CAN (Controller Area Network)
- **Peripherals Used:**
  - ADC (Analog-to-Digital Converter)
  - UART (Universal Asynchronous Receiver-Transmitter)
  - Digital Keypad
  - Character LCD (CLCD)
  - Timer0 (for timing operations)

## Project Structure
```
CAN_node_communication_automotive_25044_020/
├── ECU1.X/          # Speed and gear transmission unit
├── ECU2.X/          # RPM and indicator transmission unit
├── ECU3.X/          # Display and data reception unit
└── README.md        # This file
```

## Building the Project
Each ECU folder contains a Makefile for building the firmware. Navigate to the respective ECU folder and run:
```bash
make
```

## Development Environment
- **IDE:** MPLAB X IDE
- **Compiler:** XC8 (for PIC microcontrollers)
- **Microcontroller:** PIC18F4580 (based on xc.h)

### Using MPLAB X IDE
1. Open MPLAB X IDE
2. File → Open Project → Select ECU1.X, ECU2.X, or ECU3.X folder
3. Build the project using the Build button or Ctrl+F11
4. Program the device using the Make and Program button or Shift+F11
