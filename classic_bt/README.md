# For classic bluetooth
Android, Windows 10/11, and Linux are available.   

## Using Android   

- Pair with ESP_SPP_ACCEPTOR   
	If you are asked to enter the Pin Code, the Pin Code is "1234".   

- Launch the app and select device  
	Menu->Devices->Bluetooth Classic   
	<img width="864" height="576" alt="Image" src="https://github.com/user-attachments/assets/6a346b08-0125-4f34-ba7e-581463c338aa" />

- Connect to device   
	You can view CAN frames using Android.   
	<img width="864" height="576" alt="Image" src="https://github.com/user-attachments/assets/1c4b57ef-7fce-402c-83c1-5c5f26a6fe26" />

## Using Windows10/11   
- Attach the USB Bluetooth dongle   

- Open Settigs -> Devices   
	Click Add bluetooth or other device.   
	<img width="1138" height="675" alt="Image" src="https://github.com/user-attachments/assets/19a13249-f87a-4a13-bdbe-68c9d64364f9" />

- Select Bluetooth   
	<img width="550" height="633" alt="Image" src="https://github.com/user-attachments/assets/9b98db9f-f837-4e39-8a46-e9fc0caf97de" />

- Add ESP_SPP_ACCEPTOR   
	<img width="550" height="633" alt="Image" src="https://github.com/user-attachments/assets/7af78e85-1b94-425f-a050-3d3155691ff3" />

- Enter the PIN for ESP_SPP_ACCEPTOR   
	<img width="550" height="633" alt="Image" src="https://github.com/user-attachments/assets/e6d7aef9-cf4f-43e0-916f-3dda3619ddfe" />

- Pair with ESP_SPP_ACCEPTOR   
	<img width="550" height="633" alt="Image" src="https://github.com/user-attachments/assets/9895ee51-311e-4e38-a27d-f5a35865c174" />

- Open terminal software & open new com port   
	I use TeraTerm.   
	<img width="659" height="486" alt="Image" src="https://github.com/user-attachments/assets/d4c29c47-c245-4dae-9456-4aec811bdf43" />

- Unpair the device after use   
	<img width="1138" height="675" alt="Image" src="https://github.com/user-attachments/assets/2df38b14-c4d6-455d-8139-b4031747dd03" />


## Using Linux
- Attach the USB Bluetooth dongle   

- Install package   
	```
	$ sudo apt install bluez screen
	```

- Start daemon   
	```
	$ sudo systemctl enable --now bluetooth
	```

- Pair using bluetoothctl
	```
	$ bluetoothctl
	[bluetoothctl]> power on
	[bluetoothctl]> agent on
	[bluetoothctl]> scan on
	[CHG] Controller 00:1B:DC:03:D3:E5 Discovering: yes
	[NEW] Device F0:08:D1:C7:B5:1E ESP_SPP_ACCEPTOR
	[bluetoothctl]> scan off
	[bluetoothctl]> pair F0:08:D1:C7:B5:1E
	[agent] Enter PIN code: 1234
	Pairing successful
	[ESP_SPP_ACCEPTOR]> exit
	```

- Create serial device   
	```
	$ sudo rfcomm bind 0 F0:08:D1:C7:B5:1E
	$ ls /dev/rfcomm*
	/dev/rfcomm0
	```

- Monitor serial device using screen   
	screen termination is `ctrl+a k`   
	```
	$ screen /dev/rfcomm0
	```
	<img width="820" height="517" alt="Image" src="https://github.com/user-attachments/assets/2e563d5f-c1ba-415c-ad52-e32612d821e4" />

- Remove serial device after use   
	```
	$ sudo rfcomm release 0
	```

- Unpair using bluetoothctl   
	```
	$ bluetoothctl
	[bluetoothctl]> remove F0:08:D1:C7:B5:1E
	[bluetoothctl]> power off
	[bluetoothctl]> exit
	```
