#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <vector>
#include <stdlib.h> // abs()
#include <math.h> 	// sqrt()
#include <string>
#include <string.h>

#include "State Machine.h"
#include "Unit.h"
#include "Tile.h"

extern std::vector<Unit> unitVector_team1;
extern std::vector<Unit> unitVector_team2;

GLint CURRENT_STATE;	// states are inside of "State machine.h" and const
Unit* unit_controlled;	// the unit that will move
Unit* unit_target;
Vector3f* endTile_hex; 	// coords of where the unit will end
Vector3f* endTile_grid;
GLfloat choosenTile_offense; // these are values instead of a obj ptr because for whatever reason when you call an obj
GLfloat choosenTile_defense;		// >60 a second, the valuse get corrupted... plus this saves memory,
GLfloat choosenTile_rangeBonus;		// just a couple of floats instead of an obj

// states change in "Player control.h"
bool isUnit_controlled 		= false;	// changed when a tile that a unit is on is selected
bool isUnit_targetSelected 	= false;	// true only when a target is selected
bool isTileSelected 		= false;	// changed when a unit is already selected, and a tile is then selected again with the mouse
bool actNow 				= false;	// changes to true when [spacebar] is pressed; describes when an action takes place
bool isActionAHeal			= false;	// only true when in action state and two units of the same team are selected

void state_move()
{
	if (actNow && isUnit_controlled && isTileSelected) // true when the spacebar is pressed
	{
		// is target within move range?
		if (calculateRanges(unit_controlled->getCoords_grid(), endTile_grid) <= unit_controlled->getMovePoints())
		{
			// unit can only move once, and it must be <= movePoints

			std::cout << "Moved!!" << std::endl;
			std::cout << "  dist: " << calculateRanges(unit_controlled->getCoords_grid(), endTile_grid) << std::endl;

			unit_controlled->setCoords_grid(endTile_grid);
			unit_controlled->setCoords_hex(endTile_hex);
			unit_controlled->updateStats();

			// change state and null values to prep for next state
			CURRENT_STATE = ACTION;
			resetStateVars();
		}
		else
		{
			std::cout << "Move - distance to far" << std::endl;
			std::cout << "  dist: " << calculateRanges(unit_controlled->getCoords_grid(), endTile_grid) << std::endl;
			actNow = false;
			isTileSelected = false;
		}
	}
}

void state_action()
{
	if (actNow &&
	        isUnit_controlled && isUnit_targetSelected &&
	        !isActionAHeal && !unit_controlled->getIsHealer()) // atacking
	{
		if (calculateRanges(unit_controlled->getCoords_grid(), endTile_grid) <= unit_controlled->getFlux_damageRange())
		{
			std::cout << "Attacked!!" << std::endl;
			std::cout << "  dist: " << calculateRanges(unit_controlled->getCoords_grid(), endTile_grid) << std::endl;
			unit_controlled->printStats();
			endTile_grid->printStats();

			// decrease the targets HP by the amount that the controlled unit can attack
			unit_target->setHealth(unit_target->getHealth() - unit_controlled->getFlux_damage());

			// change state and null values to prep for next state
			CURRENT_STATE = CHECK_DEATHS;
			resetStateVars();
		}
		else
		{
			std::cout << "attack - distance to far" << std::endl;
			std::cout << "  dist: " << calculateRanges(unit_controlled->getCoords_grid(), endTile_grid) << std::endl;

			actNow = false;
			isTileSelected = false;
		}
	}
	else if (actNow &&
	         isUnit_controlled && isUnit_targetSelected &&
	         isActionAHeal && unit_controlled->getIsHealer()) // healing
	{
		// healing target within healing range?
		if (calculateRanges(unit_controlled->getCoords_grid(), endTile_grid) <= unit_controlled->getFlux_healingRange())
		{
			// heal selected unit by the healing amount of first selected unit

			std::cout << "healed!" << std::endl;
			std::cout << "  dist: " << calculateRanges(unit_controlled->getCoords_grid(), endTile_grid) << std::endl;

			unit_target->setHealth(unit_target->getHealth() + unit_controlled->getFlux_healing());

			// change state and null values to prep for next state
			CURRENT_STATE = CHECK_DEATHS;
			resetStateVars();
		}
		else
		{
			std::cout << "healing - distance to far" << std::endl;
			std::cout << "  dist: " << calculateRanges(unit_controlled->getCoords_grid(), endTile_grid) << std::endl;

			actNow = false;
			isTileSelected = false;
		}
	}
}

