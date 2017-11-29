
#include "DataTypeDefinitions.h"
#include "UART.h"
#include "Animation.h"
#include "PIT.h"
#include "TeraTerm.h"
#include "States.h"
#include "HighScores.h"

//commands to control the serial port of the first column
const TeraTermCommand commandsFirstColumn[ANIMATION_SIZE] = {
		"\033[1;10H","\033[2;10H",
		"\033[3;10H","\033[4;10H",
		"\033[5;10H","\033[6;10H",
		"\033[7;10H","\033[8;10H",
		"\033[9;10H","\033[10;10H",
		"\033[11;10H","\033[12;10H",
		"\033[13;10H","\033[14;10H",
		"\033[15;10H","\033[16;10H",
		"\033[17;10H","\033[18;10H",
		"\033[19;10H","\033[20;10H",
		"\033[21;10H","\033[22;10H",
		"\033[23;10H","\033[24;10H",
		"\033[25;10H","\033[26;10H",
		"\033[27;10H","\033[28;10H",
		"\033[29;10H","\033[30;10H",
		"\033[31;10H","\033[32;10H",
		"\033[33;10H","\033[34;10H",
};
//commands to control the serial port of the second column
const TeraTermCommand commandsSecondColumn[ANIMATION_SIZE] = {
		"\033[1;15H","\033[2;15H",
		"\033[3;15H","\033[4;15H",
		"\033[5;15H","\033[6;15H",
		"\033[7;15H","\033[8;15H",
		"\033[9;15H","\033[10;15H",
		"\033[11;15H","\033[12;15H",
		"\033[13;15H","\033[14;15H",
		"\033[15;15H","\033[16;15H",
		"\033[17;15H","\033[18;15H",
		"\033[19;15H","\033[20;15H",
		"\033[21;15H","\033[22;15H",
		"\033[23;15H","\033[24;15H",
		"\033[25;15H","\033[26;15H",
		"\033[27;15H","\033[28;15H",
		"\033[29;15H","\033[30;15H",
		"\033[31;15H","\033[32;15H",
		"\033[33;15H","\033[34;15H",
};
//commands to control the serial port of the third column
const TeraTermCommand commandsThirdColumn[ANIMATION_SIZE] = {
		"\033[1;20H","\033[2;20H",
		"\033[3;20H","\033[4;20H",
		"\033[5;20H","\033[6;20H",
		"\033[7;20H","\033[8;20H",
		"\033[9;20H","\033[10;20H",
		"\033[11;20H","\033[12;20H",
		"\033[13;20H","\033[14;20H",
		"\033[15;20H","\033[16;20H",
		"\033[17;20H","\033[18;20H",
		"\033[19;20H","\033[20;20H",
		"\033[21;20H","\033[22;20H",
		"\033[23;20H","\033[24;20H",
		"\033[25;20H","\033[26;20H",
		"\033[27;20H","\033[28;20H",
		"\033[29;20H","\033[30;20H",
		"\033[31;20H","\033[32;20H",
		"\033[33;20H","\033[34;20H",
};
//commands to control the serial port of the fourth column
const TeraTermCommand commandsFourthColumn[ANIMATION_SIZE] = {
		"\033[1;25H","\033[2;25H",
		"\033[3;25H","\033[4;25H",
		"\033[5;25H","\033[6;25H",
		"\033[7;25H","\033[8;25H",
		"\033[9;25H","\033[10;25H",
		"\033[11;25H","\033[12;25H",
		"\033[13;25H","\033[14;25H",
		"\033[15;25H","\033[16;25H",
		"\033[17;25H","\033[18;25H",
		"\033[19;25H","\033[20;25H",
		"\033[21;25H","\033[22;25H",
		"\033[23;25H","\033[24;25H",
		"\033[25;25H","\033[26;25H",
		"\033[27;25H","\033[28;25H",
		"\033[29;25H","\033[30;25H",
		"\033[31;25H","\033[32;25H",
		"\033[33;25H","\033[34;25H",
};

//This stores each song tile and the delay it needs until the system has to display the next tile
const Song songs[SONG_SIZE] = {{COLUMN_1,4.5F},{COLUMN_1,3.5F},
							   {COLUMN_1,3.5F},{COLUMN_2,3.5F},
							   {COLUMN_2,3.5F},{COLUMN_2,3.5F},
							   {COLUMN_3,3.5F},{COLUMN_3,3.5F},
							   {COLUMN_4,4.5F},{COLUMN_4,3.5F}};

