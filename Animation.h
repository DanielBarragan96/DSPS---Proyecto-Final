/*
 * Animation.h
 *
 *  Created on: 10/11/2017
 *      Author: Daniel Barragán
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "DataTypeDefinitions.h"

#define ANIMATION_SIZE 34
#define TILES_SIZE 20


typedef enum{
	COLUMN_1 = 'I',
	COLUMN_2 = 'A',
	COLUMN_3 = 'B',
	COLUMN_4 = 'D'
}Column;

typedef struct{
	Column column;
	uint8 tileIndex;
}Tiles;

BooleanType moveTiles();

BooleanType writeUI();


#endif
