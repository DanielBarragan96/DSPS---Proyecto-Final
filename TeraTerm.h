/**
	\file
	\brief
		This is the header file for the UART device driver.
		It contains the macros and function definition.
	\author Daniel Barragán
	\date	2/11/2017
	\todo
		To implement all needed functions
 */
#ifndef TERATERM_H_
#define TERATERM_H_

#include "DataTypeDefinitions.h"

/*! This data type is used to indicate when TeraTerm worked properly*/
typedef enum{
	ERROR,
	GOOD
}TeraTermStatus;


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 It sends the MainMenu through the serial port.
 	 \return GOOD if there were no troubles
 */
TeraTermStatus printTTMainMenu();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 It sends the Difficulty first state menu through the serial port.
 	 \return GOOD if there were no troubles
 */
TeraTermStatus printTTDifficulty_1();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 It sends the Difficulty second state menu through the serial port.
 	 \return GOOD if there were no troubles
 */
TeraTermStatus printTTDifficulty_2();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 It sends the Records menu through the serial port.
 	 \return GOOD if there were no troubles
 */
TeraTermStatus printTTRecords_1();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 It checks if the user decided to reset the scores.
 	 \return GOOD if there were no troubles
 */
TeraTermStatus printTTRecords_2();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function is used for preparing the UART screen trough the serial port to
 	 init the game.
 	 \return GOOD if there were no troubles
 */
BooleanType screenPlay_1();

BooleanType screenPlay_2();

#endif /* TERATERM_H_ */
