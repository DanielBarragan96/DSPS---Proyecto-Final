/*
 * DAC_Drivers.c
 *
 *  Created on: 01/10/2017
 *      Author: Alex Ávila & Daniel Barragan
 */
#include "DataTypeDefinitions.h"
#include "MK64F12.h"




 void init_DAC0(void){
     SIM->SCGC2 = 0x1000;
     DAC0->C0 = 0xC0;
 }
 void DAC0_output(uint16 x){
	 DAC0->DAT[0].DATL = (uint8) (0xFF & x);
	 DAC0->DAT[0].DATH = (uint8) (x >> 8);
 }
