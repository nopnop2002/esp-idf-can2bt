# esp-idf-can2bt
CAN(TWAI) to Bluetooth bridge for ESP-IDF.

<img width="864" height="576" alt="Image" src="https://github.com/user-attachments/assets/3de84e18-a1b7-4b2a-a441-d7bd21c8ea50" />

<img width="960" height="720" alt="Image" src="https://github.com/user-attachments/assets/742401d7-7c45-4d35-8d8c-142c25332918" />

# Software requirements
ESP-IDF V5.0 or later.   
ESP-IDF V4.4 release branch reached EOL in July 2024.   

# Hardware requirements

- SN65HVD23x CAN-BUS Transceiver   
SN65HVD23x series has 230/231/232.   
They differ in standby/sleep mode functionality.   
Other features are the same.   

- Termination resistance   
I used 150 ohms.   

# Wireing   
|SN65HVD23x||ESP32|ESP32-S2/S3|ESP32-C3/C6||
|:-:|:-:|:-:|:-:|:-:|:-:|
|D(CTX)|--|GPIO21|GPIO17|GPIO0|(*1)|
|GND|--|GND|GND|GND||
|Vcc|--|3.3V|3.3V|3.3V||
|R(CRX)|--|GPIO22|GPIO18|GPIO1|(*1)|
|Vref|--|N/C|N/C|N/C||
|CANL|--||||To CAN Bus|
|CANH|--||||To CAN Bus|
|RS|--|GND|GND|GND|(*2)|

(*1) You can change using menuconfig. But it may not work with other GPIOs.  

(*2) N/C for SN65HVD232


# Test Circuit   
```
   +-----------+   +-----------+   +-----------+ 
   | Atmega328 |   | Atmega328 |   |   ESP32   | 
   |           |   |           |   |           | 
   | Transmit  |   | Receive   |   | 21    22  | 
   +-----------+   +-----------+   +-----------+ 
     |       |       |       |       |       |   
   +-----------+   +-----------+     |       |   
   |           |   |           |     |       |   
   |  MCP2515  |   |  MCP2515  |     |       |   
   |           |   |           |     |       |   
   +-----------+   +-----------+     |       |   
     |       |       |       |       |       |   
   +-----------+   +-----------+   +-----------+ 
   |           |   |           |   | D       R | 
   |  MCP2551  |   |  MCP2551  |   |   VP230   | 
   | H      L  |   | H      L  |   | H       L | 
   +-----------+   +-----------+   +-----------+ 
     |       |       |       |       |       |   
     +--^^^--+       |       |       +--^^^--+
     |   R1  |       |       |       |   R2  |   
 |---+-------|-------+-------|-------+-------|---| BackBorn H
             |               |               |
             |               |               |
             |               |               |
 |-----------+---------------+---------------+---| BackBorn L

      +--^^^--+:Terminaror register
      R1:120 ohms
      R2:150 ohms(Not working at 120 ohms)
```

![ESP32-CAN-3V3](https://github.com/nopnop2002/esp-idf-candump/assets/6020549/dec3744e-ede1-41c7-99b6-77ebfe916123)

__NOTE__   
3V CAN Trasnceviers like VP230 are fully interoperable with 5V CAN trasnceviers like MCP2551.   
Check [here](http://www.ti.com/lit/an/slla337/slla337.pdf).


# For classic bluetooth (ESP32 only)

```
git clone https://github.com/nopnop2002/esp-idf-can2bt
cd esp-idf-can2bt/classic_bt
idf.py set-target esp32
idf.py menuconfig
idf.py flash
```


# For ble 4.2 using ESP-Bluedroid host stack

```
git clone https://github.com/nopnop2002/esp-idf-can2bt
cd esp-idf-can2bt/bluedroid_ble
idf.py set-target {esp32/esp32s3/esp32c2/esp32c3/esp32c6}
idf.py menuconfig
idf.py flash
```

# For ble 4.2 using ESP-NimBLE host stack

```
git clone https://github.com/nopnop2002/esp-idf-can2bt
cd esp-idf-can2bt/nimble_ble
idf.py set-target {esp32/esp32s3/esp32c2/esp32c3/esp32c6}
idf.py menuconfig
idf.py flash
```

# Configuration
<img width="659" height="486" alt="Image" src="https://github.com/user-attachments/assets/d0531d0b-9dd1-4ba0-ae51-28722dc396f2" />
<img width="659" height="486" alt="Image" src="https://github.com/user-attachments/assets/3718d6a3-7e8a-47d1-b0a4-31b9621da61c" />

# Android Application   
I used [this](https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal) app.   

# iOS Application   
[This](https://apps.apple.com/jp/app/bluetooth-v2-1-spp-setup/id6449416841) might work, but I don't have iOS so I don't know.   

# References

https://github.com/nopnop2002/esp-idf-can2http

https://github.com/nopnop2002/esp-idf-can2mqtt

https://github.com/nopnop2002/esp-idf-can2usb

https://github.com/nopnop2002/esp-idf-can2websocket

https://github.com/nopnop2002/esp-idf-can2socket

https://github.com/nopnop2002/esp-idf-CANBus-Monitor

