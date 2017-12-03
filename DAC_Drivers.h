/*
 * DAC_Drivers.h
 *
 *  Created on: 01/10/2017
 *      Author: Alex Ávila && Daniel Barragán
 */

#ifndef DAC_DRIVERS_H_
#define DAC_DRIVERS_H_




/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 DAC initialization, configures and starts clk.
 	 \return void
 */
void init_DAC0(void);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Gives the value the ADC is reading to the DAC high and low since they're separate
 	 \param[in] value that is gonna be converted by DAC
 	 \return void
 */
void DAC0_output(uint16 val);

#endif /* DAC_DRIVERS_H_ */
