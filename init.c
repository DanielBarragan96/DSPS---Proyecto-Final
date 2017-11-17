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
#include "Animation.h"

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

	/**Enables the clock of PortB in order to configures TX and RX of UART peripheral*/
	SIM->SCGC5 = SIM_SCGC5_PORTB_MASK;

   /**Activating the clock gating of the GPIOs and the PIT*/
   GPIO_clockGating(GPIO_C);
   PIT_clockGating();

   GPIO_pinControlRegisterType pinControlRegisterInputInterruptFallingEdge = GPIO_MUX1|GPIO_PE|INTR_FALLING_EDGE;
   GPIO_pinControlRegisterType pinControlRegisterInputInterruptRisingEdge = GPIO_MUX1|GPIO_PE|INTR_RISING_EDGE;

   /**Configure the characteristics in the GPIOs*/
	//Buttons
	GPIO_pinControlRegister(GPIO_C,BIT5,&pinControlRegisterInputInterruptFallingEdge);
	GPIO_pinControlRegister(GPIO_C,BIT7,&pinControlRegisterInputInterruptRisingEdge);
	GPIO_pinControlRegister(GPIO_C,BIT0,&pinControlRegisterInputInterruptRisingEdge);
	GPIO_pinControlRegister(GPIO_C,BIT9,&pinControlRegisterInputInterruptRisingEdge);

	/**Configure Port Pins as input/output*/
	//Buttons
	GPIO_dataDirectionPIN(GPIO_C,GPIO_INPUT,BIT5);
	GPIO_dataDirectionPIN(GPIO_C,GPIO_INPUT,BIT7);
	GPIO_dataDirectionPIN(GPIO_C,GPIO_INPUT,BIT0);
	GPIO_dataDirectionPIN(GPIO_C,GPIO_INPUT,BIT9);

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
	NVIC_enableInterruptAndPriotity(UART0_IRQ, PRIORITY_4);

	/**Enables and sets a particular interrupt and its priority*/
	NVIC_enableInterruptAndPriotity(PIT_CH0_IRQ, PRIORITY_4);
	/**Enables and sets a particular interrupt and its priority*/
	NVIC_enableInterruptAndPriotity(PIT_CH1_IRQ, PRIORITY_4);
	/**Enables and sets a particular interrupt and its priority*/
	NVIC_enableInterruptAndPriotity(PORTC_IRQ,PRIORITY_3);

	/**Enables interrupts*/
	EnableInterrupts;

	//initialize the used PIT for controlling the motor PWM
	PIT_clear(PIT_0);
	PIT_delay(PIT_0, SYSTEM_CLOCK, 3.5F);// delay until next function value

	//initialize the used PIT for controlling the motor PWM
	PIT_clear(PIT_1);
	PIT_delay(PIT_1, SYSTEM_CLOCK, 3.5F);// delay until next function value

	UART_putString(UART_0, "\033[0;32;10m");
	UART_putString(UART_0, "\033[2J");

	writeUI();
}
