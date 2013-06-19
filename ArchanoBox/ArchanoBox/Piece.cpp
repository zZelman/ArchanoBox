#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <vector>

#include "Piece.h"
#include "Tile.h"
#include "Calculations.h"

extern GLfloat distEdge;

Piece::Piece(GLfloat grid_x, GLfloat grid_y, GLfloat grid_z,
             GLfloat health,
             GLfloat movementPoints,
             GLfloat damage, GLfloat damage_range,
             GLfloat defence,
             bool isHealer, GLfloat healing, GLfloat healingRange,
             std::vector<Tile*> tVector,
             GLint teamID,
             GLfloat* color)
{
	coords_grid = new Vector3f(grid_x, grid_y, grid_z);

	GLfloat temp_x = grid_x;
	GLfloat temp_y = grid_y;
	GLfloat temp_z = grid_z;

	translate_GridToHex_XYZ(temp_x, temp_y, temp_z);

	if (((int) grid_z) % 2 == 0)  // even row
	{
		temp_x += distEdge;
	}

	coords_hex = new Vector3f(temp_x, temp_y, temp_z);

	this->health = health;
	this->movePoints = movementPoints;

	this->default_damage = damage;
	this->default_damageRange = damage_range;

	this->default_defence = defence;
	this->default_healing = healing;
	this->isHealer = isHealer;
	this->default_healingRange = healingRange;

	tileVector = tVector;

	this->teamID = teamID;

	this->color = color;

//	std::cout<< "Piece: created" << std::endl;
}

Piece::Piece()
{
	std::cout << "Piece: default constructor used, program exiting" << std::endl;
	exit(0);
}

Piece::~Piece()
{
//	std::cout << "Piece: destroyed" << std::endl;
}

// end constructor/destructors -------------------------------------------------------------------

GLfloat Piece::getHealth()
{
	return health;
}

// remember, all ranges are INDEXs (ex: 0-14)
GLfloat Piece::getMovePoints()
{
	return movePoints;
}

// you can only heal if you are marked as a healing unit
bool Piece::getIsHealer()
{
	return isHealer;
}

GLfloat Piece::getDefault_damage()
{
	return default_damage;
}

// remember, all ranges are INDEXs (ex: 0-14)
GLfloat Piece::getDefault_damageRange()
{
	return default_damageRange;
}

GLfloat Piece::getDefault_defence()
{
	return default_defence;
}

GLfloat Piece::getDefault_healing()
{
	return default_healing;
}

// remember, all ranges are INDEXs (ex: 0-14)
GLfloat Piece::getDefault_healingRange()
{
	return default_healingRange;
}

GLfloat Piece::getFlux_damage()
{
	return flux_damage;
}

// remember, all ranges are INDEXs (ex: 0-14)
GLfloat Piece::getFlux_damageRange()
{
	return flux_damageRange;
}

GLfloat Piece::getFlux_defence()
{
	return flux_defence;
}

GLfloat Piece::getFlux_healing()
{
	return flux_healing;
}

// remember, all ranges are INDEXs (ex: 0-14)
GLfloat Piece::getFlux_healingRange()
{
	return flux_healingRange;
}

GLfloat Piece::getSpecial_range()
{
	return special_range;
}

GLfloat Piece::getSpecial_healing()
{
	return special_healing;
}

GLfloat Piece::getSpecial_damage()
{
	return special_damage;
}

GLfloat Piece::getSpecial_move()
{
	return special_move;
}

Vector3f* Piece::getCoords_hex()
{
	return this->coords_hex;
}

Vector3f* Piece::getCoords_grid()
{
	return this->coords_grid;
}

GLfloat Piece::getIndex_grid(GLint index)
{
	return this->coords_grid->operator [](index);
}

GLfloat Piece::getIndex_hex(GLint index)
{
	return this->coords_hex->operator [](index);
}

// end getters ------------------------------------------------------------------------------------

void Piece::setHealth(GLfloat newHealth)
{
	if (newHealth < 0)
	{
		health = 0;
	}
	else
	{
		health = newHealth;
	}
}

void Piece::setMovePoints()
{

}


void Piece::setDamage()
{

}

// remember, all ranges are INDEXs (ex: 0-14)
void Piece::setDamage_range()
{

}

void Piece::setDefence()
{

}

void Piece::setHealing()
{

}

// remember, all ranges are INDEXs (ex: 0-14)
void Piece::setHealing_range()
{

}


void Piece::setSpecial_range()
{

}

void Piece::setSpecial_healing()
{

}

void Piece::setSpecial_damage()
{

}

void Piece::setSpecial_move()
{

}

void Piece::setCoords_hex(Vector3f* other)
{
	this->coords_hex->setValue(0, other->operator [](0));
	this->coords_hex->setValue(1, other->operator [](1));
	this->coords_hex->setValue(2, other->operator [](2));
}

void Piece::setCoords_grid(Vector3f* other)
{
	this->coords_grid->setValue(0, other->operator [](0));
	this->coords_grid->setValue(1, other->operator [](1));
	this->coords_grid->setValue(2, other->operator [](2));
}

// end setters ------------------------------------------------------------------------------------

void Piece::printStats()
{
	using namespace std;
	cout << "Piece - Printing stats:" << endl;
	cout << "   team         : " << teamID << endl;
	cout << "   location_grid: (" << coords_grid->operator [](0) << ", " << coords_grid->operator [](1) << ", " << coords_grid->operator [](2) << ")" << endl;
	cout << "   location_hex : (" << coords_hex->operator [](0) << ", " << coords_hex->operator [](1) << ", " << coords_hex->operator [](2) << ")" << endl;
	cout << "   move points  : " << movePoints << endl;
	cout << "   health       : " << health << endl;
	cout << "   (flux) damage: " << flux_damage << ", Range: " << flux_damageRange << endl;
	cout << "   damage       : " << default_damage << ", Range: " << default_damageRange << endl;
	cout << "   defense      : " << flux_defence << endl << endl;
}

void Piece::updateStats()
{
	// reset stats
	this->flux_damage 		= this->default_damage;
	this->flux_damageRange 	= this->default_damageRange;
	this->flux_defence 		= this->default_defence;
	this->flux_healing 		= this->default_healing;
	this->flux_healingRange = this->default_healingRange;

	// check for tiles
	for (std::vector<Tile*>::iterator itr = tileVector.begin(); itr != tileVector.end(); ++itr)
	{
		// if true, the unit is on this specific tile
		if ((*itr)->getCoords_grid()->equals(this->coords_grid))
		{
			this->flux_damage 		= this->default_damage + (*itr)->getStats_offence();
//			this->flux_damageRange 	=
			this->flux_defence 		= this->default_defence + (*itr)->getStats_defence();
//			this->flux_healing 		=
//			this->flux_healingRange =

			break; // already found what you are looking for, why keep looking?
		}
	}
}
