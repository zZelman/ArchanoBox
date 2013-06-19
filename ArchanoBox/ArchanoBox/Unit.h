#ifndef UNIT_H_INCLUDE
#define UNIT_H_INCLUDE

#include <iostream>
#include <vector>

#include "Piece.h"

class Unit : public Piece
{
	public:
		Unit(GLfloat grid_x, GLfloat grid_y, GLfloat grid_z,
		     GLfloat health,
		     GLfloat movementPoints,
		     GLfloat damage, GLfloat damage_range,
		     GLfloat defence,
		     bool isHealer, GLfloat healing, GLfloat healingRange,
		     std::vector<Tile*> tileVector,
		     GLint teamID,
		     GLfloat* color);

		Unit();
		~Unit();

		bool canMove_Xpos();
		bool canMove_Xneg();
		bool canMove_Zpos();
		bool canMove_Zneg();

		// movement directions (one hex at a time)
		void move_Xpos();
		void move_Xneg();
		void move_Zpos();
		void move_Zneg();
		void move_Diagonally_LR_down(); // top left to bottom right (L->R)
		void move_Diagonally_LR_up();
		void move_Diagonally_RL_down(); // top right to bottom left (R->L)
		void move_Diagonally_RL_up();

		void drawUnit();
		Unit* returnThis();

};

#endif
