#ifndef	STATE_MACHINE_H_INCLUDE
#define STATE_MACHINE_H_INCLUDE

#include "Tile.h"

// defined states
//		see "Terminology.txt" for more information
const int MOVE 				= 0; // One unit can move upto their movementPoints (or less than), one tile at a time.
const int ACTION 			= 1; // attack/heal
const int UPDATE			= 2; // decrement the remaining values of buff/debuff counters
const int CHECK_DEATHS 		= 3; // checks if units have <0 hp -> death
const int CHECK_GAMEOVER 	= 4; // check end of game condition
const int GAMEOVER			= 5; // game has ended

void state_move();
void state_action();
void state_check_deaths();
void state_update();
void state_check_gameOver();
void state_gameOver();

GLfloat calculateRanges(Vector3f* start, Vector3f* end); // calculates the range of from the selected unit/tile to the next selected unit/tile
void resetStateVars();
void chooseState();
void selectionForStates(Tile* choosenTile); // given to "State Machine.cpp" from the mouse ray selection in "Player control.cpp"

#endif
