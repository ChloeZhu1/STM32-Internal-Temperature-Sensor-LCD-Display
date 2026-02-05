# STM32-Internal-Temperature-Sensor-LCD-Display
A bare-metal STM32F10x embedded systems project that measures temperature using the on-chip internal temperature sensor and displays the result in real time on an LCD screen.

This repository contains a bare-metal STM32F10x embedded systems project that measures temperature using the on-chip internal temperature sensor and displays the result in real time on an LCD screen.
The project is implemented in C using the STM32 Standard Peripheral Library (StdPeriph) and targets an STM32F103 (ARM Cortex-M3) microcontroller. It demonstrates core embedded concepts including ADC configuration, sensor calibration, LCD interfacing, and real-time data display.

## Features

* 📟 Real-time temperature measurement using STM32 internal sensor
* 🔢 ADC data acquisition and voltage-to-temperature conversion
* 🧮 Floating-point computation on Cortex-M3
* 🖥 LCD text rendering with formatted output
* ⏱ Periodic sampling with software delay
* 🧩 Modular project structure (CMSIS, drivers, user code)

## Hardware & Tools

Target MCU
* STM32F10x series (e.g., STM32F103)
  
Peripherals Used
* Internal temperature sensor
* ADC (12-bit)
* LCD display
* USART1 (debug / expansion)
  
Development Environment
* Keil MDK (uVision) or compatible ARM toolchain
* STM32 Standard Peripheral Library

## Project Structure
```graphql
.
├── CMSIS/          # ARM CMSIS core and startup code
├── FWLIB/          # STM32 Standard Peripheral Library drivers
│   ├── inc/        # Peripheral header files
│   └── src/        # Peripheral driver implementations
├── USER/           # User application code (main logic)
│   └── main.c
├── LISTING/        # Compiler-generated listing files
├── OUTPUT/         # Build outputs (HEX/ELF/AXF)
└── README.md
```
## How It Works
1. ADC Initialization
The ADC is configured to sample the STM32 internal temperature sensor.
2. Data Acquisition
A 12-bit ADC value (0–4095) is read periodically.
3. Voltage Conversion
The ADC value is converted to sensor voltage assuming a 3.3 V reference.
4. Temperature Calculation
Temperature is computed using the STM32 datasheet linear approximation:<br>
$T(°C) = \frac{V_{25} - V_sense}{AvgSlope}+25$<br>
where:
* $V_{25} \approx 1.43V $
* $AvgSlope \approx 4.3mV/°C$
5. Display Output
The temperature is formatted and displayed on the LCD in real time.

## System Diagram
**Hardware Block Diagram**
```text
+-------------------------+
|        STM32F103        |
|                         |
|  +-------------------+  |
|  | Internal Temp     |  |
|  | Sensor            |  |
|  +---------+---------+  |
|            | ADC         |
|            v             |
|      +-----------+       |
|      |   ADC     |       |
|      | 12-bit    |       |
|      +-----------+       |
|            |             |
|     Temperature           |
|     Computation           |
|            |             |
|      +-----------+       |
|      |   LCD     |<------+
|      | Display   |
|      +-----------+
|
+-------------------------+
```
**Data Flow**
1. Internal temperature sensor produces an analog voltage
2. ADC samples the voltage
3. Firmware converts voltage → temperature (°C)
4. Result is rendered on the LCD
   
**Software Architecture**
```text
USER/
 ├── main.c
 │    ├── System initialization
 │    ├── ADC sampling loop
 │    ├── Temperature calculation
 │    └── LCD update
 │
 ├── temperature.c
 │    └── ADC configuration & sensor readout
 │
 ├── lcd.c
 │    └── LCD driver and text rendering
 │
 └── delay.c
      └── Timing utilities
```
This layered structure cleanly separates:
* Hardware access
* Sensor logic
* Display logic
* Application control
  
## Example Output
```ini
Temperature = 27.356 °C
```
(Displayed directly on the LCD screen)

## Notes on Accuracy
* The STM32 internal temperature sensor is intended for trend monitoring, not precise ambient temperature measurement.
* Absolute accuracy varies between chips and typically requires calibration for high-precision applications.

## Project Value
This project demonstrates:

* Low-level microcontroller programming
* ADC configuration and sensor modeling
* Embedded floating-point computation
* Peripheral driver integration
* Real-time embedded application structure

