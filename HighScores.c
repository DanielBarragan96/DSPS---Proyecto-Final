
#include "HighScores.h"
#include "DataTypeDefinitions.h"
#include "UART.h"
#include "Animation.h"
#include "PIT.h"
#include "TeraTerm.h"
#include "States.h"
#include "MEM24LC256.h"

static uint8 actualScores[SCORES_ARRAY_SIZE];

uint8 updateScores(uint8 newScore){
	uint8 newScoreCast = newScore;
	uint8 a = 5;
	MEM24LC256_setData(RECORD_MEM_1,(uint8*) &a);
	readScores();
	uint8 index = SCORES_ARRAY_SIZE -1;
	if(actualScores[index] > newScoreCast)
		return FALSE;
	for(index; index >= ARRAY_END; index--){
		if(actualScores[index] >= newScoreCast)
			break;
	}
	uint8 subIndex = SCORES_ARRAY_SIZE -1;
	while(index < subIndex){
		actualScores[subIndex--] = actualScores[subIndex];
	}
	actualScores[++index] = newScoreCast;
	writeScores();
	return (index+1);//Position of the actual score
}

BooleanType readScores(){
	MEM24LC256_getData(RECORD_MEM_1, SCORES_BYTES, &actualScores[RECORD_MEM_1]);
	MEM24LC256_getData(RECORD_MEM_2, SCORES_BYTES, &actualScores[RECORD_MEM_2]);
	MEM24LC256_getData(RECORD_MEM_3, SCORES_BYTES, &actualScores[RECORD_MEM_3]);
	MEM24LC256_getData(RECORD_MEM_4, SCORES_BYTES, &actualScores[RECORD_MEM_4]);
	MEM24LC256_getData(RECORD_MEM_5, SCORES_BYTES, &actualScores[RECORD_MEM_5]);
	MEM24LC256_getData(RECORD_MEM_6, SCORES_BYTES, &actualScores[RECORD_MEM_6]);
	MEM24LC256_getData(RECORD_MEM_7, SCORES_BYTES, &actualScores[RECORD_MEM_7]);
	MEM24LC256_getData(RECORD_MEM_8, SCORES_BYTES, &actualScores[RECORD_MEM_8]);
	MEM24LC256_getData(RECORD_MEM_9, SCORES_BYTES, &actualScores[RECORD_MEM_9]);
	MEM24LC256_getData(RECORD_MEM_10, SCORES_BYTES, &actualScores[RECORD_MEM_10]);
	return TRUE;
}

BooleanType writeScores(){
//	MEM24LC256_setData(RECORD_MEM_1, actualScores[RECORD_MEM_1].score);
//	MEM24LC256_setData(RECORD_MEM_2, actualScores[RECORD_MEM_2].score);
//	MEM24LC256_setData(RECORD_MEM_3, actualScores[RECORD_MEM_3].score);
//	MEM24LC256_setData(RECORD_MEM_4, actualScores[RECORD_MEM_4].score);
//	MEM24LC256_setData(RECORD_MEM_5, actualScores[RECORD_MEM_5].score);
//	MEM24LC256_setData(RECORD_MEM_6, actualScores[RECORD_MEM_6].score);
//	MEM24LC256_setData(RECORD_MEM_7, actualScores[RECORD_MEM_7].score);
//	MEM24LC256_setData(RECORD_MEM_8, actualScores[RECORD_MEM_8].score);
//	MEM24LC256_setData(RECORD_MEM_9, actualScores[RECORD_MEM_9].score);
//	MEM24LC256_setData(RECORD_MEM_10, actualScores[RECORD_MEM_10].score);
	return TRUE;
}
