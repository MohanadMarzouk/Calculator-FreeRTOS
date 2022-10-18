/*
* DIO_config.h
*
* Created: 4/8/2022 2:06:07 PM
*  Author: the samoray
*/


#ifndef DIO_CONFIG_H_
#define DIO_CONFIG_H_



typedef enum {DIO_PORTA,
	DIO_PORTB,
	DIO_PORTC,
DIO_PORTD} PORT_TYPE;


#define PIN0   0
#define	PIN1   1
#define	PIN2   2
#define	PIN3   3
#define	PIN4   4
#define	PIN5   5
#define	PIN6   6
#define	PIN7   7


//typedef enum {PIN0,PIN1,PIN2,PIN3,PIN4,PIN5,PIN6,PIN7} PIN_TYPE;

typedef unsigned char PIN_TYPE;

typedef enum {LOW_PIN, HIGH_PIN} STATE_TYPE;

typedef enum {INPUT_PIN,OUTPUT_PIN} DIR_TYPE;

typedef enum {Data_H_To_Port_H,
	Data_L_To_Port_H,
	Data_H_To_Port_L,
Data_L_To_Port_L} NIPPLE_TYPE;





#endif /* DIO_CONFIG_H_ */