
#include "HighScores.h"
#include "DataTypeDefinitions.h"
#include "UART.h"
#include "Animation.h"
#include "PIT.h"
#include "TeraTerm.h"
#include "States.h"
#include "MEM24LC256.h"

//this array stores the high scoress from the game, it starts and can be used for restarting the memory high scores
static uint8 actualScores[SCORES_ARRAY_SIZE] = {'0','0','0','0','0','0','0','0','0','0'};

uint8 updateScores(uint8 newScore){
	newScore += 48;//change value to ASCII
	readScores();//update actualScores array
	uint8 index = SCORES_ARRAY_SIZE -1;//index starting in last position
	if(actualScores[index] > newScore)//no new high score
		return FALSE;
	if(actualScores[ARRAY_END] < newScore){//newScore bigger than older major high score
		while(index){
			actualScores[index--] = actualScores[index];//move all scores one position
		}
		actualScores[RECORD_MEM_1] = newScore;//position new high score
	}
	else{//other wise
		for(index; index >= ARRAY_END; index--){
			if(actualScores[index] >= newScore)//search higher score than newScore
				break;//and stop searching
		}
		uint8 subIndex = SCORES_ARRAY_SIZE -1;//index in last position
		while(index < subIndex){
			actualScores[subIndex--] = actualScores[subIndex];//move all scores one position
		}
		actualScores[++index] = newScore;//add new high score
	}
	writeScores();//update scores in memory
	return (index+1);//Position of the actual score
}

BooleanType readScores(){//read scores from external memory using I2C
	MEM24LC256_getData(RECORD_MEM_1, SCORES_BYTES, actualScores);
	return TRUE;
}

BooleanType writeScores(){//write scores to external memory using I2C
	MEM24LC256_setData(RECORD_MEM_1, (uint8*) &actualScores[RECORD_MEM_1]);
	return TRUE;
}
