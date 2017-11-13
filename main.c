/**
	\file
	\brief
		This project controls the UART and I2C protocols.
	\author Daniel Barragán and Alejandro Ávila
	\date	07/11/2017
 */

#include "MK64F12.h"
#include "UART.h"
#include "NVIC.h"
#include "GPIO.h"
#include "init.h"
#include "FIFO.h"
#include "UART.h"
#include "States.h"
#include "I2C.h"
#include "MCG.h"
#include "PCF8563.h"
#include "TeraTerm.h"
#include "Animation.h"

int main(void)
{
	initMain();//initialize all configurations for using this practice

	moveLetter('A');
	for(;;) {	   



	}
	return 0;
}
