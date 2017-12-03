/*
 * Animation.h
 *
 *  Created on: 10/11/2017
 *      Author: Daniel Barragán
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "DataTypeDefinitions.h"

#define ANIMATION_SIZE 34 // number of commands to move the tiles (rows)
#define TILES_SIZE 100 // maximum number of tiles that can be displayed in screen simultaneously
#define INTERFACE_TILE 219 // the tile shown in the UI
#define SONG_SIZE 10 // the number of tiles per song
#define NO_TILE 100 // this value is used to indicate when no tile was founded
#define FIRST_ELEMENT 0 // first element of an array

//values to handle the LED color
#define RED_LED 0.2F
#define BLUE_LED 0.5F
#define GREEN_LED 0.8F

/*! This data type is used for selecting the difficulty of the game*/
typedef enum{
	EASY = ANIMATION_SIZE - 7,
	MEDIUM = ANIMATION_SIZE - 5,
	HARD = ANIMATION_SIZE - 3,
	EASY_INPUT = '1',
	MEDIUM_INPUT = '2',
	HARD_INPUT = '3'
}Dificulty;
/*! This data type is used for selecting the column of the Tile
 * and also the ASCII code to print for each column*/
typedef enum{
	COLUMN_1 = 'I',
	COLUMN_2 = 'A',
	COLUMN_3 = 'B',
	COLUMN_4 = 'D'
}Column;
/*! This data type have the necessary elements for each tile*/
typedef struct{
	Column column;
	uint8 tileIndex;
}Tiles;
/*! This data type have the necessary elements to display the tiles of a song*/
typedef struct{
	Column column;
	uint8 delay;
}Song;

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function handles the pressed pad and the playerScore.
 	 \param[in]  column to add the tile.
 	 \return TRUE if the player scored, FALES if missed/error.
 */
BooleanType handleTilePress(Column column);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function finds the first tile in a specific column.
 	 \param[in]  column to find the first tile.
 	 \return current first tile index of the tiles array.
 */
uint8 getLowerColumnVal(Column column);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function add the next song tile to the tiles array.
 	 \return TRUE if there were no troubles adding the tile.
 */
BooleanType controlSong();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function add a new tile to the tiles array.
 	 \param[in]  column to add the tile.
 	 \return TRUE if there were no troubles adding the tile.
 */
BooleanType addTile(Column column);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function removes a specific tile, and move all the other tiles after
 	 the "index"to the left
 	 \param[in]  index of the tile to remove.
 	 \return TRUE if there were no troubles.
 */
BooleanType removeTile(uint8 index);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function update each tile position inside the tiles array.
 	 \return TRUE if there were no troubles.
 */
BooleanType moveTiles();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function writes  the interface of the game.
 	 \return TRUE if there were no troubles.
 */
BooleanType writeUI();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function gets the game difficulty.
 	 \return gameDifficulty status.
 */
Dificulty getGameDifficulty();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function updates the gameDifficulty
 	 \param[in]  newDifficulty sets the gameDifficulty new value.
 	 \return TRUE if there were no troubles.
 */
BooleanType setDifficulty(Dificulty newDifficulty);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function returns the difficulty of the game.
 	 \return playerScore value.
 */
Dificulty getGameDifficulty();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function returns the player score value.
 	 \return playerScore value.
 */
uint8 getPlayerScore();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function returns the song score value.
 	 \return songScore value.
 */
uint8 getSongScore();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function is used as a simple delay used to manage the LEDs.
 	 \param[in]  delay indicates the value of the delay.
 	 \return TRUE if there was no error.
 */
BooleanType delayLEDs(uint16 delay);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function turns off all the LEDs of the Kinetis.
 	 \return TRUE if there was no error.
 */
BooleanType turnLEDsOff();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function turns on the blue LED of the Kinetis.
 	 \return TRUE if there was no error.
 */
BooleanType blueLEDOn();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function turns on the red LED of the Kinetis.
 	 \return TRUE if there was no error.
 */
BooleanType redLEDOn();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function turns on the green LED of the Kinetis.
 	 \return TRUE if there was no error.
 */
BooleanType greenLEDOn();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function is used as a simple delay used to manage the LEDs.
 	 \param[in]  song is the new value of the songEnd variable.
 	 \return TRUE if there was no error.
 */
BooleanType setSongEnd(uint8 song);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function reset all the variables of animation.
 	 \return TRUE if there was no error.
 */
BooleanType restartAnimation();

#endif
