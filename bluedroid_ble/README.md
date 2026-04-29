# For ble 4.2 using ESP-Bluedroid host stack
ESP-IDF can use either the ESP-Bluedroid host stack or the ESP-NimBLE host stack.   
The differences between the two are detailed [here](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-guides/ble/overview.html).   
This project uses the ESP-Bluedroid host stack.   

- pair with ESP_SPP_SERVER   

- Launch the app and select device  
	Menu->Devices->Bluetooth LE   

- Long press the device and select the Edit menu   
	<img width="864" height="576" alt="Image" src="https://github.com/user-attachments/assets/1e9aa8f7-0814-4d49-8b29-148d0e04f787" />

- Select Custom and specify UUID   
	The UUIDs are different for ESP-Bluedroid and ESP-NimBLE.   
	<img width="864" height="576" alt="Image" src="https://github.com/user-attachments/assets/9301d6dd-951f-47c5-b25e-7581dacc3f15" />

- Connect to device   
	You can view CAN frames using Android.   
	<img width="864" height="576" alt="Image" src="https://github.com/user-attachments/assets/86cdca7f-5b96-4b7b-8a25-d45cf461b57e" />
