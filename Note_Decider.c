/*
 * Note_Decider.c
 *
 *  Created on: 21/11/2017
 *      Author: ALEX
 */

#include "Note_Decider.h"

//TODO Idea to make after x number of the same note, go to another note directly.
//TODO Idea to make after x number of notes make it last longer/send another note directly after.
//TODO Idea to make the note out frequency vary.
//TODO Pointfunct of addTile on notedecider.
//TODO easy medium and hard Music Processor/ switch not only the rate which notes are produced.
//TODO lijar pinche tarima/pensar que ponerle arriba.
//TODO contador para los filtros de soule.
//TODO contador cambian cada cuanto se mandan las flechas diferentes funciones que cambian ese rate y usar funct poin.

    static ufloat32 Note_Type = 0;
    static ufloat32 Note_Prom = 0;
    static uint8 Note_Out = 0;
    static ufloat32 max = 0;
    static ufloat32 min = 2000;
    static ufloat32 med = 0;
    /*Arreglo en el que se almacenarán los valores del ADC*/
    static float VALUES[32000] ={0};
    static uint16 salida = 0;
    static float notemax = 0;
	static float notemin = .5060;
	static uint16 Down_counter = 0;
	static uint16 Left_counter = 0;
	static uint16 Right_counter = 0;
	static uint16 Up_counter = 0;

/*s*/
static uint32 Fs = 0;
/*Indice que indicará la posición del arreglo donde se guarda un valor, por lo tanto, uno anterior será el más nuevo*/
static uint32 Index = 0;

uint32 Get_Fs()
{
	return Fs;
}

void Set_Fs(uint32 rate)
{
	Fs = rate;
}

void Difficulty_NoteRate(Dificulty difficulty)
{
	switch(difficulty)
	{
	case EASY:
		Set_Fs(32000);
		break;
	case MEDIUM:
		Set_Fs(16000);
		break;
	case HARD:
		Set_Fs(10667);
	}
}

void Note_Sender()
{
	;
}

void Music_Processor()
{
//	while(1)
//	{
			if(TRUE == get_FrecuencyFlag())
			{
				Note_Type -= VALUES[Index];
//				med = VALUES[Index];
//				if(med > max)
//				{
//					max = med;
//				}
//				if((med < min) && (med > 0))
//				{
//					min = med;
//				}
				VALUES[Index] = ( float )( ADC_Values() / VALUE_DIVIDER);
//				TODO agregar if values<0 values = 0
				salida =(uint16) ( VALUE_DIVIDER*VALUES[Index]);
				DAC0_output(salida);
				Note_Type += VALUES[Index];
				Index = (Index < (Get_Fs()-1)) ? Index+1 : 0;
				clear_FrecuencyFlag();
			}
				if(Index == (Get_Fs()-1))
				{
					Note_Prom = ((Note_Type/(Get_Fs()))-.502070)/.004945;//-.486610)/.005374;
//					if(Note_Prom > notemax)
//					{
//						notemax = Note_Prom;
//					}
//					if((Note_Prom < notemin) && (Note_Prom > 0))
//					{
//						notemin = Note_Prom;
//					}

					if(Note_Prom < ABAJO)
					{
						Left_counter = 0;
						Right_counter = 0;
						Up_counter = 0;
						if(Down_counter == 4)
						{
							addTile(COLUMN_4);
							Down_counter = 0;
						}else
						{
							addTile(COLUMN_3);
						}
						Down_counter++;
					}else if(Note_Prom < IZQUIERDA && Note_Type > ABAJO)
					{
						Down_counter = 0;
						Right_counter = 0;
						Up_counter = 0;
						if(Left_counter == 4)
						{
							addTile(COLUMN_2);
							Left_counter = 0;
						}else
						{
							addTile(COLUMN_1);
						}
						Left_counter++;
					}else if(Note_Prom < DERECHA && Note_Type > IZQUIERDA)
					{
						Down_counter = 0;
						Left_counter = 0;
						Up_counter = 0;
						if(Right_counter == 4)
						{
							addTile(COLUMN_3);
							Right_counter = 0;
						}else
						{
							addTile(COLUMN_4);
						}
						Right_counter++;
					}else
					{
						Down_counter = 0;
						Left_counter = 0;
						Right_counter = 0;
						if(Up_counter == 4)
						{
							addTile(COLUMN_1);
							Up_counter = 0;
						}else
						{
						addTile(COLUMN_2);
						}
						Up_counter++;
					}
				}
}
