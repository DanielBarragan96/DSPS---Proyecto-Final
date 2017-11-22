/*
 * HighScoress.h
 *
 *  Created on: 21/11/2017
 *      Author: Daniel Barragán
 */

#ifndef HIGHSCORES_H_
#define HIGHSCORES_H_

#include "DataTypeDefinitions.h"

#define ARRAY_END 0

#define RECORD_MEM_1 0
#define RECORD_MEM_2 1
#define RECORD_MEM_3 2
#define RECORD_MEM_4 3
#define RECORD_MEM_5 4
#define RECORD_MEM_6 5
#define RECORD_MEM_7 6
#define RECORD_MEM_8 7
#define RECORD_MEM_9 8
#define RECORD_MEM_10 9

#define SCORES_ARRAY_SIZE 10
#define SCORES_BYTES 1

typedef struct{
	uint8* score;
}Score;

uint8 updateScores(uint8 newScore);

BooleanType readScores();

BooleanType writeScores();

#endif
