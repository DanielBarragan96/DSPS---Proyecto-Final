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
//TODO minsalida-x is new 0 maxsalida+x is 1.

    static ufloat32 Note_Type = 0;
    static ufloat32 Note_Prom = 0;
    static uint8 Note_Out = 0;
    static ufloat32 max = 0;
    static ufloat32 min = 2000;
    static ufloat32 med = 0;
    /*Arreglo en el que se almacenarán los valores del ADC*/
    static float VALUES[32000] ={0};
    static float salida = 0;

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
				med = VALUES[Index];
				if(med > max)
				{
					max = med;
				}
				if((med < min) && (med > 0))
				{
					min = med;
				}
				VALUES[Index] = ( float )( ADC_Values() / VALUE_DIVIDER);
//				TODO agregar if values<0 values = 0
				salida =( VALUE_DIVIDER*VALUES[Index]);
				DAC0_output(salida);
				Note_Type += VALUES[Index];
				Index = (Index < (Get_Fs()-1)) ? Index+1 : 0;
				clear_FrecuencyFlag();
			}
				if(Index == (Get_Fs()-1))
				{
					Note_Prom = (Note_Type/(Get_Fs()));
					if(Note_Prom < ABAJO)
					{
						addTile(COLUMN_3);
						Note_Out = 2;

					}else if(Note_Prom < IZQUIERDA && Note_Type > ABAJO)
					{
						addTile(COLUMN_1);
						Note_Out = 0;
					}else if(Note_Prom < DERECHA && Note_Type > IZQUIERDA)
					{
						addTile(COLUMN_4);
						Note_Out = 3;
					}else
						addTile(COLUMN_2);
						Note_Out = 1;
				}
//			}
//    ufloat32 Note_Type = 0;
//    ufloat32 Note_Prom = 0;
//    uint8 Note_Out = 0;
//    ufloat32 max = 0;
//    ufloat32 min = 2000;
//    ufloat32 med = 0;
//    /*Arreglo en el que se almacenarán los valores del ADC*/
//    float VALUES[32000] ={0};
//
//    /*Indice que indicará la posición del arreglo donde se guarda un valor, por lo tanto, uno anterior será el más nuevo*/
//    uint32 Index = 0;
//
//    float salida = 0;
//
//	while(1)
//	{
//			if(TRUE == get_FrecuencyFlag())
//			{
//				Note_Type -= VALUES[Index];
//				med = VALUES[Index];
//				if(med > max)
//				{
//					max = med;
//				}
//				if((med < min) && (med > 0))
//				{
//					min = med;
//				}
//				VALUES[Index] = ( float )( ADC_Values() / VALUE_DIVIDER);
////				TODO agregar if values<0 values = 0
//				salida =( VALUE_DIVIDER*VALUES[Index]);
//				DAC0_output(salida);
//				Note_Type += VALUES[Index];
//				Index = (Index < 31999 ) ? Index+1 : 0;
//				clear_FrecuencyFlag();
//			}
//				if(Index == 31999)
//				{
//					Note_Prom = (Note_Type/32000);
//					if(Note_Prom < ABAJO)
//					{
//						addTile(COLUMN_3);
//						Note_Out = 2;
//
//					}else if(Note_Prom < IZQUIERDA && Note_Type > ABAJO)
//					{
//						addTile(COLUMN_1);
//						Note_Out = 0;
//					}else if(Note_Prom < DERECHA && Note_Type > IZQUIERDA)
//					{
//						addTile(COLUMN_4);
//						Note_Out = 3;
//					}else
//						addTile(COLUMN_2);
//						Note_Out = 1;
//				}
//			}
}
