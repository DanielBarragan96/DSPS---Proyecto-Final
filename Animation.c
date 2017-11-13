
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

static Tiles tiles[TILES_SIZE] = {{COLUMN_1,0},{COLUMN_2,0},{COLUMN_3,2},{COLUMN_4,3},{COLUMN_1,3},{COLUMN_4,10}};
static uint8 listSize = 5;

BooleanType moveTiles(){
	uint8 passTiles = 0;
	while(listSize >= passTiles){
		if(ANIMATION_SIZE <= (tiles[passTiles].tileIndex + 1)){
			tiles[passTiles].tileIndex = 0;
			writeUI();
		}

		//initialize the used PIT for controlling the motor PWM
		PIT_clear(PIT_0);
		PIT_delay(PIT_0, SYSTEM_CLOCK, 0.5F);// delay until next function value

		switch(tiles[passTiles].column){
			case COLUMN_1:{
				UART_putString(UART_0, commandsFirstColumn[tiles[passTiles].tileIndex++]);
				UART_putChar(UART_0, ' ');
				UART_putString(UART_0, commandsFirstColumn[tiles[passTiles++].tileIndex]);
				UART_putChar(UART_0, COLUMN_1);
				break;
			}
			case COLUMN_2:{
				UART_putString(UART_0, commandsSecondColumn[tiles[passTiles].tileIndex++]);
				UART_putChar(UART_0, ' ');
				UART_putString(UART_0, commandsSecondColumn[tiles[passTiles++].tileIndex]);
				UART_putChar(UART_0, COLUMN_2);
				break;
				}
			case COLUMN_3:{
				UART_putString(UART_0, commandsThirdColumn[tiles[passTiles].tileIndex++]);
				UART_putChar(UART_0, ' ');
				UART_putString(UART_0, commandsThirdColumn[tiles[passTiles++].tileIndex]);
				UART_putChar(UART_0, COLUMN_3);
				break;
				}
			case COLUMN_4:{
				UART_putString(UART_0, commandsFourthColumn[tiles[passTiles].tileIndex++]);
				UART_putChar(UART_0, ' ');
				UART_putString(UART_0, commandsFourthColumn[tiles[passTiles++].tileIndex]);
				UART_putChar(UART_0, COLUMN_4);
				break;
				}
			default:
				return FALSE;
		}
	}

	UART_putString(UART_0, commandsFourthColumn[ANIMATION_SIZE-1]);

	return TRUE;
}

BooleanType writeUI(){
	UART_putString(UART_0, "\033[34;10H");
	UART_putChar(UART_0, 219);
	UART_putString(UART_0, "\033[34;15H");
	UART_putChar(UART_0, 219);
	UART_putString(UART_0, "\033[34;20H");
	UART_putChar(UART_0, 219);
	UART_putString(UART_0, "\033[34;25H");
	UART_putChar(UART_0, 219);
	return TRUE;
}