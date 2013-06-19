#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <vector>

#include "Piece.h"
#include "Unit.h"
#include "Tile.h"
#include "Primitive Drawing.h"
#include "Calculations.h"

// initialization in main.cpp
extern GLfloat distEdge;
extern GLfloat offset;
extern GLfloat zOffset;
extern GLfloat numHexagonX;
extern GLfloat numHexagonZ;
extern GLfloat startCoords_x;
extern GLfloat startCoords_z;

Unit::Unit(GLfloat grid_x, GLfloat grid_y, GLfloat grid_z,
           GLfloat health,
           GLfloat movementPoints,
           GLfloat damage, GLfloat damage_range,
           GLfloat defence,
           bool isHealer, GLfloat healing, GLfloat healingRange,
           std::vector<Tile*> tVector,
           GLint teamID,
           GLfloat* color)
	: Piece::Piece(grid_x, grid_y, grid_z,
	               health,
	               movementPoints,
	               damage, damage_range,
	               defence,
	               isHealer, healing, healingRange,
	               tVector,
	               teamID,
	               color)
{
	// calls the super constructor and sets the instance variables that way

//	std::cout << "Unit: created" << std::endl;
}

Unit::Unit()
{
	std::cout << "Unit: default constructor used, program will now exit" << std::endl;
	exit(0);
}

Unit::~Unit()
{
//	std::cout << "Unit: 'deleted tile pointer' (not really)" << std::endl;
}

// end constructors/destructors -------------------------------------------------------------------

// checking before moving - functions (push functionality onto unit, the subclass)
bool Unit::canMove_Xpos()
{
	if (this->getIndex_grid(0) + 1 < numHexagonX)
	{
		return true;
	}
	return false;
}

bool Unit::canMove_Xneg()
{
	if (this->getIndex_grid(0) - 1 >= startCoords_x)
	{
		return true;
	}
	return false;
}

bool Unit::canMove_Zpos()
{
	if (this->getIndex_grid(2) + 1 < numHexagonZ)
	{
		return true;
	}
	return false;
}

bool Unit::canMove_Zneg()
{
	if (this->getIndex_grid(2) - 1 >= startCoords_z)
	{
		return true;
	}
	return false;
}

// end canMove checking ---------------------------------------------------------------------------

/* NOTES FOR MOVING:
 * 		> moves one hex at a time
 * 		> 2* because distEdge only measures one for one hex
 * 		> Moving up and down (+z & -z) so far only stay in the same x cords
 * 		> TODO: allow for diagonal movement
 */

// movement directions (one hex at a time)
// 2* becaue distEdge only mesures for one hex
void Unit::move_Xpos()
{
	if (canMove_Xpos())
	{
		this->coords_hex->setValue(0, this->coords_hex->operator [](0) + 2 * distEdge * offset);
		this->coords_grid->setValue(0, this->coords_grid->operator [](0) + 1);

		updateStats();
	}
	else
	{

	}
}

void Unit::move_Xneg()
{
	if (canMove_Xneg())
	{
		this->coords_hex->setValue(0, this->coords_hex->operator [](0) - 2 * distEdge * offset);

		this->coords_grid->setValue(0, this->coords_grid->operator [](0) - 1);

		updateStats();
	}
	else
	{

	}
}

void Unit::move_Zpos()
{
	if (canMove_Zpos())
	{
		// staying on the same x coord, just moving in the z direction
		// thats why its -= on even and += on odd (oscillating)
		if (((int) this->coords_grid->operator [](2)) % 2 == 0)  // even row
		{
			this->coords_hex->setValue(0, this->coords_hex->operator [](0) - distEdge * offset);
		}
		else // odd row
		{
			this->coords_hex->setValue(0, this->coords_hex->operator [](0) + distEdge * offset);
		}

		this->coords_hex->setValue(2, this->coords_hex->operator [](2) + 2 * distEdge * zOffset * offset);
		this->coords_grid->setValue(2, this->coords_grid->operator [](2) + 1);

		updateStats();
	}
	else
	{

	}
}

void Unit::move_Zneg()
{
	if (canMove_Zneg())
	{
		// staying on the same x coord, just moving in the z direction
		// thats why its -= on even and += on odd (oscillating)
		if (((int) this->coords_grid->operator [](2)) % 2 == 0)  // even row
		{
			this->coords_hex->setValue(0, this->coords_hex->operator [](0) - distEdge * offset);
		}
		else // odd row
		{
			this->coords_hex->setValue(0, this->coords_hex->operator [](0) + distEdge * offset);
		}

		this->coords_hex->setValue(2, this->coords_hex->operator [](2) - 2 * distEdge * zOffset * offset);
		this->coords_grid->setValue(2, this->coords_grid->operator [](2) - 1);

		updateStats();
	}
	else
	{

	}
}

