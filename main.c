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
#include "HighScores.h"
#include "Note_Decider.h"
//TODO quitar controlsong maybe

int main(void)
{
	initMain();//initialize all configurations for using this practice
//	writeScores();//reset scores
	Difficulty_NoteRate(EASY);

	for(;;) {

		if(getEnterFlag())	controlMenu();//When ENTER was pressed handle the input

		if(PLAY == getSystem()->currentStatus){
			if (PIT_getIntrStutus(PIT_0)) moveTiles();//update the Tiles position in screen
			if (PIT_getIntrStutus(PIT_1)) controlSong();//update current song tiles
			Music_Processor();
		}
	}
	return 0;
}
