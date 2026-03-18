# Smart Agriculture System (Arduino + Tinkercad)

An automated smart agriculture system designed using Arduino and simulated in Tinkercad.
This project monitors environmental parameters and automates irrigation, ventilation, and security for efficient and safe farming.

---

## 🔗 Tinkercad Simulation

[Click here to view the live simulation](https://www.tinkercad.com/things/hg5rS0qFnWG-smartagriculturesystem)

---

## Features

*  Temperature Monitoring (TMP36 Sensor)
*  Humidity Detection
*  Soil Moisture-Based Irrigation System
*  Intruder Detection using Ultrasonic Sensor
*  Buzzer Alert System
*  Automatic Air Vent Control (Servo Motor)
*  LCD Display for Real-Time Monitoring

---

##  Project Overview

This system is designed to automate greenhouse/agriculture operations by continuously monitoring environmental conditions such as temperature, humidity, and soil moisture.

Based on sensor data:

* Water pump turns ON/OFF automatically
* Air vents open/close using a servo motor
* Alerts are generated if an intruder is detected

Such smart systems help reduce manual effort, improve crop health, and optimize water usage in modern agriculture .

---

## Components Used

* Arduino Uno
* 16x2 LCD Display
* Ultrasonic Sensor (HC-SR04)
* Servo Motor
* Buzzer
* Soil Moisture Sensor
* TMP36 Temperature Sensor
* Humidity Sensor
* Water Pump (Motor)

---

## Pin Configuration

| Component            | Pin                |
| -------------------- | ------------------ |
| LCD RS, E, D4–D7     | 12, 11, 5, 4, 3, 2 |
| Ultrasonic Trigger   | 10                 |
| Ultrasonic Echo      | 8                  |
| Servo Motor          | 9                  |
| Buzzer               | 7                  |
| Soil Moisture Sensor | A0                 |
| Temperature Sensor   | A1                 |
| Humidity Sensor      | A2                 |
| Water Pump (Motor)   | 6                  |

---

## Working Principle

1. Ultrasonic sensor detects nearby objects (intruders)
2. Temperature & humidity are displayed on LCD
3. If humidity > 60% → air vents open automatically
4. If soil moisture is low → water pump turns ON
5. If intruder detected → buzzer alert is triggered

---

## Project Preview

### Circuit Diagram

![Circuit](docs/circuit_diagram.png)

### System Setup

![Setup](images/setup.jpg)


## Simulation Platform

This project was built and tested using **Tinkercad Circuits**, an online platform for simulating Arduino-based electronics projects.

---

## Author

**Your Name**
Nirupama Sahu

---

[1]: https://rsisinternational.org/journals/ijriss/view/simulation-of-arduino-based-greenhouse-monitoring-system-using-tinkercad?utm_source=chatgpt.com "Simulation of Arduino-Based Greenhouse Monitoring System Using TinkerCAD | IJRISS"