//array of stored tiles
static Tiles tiles[TILES_SIZE];
//size of the tiles List
static uint8 listSize = 0;

//indicate the game difficulty
static Dificulty gameDificulty = EASY;
//game scores
static uint8 playerScore = 0;
static uint8 songScore = 0;
//indicate when the song is ended
BooleanType songEnded = FALSE;
//indicate the current tile printed of the song
static uint8 songIndex = 0;
//List flags
static BooleanType tilesEmpty = FALSE;
static BooleanType tilesFull = FALSE;

BooleanType handleTilePress(Column column){
	uint8 currentTileSongIndex = getLowerColumnVal(column);
	if(NO_TILE != currentTileSongIndex){//there was a tile in the column
			uint8 index = tiles[currentTileSongIndex].tileIndex;//get the index of the tile
			if(gameDificulty <= index){//if the tile is in the limit according to the difficulty
				playerScore++;//increase player score
				switch(column){//update each column animation for the tiles
					case COLUMN_1:{
						UART_putString(UART_0, commandsFirstColumn[index]);
						break;
					}
					case COLUMN_2:{
						UART_putString(UART_0, commandsSecondColumn[index]);
						break;
						}
					case COLUMN_3:{
						UART_putString(UART_0, commandsThirdColumn[index]);
						break;
						}
					case COLUMN_4:{
						UART_putString(UART_0, commandsFourthColumn[index]);
						break;
						}
					default:
						return FALSE;//if column selected out of order (ERROR)
				}
				UART_putChar(UART_0, ' ');//Erase last screen value of the Tile
				removeTile(currentTileSongIndex);//remove the pressed tile
				return TRUE;//scored
			}
	}
	return FALSE;//there was an error
}

uint8 getLowerColumnVal(Column column){
	uint8 searchIndex = 0;
	while(listSize > searchIndex){//check all the tiles
		if(column == tiles[searchIndex].column){//first tile in the column
			return searchIndex;//return the index of the tiles array
		}
		searchIndex++;//else pass to next tile
	}
	return NO_TILE;//there is no tile in the specified column
}

BooleanType controlSong(){
	PIT_clear(PIT_1);
	if(SONG_SIZE <= songIndex) return FALSE;//when song ended
	addTile(songs[songIndex].column);//add next song tile
	PIT_delay(PIT_1, SYSTEM_CLOCK, songs[songIndex++].delay);// delay until update screen
	return TRUE;
}

BooleanType addTile(Column column){
	if(TILES_SIZE <= listSize){
		tilesFull = TRUE;//if the list is full set flags
		tilesEmpty = FALSE;
		return FALSE;//because the value wasn't saved
	}
	tiles[listSize].column = column;//add new tile to the List
	tiles[listSize++].tileIndex = 0;
	tilesEmpty = FALSE;
	return TRUE;//new tile added
}

BooleanType removeTile(uint8 index){
	if(listSize <= index)
		return FALSE;//if out of index
	while(listSize > index){
		tiles[index] = tiles[1+index];//move all tiles after the "index"to the left
		index++;
	}
	listSize--;//decrease List size
	songScore++;
	if(0 == listSize) tilesEmpty = TRUE;
	return TRUE;
}

