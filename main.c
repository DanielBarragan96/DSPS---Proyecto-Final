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
		//TODO ver que podemos hacer sobre el array con el que empieza, ya sea eliminarlo o restar ese numero de flechas del total del score
		//TODO uno de los sensore no estaba jalando ayer en la noche.
		//TODO recuerda checar el valor que debemos calibrar en notedecider.c ahi viene como.
		//TODO ve si puedes hacer algo sobre el bug de que se cancela de la nada la canción en easy, si es necesario en el SetFS de easy reduce un poco ese value para que genere la nota más rapido que en 1 sec, en 32000= 1 flecha por segundo.
		//TODO el botón que nos llev al menu de scores.

		if(getEnterFlag())	controlMenu();//When ENTER was pressed handle the input

		if(PLAY == getSystem()->currentStatus){
			if (PIT_getIntrStutus(PIT_0)) moveTiles();//update the Tiles position in screen
			if (PIT_getIntrStutus(PIT_1)) controlSong();//update current song tiles
			Music_Processor();//process song
		}

		if(TRUE == GPIO_getIRQStatus(GPIO_C)) handleInput();//when pad is pressed
	}
	return 0;
}
