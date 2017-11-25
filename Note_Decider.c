/*
 * Note_Decider.c
 *
 *  Created on: 21/11/2017
 *      Author: ALEX
 */

#include "Note_Decider.h"

#define ABAJO .25
#define IZQUIERDA .50
#define DERECHA .75

//TODO Idea to make after x number of the same note, go to another note directly
//TODO Idea to make after x number of notes make it last longer/send another note directly after.
//TODO Idea to make the note out frequency vary.
//TODO Pointfunct of addTile on notedecider.
//TODO easy medium and hard Music Processor.
//TODO

void Music_Processor()
{
    ufloat32 Note_Type = 0;
    ufloat32 Note_Prom = 0;
    uint8 Note_Out = 0;
    ufloat32 max = 0;
    ufloat32 min = 2000;
    ufloat32 med = 0;
    /*Arreglo en el que se almacenarán los valores del ADC*/
    float VALUES[32000] ={0};

    /*Indice que indicará la posición del arreglo donde se guarda un valor, por lo tanto, uno anterior será el más nuevo*/
    uint32 Index = 0;

    float salida = 0;

	while(1)
	{
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
				VALUES[Index] = ( float )( ADC_Values() / 4096.0);
//				TODO agregar if values<0 values = 0
				salida =( 4096*VALUES[Index]);
				DAC0_output(salida);
				Note_Type += VALUES[Index];
				Index = (Index < 31999 ) ? Index+1 : 0;
				clear_FrecuencyFlag();
			}
				if(Index == 31999)
				{
					Note_Prom = (Note_Type/32000);
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
			}
	return 0;
}
