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

#define ABAJO .25
#define IZQUIERDA .50
#define DERECHA .75
#define VALUE_DIVIDER 4096.0

uint32 Get_Fs();
void Set_Fs(uint32 rate);
void Difficulty_NoteRate(Dificulty difficulty);
void Music_Processor();

#endif /* NOTE_DECIDER_H_ */
