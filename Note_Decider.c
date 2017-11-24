/*
 * Note_Decider.c
 *
 *  Created on: 21/11/2017
 *      Author: ALEX
 */

#include "DataTypeDefinitions.h"
#include "GPIO.h"
#include "ADC.h"
#include "FlexTimer.h"
#include "NVIC.h"
#include "MK64F12.h"
#include "stdio.h"
#include "MCG.h"
#include "DAC_Drivers.h"
#include <Math.h>

#define CLK_FREQ_HZ 50000000  /* CLKIN0 frequency */
#define SLOW_IRC_FREQ 32768	/*This is the approximate value for the slow irc*/
#define FAST_IRC_FREQ 4000000 /*This is the approximate value for the fast irc*/
#define EXTERNAL_CLOCK 0 /*It defines an external clock*/
#define PLL_ENABLE 1 /**PLL is enabled*/
#define PLL_DISABLE 0 /**PLL is disabled*/
#define CRYSTAL_OSC 1  /*It defines an crystal oscillator*/
#define LOW_POWER 0     /* Set the oscillator for low power mode */
#define SLOW_IRC 0 		/* Set the slow IRC */
#define CLK0_TYPE 0     /* Crystal or canned oscillator clock input */
#define PLL0_PRDIV 25    /* PLL predivider value */
#define PLL0_VDIV 30    /* PLL multiplier value*/
#define ABAJO .25
#define IZQUIERDA .50
#define DERECHA .75

int main(void)
{

	int mcg_clk_hz;
	unsigned char modeMCG = 0;


	#ifndef PLL_DIRECT_INIT
	    mcg_clk_hz = fei_fbi(SLOW_IRC_FREQ,SLOW_IRC);// 64 Hz ---> 32768
	    mcg_clk_hz = fbi_fbe(CLK_FREQ_HZ,LOW_POWER,EXTERNAL_CLOCK); // 97.656KHz ---> 50000000
	    mcg_clk_hz = fbe_pbe(CLK_FREQ_HZ,PLL0_PRDIV,PLL0_VDIV);	// 97.656KHz ---> 50000000 and PLL is configured to generate 60000000
	    mcg_clk_hz =  pbe_pee(CLK_FREQ_HZ);// 117.18 KHz ---> 60000000
	#else
	       mcg_clk_hz = pll_init(CLK_FREQ_HZ, LOW_POWER, EXTERNAL_CLOCK, PLL0_PRDIV, PLL0_VDIV, PLL_ENABLE);
	#endif


	modeMCG = what_mcg_mode();
	ADC_init();
	init_DAC0();
	FlexTimer3_Init(32000);

    ufloat32 Note_Type = 0;
    ufloat32 Note_Prom = 0;
    uint8 Note_Out = 0;

    /*Arreglo en el que se almacenarán los valores del ADC*/
    float VALUES[44000] ={0};

    /*Indice que indicará la posición del arreglo donde se guarda un valor, por lo tanto, uno anterior será el más nuevo*/
    uint32 Index = 0;

    float salida = 0;

    NVIC_enableInterruptAndPriotity(FTM3_IRQ, PRIORITY_4);
	while(1)
	{
			if(TRUE == get_FrecuencyFlag())
			{
				Note_Type -= VALUES[Index];
				VALUES[Index] = ( float )( ADC_Values() / 4096.0);
				salida =( 4096*VALUES[Index]);
				DAC0_output(salida);
				Note_Type += VALUES[Index];
				Index = (Index < 43999 ) ? Index+1 : 0;
				clear_FrecuencyFlag();
			}
				if(Index == 43999)
				{
					Note_Prom = (Note_Type/44000);
					if(Note_Prom < ABAJO)
					{
						Note_Out = 2;//TODO Madre generada = abajo

					}else if(Note_Prom < IZQUIERDA && Note_Type > ABAJO)
					{
						Note_Out = 0;//TODO Madre generada = izq
					}else if(Note_Prom < DERECHA && Note_Type > IZQUIERDA)
					{
						Note_Out = 3;//TODO Madre generada = derecha
					}else
						Note_Out = 1;//TODO Madre generada = arriba
				}
			}
	return 0;
}
