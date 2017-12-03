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
    static uint16 End_Counter = 0;
    static ufloat32 max = 0;
    static ufloat32 min = 2900;
    static ufloat32 med = 0;
    /*Arreglo en el que se almacenarán los valores del ADC*/
    static ufloat32 VALUES[32000] ={0};
    static uint16 salida = 0;
    static ufloat32 notemax = 0;
	static ufloat32 notemin = 1;
	static uint16 Down_counter = 0;
	static uint16 Left_counter = 0;
	static uint16 Right_counter = 0;
	static uint16 Up_counter = 0;
	static uint16 Double_Ncounter = 0;
	static uint16 Passed_Notes = 0;


/*s*/
static uint32 Fs = 0;
/*Indice que indicará la posición del arreglo donde se guarda un valor, por lo tanto, uno anterior será el más nuevo*/
static uint32 N_Index = 0;

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

void Note_Sender()
{
	;
}

void Music_Processor()
{
			if(TRUE == get_FrecuencyFlag())
			{
				Note_Type -= VALUES[N_Index];
//				med = VALUES[Index];
//				if(med > max)
//				{
//					max = med;
//				}
//				if((med < min) && (med > 0))
//				{
//					min = med;
//				}
				VALUES[N_Index] = ( float )( ADC_Values() / VALUE_DIVIDER);
//				TODO agregar if values<0 values = 0
				salida =(uint16) ( VALUE_DIVIDER*VALUES[N_Index]);
//				med = salida;
//				if(med > max)
//				{
//					max = med;
//				}
//				if((med < min) && (med > 0))
//				{
//					min = med;
//				}
				DAC0_output(salida);
				Note_Type += VALUES[N_Index];
				N_Index = (N_Index < (Get_Fs()-1)) ? N_Index+1 : 0;
				clear_FrecuencyFlag();
			}

//			if((salida>2035) && (salida<2226))
//			{
//				PIT_delay(PIT_2, SYSTEM_CLOCK, 0.1F);
//				End_Counter++;
//				if(End_Counter == 300)
//				{
//					getSystem()->currentStatus =  PRINCIPAL;
//					getSystem()->stateIndex = CERO;
//					printTTMainMenu();
//				}
//			}else
//				End_Counter = 0;

			if(N_Index == (Get_Fs()-1))
			{
				Note_Prom = ((Note_Type/(Get_Fs()))-.499920)/.001307;
					if(Note_Prom > notemax)
					{
						notemax = Note_Prom;
					}
					if((Note_Prom < notemin) && (Note_Prom > 0))
					{
						notemin = Note_Prom;
					}

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