BooleanType moveTiles(){
	if(tilesEmpty){//if the tiles are empty
		PIT_clear(PIT_0);
		UART_putString(UART_0, "\033[2J");//clear screen
		songEnded = TRUE;//indicate the end of the song
		songIndex = 0;
		tilesEmpty = FALSE;

		//TODO change to check in the HighScores
		updateScores(playerScore);//save to memory
		controlMenu();//show score
		//reset game variables
		playerScore = 0;
		songScore = 0;
		return FALSE;
	}
	uint8 passTiles = 0;
	while(listSize > passTiles){//check all the Tiles of the List
		if(ANIMATION_SIZE <= (tiles[passTiles].tileIndex + 1)){
			removeTile(passTiles);//if the tile index is out of the limits delete the tile
			writeUI();
		}
		else{
			switch(tiles[passTiles].column){//update each column animation for the tiles
				case COLUMN_1:{
					UART_putString(UART_0, commandsFirstColumn[tiles[passTiles].tileIndex++]);
					UART_putChar(UART_0, ' ');//Erase last screen value of the Tile
					/** VT100 command for text in red and background in black*/
					UART_putString(UART_0,"\033[0;49;31m");
					UART_putString(UART_0, commandsFirstColumn[tiles[passTiles++].tileIndex]);
					UART_putChar(UART_0, COLUMN_1);//Update tile position
					break;
				}
				case COLUMN_2:{
					UART_putString(UART_0, commandsSecondColumn[tiles[passTiles].tileIndex++]);
					UART_putChar(UART_0, ' ');//Erase last screen value of the Tile
					/** VT100 command for text in yellow and background in black*/
					UART_putString(UART_0,"\033[0;49;33m");
					UART_putString(UART_0, commandsSecondColumn[tiles[passTiles++].tileIndex]);
					UART_putChar(UART_0, COLUMN_2);//Update tile position
					break;
					}
				case COLUMN_3:{
					UART_putString(UART_0, commandsThirdColumn[tiles[passTiles].tileIndex++]);
					UART_putChar(UART_0, ' ');//Erase last screen value of the Tile
					/** VT100 command for text in blue and background in black*/
						UART_putString(UART_0,"\033[0;49;34m");
					UART_putString(UART_0, commandsThirdColumn[tiles[passTiles++].tileIndex]);
					UART_putChar(UART_0, COLUMN_3);//Update tile position
					break;
					}
				case COLUMN_4:{
					UART_putString(UART_0, commandsFourthColumn[tiles[passTiles].tileIndex++]);
					UART_putChar(UART_0, ' ');//Erase last screen value of the Tile
					/** VT100 command for text in green and background in black*/
					UART_putString(UART_0,"\033[0;32;10m");
					UART_putString(UART_0, commandsFourthColumn[tiles[passTiles++].tileIndex]);
					UART_putChar(UART_0, COLUMN_4);//Update tile position
					break;
					}
				default:
					return FALSE;//if column selected out of order (ERROR)
			}
		}
	}

	if(EASY == gameDificulty)//move the cursor for better view
		UART_putString(UART_0, "\033[27;30H");
	else if(MEDIUM == gameDificulty)//move the cursor for better view
		UART_putString(UART_0, "\033[29;30H");
	else if(HARD == gameDificulty)//move the cursor for better view
		UART_putString(UART_0, "\033[31;30H");
	PIT_clear(PIT_0);
	PIT_delay(PIT_0, SYSTEM_CLOCK, 1.0F);// delay until update screen

	return TRUE;
}

BooleanType writeUI(){//write the interface
	/** VT100 command for text in red and background in black*/
	UART_putString(UART_0,"\033[0;49;31m");
	UART_putString(UART_0, "\033[34;10H");
	UART_putChar(UART_0, INTERFACE_TILE);

	/** VT100 command for text in yellow and background in black*/
	UART_putString(UART_0,"\033[0;49;33m");
	UART_putString(UART_0, "\033[34;15H");
	UART_putChar(UART_0, INTERFACE_TILE);

	/** VT100 command for text in blue and background in black*/
	UART_putString(UART_0,"\033[0;49;34m");
	UART_putString(UART_0, "\033[34;20H");
	UART_putChar(UART_0, INTERFACE_TILE);

	/** VT100 command for text in green and background in black*/
	UART_putString(UART_0,"\033[0;49;32m");
	UART_putString(UART_0, "\033[34;25H");
	UART_putChar(UART_0, INTERFACE_TILE);

	//Print interface for the difficulty
	/** VT100 command for text in white and background in black*/
	UART_putString(UART_0,"\033[0;49;37m");
	if(EASY == gameDificulty){
		UART_putString(UART_0, "\033[27;30H");
		UART_putChar(UART_0, INTERFACE_TILE);
	}else if(MEDIUM == gameDificulty){
		UART_putString(UART_0, "\033[29;30H");
		UART_putChar(UART_0, INTERFACE_TILE);
	}else if(HARD == gameDificulty){
		UART_putString(UART_0, "\033[31;30H");
		UART_putChar(UART_0, INTERFACE_TILE);
	}
	return TRUE;
}

BooleanType getSongEnded(){ return songEnded; }// return the songEnded flag

Dificulty getGameDifficulty(){ return gameDificulty; }//return gameDificulty

BooleanType setDifficulty(Dificulty newDifficulty){
	gameDificulty = newDifficulty;//change gameDifficulty
	return TRUE;
}
uint8 getPlayerScore(){	return playerScore;	}//return playerScore value
