
#include "MK64F12.h"
#include "NVIC.h"
#include "UART.h"
#include "DataTypeDefinitions.h"
#include "FIFO.h"
#include "States.h"
#include "TeraTerm.h"
#include "PCF8563.h"
#include "Animation.h"
#include "GPIO.h"

//arrrays for handling the inputs
PadsInput padsInput = {FALSE,FALSE,FALSE,FALSE};
PadsInput padsReset = {FALSE,FALSE,FALSE,FALSE};

//This structure is used for controlling the menus shown in the serial port
//Each menu has up to 3 sub stages which are changed whenever controlSystem is used
const StateType FSM_Moore[] =
	{
			{&printTTMainMenu,&controlMenu,&noFunction},
			{&screenPlay_1,&screenPlay_2,&noFunction},
			{&printTTDifficulty_1,&printTTDifficulty_2,&noFunction},
			{&printTTRecords_1,&printTTRecords_2,noFunction}
	};
//This structure handles the current system status
SystemControl currentSystem = {PRINCIPAL,0};

BooleanType noFunction(){
	//as we put an index in the limit, control Menu will restart the serial port
	currentSystem.stateIndex = STATE_MACHINE_SIZE;
	controlMenu();
	return FALSE;
}

BooleanType controlSystem(){//control system alternates the sub functions inside an state of the FSM_Moore
	uint8 index = (currentSystem.currentStatus - 48);//because currentStatus is in ASCII value, we have to decrease 48
	//according to the index value we control the sub functions of the current FSM_Moore state
	if(CERO == currentSystem.stateIndex) FSM_Moore[index].fptrFirst();
	else if(ONE== currentSystem.stateIndex) FSM_Moore[index].fptrSecond();
	else if(TWO == currentSystem.stateIndex) FSM_Moore[index].fptrThird();

	currentSystem.stateIndex++;//update the sub function index for the next lap
	return TRUE;
}

BooleanType controlMenu(){
	if(STATE_MACHINE_SIZE <= currentSystem.stateIndex){//if we overpassed the state machine size
			currentSystem.stateIndex = 0;//restore the initial configuration of the screen
			currentSystem.currentStatus = PRINCIPAL;
	}
	else if(PRINCIPAL == currentSystem.currentStatus){//if we are in the main menu select next menu
		if(ONE < getFIFOIndex()) noFunction();//if the FIFO has more than one element do nothing
		if(PLAY == (*getFIFO())) currentSystem.currentStatus = PLAY;
		else if(DIFFICULTY == (*getFIFO())) currentSystem.currentStatus = DIFFICULTY;
		else if(RECORDS == (*getFIFO())) currentSystem.currentStatus = RECORDS;
		currentSystem.stateIndex = 0;//because we have changed of menu, we have to reset the index
	}

	controlSystem();//update the serial port screen
	clearEnter();//clear enter flag, which is enabled in the UART interruption
	clearFIFO();//reset the stored FIFO
	return TRUE;
}

BooleanType updateInput(){
	padsInput.up = GPIO_readPIN(GPIO_C, BIT5);//UP
	padsInput.right = GPIO_readPIN(GPIO_C, BIT7);//RIGHT
	padsInput.left = GPIO_readPIN(GPIO_C, BIT0);//LEFT
	padsInput.down = GPIO_readPIN(GPIO_C, BIT9);//DOWN
	return TRUE;
}

BooleanType handleInput(){
	GPIO_clearIRQStatus(GPIO_C);//clear PORT_C interruption
	if(FALSE == padsInput.up) handleTilePress(COLUMN_1);//UP
	if(FALSE == padsInput.right) handleTilePress(COLUMN_2);//RIGHT
	if(FALSE == padsInput.left) handleTilePress(COLUMN_3);//LEFT
	if(FALSE == padsInput.down) handleTilePress(COLUMN_4);//DOWN
	padsInput = padsReset;//reset input
	return TRUE;
}

SystemControl* getSystem(){ return &currentSystem; }//return currentSstem direction

PadsInput* getPadsInput(){	return &padsInput;	}//return the padsInput direction
