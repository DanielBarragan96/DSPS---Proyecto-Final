
#include "DataTypeDefinitions.h"
#include "UART.h"
#include "Animation.h"
#include "PIT.h"

const TeraTermCommand commands[ANIMATION_SIZE] = {
		"\033[0;32;10m","\033[2J",
		"\033[1;10H","\033[2;10H",
		"\033[3;10H","\033[4;10H",
		"\033[5;10H","\033[6;10H",
		"\033[7;10H","\033[8;10H",
		"\033[9;10H","\033[10;10H",
		"\033[11;10H","\033[12;10H",
		"\033[13;10H","\033[14;10H",
		"\033[15;10H","\033[16;10H",
		"\033[17;10H","\033[18;10H",
		"\033[19;10H","\033[20;10H",
		"\033[21;10H","\033[22;10H",
		"\033[23;10H","\033[24;10H",
		"\033[25;10H","\033[26;10H",
		"\033[27;10H","\033[28;10H",
		"\033[29;10H","\033[30;10H",
		"\033[31;10H","\033[32;10H",
		"\033[33;10H","\033[34;10H",
};

uint8 animationIndex = 0;

BooleanType moveLetter(sint8 data){

	UART_putString(UART_0, commands[animationIndex++]);
	UART_putString(UART_0, commands[animationIndex]);

	while(ANIMATION_SIZE > animationIndex){
		//initialize the used PIT for controlling the motor PWM
		PIT_clear(PIT_0);
		PIT_delay(PIT_0, SYSTEM_CLOCK, 2.0F);// delay until next function value

		UART_putString(UART_0, commands[animationIndex++]);
		UART_putChar(UART_0, ' ');
		UART_putString(UART_0, commands[animationIndex]);
		UART_putChar(UART_0, data);

		UART_putString(UART_0, commands[ANIMATION_SIZE-1]);
		while(TRUE != PIT_getIntrStutus());

	}
	return TRUE;
}
