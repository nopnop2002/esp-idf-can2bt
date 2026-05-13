# For ble 4.2 using ESP-NimBLE host stack
ESP-IDF can use either the ESP-Bluedroid host stack or the ESP-NimBLE host stack.   
The differences between the two are detailed [here](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-guides/ble/overview.html).   
This project uses the ESP-NimBLE host stack.   

- pair with ESP_NIMBLE_SERVER   

- Launch the app and select device  
	Menu->Devices->Bluetooth LE   

- Long press the device and select the Edit menu   
	<img width="864" height="576" alt="Image" src="https://github.com/user-attachments/assets/5bf0c309-8d49-4d9e-9c22-4e7537582d3b" />

- Select Custom and specify UUID   
	The UUIDs are different for ESP-Bluedroid and ESP-NimBLE.   
	<img width="864" height="576" alt="Image" src="https://github.com/user-attachments/assets/176b326d-8d30-4e17-adea-791128bbdc09" />

- Connect to device   
	You can view CAN frames using Android.   
	<img width="864" height="576" alt="Image" src="https://github.com/user-attachments/assets/eb211d80-2756-40f4-8a02-728389179475" />

# Concurrent connection
Unlike ESP-Bluedroid host stack, ESP-NimBLE host stack allows concurrent connections.   
The maximum number of simultaneous connections is specified here.   
<img width="659" height="486" alt="Image" src="https://github.com/user-attachments/assets/73c527ca-a44f-4b2b-bccb-6f6ccbac8397" />

You can view CAN frames using multiple devices.   
<img width="864" height="576" alt="Image" src="https://github.com/user-attachments/assets/a6191a56-44cb-4baa-a596-69f23ba4fadf" />
