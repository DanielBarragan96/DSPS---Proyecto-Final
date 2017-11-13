/*
 * init.h
 *
 *  Created on: 17/09/2017
 *      Author: Daniel Barragán
 */

#include "DataTypeDefinitions.h"
#include "NVIC.h"
#include "GPIO.h"
#include "PIT.h"
#include "MK64F12.h"
#include "init.h"
#include "UART.h"
#include "I2C.h"
#include "MCG.h"
#include "PCF8563.h"
#include "TeraTerm.h"

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

void initMain(){
	//Change the Kinetis clock speed
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
		   I2C_init(I2C_0, 60000000, 100000);

	   //set initial values for the clock
	   PCF8563_setSeconds(0x50);
	   PCF8563_setMinutes(0x59);
	   PCF8563_setHours(0x21);
	   PCF8563_setYears(0x98);
	   PCF8563_setMonths(0x11);
	   PCF8563_setDays(0x30);

	/**Enables the clock of PortB in order to configures TX and RX of UART peripheral*/
	SIM->SCGC5 = SIM_SCGC5_PORTB_MASK;

	/**Configures the pin control register of pin16 in PortB as UART RX*/
	PORTB->PCR[16] = PORT_PCR_MUX(3);
	/**Configures the pin control register of pin16 in PortB as UART TX*/
	PORTB->PCR[17] = PORT_PCR_MUX(3);
	/**Configures UART 0 to transmit/receive at 11520 bauds with a 21 MHz of clock core*/
	UART_init (UART_0,  60000000, BD_115200);
	/**Enables the UART 0 interrupt*/
	UART0_interruptEnable(UART_0);

	/**Sets the threshold for interrupts, if the interrupt has higher priority constant that the BASEPRI, the interrupt will not be attended*/
	NVIC_setBASEPRI_threshold(PRIORITY_5);
	/**Enables the UART 0 interrupt in the NVIC*/
	NVIC_enableInterruptAndPriotity(UART0_IRQ, PRIORITY_3);

	PIT_clockGating();
	/**Enables and sets a particular interrupt and its priority*/
	NVIC_enableInterruptAndPriotity(PIT_CH0_IRQ, PRIORITY_2);
	/**Enables and sets a particular interrupt and its priority*/
	NVIC_enableInterruptAndPriotity(PIT_CH1_IRQ, PRIORITY_2);
	/**Enables and sets a particular interrupt and its priority*/
	NVIC_enableInterruptAndPriotity(PIT_CH2_IRQ, PRIORITY_2);
	/**Enables and sets a particular interrupt and its priority*/
	NVIC_enableInterruptAndPriotity(PIT_CH3_IRQ, PRIORITY_2);

	/**Enables interrupts*/
	EnableInterrupts;

	//initialize the used PIT for controlling the motor PWM
	PIT_clear(PIT_0);
	PIT_delay(PIT_0, SYSTEM_CLOCK, 0.2);// delay until next function value
	//initialize the used PIT for controlling the motor PWM
	PIT_clear(PIT_1);
	PIT_delay(PIT_1, SYSTEM_CLOCK, 0.2F);// delay until next function value
	//initialize the used PIT for controlling the motor PWM
	PIT_clear(PIT_2);
	PIT_delay(PIT_2, SYSTEM_CLOCK, 0.2F);// delay until next function valu
	//initialize the used PIT for controlling the motor PWM
	PIT_clear(PIT_3);
	PIT_delay(PIT_3, SYSTEM_CLOCK, 0.2F);// delay until next function valu

	UART_putString(UART_0, "\033[0;32;10m");
	UART_putString(UART_0, "\033[2J");

	UART_putChar(UART_0, 219);
	UART_putString(UART_0, "\033[34;10H");
	UART_putChar(UART_0, 219);
	UART_putString(UART_0, "\033[34;15H");
	UART_putChar(UART_0, 219);
	UART_putString(UART_0, "\033[34;20H");
	UART_putChar(UART_0, 219);
	UART_putString(UART_0, "\033[34;25H");
}
