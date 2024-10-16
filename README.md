# Car-Project
Dual-Mode Bluetooth-Controlled Arduino Car
🚗 Overview
An Arduino-based smart car project featuring autonomous obstacle avoidance and manual Bluetooth control. This project demonstrates advanced control systems integration in a compact, DIY robotics platform.
🌟 Features

Dual control modes: autonomous and manual
Real-time obstacle detection and avoidance
Bluetooth Low Energy (BLE) wireless control
Custom mobile app for user interaction
Optimized motor control for precise movement

🎮 Control Systems
Autonomous Mode

Utilizes HC-SR04 ultrasonic sensor for obstacle detection
Implements custom algorithm for decision-making:

Scans environment continuously
Calculates optimal path based on sensor data
Adjusts motor speed and direction in real-time


Fallback mechanisms for unexpected obstacles

Manual Control

Bluetooth Low Energy (BLE) communication via HM10 module
Custom GATT services for efficient data transfer
Mobile app features:

Directional pad for movement control
Speed adjustment slider
Mode switching button
Real-time feedback on car status



Motor Control

L298N driver for precise DC motor management
PWM signals for variable speed control
Differential steering for smooth turns
Acceleration and deceleration algorithms for fluid movement

🛠 Hardware

Arduino Mega 2560
L298N Motor Driver
HC-SR04 Ultrasonic Sensor
HM10 Bluetooth Module
DC Motors (x2)
Car Chassis and Wheels
9V Battery
Jumper Wires

💻 Software

Arduino IDE
Dabble app 
All open source libraries 
![car_img_1](https://github.com/user-attachments/assets/143caa3a-6c31-4b76-824e-3241db2f5d9e)

![car_img_2](https://github.com/user-attachments/assets/31f5589d-d865-4a30-bd5e-f7fc40fafd59)

