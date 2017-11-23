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

#define RECORD_MEM_1 0x0
#define RECORD_MEM_2 0x1
#define RECORD_MEM_3 0x2
#define RECORD_MEM_4 0x3
#define RECORD_MEM_5 0x4
#define RECORD_MEM_6 0x5
#define RECORD_MEM_7 0x6
#define RECORD_MEM_8 0x7
#define RECORD_MEM_9 0x8
#define RECORD_MEM_10 0x9
#define SCORES_ARRAY_SIZE 10
#define SCORES_BYTES 10

typedef struct{
	uint8* score;
}Score;

uint8 updateScores(uint8 newScore);

BooleanType readScores();

BooleanType writeScores();

#endif
