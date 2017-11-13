
#include "DataTypeDefinitions.h"
#include "UART.h"
#include "Animation.h"
#include "PIT.h"

const TeraTermCommand commandsFirstColumn[ANIMATION_SIZE] = {
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

const TeraTermCommand commandsSecondColumn[ANIMATION_SIZE] = {
		"\033[1;15H","\033[2;15H",
		"\033[3;15H","\033[4;15H",
		"\033[5;15H","\033[6;15H",
		"\033[7;15H","\033[8;15H",
		"\033[9;15H","\033[10;15H",
		"\033[11;15H","\033[12;15H",
		"\033[13;15H","\033[14;15H",
		"\033[15;15H","\033[16;15H",
		"\033[17;15H","\033[18;15H",
		"\033[19;15H","\033[20;15H",
		"\033[21;15H","\033[22;15H",
		"\033[23;15H","\033[24;15H",
		"\033[25;15H","\033[26;15H",
		"\033[27;15H","\033[28;15H",
		"\033[29;15H","\033[30;15H",
		"\033[31;15H","\033[32;15H",
		"\033[33;15H","\033[34;10H",
};

const TeraTermCommand commandsThirdColumn[ANIMATION_SIZE] = {
		"\033[1;20H","\033[2;20H",
		"\033[3;20H","\033[4;20H",
		"\033[5;20H","\033[6;20H",
		"\033[7;20H","\033[8;20H",
		"\033[9;20H","\033[10;20H",
		"\033[11;20H","\033[12;20H",
		"\033[13;20H","\033[14;20H",
		"\033[15;20H","\033[16;20H",
		"\033[17;20H","\033[18;20H",
		"\033[19;20H","\033[20;20H",
		"\033[21;20H","\033[22;20H",
		"\033[23;20H","\033[24;20H",
		"\033[25;20H","\033[26;20H",
		"\033[27;20H","\033[28;20H",
		"\033[29;20H","\033[30;20H",
		"\033[31;20H","\033[32;20H",
		"\033[33;20H","\033[34;20H",
};

const TeraTermCommand commandsFourthColumn[ANIMATION_SIZE] = {
		"\033[1;25H","\033[2;25H",
		"\033[3;25H","\033[4;25H",
		"\033[5;25H","\033[6;25H",
		"\033[7;25H","\033[8;25H",
		"\033[9;25H","\033[10;25H",
		"\033[11;25H","\033[12;25H",
		"\033[13;25H","\033[14;25H",
		"\033[15;25H","\033[16;25H",
		"\033[17;25H","\033[18;25H",
		"\033[19;25H","\033[20;25H",
		"\033[21;25H","\033[22;25H",
		"\033[23;25H","\033[24;25H",
		"\033[25;25H","\033[26;25H",
		"\033[27;25H","\033[28;25H",
		"\033[29;25H","\033[30;25H",
		"\033[31;25H","\033[32;25H",
		"\033[33;25H","\033[34;25H",
};

uint8 animationIndex = 0;
uint8 animationIndex2 = 0;
uint8 animationIndex3 = 0;
uint8 animationIndex4 = 0;

BooleanType moveLetter(sint8 data){
	if(ANIMATION_SIZE <= (animationIndex+1))
		animationIndex = 0;

	//initialize the used PIT for controlling the motor PWM
	PIT_clear(PIT_0);
	PIT_delay(PIT_0, SYSTEM_CLOCK, 2.0F);// delay until next function value

	UART_putString(UART_0, commandsFirstColumn[animationIndex++]);
	UART_putChar(UART_0, ' ');
	UART_putString(UART_0, commandsFirstColumn[animationIndex]);
	UART_putChar(UART_0, data);

	UART_putString(UART_0, commandsFirstColumn[ANIMATION_SIZE-1]);

	return TRUE;
}

BooleanType moveLetter2(sint8 data){
	if(ANIMATION_SIZE <= (animationIndex2+1))
		animationIndex2 = 0;

	//initialize the used PIT for controlling the motor PWM
	PIT_clear(PIT_1);
	PIT_delay(PIT_1, SYSTEM_CLOCK, 5.0F);// delay until next function value

	UART_putString(UART_0, commandsSecondColumn[animationIndex2++]);
	UART_putChar(UART_0, ' ');
	UART_putString(UART_0, commandsSecondColumn[animationIndex2]);
	UART_putChar(UART_0, data);

	UART_putString(UART_0, commandsSecondColumn[ANIMATION_SIZE-1]);

	return TRUE;
}

BooleanType moveLetter3(sint8 data){
	if(ANIMATION_SIZE <= (animationIndex3+1))
		animationIndex3 = 0;

	//initialize the used PIT for controlling the motor PWM
	PIT_clear(PIT_2);
	PIT_delay(PIT_2, SYSTEM_CLOCK, 0.5F);// delay until next function value

	UART_putString(UART_0, commandsThirdColumn[animationIndex3++]);
	UART_putChar(UART_0, ' ');
	UART_putString(UART_0, commandsThirdColumn[animationIndex3]);
	UART_putChar(UART_0, data);

	UART_putString(UART_0, commandsThirdColumn[ANIMATION_SIZE-1]);

	return TRUE;
}

BooleanType moveLetter4(sint8 data){
	if(ANIMATION_SIZE <= (animationIndex4+1))
		animationIndex4 = 0;

	//initialize the used PIT for controlling the motor PWM
	PIT_clear(PIT_3);
	PIT_delay(PIT_3, SYSTEM_CLOCK, 15.0F);// delay until next function value

	UART_putString(UART_0, commandsFourthColumn[animationIndex4++]);
	UART_putChar(UART_0, ' ');
	UART_putString(UART_0, commandsFourthColumn[animationIndex4]);
	UART_putChar(UART_0, data);

	UART_putString(UART_0, commandsFourthColumn[ANIMATION_SIZE-1]);

	return TRUE;
}
