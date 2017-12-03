/*
 * Note_Decider.c
 *
 *  Created on: 21/11/2017
 *      Author: ALEX
 */

#include "Note_Decider.h"

static ufloat32 Note_Type = 0; //arrow range
static ufloat32 Note_Prom = 0; //to sum samples
static ufloat32 VALUES[32000] ={0}; //to save adc values
static uint16 salida = 0;	//output of adc
static ufloat32 notemax = 0; //max for adc calibration
static ufloat32 notemin = 1; // min for adc calibration
static uint16 Down_counter = 0; // arrow counters
static uint16 Left_counter = 0;
static uint16 Right_counter = 0;
static uint16 Up_counter = 0;
static uint16 Double_Ncounter = 0; // counter for double arrow
static uint16 Passed_Notes = 0; // counter of added arrows
static uint32 Fs = 0; // for sample frequency
static uint32 N_Index = 0; // index to move array

uint32 Get_Fs()
{
	return Fs;
}

void Set_Fs(uint32 rate)
{
	Fs = rate;
}

uint16 Get_Ncounter()
{
	return Double_Ncounter;
}

void Set_Ncounter(uint16 limit)
{
	Double_Ncounter = limit;
}

void Difficulty_NoteRate(Dificulty difficulty)
{
	switch(difficulty)
	{
	case EASY:
		Set_Fs(32000);
		Set_Ncounter(7);
		break;
	case MEDIUM:
		Set_Fs(16000);
		Set_Ncounter(12);
		break;
	case HARD:
		Set_Fs(10667);
		Set_Ncounter(18);
	}
}

void Music_Processor()
{
			if(TRUE == get_FrecuencyFlag()) // if there was an flex timer interrupt
			{
				Note_Type -= VALUES[N_Index]; // eliminates first value of array
				VALUES[N_Index] = ( float )( ADC_Values() / VALUE_DIVIDER); // divides the value the adc reads to get val between 0 and 1
				salida =(uint16) ( VALUE_DIVIDER*VALUES[N_Index]); // multiplies value of index so the output is in dac range
				DAC0_output(salida); // gives value to dac
				Note_Type += VALUES[N_Index]; // adds the current index of array
				N_Index = (N_Index < (Get_Fs()-1)) ? N_Index+1 : 0; // resets index before it goes over sampling limit
				clear_FrecuencyFlag();
			}
			if(N_Index == (Get_Fs()-1)) //if the index equals the sampling limit generates an arrow depending on conditionals
			{
				Note_Prom = (Note_Type/(Get_Fs()));//-.499920)/.001307;
					if(Note_Prom > notemax)
					{
						notemax = Note_Prom;
					}
					if((Note_Prom < notemin) && (Note_Prom > 0))
					{
						notemin = Note_Prom;
					}
				/**Generates the next arrow depending on how loud was the song in that moment
				 * also depending on difficulty generates a double arrow, and doesnt permit the same
				 * arrow to be generated more than 3 times in a row*/
				if(Note_Prom < ABAJO)
				{
					Left_counter = 0;
					Right_counter = 0;
					Up_counter = 0;
					if(Passed_Notes == Get_Ncounter())
					{
						addTile(COLUMN_4);
						addTile(COLUMN_3);
						Passed_Notes = 0;
						Down_counter = 0;
					}else if(Down_counter == 3)
					{
						addTile(COLUMN_4);
						Down_counter = 0;
						Passed_Notes++;
					}else
					{
						addTile(COLUMN_3);
						Passed_Notes++;
						Down_counter++;
					}
				}else if(Note_Prom < IZQUIERDA && Note_Type > ABAJO)
				{
					Down_counter = 0;
					Right_counter = 0;
					Up_counter = 0;
					if(Passed_Notes == Get_Ncounter())
					{
						addTile(COLUMN_2);
						addTile(COLUMN_1);
						Passed_Notes = 0;
						Left_counter = 0;
					}else if(Left_counter == 3)
					{
						addTile(COLUMN_2);
						Left_counter = 0;
						Passed_Notes++;
					}else
					{
						addTile(COLUMN_1);
						Passed_Notes++;
						Left_counter++;
					}
				}else if(Note_Prom < DERECHA && Note_Type > IZQUIERDA)
				{
					Down_counter = 0;
					Left_counter = 0;
					Up_counter = 0;
					if(Passed_Notes == Get_Ncounter())
					{
						addTile(COLUMN_1);
						addTile(COLUMN_4);
						Passed_Notes = 0;
						Right_counter = 0;
					}else if(Right_counter == 3)
					{
						addTile(COLUMN_3);
						Right_counter = 0;
						Passed_Notes++;
					}else
					{
						addTile(COLUMN_4);
						Passed_Notes++;
						Right_counter++;
					}
				}else
				{
					Down_counter = 0;
					Left_counter = 0;
					Right_counter = 0;
					if(Passed_Notes == Get_Ncounter())
					{
						addTile(COLUMN_3);
						addTile(COLUMN_2);
						Passed_Notes = 0;
						Up_counter = 0;
					}else if(Up_counter == 3)
					{
						addTile(COLUMN_1);
						Up_counter = 0;
						Passed_Notes++;
					}else
					{
					addTile(COLUMN_2);
					Passed_Notes++;
					Up_counter++;
					}
				}
			}
}
