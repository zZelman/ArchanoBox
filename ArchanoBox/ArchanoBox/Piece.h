#ifndef PIECE_H_INCLUDE
#define PIECE_H_INCLUDE

#include <vector>
#include <iostream>

#include "Tile.h"

class Piece
{
	protected:
		GLint teamID; // which team this piece is on

		GLfloat health;
		GLfloat movePoints; // remember, all ranges are INDEXs (ex: 0-14)
		bool isHealer;

		GLfloat default_damage;
		GLfloat default_damageRange;
		GLfloat default_defence;
		GLfloat default_healing;
		GLfloat default_healingRange;

		// flux stats are default stats + tile stats (tile stats can be negitive)
		// they are what the piece does every action with
		GLfloat flux_damage;
		GLfloat flux_damageRange; 	// remember, all ranges are INDEXs (ex: 0-14)
		GLfloat flux_defence;
		GLfloat flux_healing;
		GLfloat flux_healingRange; 	// remember, all ranges are INDEXs (ex: 0-14)

		GLfloat special_range; 		// remember, all ranges are INDEXs (ex: 0-14)
		GLfloat special_healing;
		GLfloat special_damage;
		GLfloat special_move;

		// the position in hex coordinates
		Vector3f* coords_hex;

		// the position in grid coordinates
		// IMPORTANT NOTE: these coords do not map directly onto the Cartesian system,
		// 		instead they represent where on the BOARD the piece is.
		//		Top left is the origin @ (0,0,0) if there is only one tile.
		//		0 in the y represents the base tile.
		//		THESE VALUES CANNOT BE NEGITIVE, AND MUST BE WHOLE NUMBERS
		Vector3f* coords_grid;

		std::vector<Tile*> tileVector;

		GLfloat* color; // what color the piece is drawn

		Tile* tile;

	public:
		// constructors/destructors
		Piece(GLfloat grid_x, GLfloat grid_y, GLfloat grid_z,
		      GLfloat health,
		      GLfloat movementPoints,
		      GLfloat damage, GLfloat damage_range,
		      GLfloat defence,
		      bool isHealer, GLfloat healing, GLfloat healingRange,
		      std::vector<Tile*> tVector,
		      GLint teamID,
		      GLfloat* color);
		Piece();
		virtual ~Piece() = 0; // TODO: add a destructor to each sub-class

		// getters
		GLfloat getHealth();
		GLfloat getMovePoints();
		bool getIsHealer();

		GLfloat getDefault_damage();
		GLfloat getDefault_damageRange();
		GLfloat getDefault_defence();
		GLfloat getDefault_healing();
		GLfloat getDefault_healingRange();

		GLfloat getFlux_damage();
		GLfloat getFlux_damageRange();
		GLfloat getFlux_defence();
		GLfloat getFlux_healing();
		GLfloat getFlux_healingRange();

		GLfloat getSpecial_range();
		GLfloat getSpecial_healing();
		GLfloat getSpecial_damage();
		GLfloat getSpecial_move();

		Vector3f* getCoords_hex();
		Vector3f* getCoords_grid();
		GLfloat getIndex_grid(GLint index);
		GLfloat getIndex_hex(GLint index);

		// setters
		void setHealth(GLfloat newHealth);
		void setMovePoints();

		void setDamage();
		void setDamage_range();

		void setDefence();

		void setHealing();
		void setHealing_range();

		void setSpecial_range();
		void setSpecial_healing();
		void setSpecial_damage();
		void setSpecial_move();

		void setCoords_hex(Vector3f* other);
		void setCoords_grid(Vector3f* other);

		// checking before moving - virtual functions (push functionality onto unit, the subclass)
		virtual bool canMove_Xpos() = 0;
		virtual bool canMove_Xneg() = 0;
		virtual bool canMove_Zpos() = 0;
		virtual bool canMove_Zneg() = 0;

		// movement directions (one hex at a time)
		virtual void move_Xpos() = 0;
		virtual void move_Xneg() = 0;
		virtual void move_Zpos() = 0;
		virtual void move_Zneg() = 0;

		virtual void drawUnit() = 0; // virtual function

		// print out all instance variables
		void printStats();

		void updateStats();

};

#endif
