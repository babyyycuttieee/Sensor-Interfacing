# Sensor Interfacing

## Objectives

Upon completion of this laboratory session, the student should be able to:

1. Understand the concept of I2C in STM32 ARM MCU.
2. Design and develop a program to demonstrate the I2C functionality.

## Equipment

1. Personal computer running Microsoft Windows® 10 (and above) with a minimum of 8GB RAM running STM32CubeIDE, Digilent Waveform Generator and Arduino IDE.
2. STM32 Nucleo development board.
3. I2C Accelerometer.

## Safety

1. Ensure hands are dry when using the equipment or touching the switches.
2. Do not use plugs with cracks, signs of overheating (e.g., discoloration, charring, or deformation) or loosen parts.
3. Stop using the equipment if abnormal operating conditions occur, such as being too noisy or having signs of overheating.
4. Keep all equipment organized and easily reachable without bending or stretching.

## Theory

Besides the microcontroller, other devices, such as sensors, switches, displays, keypads, and motors, are important components in an Embedded System. The microcontroller is basically used as the brain or intelligent processing unit to interface with those devices to perform some automation task. A sensor is a device that is used to detect and respond to events or changes in its environment and then provide a corresponding output. A sensor is a type of transducer. An electric sensor converts a physical parameter, for example, temperature, pressure, light, humidity, speed, tilt, moisture, sound, seismic, and many more into an electric signal that can be processed by the microcontroller. The output signal can be an analog voltage changing based on the input physical quantity, or the output can be a digital number or provided in serial communication such as I2C or SPI. Therefore, the datasheet of the sensor is the important reference before interfacing the sensor to the microcontroller.

## Procedures

1. Refer to the datasheet of a sensor and connect it to the STM32 development board accordingly.
2. Create a new project in STM32Cube IDE and develop the program to read the sensor value and display it through the serial port.
3. Compile and debug the project to observe the output.

---
*This project is part of the course BENR3523 Embedded System Universiti Teknikal Malaysia Melaka.*
