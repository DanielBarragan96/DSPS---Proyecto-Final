
#include "HighScores.h"
#include "DataTypeDefinitions.h"
#include "UART.h"
#include "Animation.h"
#include "PIT.h"
#include "TeraTerm.h"
#include "States.h"
#include "MEM24LC256.h"

static uint8 actualScores[SCORES_ARRAY_SIZE] = {'0','0','0','0','0','0','0','0','0','0'};

uint8 updateScores(uint8 newScore){
	newScore += 48;
	readScores();
	uint8 index = SCORES_ARRAY_SIZE -1;
	if(actualScores[index] > newScore)
		return FALSE;
	if(actualScores[ARRAY_END] < newScore){
		while(index){
			actualScores[index--] = actualScores[index];
		}
		actualScores[RECORD_MEM_1] = newScore;
	}
	else{
		for(index; index >= ARRAY_END; index--){
			if(actualScores[index] >= newScore)
				break;
		}
		uint8 subIndex = SCORES_ARRAY_SIZE -1;
		while(index < subIndex){
			actualScores[subIndex--] = actualScores[subIndex];
		}
		actualScores[++index] = newScore;
	}
	writeScores();
	return (index+1);//Position of the actual score
}

BooleanType readScores(){
	MEM24LC256_getData(RECORD_MEM_1, SCORES_BYTES, actualScores);
	return TRUE;
}

BooleanType writeScores(){
	MEM24LC256_setData(RECORD_MEM_1, (uint8*) &actualScores[RECORD_MEM_1]);
	return TRUE;
}
