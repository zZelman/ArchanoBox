#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <string.h>

#include "HUD.h"
#include "Imageloader.h"
#include "Fonts.h"
#include "Unit.h"

// initialization in main.cpp
extern GLint window_width;
extern GLint window_height;

// Initializations in "State machine.cpp"
extern Unit* unit_controlled;
extern Unit* unit_target;
extern Vector3f* endTile_hex;
extern Vector3f* endTile_grid;
extern GLfloat choosenTile_offense;
extern GLfloat choosenTile_defense;
extern GLfloat choosenTile_rangeBonus;
extern bool isUnit_controlled;
extern bool isUnit_targetSelected;
extern bool isTileSelected;
extern bool actNow;
extern bool isActionAHeal;

//extern GLfloat blue[];
extern GLfloat white[];
extern GLfloat grey[];
GLfloat* color = grey;

// infoBar dimensions - percents based on total width or height
GLfloat infoBar_height 	= 0.15;
GLfloat infoBar_width 	= 0.80; // 20% background on either side

// sidebar dimensions - percents based on total width or height
GLfloat sideBar_height 	= 0.80;
GLfloat sideBar_width	= 0.15;

// text dementions
GLfloat textSize 			= 15; 	// vertical offset for each individual text type
GLfloat textGap_vertical 	= 3; 	// space between text lines
GLfloat textGap_horizontal	= 3; 	// the size of the gap between the colums

// TODO: make this file a class for performance -> see 13 BouncingBalls

//void setTilePtr(Tile* tile)
//{
//	choosenTile = tile;
//}

void drawInfoBar()
{
	/* The info bar is for displaying current selected tile and piece information
	 * It is at the very bottom edge of the screen with background on either side
	 */

	Image* image = loadBMP("res/images/vtr.bmp");
	GLuint textureId = loadTexture(image);
	delete image;

	// coords for bar (in 2D)
	GLfloat top_left_x 		= window_width * (1 - infoBar_width);
	GLfloat top_left_y 		= window_height - window_height * infoBar_height;
	GLfloat top_right_x 	= window_width - window_width * (1 - infoBar_width);
	GLfloat top_right_y 	= window_height - window_height * infoBar_height;
	GLfloat bottom_right_x 	= window_width - window_width * (1 - infoBar_width);
	GLfloat bottom_right_y 	= window_height;
	GLfloat bottom_left_x 	= window_width * (1 - infoBar_width);
	GLfloat bottom_left_y 	= window_height;

//	glEnable(GL_TEXTURE_2D);
//	glBindTexture(GL_TEXTURE_2D, textureId);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		{
			glLoadIdentity();
			using namespace std;

			// ############################################################################################
			// UNIT STATS
			string health 		= "Health       : ";
			string movePoints 	= "Move         : ";
			string damage 		= "Damage       : ";
			string damageRange	= "Damage Range : ";
			string defense_unit	= "Defense      : ";
			string healing		= "Healing      : ";
			string healingRange	= "Healing range: ";

			if (isUnit_controlled)
			{
				health.operator += (toString_float(unit_controlled->getHealth()));
				movePoints.operator += (toString_float(unit_controlled->getMovePoints()));
				damage.operator += (toString_float(unit_controlled->getFlux_damage()));
				damageRange.operator += (toString_float(unit_controlled->getFlux_damageRange()));
				defense_unit.operator += (toString_float(unit_controlled->getFlux_defence()));
				if (unit_controlled->getIsHealer())
				{
					healing.operator += (toString_float(unit_controlled->getFlux_healing()));
					healingRange.operator += (toString_float(unit_controlled->getFlux_healingRange()));
				}
			}
			renderText2D(top_left_x + textGap_horizontal, top_left_y + textSize * 1, "Unit Controlled");
			renderText2D(top_left_x + textGap_horizontal, top_left_y + textSize * 2, health);
			renderText2D(top_left_x + textGap_horizontal, top_left_y + textSize * 3, movePoints);
			renderText2D(top_left_x + textGap_horizontal, top_left_y + textSize * 4, damage);
			renderText2D(top_left_x + textGap_horizontal, top_left_y + textSize * 5, damageRange);
			renderText2D(top_left_x + textGap_horizontal, top_left_y + textSize * 6, defense_unit);
			if (isUnit_controlled && unit_controlled->getIsHealer())
			{
				renderText2D(top_left_x + textGap_horizontal, top_left_y + textSize * 7, healing);
				renderText2D(top_left_x + textGap_horizontal, top_left_y + textSize * 8, healingRange);
			}

			// ############################################################################################
			// TILE STATS
			string offense 		= "Offense    : ";
			string defense_tile	= "Defense    : ";
			string rangeBonus 	= "Range Bonus: ";

			if (isTileSelected)
			{
				offense.operator += (toString_float(choosenTile_offense));
				defense_tile.operator += (toString_float(choosenTile_defense));
				// TODO: have tiles have a range bonus
				rangeBonus.operator += (toString_float(0));
			}

			char maxCharsHealth[] = "Health       : 100"; // do not want text to overwrite
			renderText2D(top_left_x + textGap_horizontal + strlen(maxCharsHealth) * (textSize - 5), top_left_y + textSize * 1, "Tile selected");
			renderText2D(top_left_x + textGap_horizontal + strlen(maxCharsHealth) * (textSize - 5), top_left_y + textSize * 2, offense);
			renderText2D(top_left_x + textGap_horizontal + strlen(maxCharsHealth) * (textSize - 5), top_left_y + textSize * 3, defense_tile);
			renderText2D(top_left_x + textGap_horizontal + strlen(maxCharsHealth) * (textSize - 5), top_left_y + textSize * 4, rangeBonus);

			// ############################################################################################
			// BACKGROUND
			glBegin(GL_QUADS);
			{
				glColor3f(color[0], color[1], color[2]);

				// top left - (0,0)
//				glTexCoord2f(0, 0);
				glVertex2f(top_left_x, top_left_y);

				// top right - (1,0)
//				glTexCoord2f(0, 1);
				glVertex2f(top_right_x, top_right_y);

				// bottom right - (1,1)
//				glTexCoord2f(1, 1);
				glVertex2f(bottom_right_x, bottom_right_y);

				// bottom left - (0,1)
//				glTexCoord2f(1, 0);
				glVertex2f(bottom_left_x, bottom_left_y);


			}
			glEnd();

		}
		glPopMatrix();
	}
