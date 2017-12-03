/*
 * Note_Decider.h
 *
 *  Created on: 21/11/2017
 *      Author: ALEX
 */

#ifndef NOTE_DECIDER_H_
#define NOTE_DECIDER_H_

#include "FlexTimer.h"
#include "DataTypeDefinitions.h"
#include "GPIO.h"
#include "ADC.h"
#include "FlexTimer.h"
#include "NVIC.h"
#include "MK64F12.h"
#include "DAC_Drivers.h"
#include "Animation.h"
#include "PIT.h"
#include "TeraTerm.h"
#include "States.h"

#define ABAJO .35
#define IZQUIERDA .45
#define DERECHA .57
#define VALUE_DIVIDER 4096.0

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Returns the sampling limit.
 	 \return FS
 */
uint32 Get_Fs();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Updates the sampling limit
 	 \param[in] New sampling limit.
 	 \return void
 */
void Set_Fs(uint32 rate);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Returns the counter for the double note depending on difficulty
 	 \return Double_NCounter
 */
uint16 Get_Ncounter();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Updates the Double note generation value
 	 \param[in] New double note generation value
 	 \return void
 */
void Set_Ncounter(uint16 limit);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Switch case which depending on difficulty sets both the sampling limit and the double not generation value.
 	 \param[in] current difficulty
 	 \return void
 */
void Difficulty_NoteRate(Dificulty difficulty);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function does the music processing while we're in the play menu
 	 	 	by checking some conditionals generates the whole arrows for the game
 	 \return void
 */
void Music_Processor();

#endif /* NOTE_DECIDER_H_ */
