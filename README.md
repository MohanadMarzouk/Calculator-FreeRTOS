# Calculator-FreeRTOS
A calculator using FreeRTOS

Implemented a calculator based on FreeRTOS. The program has 3 main tasks. The first task, being the highest priority task, handles the password the user should provide to move forward to enter the operands and do the operation. The second task, with a priority less than the password task, takes the input operands from the user through the 4x4 keypad. The third task, with the least priority, takes the operands and do the operation and show it on the 16x2 LCD.
A mutex is used in order to gaurd the shared resouece which is the 16x2 LCD.

P.S: simulation is held on protues with the ATmega32 as the MCU.

The user should enter the pin required for the calculator: 
![image](https://user-images.githubusercontent.com/89541126/196393043-09493cb4-7e6d-4c47-8f74-fabd894c2770.png)

If the pin is incorrect, then a try again pop-up will appear and the user should re-enter the pin.
![image](https://user-images.githubusercontent.com/89541126/196393378-23835377-a132-4ab4-9a3f-4891432e4abf.png)

After the user has entered the pin correctly, he/she can then enter the operands and get the result of the operation.
![image](https://user-images.githubusercontent.com/89541126/196394201-7dd00f11-70b5-40d4-96f8-3a101e1ae255.png)


