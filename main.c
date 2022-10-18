/*
 * Calculator
 *
 * Created: 10/14/2022 5:56:56 PM
 * Author : Mohanad Marzouk
 */ 

#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/task.h"
#include "FreeRTOS/semphr.h"
#include "HAL/LED.h"
#include "HAL/keypad.h"
#include "HAL/LCD_interface.h"
#include "MCAL/DIO_interface.h"
#include "LSTD_TYPES.h"
#include "string.h"
#include <util/delay.h>

#define FACTOR 10
#define ZERO_ASCII	48

void getNum_Task(); // do operation
void showOnLCD_Task(); // show on LCD
void password_Task();
xTaskHandle T1Handler_Num;
xTaskHandle T2Handler_LCD;
xTaskHandle T3Handler_Password;

Sint16 num1;		// operand 1
Sint16 num2;		// operand 2
Sint16 op;		// operator
Sint16 res;		// result
Sint8 userEntry[20] = {0};		// user entry
char pin[5] = "1311";
char enteredpassword [5];


SemaphoreHandle_t xSemaphore = NULL;


int main(void)
{
	LCD_init();			//initialize LCD
	KeyPad_init();		//initialize keypad
	xSemaphore = xSemaphoreCreateMutex();														//create mutex to guard the shared resource
	xTaskCreate(showOnLCD_Task, "Show on LCD", 228, NULL, 1, T2Handler_LCD);					// Task to show on LCD
	xTaskCreate(getNum_Task, "Get Numbers", 228, NULL, 2, T1Handler_Num);						// Task to take numbers from the user
	xTaskCreate(password_Task, "Password Function", 228, NULL, 3, T3Handler_Password);		// Task for the calculator password
	vTaskStartScheduler();																		// Start the FreeRTOS scheduler
	for(;;);
}
void password_Task()
{
	Uint8 userInput;			// Take password from user
	
	for(;;)
	{
		if (xSemaphore != NULL)
		{
			/* See if the semaphore can be obtained.  If the semaphore is not
        available wait 10 ticks to see if it becomes free. */
			
			if(xSemaphoreTake(xSemaphore, (TickType_t) 10) == pdTRUE)		//
			{
				/* semaphore obtained and can now access the
            shared resource. */
				
				LCD_WriteSTRING("Enter Pin: ");
				for (int i = 0; i < 4; i++)
				{
					while(userInput == 0)
					{
						userInput = KeyPad_GetKey();
					}
					enteredpassword [i] = userInput; 
					LCD_WriteCHAR(userInput);
					userInput = 0;
					_delay_ms(200);
				}
				enteredpassword[4] = '\0';
				if(strcmp(enteredpassword, pin) == 0)
				{
					LCD_Clear();
					LCD_WriteSTRING("Welcome");
					_delay_ms(200);
					LCD_Clear();
					xSemaphoreGive(xSemaphore);
					vTaskSuspend(NULL);
				}
				else
				{
					LCD_Clear();
					LCD_WriteSTRING("Try again");
				}
			}
		} 
		else
		{
			/*  could not obtain the semaphore and can therefore not access
			the shared resource safely. */
		}
	}
}
void getNum_Task() //keypad
{
	for(;;)
	{
		Uint8 index = 0;		
		if(xSemaphore != NULL)
		{
			/* See if the semaphore can be obtained.  If the semaphore is not
        available wait 10 ticks to see if it becomes free. */
			if( xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) == pdTRUE )
			{
				/* semaphore obtained and can now access the
            shared resource. */
				while(userEntry[index-1] != '=')
				{
					while(KeyPad_GetKey() == 0){}
					if(KeyPad_GetKey() != 0)		//button is pressed
					{
						userEntry[index] = KeyPad_GetKey();
						
					} /*if*/
					
					LCD_WriteCHAR(userEntry[index]);	//show the numbers
					++index;
					
				}/*while*/
				
					xSemaphoreGive( xSemaphore );
					vTaskResume(T2Handler_LCD);
					vTaskSuspend(NULL);
			}/*if*/
				
		}/*if*/
		
		else
		{
			 /*  could not obtain the semaphore and can therefore not access
			the shared resource safely. */
		}
	}
}/*end of task*/

void showOnLCD_Task()
{
	for(;;)
	{	
		Uint8 index = 0;
		if(xSemaphore != NULL)
		{
			/* See if the semaphore can be obtained.  If the semaphore is not
        available wait 10 ticks to see if it becomes free. */
			
			if( xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) == pdTRUE )		// obtain mutex
			{
				/* semaphore obtained and can now access the
            shared resource. */
				while((userEntry[index] != '+') && (userEntry[index] != '-') && (userEntry[index] != '/') && (userEntry[index] != '*'))
				{
					if((userEntry[index] >= '0') && (userEntry[index] <= '9'))
					{
						num1=(num1 * FACTOR) + (userEntry[index] - ZERO_ASCII);
						++index;
						op = userEntry[index];
					}
					else
					{
						++index;
						op = userEntry[index];
					}
				}
				LCD_WriteCMD(CMD_Clear_Display);
				LCD_WriteNUM(num1);		LCD_WriteCHAR(op);
				++index;
				while(userEntry [index] != '=')		/*break from the loop if the user typed '='*/
				{
					if((userEntry[index] >= '0') && (userEntry[index] <= '9'))
					{
						num2 = (num2 * FACTOR) + (userEntry[index] - ZERO_ASCII);
						++index;
					}
					else
					{
						++index;
					}
				}
				LCD_WriteNUM(num2);		LCD_WriteCHAR('=');
				calcOp();				/*calculate the two inputs*/
				LCD_WriteNUM(res);
				xSemaphoreGive( xSemaphore );				
				vTaskResume(T1Handler_Num);
				vTaskSuspend(NULL);
			}
		}
			else
			{
					           /*  could not obtain the semaphore and can therefore not access
								the shared resource safely. */
			}
	}

}/*end of task*/

void calcOp()
{
	switch (op)
	{
		case '+':
			res = num1 + num2;
			break;
		case '-':
			res = num1 - num2;
			break;
		case '*':
			res = num1 * num2;
			break;
		case '/':
			res = num1 / num2;
			break;
		default:
			break;
	}
	
}