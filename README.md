# Automatic-regulation-of-the-heater

Project topic: “Automatic radiator control”.


---

# Program concept

- The ESP32 will collect data from the temperature sensor and RTC, and then compare the read temperature with the target temperature.
- The user will be able to set the target temperature with a potentiometer or with a button.
- The OLED display will show the current room temperature.
- Depending on the temperature, the thermoelectric actuator will either close or open the heat supply to the heater.
- The LEDs will inform the user of our product in what position our actuator is (whether closed (red LED) and open (green LED))
The "Autonomous Radiator Control" project will allow efficient and convenient control of the temperature in the room, which can contribute to saving energy and providing comfort to the user.
In the future, the project can be expanded through a phone application that would allow the user to control radiators throughout the house from anywhere on earth, thanks to Internet access.


---

# Component list

- ESP32
- Temperature sensor
- RTC module
- OLED display
- Contact board
- Potentiometer
- Optotriac
- Thermoelectric actuator
 - Electronic components: resistors, LEDs
- 9V battery, power supply module
- Monostable button

---


# Electrical diagram 

The electrical diagram was made in Autodesk EAGLE software.

![image](https://github.com/user-attachments/assets/1df316c9-2dca-4120-b561-2bc4e2250f0c)

---

# Controller housing

The enclosure was designed in Autodesk Inventor.

![image](https://github.com/user-attachments/assets/a60971ef-3ca5-4b23-b71f-3651ddef213d)

---