void state_check_deaths()
{
	std::vector<Unit> nonDeadUnits_team1;
	std::vector<Unit> nonDeadUnits_team2;

	//###################
	//##### team 1 ######
	//###################
	for (std::vector<Unit>::iterator unit = unitVector_team1.begin(); unit != unitVector_team1.end(); ++unit)
	{
		if (unit->getHealth() <= 0)
		{
			std::cout << "team 1 unit dead" << std::endl;
		}
		else
		{
			nonDeadUnits_team1.push_back(*unit);
		}
	}

	//###################
	//##### team 2 ######
	//###################
	for (std::vector<Unit>::iterator unit = unitVector_team2.begin(); unit != unitVector_team2.end(); ++unit)
	{
		if (unit->getHealth() <= 0)
		{
			std::cout << "team 2 unit dead" << std::endl;
		}
		else
		{
			nonDeadUnits_team2.push_back(*unit);
		}
	}
	// set the unitVectors equal to the alive units
	unitVector_team1.clear();
	unitVector_team1 = nonDeadUnits_team1;
	unitVector_team2.clear();
	unitVector_team2 = nonDeadUnits_team2;

	CURRENT_STATE = UPDATE;
	resetStateVars();
}

void state_update()
{
	std::cout << "<update>" << std::endl;

	CURRENT_STATE = CHECK_GAMEOVER;
}

void state_check_gameOver()
{
	//##### FIRST CHECK IF DEBUFS KILLED ANY UNITS ######

	std::vector<Unit> nonDeadUnits_team1;
	std::vector<Unit> nonDeadUnits_team2;

	//###################
	//##### team 1 ######
	//###################
	for (std::vector<Unit>::iterator unit = unitVector_team1.begin(); unit != unitVector_team1.end(); ++unit)
	{
		if (unit->getHealth() <= 0)
		{
			std::cout << "team 1 unit dead" << std::endl;
		}
		else
		{
			nonDeadUnits_team1.push_back(*unit);
		}
	}

	//###################
	//##### team 2 ######
	//###################
	for (std::vector<Unit>::iterator unit = unitVector_team2.begin(); unit != unitVector_team2.end(); ++unit)
	{
		if (unit->getHealth() <= 0)
		{
			std::cout << "team 2 unit dead" << std::endl;
		}
		else
		{
			nonDeadUnits_team2.push_back(*unit);
		}
	}
	// set the unitVectors equal to the alive units
	unitVector_team1.clear();
	unitVector_team1 = nonDeadUnits_team1;
	unitVector_team2.clear();
	unitVector_team2 = nonDeadUnits_team2;


	//#### CHECK GAME OVER CONDITION #####
	// one teams units are all dead && one teams base is dead (TODO: implement a 'base')

	if (unitVector_team1.size() == 0 &&
	        unitVector_team2.size() > 0)
	{
		std::cout << "Team 2 wins!" << std::endl;
		std::cout << "#### GAME OVER ####" << std::endl;
		CURRENT_STATE = GAMEOVER;
	}
	else if (unitVector_team2.size() == 0 &&
	         unitVector_team1.size() > 0)
	{
		std::cout << "Team 1 wins!" << std::endl;
		std::cout << "#### GAME OVER ####" << std::endl;
		CURRENT_STATE = GAMEOVER;
	}
	else if (unitVector_team1.size() == 0 &&
	         unitVector_team2.size() == 0)
	{
		std::cout << "This shouldnt happen, but draw?" << std::endl;
		std::cout << "#### DRAW?? ####" << std::endl;
		CURRENT_STATE = GAMEOVER;
	}
	else
	{
		std::cout << "Game continues!" << std::endl;
		CURRENT_STATE = MOVE;
		resetStateVars();
	}
}

void chooseState()
{
//	CURRENT_STATE = ACTION;
	switch (CURRENT_STATE)
	{
		case (MOVE):
			state_move();
			break;
		case (ACTION):
			state_action();
			break;
		case (UPDATE):
			state_update();
			break;
		case (CHECK_DEATHS):
			state_check_deaths();
			break;
		case (CHECK_GAMEOVER):
			state_check_gameOver();
			break;
		case (GAMEOVER):
			break;
	}
}

