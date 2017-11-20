#include "MK64F12.h"
#include "NVIC.h"
#include "UART.h"
#include "DataTypeDefinitions.h"
#include "TeraTerm.h"
#include "PCF8563.h"
#include "FIFO.h"
#include "States.h"
#include "MEM24LC256.h"
#include "Animation.h"
#include "PIT.h"

TeraTermStatus printTTMainMenu(){

	/**The following sentences send strings to PC using the UART_putString function. Also, the string
	 * is coded with terminal code*/
	/** VT100 command for text in red and background in cyan*/
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
	/** VT100 command for text in red and background in cyan*/
	UART_putString(UART_0,"\033[0;32;10m");
	/*VT100 command for clearing the screen*/
	UART_putString(UART_0,"\033[2J");
	/* VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[3;10H");
	UART_putString(UART_0, "Elegir dificultad del juego: \r Facil = 1 \r Mediana = 2 \r Dificil = 3 \r");
	/* VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[4;10H");
	UART_putString(UART_0, "Facil = 1 \r");
	/* VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[5;10H");
	UART_putString(UART_0, "Mediana = 2 \r");
	/* VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[6;10H");
	UART_putString(UART_0, "Dificil = 3 \r");
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
		UART_putString(UART_0, "Easy");
		setDifficulty(EASY);
	}
	else if(MEDIUM_INPUT == gameDiffuculty){
		UART_putString(UART_0, "Medium");
		setDifficulty(MEDIUM);
	}
	else if(HARD_INPUT == gameDiffuculty){
		UART_putString(UART_0, "Hard");
		setDifficulty(HARD);
	}
	else
		UART_putString(UART_0, "ERROR: la dificultad no ha sido cambiada.");
	/* VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[10;10H");

	return GOOD;
}

TeraTermStatus printTTRecords(){
	/**The following sentences send strings to PC using the UART_putString function. Also, the string
	 * is coded with terminal code*/
	/** VT100 command for text in red and background in cyan*/
	UART_putString(UART_0,"\033[0;32;10m");
	/*VT100 command for clearing the screen*/
	UART_putString(UART_0,"\033[2J");
	/* VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[1;10H");
	UART_putString(UART_0, "Los records actuales son:  \r");

	UART_putString(UART_0,"\033[3;10H");
	UART_putString(UART_0, "1.  \r");

	UART_putString(UART_0,"\033[4;10H");
	UART_putString(UART_0, "2. \r");

	UART_putString(UART_0,"\033[5;10H");
	UART_putString(UART_0, "3. \r");

	UART_putString(UART_0,"\033[6;10H");
	UART_putString(UART_0, "4. \r");

	UART_putString(UART_0,"\033[7;10H");
	UART_putString(UART_0, "5. \r");

	UART_putString(UART_0,"\033[8;10H");
	UART_putString(UART_0, "6. \r");

	UART_putString(UART_0,"\033[9;10H");
	UART_putString(UART_0, "7. \r");

	UART_putString(UART_0,"\033[10;10H");
	UART_putString(UART_0, "8. \r");

	UART_putString(UART_0,"\033[11;10H");
	UART_putString(UART_0, "9. \r");

	UART_putString(UART_0,"\033[12;10H");
	UART_putString(UART_0, "10. \r");

	/* VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[14;10H");

	return GOOD;
}
BooleanType clearScreenPlay(){/*VT100 command for clearing the screen*/
	UART_putString(UART_0,"\033[2J");
	writeUI();
	PIT_delay(PIT_0, SYSTEM_CLOCK, 0.1F);// delay until update screen
	PIT_delay(PIT_1, SYSTEM_CLOCK, 0.1F);// delay until update screen
	return TRUE;
};