// moves on diagonal top left to bottom right
void Unit::move_Diagonally_LR_down()
{
	if (canMove_Zpos())
	{
		if (((int) this->coords_grid->operator [](2)) % 2 == 0)  // even row
		{
			this->coords_hex->setValue(0, this->coords_hex->operator [](0) + distEdge * offset);
			this->coords_grid->setValue(0, this->coords_grid->operator [](0) + 1);
		}
		else // odd row
		{
			this->coords_hex->setValue(0, this->coords_hex->operator [](0) + distEdge * offset);
		}

		this->coords_hex->setValue(2, this->coords_hex->operator [](2) + 2 * distEdge * zOffset * offset);
		this->coords_grid->setValue(2, this->coords_grid->operator [](2) + 1);

		updateStats();
	}
	else
	{

	}
}

// moves on diagonal top left to bottom right
void Unit::move_Diagonally_LR_up()
{
	if (canMove_Zneg())
	{
		if (((int) this->coords_grid->operator [](2)) % 2 == 0)  // even row
		{
			this->coords_hex->setValue(0, this->coords_hex->operator [](0) - distEdge * offset);
			this->coords_grid->setValue(0, this->coords_grid->operator [](0) - 1);
		}
		else // odd row
		{
			this->coords_hex->setValue(0, this->coords_hex->operator [](0) - distEdge * offset);
		}

		this->coords_hex->setValue(2, this->coords_hex->operator [](2) - 2 * distEdge * zOffset * offset);
		this->coords_grid->setValue(2, this->coords_grid->operator [](2) - 1);

		updateStats();
	}
	else
	{

	}
}

// moves on diagonal top right to bottom left
void Unit::move_Diagonally_RL_down()
{
	if (canMove_Zpos())
	{
		if (((int) this->coords_grid->operator [](2)) % 2 == 0)  // even row
		{
			this->coords_hex->setValue(0, this->coords_hex->operator [](0) - distEdge * offset);

			this->coords_hex->setValue(2, this->coords_hex->operator [](2) + 2 * distEdge * zOffset * offset);
			this->coords_grid->setValue(2, this->coords_grid->operator [](2) + 1);
		}
		else // odd row
		{
			if (canMove_Xneg())
			{
				this->coords_hex->setValue(0, this->coords_hex->operator [](0) - distEdge * offset);
				this->coords_grid->setValue(0, this->coords_grid->operator [](0) - 1);

				this->coords_hex->setValue(2, this->coords_hex->operator [](2) + 2 * distEdge * zOffset * offset);
				this->coords_grid->setValue(2, this->coords_grid->operator [](2) + 1);
			}
		}

		updateStats();
	}
	else
	{

	}
}

// moves on diagonal top right to bottom left
void Unit::move_Diagonally_RL_up()
{
	if (canMove_Zneg())
	{
		if (((int) this->coords_grid->operator [](2)) % 2 == 0)  // even row
		{
			if (canMove_Xpos())
			{
				this->coords_hex->setValue(0, this->coords_hex->operator [](0) + distEdge * offset);
				this->coords_grid->setValue(0, this->coords_grid->operator [](0) + 1);

				this->coords_hex->setValue(2, this->coords_hex->operator [](2) - 2 * distEdge * zOffset * offset);
				this->coords_grid->setValue(2, this->coords_grid->operator [](2) - 1);
			}
		}
		else // odd row
		{
			this->coords_hex->setValue(0, this->coords_hex->operator [](0) + distEdge * offset);

			this->coords_hex->setValue(2, this->coords_hex->operator [](2) - 2 * distEdge * zOffset * offset);
			this->coords_grid->setValue(2, this->coords_grid->operator [](2) - 1);
		}

		updateStats();
	}
	else
	{

	}
}

// end moving ------------------------------------------------------------------------------------

void Unit::drawUnit()
{
	drawSolidCubeBottom(coords_hex->operator [](0), coords_hex->operator [](1), coords_hex->operator [](2),
	                    0.95,
	                    color);
}

Unit* Unit::returnThis()
{
	return this;
}
