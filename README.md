# arduino-read-data-flight
This repository contains the Arduino code and system documentation for a lightweight and low-cost GPS logging system mounted on a commercial drone (SG906 MAX2 BEAST 3E). The system is based on the Arduino Mega 2560 platform and records data using the u-blox NEO-6M GPS module, and stores the data on a microSD card.

# Components
1. Arduino Mega 2560
2. u-blox NEO-6M GPS module
3. SD card module
4. LiPo 3.7V 500mAh battery
5. MT3608 step-up converter
6. OFF-ON switch

# Usage
Upload arduino_read_data.ino code to Arduino Mega (or other Arduino platform). The system logs GPS data automatically when powered on. The collected .csv file is used to visualize drone's flight path in 2D and 3D format using different softwares.

# Collected data format
Every flight has its unique name and all collected data is in .csv format.
One row contains: Time,Latitude,Longitude,Altitude(m),Satellites,HDOP,Speed(km/h)

# Citation
If you use this system or code in your work, please cite the related paper or link back to this repository.
