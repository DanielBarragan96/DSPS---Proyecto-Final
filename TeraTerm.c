#include "MK64F12.h"
#include "NVIC.h"
#include "UART.h"
#include "DataTypeDefinitions.h"
#include "TeraTerm.h"
#include "FIFO.h"
#include "States.h"
#include "MEM24LC256.h"
#include "Animation.h"
#include "PIT.h"
#include "HighScores.h"
#include "States.h"
#include "HighScores.h"

TeraTermStatus printTTMainMenu(){

	/**The following sentences send strings to PC using the UART_putString function. Also, the string
	 * is coded with terminal code*/
	/** VT100 command for text in green and background in black*/
	UART_putString(UART_0,"\033[0;32;10m");
	/*VT100 command for clearing the screen*/
	UART_putString(UART_0,"\033[2J");

	/* VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[3;10H");
	UART_putString(UART_0, "1) Jugar \r");
	/* VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[4;10H");
	UART_putString(UART_0, "2) Elegir dificultad \r");
	/* VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[5;10H");
	UART_putString(UART_0, "3) Records \r");

	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[13;10H");

	return GOOD;
}

TeraTermStatus printTTDifficulty_1(){
	/**The following sentences send strings to PC using the UART_putString function. Also, the string
	 * is coded with terminal code*/
	/** VT100 command for text in green and background in black*/
	UART_putString(UART_0,"\033[0;32;10m");
	/*VT100 command for clearing the screen*/
	UART_putString(UART_0,"\033[2J");
	/* VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[3;10H");
	UART_putString(UART_0, "Elegir dificultad del juego: \r Facil = 1 \r Mediana = 2 \r Dificil = 3 \r");

	/** VT100 command for text in blue and background in black*/
	UART_putString(UART_0,"\033[0;49;34m");
	/* VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[4;10H");
	UART_putString(UART_0, "Facil = 1 \r");

	/** VT100 command for text in yellow and background in black*/
	UART_putString(UART_0,"\033[0;49;33m");
	/* VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[5;10H");
	UART_putString(UART_0, "Mediana = 2 \r");

	/** VT100 command for text in red and background in black*/
	UART_putString(UART_0,"\033[0;49;31m");
	/* VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[6;10H");
	UART_putString(UART_0, "Dificil = 3 \r");

	/** VT100 command for text in green and background in black*/
	UART_putString(UART_0,"\033[0;32;10m");
	/* VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[7;10H");

	return GOOD;
}

TeraTermStatus printTTDifficulty_2(){
	/* VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[8;10H");
	UART_putString(UART_0, "La dificultad es: \r");
	UART_putString(UART_0,"\033[9;10H");
	Dificulty gameDiffuculty = (Dificulty) *getFIFO();
	if(EASY_INPUT== gameDiffuculty){
		/** VT100 command for text in blue and background in black*/
		UART_putString(UART_0,"\033[0;49;34m");
		UART_putString(UART_0, "Facil");
		setDifficulty(EASY);
		Difficulty_NoteRate(EASY);
	}
	else if(MEDIUM_INPUT == gameDiffuculty){
		/** VT100 command for text in yellow and background in black*/
		UART_putString(UART_0,"\033[0;49;33m");
		UART_putString(UART_0, "Mediana");
		setDifficulty(MEDIUM);
		Difficulty_NoteRate(MEDIUM);
	}
	else if(HARD_INPUT == gameDiffuculty){
		/** VT100 command for text in red and background in black*/
		UART_putString(UART_0,"\033[0;49;31m");
		UART_putString(UART_0, "Dificil");
		setDifficulty(HARD);
		Difficulty_NoteRate(HARD);
	}
	else
		UART_putString(UART_0, "ERROR: la dificultad no ha sido cambiada.");
	/* VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[10;10H");

	return GOOD;
}

TeraTermStatus printTTRecords_1(){
	/**The following sentences send strings to PC using the UART_putString function. Also, the string
	 * is coded with terminal code*/
	/** VT100 command for text in green and background in black*/
	UART_putString(UART_0,"\033[0;32;10m");
	/*VT100 command for clearing the screen*/
	UART_putString(UART_0,"\033[2J");
	readScores();
	/* VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[1;10H");
	UART_putString(UART_0, "Los records actuales son:  \r");
	uint8 currentScore;
	UART_putString(UART_0,"\033[3;10H");
	UART_putString(UART_0, "1. ");
	currentScore = getScore(0);
	UART_putChar(UART_0, currentScore);
	UART_putString(UART_0,"\033[4;10H");
	UART_putString(UART_0, "2. ");
	currentScore = getScore(1);
	UART_putChar(UART_0, currentScore);
	UART_putString(UART_0,"\033[5;10H");
	UART_putString(UART_0, "3. ");
	currentScore = getScore(2);
	UART_putChar(UART_0, currentScore);
	UART_putString(UART_0,"\033[6;10H");
	UART_putString(UART_0, "4. ");
	currentScore = getScore(3);
	UART_putChar(UART_0, currentScore);
	UART_putString(UART_0,"\033[7;10H");
	UART_putString(UART_0, "5. ");
	currentScore = getScore(4);
	UART_putChar(UART_0, currentScore);
	UART_putString(UART_0,"\033[8;10H");
	UART_putString(UART_0, "6. ");
	currentScore = getScore(5);
	UART_putChar(UART_0, currentScore);
	UART_putString(UART_0,"\033[9;10H");
	UART_putString(UART_0, "7. ");
	currentScore = getScore(6);
	UART_putChar(UART_0, currentScore);
	UART_putString(UART_0,"\033[10;10H");
	UART_putString(UART_0, "8. ");
	currentScore = getScore(7);
	UART_putChar(UART_0, currentScore);
	UART_putString(UART_0,"\033[11;10H");
	UART_putString(UART_0, "9. ");
	currentScore = getScore(8);
	UART_putChar(UART_0, currentScore);
	UART_putString(UART_0,"\033[12;10H");
	UART_putString(UART_0, "10. ");
	currentScore = getScore(9);
	UART_putChar(UART_0, currentScore);
	UART_putString(UART_0,"\033[16;10H");
	UART_putString(UART_0, "Para resetear los scores en memoria escriba: 1 \r");

	/* VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[14;10H");

	return GOOD;
}

TeraTermStatus printTTRecords_2(){
	/**The following sentences send strings to PC using the UART_putString function. Also, the string
	 * is coded with terminal code*/
	/** VT100 command for text in green and background in black*/
	UART_putString(UART_0,"\033[0;32;10m");
	/*VT100 command for clearing the screen*/
	UART_putString(UART_0,"\033[2J");
	/* VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[2;10H");
	if(RESET_HIGH_SCORES == pop()){//if the last inserted value was '1'
		resetScores();//reset the scores
		UART_putString(UART_0, "Los records fueron reseteados.  \r");
	}
	else
		noFunction();// if no reset, return to mainMenu

	/* VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[14;10H");

	return GOOD;
}

BooleanType screenPlay_1(){/*VT100 command for clearing the screen*/
	UART_putString(UART_0,"\033[2J");
	writeUI();
	greenLEDOn();
	restartAnimation();
	PIT_delay(PIT_0, SYSTEM_CLOCK, 0.1F);// delay until update screen
	return TRUE;
};

BooleanType screenPlay_2(){
	/** VT100 command for text in green and background in black*/
	UART_putString(UART_0,"\033[0;32;10m");
	/*VT100 command for clearing the screen*/
	UART_putString(UART_0,"\033[2J");

	UART_putString(UART_0,"\033[2;10H");
	UART_putString(UART_0, "Puntaje:  \r");
	UART_putString(UART_0,"\033[3;10H");
	UART_putChar(UART_0, ((uint8) (48 + 10*getPlayerScore()/getSongScore())));//show score in ASCII

	//playerScore = 0;
	//songScore = 0;

	turnLEDsOff();
	return TRUE;
}