// uses GRID COORDS
// returns the range accounting for diagonal movement
// should return an int in float form, but may have rounding errors if numbers are huge
GLfloat calculateRanges(Vector3f* start, Vector3f* end)
{
	GLfloat start_x = start->operator [](0);
	GLfloat start_y = start->operator [](1);
	GLfloat start_z = start->operator [](2);
	GLfloat end_x 	= end->operator [](0);
	GLfloat end_y 	= end->operator [](1);
	GLfloat end_z 	= end->operator [](2);

	// start == end
	if (start_x == end_x &&
	        start_y == end_y &&
	        start_z == end_y)
	{
		return 0;
	}

	// moving horizontally
	if (start_x == end_x) // horizontally (x-axis)
	{
		return abs(start_z - end_z);
	}
	else if (start_z == end_z)
	{
		return abs(start_x - end_x); // horizontally (z-axis)
	}

	// moveing some degree of diagonally
	/* Formula:
	 * 		sqrt(x^2 + z^2)
	 * 		---------------
	 * 		sqrt(1^2 + (x/z)^2)
	 * 	this puts the diagonal into an int if no rounding errors
	 * 	that represents the distance in INDEX representation
	 * 	from the start to finish along the diagonal
	 */
	// these values represent a and b in (a^2 + b^2 = c^2) the formula to find the Hypotenuse of a triangle
	// 		they are the x and z above, respectively
	GLfloat change_x = abs(start_x - end_x);
	GLfloat change_z = abs(start_z - end_z);

	return (sqrt(pow(change_x, 2) + pow(change_z, 2))) / (sqrt(pow(1, 2) + pow((change_x / change_z), 2)));
}

// reset all bool values to false
void resetStateVars()
{
	isUnit_controlled 		= false;
	isUnit_targetSelected 	= false;
	isTileSelected 			= false;
	actNow 					= false;
	isActionAHeal 			= false;
}

// the tile pointer is given to this function by the mouse ray selection in "Player Controll.cpp"
// it changes the global values to reflect what has been chosen by the user
void selectionForStates(Tile* selectedTile)
{
	choosenTile_offense = selectedTile->getStats_offence();
	choosenTile_defense = selectedTile->getStats_defence();
//	choosenTile_rangeBonus = selectedTile->getStats_rangeBonus();

	Vector3f* tileCoords_grid = selectedTile->getCoords_grid();
	Vector3f* tileCoords_hex = selectedTile->getCoords_hex();

	if (isUnit_controlled)
	{
		if (CURRENT_STATE == MOVE)
		{
			endTile_grid = tileCoords_grid;
			endTile_hex = tileCoords_hex;

			isTileSelected = true;
			std::cout << "State Machine - tile selected" << std::endl;
		}
		else if (CURRENT_STATE == ACTION)
		{
			// reset values to new endTile
			endTile_grid = tileCoords_grid;
			endTile_hex = tileCoords_hex;

			// search through all units to try and find a match to the tile that was selected by the mouse ray
			// selecting a team unit results in a heal, even if a value of 0
			for (std::vector<Unit>::iterator unit = unitVector_team1.begin(); unit != unitVector_team1.end(); ++unit)
			{
				if (tileCoords_grid->equals(unit->getCoords_grid()) &&
				        unit_controlled->getIsHealer()) // can only heal if you are marked as a healer unit
				{
					// used for state machine
					unit_target = unit->returnThis();
					std::cout << "targeted - heal" << std::endl;
					isUnit_targetSelected = true;
					isActionAHeal = true;
					break;
				}
			}
			if (!isUnit_targetSelected) // Cheap performance increase
			{
				for (std::vector<Unit>::iterator unit = unitVector_team2.begin(); unit != unitVector_team2.end(); ++unit)
				{
					if (tileCoords_grid->equals(unit->getCoords_grid()) &&
					        !unit_controlled->getIsHealer())
					{
						// used for state machine
						unit_target = unit->returnThis();
						std::cout << "targeted" << std::endl;
						isUnit_targetSelected = true;
						break;
					}
					else if (tileCoords_grid->equals(unit->getCoords_grid()) &&
					         unit_controlled->getIsHealer())
					{
						std::cout << "healers cannot attack" << std::endl;
						break;
					}
				}
			}
		}

	}
	else if (!isUnit_controlled)
	{
		// search through all units to try and find a match to the tile that was selected by the mouse ray
		for (std::vector<Unit>::iterator unit = unitVector_team1.begin(); unit != unitVector_team1.end(); ++unit)
		{
			if (tileCoords_grid->equals(unit->getCoords_grid()))
			{
				// used for state machine
				unit_controlled = unit->returnThis();
				std::cout << "State Machine - unit selected" << std::endl;
				isUnit_controlled = true;
				break;
			}
		}
	}
}
