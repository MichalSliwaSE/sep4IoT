# SEP4-IoT

This repository is a part of a bigger Semester Project (SEP). It aims at connecting different tiers into a bigger and more complex project. The other two tiers are a Front-end and a Back-end.


# sep4_drivers
This repository contains a collection of drivers designed to to work with the hardware at SEP4 at Software Technology Engineering at VIA. All drivers are located in the lib/drivers directory.

### 1. dht11.h
The DHT11 is a basic digital temperature and humidity sensor. This driver allows for interfacing with the DHT11 to obtain temperature and humidity readings.

### 2. light.h
This driver controls the photoresistor and is capable of measuring the amount of light in the environment.

### 3. pc_comm.h
Facilitates communication to the PC over USB using UART. 

### 4. servo.h
This driver interfaces with the SG90 servo motor and can set it to a position ranging from 0 to 180 degrees.

### 5. uart.h
This driver facilitates UART (Universal Asynchronous Receiver-Transmitter) communication. It is utilized by both the pc_comm and wifi drivers to enable data transfer and communication functionalities.

### 6. wifi.h
This driver interfaces with the ESP8266 module, a Wi-Fi microchip with full TCP/IP stack and microcontroller capability. With this driver, you can connect to an Access Point (AP) and establish a TCP connection, and send and receive data through the TCP-connection.

### 7. co2.h
This driver measures CO2 levels present in the air ranging from 500 - 2000 ppm.

### 8. ph_sensor.h
This driver measures water pH within a range from 0 (pure acid) to 14 (pure base).

### 9. water_ec.h
This driver measures water electrical conductivity within a range of 0 (distilled water) to 5000 (industrial wastewater) microSiemens.

### 10. water_temperature.h
This driver measures water temperature in a range of 1 - 31 C.
