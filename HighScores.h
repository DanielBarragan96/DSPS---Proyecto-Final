/*
 * HighScoress.h
 *
 *  Created on: 21/11/2017
 *      Author: Daniel Barragán
 */

#ifndef HIGHSCORES_H_
#define HIGHSCORES_H_

#include "DataTypeDefinitions.h"

//indicates the end index of the array
#define ARRAY_END 0

//the next variables represents the memory direction for the highscores
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
//this defines the size of the score places
#define SCORES_ARRAY_SIZE 10
#define SCORES_BYTES 10
//this value indicates that the user wants to reset the high scores
#define RESET_HIGH_SCORES '1'

/*! This data type stores the score direction with a pointer*/
typedef struct{
	uint8* score;
}Score;

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function checks if the new score is a high score.
 	 \param[in]  score from the player.
 	 \return TRUE if the score was equal or higher of the previous high scores, FALSE if it wasn't.
 */
uint8 updateScores(uint8 newScore);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function reads the high scores stored in the memory.
 	 \return TRUE if there was no problem reading the values.
 */
BooleanType readScores();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function resets to zero the actualScores to the memory.
 	 \return TRUE if there was no problem storing the values.
 */
BooleanType resetScores();

#endif