//	glDisable(GL_TEXTURE_2D);

}

void drawPlayerPiecesSidebar()
{
	Image* image = loadBMP("res/images/vtr.bmp");
	GLuint textureId = loadTexture(image);
	delete image;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureId);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		{
			// BACKGROUND
			glBegin(GL_QUADS);
			{
				glColor3f(color[0], color[1], color[2]);

				// top left - (0,0)
				glTexCoord2f(0, 0);
				glVertex2f(0, (window_height * (1 - sideBar_height)));

				// top right - (1,0)
				glTexCoord2f(0, 1);
				glVertex2f((window_width * sideBar_width), (window_height * (1 - sideBar_height)));

				// bottom right - (1,1)
				glTexCoord2f(1, 1);
				glVertex2f((window_width * sideBar_width), (window_height * sideBar_height));

				// bottom left - (0,1)
				glTexCoord2f(1, 0);
				glVertex2f(0, (window_height * sideBar_height));


			}
			glEnd();
		}
		glPopMatrix();
	}
	glDisable(GL_TEXTURE_2D);
}

void drawOpponentPiecesSidebar()
{
	Image* image = loadBMP("res/images/vtr.bmp");
	GLuint textureId = loadTexture(image);
	delete image;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureId);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		{
			// BACKGROUND
			glBegin(GL_QUADS);
			{
				glColor3f(color[0], color[1], color[2]);

				// top left - (0,0)
				glTexCoord2f(0, 0);
				glVertex2f((window_width - (window_width * sideBar_width)), (window_height * (1 - sideBar_height)));

				// top right - (1,0)
				glTexCoord2f(0, 1);
				glVertex2f(window_width, (window_height * (1 - sideBar_height)));

				// bottom right - (1,1)
				glTexCoord2f(1, 1);
				glVertex2f(window_width, (window_height * sideBar_height));

				// bottom left - (0,1)
				glTexCoord2f(1, 0);
				glVertex2f((window_width - (window_width * sideBar_width)), (window_height * sideBar_height));


			}
			glEnd();
		}
		glPopMatrix();
	}
	glDisable(GL_TEXTURE_2D);
}

void drawHUD()
{
	drawInfoBar();
//	drawPlayerPiecesSidebar();
//	drawOpponentPiecesSidebar();
}
