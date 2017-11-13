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
#include "PIT.h"
#include "PCF8563.h"
#include "TeraTerm.h"
#include "Animation.h"

int main(void)
{
	initMain();//initialize all configurations for using this practice

	//initialize some tiles
	addTile(COLUMN_1);
	addTile(COLUMN_2);
	addTile(COLUMN_3);

	for(;;) {	   

		if (TRUE == PIT_getIntrStutus(PIT_0)) moveTiles();//update the Tiles position in screen


	}
	return 0;
}
