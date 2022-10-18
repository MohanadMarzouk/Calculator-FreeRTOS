





/*
* DIO.h
*
* Created: 5/26/2021 12:44:58 PM
*  Author: EN.ESLAM EID
*/


#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#include "DIO_private.h"
#include "DIO_config.h"
#include "../BITMATH.h"

#define OFF 0
#define ON  1


void DIO_SetPinDir(PORT_TYPE , PIN_TYPE , DIR_TYPE );

void DIO_SetPinVal(PORT_TYPE , PIN_TYPE , STATE_TYPE);

void DIO_TogglePin(PORT_TYPE , PIN_TYPE );

STATE_TYPE DIO_GetPinVal(PORT_TYPE,PIN_TYPE);

void DIO_SetPullup(PORT_TYPE , PIN_TYPE );


void DIO_SetPortNibble(PORT_TYPE , Uint8 Data,NIPPLE_TYPE );



#endif