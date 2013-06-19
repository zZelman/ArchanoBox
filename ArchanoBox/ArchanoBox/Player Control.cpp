#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>

#include "Player Control.h"
#include "Camera.h"
#include "Ray.h"
#include "Unit.h"
#include "Vector3f.h"
#include "State Machine.h"

// initialization in main.cpp
extern Camera* camera;
extern GLint window_width;
extern GLint window_height;
extern GLfloat viewPlane_close;
extern GLfloat viewPlane_far;
extern std::vector<Ray> rayVector;
extern std::vector<Tile> tileVector;
extern std::vector<Unit> unitVector_team1;
extern std::vector<Unit> unitVector_team2;

// initializations in State Machine.cpp
extern Unit* unit_controlled;	// the unit that will move
extern Unit* unit_target;
extern bool isUnit_controlled;
extern bool isUnit_targetSelected;
extern bool isTileSelected;
extern bool actNow;

void proccess_Keyboard(unsigned char key, int x, int y)
{
//	std::cout << "std-Key Recognized: " << key << std::endl;
//	std::cout << "   modifer: " << glutGetModifiers() << std::endl;

	switch (key)
	{
			// escape key
		case 27:
			exit(0);

		case ' ':
			if ((isUnit_controlled && isTileSelected) ||		// move state
			        (isUnit_controlled && isUnit_targetSelected)) 	// action state
			{
				actNow = true;
			}
			break;

		case 'z':
		case 'Z':
//			tileVector.clear();
//			unitVector_team1.clear();
//			unitVector_team2.clear();
			rayVector.clear();
			break;
		case 'x':
		case 'X':
			if (isUnit_controlled)
			{
				std::cout << "Controlled Unit:" << std::endl;
			}
			if (isUnit_targetSelected)
			{
				std::cout << "Targeted Unit:" << std::endl;
			}

			std::cout << "-------------" << std::endl << std::endl;

			break;

			// camera control - strafing
		case 'a':
		case 'A':
			camera->shift_Xneg();
			break;
		case 'd':
		case 'D':
			camera->shift_Xpos();
			break;
		case 's':
		case 'S':
			camera->shift_Zpos(); // remember that the pos z is facing you
			break;
		case 'w':
		case 'W':
			camera->shift_Zneg();
			break;
		case 'r':
		case 'R':
			camera->shift_Ypos();
			break;
		case 'f':
		case 'F':
			camera->shift_Yneg();
			break;

			// camera control - fixed positions based off of camera->angle
		case 'h':
		case 'H':
			camera->look_Xneg();
			break;
		case 'k':
		case 'K':
			camera->look_Xpos();
			break;
		case 'u':
		case 'U':
			camera->look_Zneg();
			break;
		case 'j':
		case 'J':
			camera->look_Zpos();
			break;

			// TODO: fix vertical look-up and look-down
		case 't':
		case 'T':
			camera->look_up();
			break;
		case 'g':
		case 'G':
			camera->look_down();
			break;
	}
}

void proccess_SpecialKey(int key, int x, int y)
{
//	std::cout << "special-Key Recognized: " << key << ", " << x << ", " << y << std::endl;
	GLint modKey = glutGetModifiers();
	/* Poosible mod keys:
	 * 		GLUT_ACTIVE_SHIFT
	 * 		GLUT_ACTIVE_CTRL
	 * 		GLUT_ACTIVE_ALT
	 */
	// current controls: press ault on-top of everything else to control team 2, not ault is team 1

	switch (key)
	{
		case GLUT_KEY_UP:
			//###################
			//##### team 2 ######
			//###################
			if (modKey == (GLUT_ACTIVE_CTRL + GLUT_ACTIVE_ALT)) // move diagonally LR
			{
				for (std::vector<Unit>::iterator itr = unitVector_team2.begin(); itr != unitVector_team2.end(); ++itr)
				{
					itr->move_Diagonally_LR_up();
				}
			}
			else if (modKey == (GLUT_ACTIVE_SHIFT + GLUT_ACTIVE_ALT)) // move diagonally RL
			{
				for (std::vector<Unit>::iterator itr = unitVector_team2.begin(); itr != unitVector_team2.end(); ++itr)
				{
					itr->move_Diagonally_RL_up();
				}
			}
			else if (modKey == GLUT_ACTIVE_ALT)
			{
				for (std::vector<Unit>::iterator itr = unitVector_team2.begin(); itr != unitVector_team2.end(); ++itr)
				{
					itr->move_Zneg();
				}
			}
			//###################
			//##### team 1 ######
			//###################
			else if (modKey == GLUT_ACTIVE_CTRL) // move diagonally LR
			{
				for (std::vector<Unit>::iterator itr = unitVector_team1.begin(); itr != unitVector_team1.end(); ++itr)
				{
					itr->move_Diagonally_LR_up();
				}
			}
			else if (modKey == GLUT_ACTIVE_SHIFT) // move diagonally RL
			{
				for (std::vector<Unit>::iterator itr = unitVector_team1.begin(); itr != unitVector_team1.end(); ++itr)
				{
					itr->move_Diagonally_RL_up();
				}
			}
			else if (modKey != GLUT_ACTIVE_ALT)
			{
				for (std::vector<Unit>::iterator itr = unitVector_team1.begin(); itr != unitVector_team1.end(); ++itr)
				{
					itr->move_Zneg();
				}
			}
			break;

		case GLUT_KEY_DOWN:
			//###################
			//##### team 2 ######
			//###################
			if (modKey == (GLUT_ACTIVE_CTRL + GLUT_ACTIVE_ALT)) // move diagonally LR
			{
				for (std::vector<Unit>::iterator itr = unitVector_team2.begin(); itr != unitVector_team2.end(); ++itr)
				{
					itr->move_Diagonally_LR_down();
				}
			}
			else if (modKey == (GLUT_ACTIVE_SHIFT + GLUT_ACTIVE_ALT)) // move diagonally RL
			{
				for (std::vector<Unit>::iterator itr = unitVector_team2.begin(); itr != unitVector_team2.end(); ++itr)
				{
					itr->move_Diagonally_RL_down();
				}
			}
			else if (modKey == GLUT_ACTIVE_ALT)
			{
				for (std::vector<Unit>::iterator itr = unitVector_team2.begin(); itr != unitVector_team2.end(); ++itr)
				{
					itr->move_Zpos();
				}
			}
			//###################
			//##### team 1 ######
			//###################
			else if (modKey == GLUT_ACTIVE_CTRL) // move diagonally LR
			{
				for (std::vector<Unit>::iterator itr = unitVector_team1.begin(); itr != unitVector_team1.end(); ++itr)
				{
					itr->move_Diagonally_LR_down();
				}
			}
			else if (modKey == GLUT_ACTIVE_SHIFT) // move diagonally RL
			{
				for (std::vector<Unit>::iterator itr = unitVector_team1.begin(); itr != unitVector_team1.end(); ++itr)
				{
					itr->move_Diagonally_RL_down();
				}
			}
			else if (modKey != GLUT_ACTIVE_ALT)
			{
				for (std::vector<Unit>::iterator itr = unitVector_team1.begin(); itr != unitVector_team1.end(); ++itr)
				{
					itr->move_Zpos();
				}
			}
			break;

		case GLUT_KEY_LEFT:
			//###################
			//##### team 1 ######
			//###################
			if (modKey != GLUT_ACTIVE_ALT)
			{
				for (std::vector<Unit>::iterator itr = unitVector_team1.begin(); itr != unitVector_team1.end(); ++itr)
				{
					itr->move_Xneg();
				}
			}

			//###################
			//##### team 2 ######
			//###################
			if (modKey == GLUT_ACTIVE_ALT)
			{
				for (std::vector<Unit>::iterator itr = unitVector_team2.begin(); itr != unitVector_team2.end(); ++itr)
				{
					itr->move_Xneg();
				}
			}
			break;

		case GLUT_KEY_RIGHT:
			//###################
			//##### team 1 ######
			//###################
			if (modKey != GLUT_ACTIVE_ALT)
			{
				for (std::vector<Unit>::iterator itr = unitVector_team1.begin(); itr != unitVector_team1.end(); ++itr)
				{
					itr->move_Xpos();
				}
			}

			//###################
			//##### team 2 ######
			//###################
			if (modKey == GLUT_ACTIVE_ALT)
			{
				for (std::vector<Unit>::iterator itr = unitVector_team2.begin(); itr != unitVector_team2.end(); ++itr)
				{
					itr->move_Xpos();
				}
			}
			break;

		case GLUT_KEY_END:
			//###################
			//##### team 1 ######
			//###################
			if (modKey != GLUT_ACTIVE_ALT)
			{
				for (std::vector<Unit>::iterator itr = unitVector_team1.begin(); itr != unitVector_team1.end(); ++itr)
				{
					itr->printStats();
				}
			}

			//###################
			//##### team 2 ######
			//###################
			if (modKey == GLUT_ACTIVE_ALT)
			{
				for (std::vector<Unit>::iterator itr = unitVector_team2.begin(); itr != unitVector_team2.end(); ++itr)
				{
					itr->printStats();
				}
			}
			break;

		case GLUT_KEY_HOME:
			camera->printPosAndLook();
			break;

	}
}

void proccess_Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_RIGHT_BUTTON &&
	        state == GLUT_UP)
	{
		resetStateVars();
	}

	if (button == GLUT_LEFT_BUTTON &&
	        state == GLUT_UP)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(camera->getAngle(), window_width / window_height, viewPlane_close, viewPlane_far);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(camera->getIndex_position(0), camera->getIndex_position(1), 	camera->getIndex_position(2),
		          camera->getIndex_looking(0),	camera->getIndex_looking(1),	camera->getIndex_looking(2),
		          0, 							-1,  							0);

		// methodology from: http://www.bfilipek.com/2012/06/select-mouse-opengl.html
		// image reference: http://profs.sci.univr.it/~colombar/html_openGL_tutorial/images/perspective_proj_glfrustum.gif
		//		and http://i.stack.imgur.com/YqV0O.png

		// 1: creating a mouse selection ray
		GLint viewport[4];
		GLdouble modelview[16];		// < ^ v holding respective matrix information
		GLdouble projection[16];

		GLfloat winX, winY;					// clicked coords on the screen
		GLdouble near_x, near_y, near_z; 	// position of the mouse on the near view plane
		GLdouble far_x, far_y, far_z;		// position of the mouse on the far view plane

		glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
		glGetDoublev(GL_PROJECTION_MATRIX, projection);
		glGetIntegerv(GL_VIEWPORT, viewport);

		winX = (float)x;
		winY = (float)viewport[3] - (float)y; // window height - click position

		gluUnProject(winX, winY, 0.0, modelview, projection, viewport, &near_x, &near_y, &near_z);
		gluUnProject(winX, winY, 1.0, modelview, projection, viewport, &far_x, &far_y, &far_z);

		Vector3f* near = new Vector3f(near_x, near_y, near_z);
		Vector3f* far	= new Vector3f(far_x, far_y, far_z);

		// draw a line between the two points for debugging
//		Ray ray(near_x, near_y, near_z,
//		        far_x, far_y, far_z);
//		rayVector.push_back(ray);

		// 2: Collision checking
		// info (for a sphere): find the distance between the ray (3d line)
		//		and the center of the sphere. If that distance is less then the radius of the sphere then we have a hit!
		// NOTE: all real coding is done in Class Tile (Tile.cpp)
		std::vector<Tile> tilesSelected; // used for finding the closest tile that the ray has hit
		for (std::vector<Tile>::iterator itr = tileVector.begin(); itr != tileVector.end(); ++itr)
		{
			bool hit = itr->intersection(*near, *far);
			if (hit == true)
			{
				tilesSelected.push_back(*itr);
			}
		}

//		std::cout << "Player control - tilesSelected.size() = " << tilesSelected.size() << std::endl;

		// 3: Determining which tile was intended to be selected
		// now tilesSelected has all of the tiles the ray has intersected with, just got to find the closest one to the camera
		Tile* choosenTile = NULL;
		if (tilesSelected.size() > 1)
		{
			for (std::vector<Tile>::iterator itr = tilesSelected.begin(); itr != tilesSelected.end(); ++itr)
			{
				// hierarchy: y > dist from camera to tile > everything else
				for (std::vector<Tile>::iterator itr2 = tilesSelected.begin(); itr2 != tilesSelected.end(); ++itr2)
				{
					if (itr->equals(*itr2)) // only checks grid coords for equality!
					{
						continue;
					}

					// checking y values
					// always save the largest y into choosenTile
					if (itr->getIndex_hex(1) > itr2->getIndex_hex(1))
					{
						if (choosenTile == NULL)
						{
							if (itr->getIndex_hex(1) > choosenTile->getIndex_hex(1))
							{
								choosenTile = itr->returnThis();
							}
						}
						else if (choosenTile != NULL)
						{
							if (itr->getIndex_hex(1) > choosenTile->getIndex_hex(1))
							{
								if (itr->getIndex_hex(1) > choosenTile->getIndex_hex(1))
								{
									choosenTile = itr->returnThis();
								}
							}
						}
					}
					else if (itr->getIndex_hex(1) < itr2->getIndex_hex(1))
					{
						if (choosenTile == NULL)
						{
							if (itr2->getIndex_hex(1) > choosenTile->getIndex_hex(1))
							{
								choosenTile = itr2->returnThis();
							}
						}
						else if (choosenTile != NULL)
						{
							if (itr2->getIndex_hex(1) > choosenTile->getIndex_hex(1))
							{
								if (itr2->getIndex_hex(1) > choosenTile->getIndex_hex(1))
								{
									choosenTile = itr2->returnThis();
								}
							}
						}
					}
					else // y values are the same, calculate the distance between the (itr and camera), (itr2 and camera)
					{
						GLfloat distTo_itr 	= itr->getCoords_hex()->distance(camera->getCamera_position());
						GLfloat distTo_itr2	= itr2->getCoords_hex()->distance(camera->getCamera_position());

						if (choosenTile == NULL) // should only go through ever once
						{
							if (distTo_itr < distTo_itr2) // calculate the distance between the itr and camera, itr2 and camera
							{
								choosenTile = itr->returnThis();
							}
							else if (distTo_itr2 < distTo_itr)
							{
								choosenTile = itr2->returnThis();
							}
							else
							{
								std::cout << "Player control - (choosenTile == null) "
								          "ray predicted 2 tiles that are not the same, and have the same distance?";
								choosenTile = itr->returnThis();
							}
						}
						else if (choosenTile != NULL)
						{
							GLfloat distTo_choosenTile = choosenTile->getCoords_hex()->distance(camera->getCamera_position());

							if (distTo_itr < distTo_itr2) // calculate the distance between the itr and camera, itr2 and camera
							{
								if (distTo_itr < distTo_choosenTile)
								{
									choosenTile = itr->returnThis();
								}
							}
							else if (distTo_itr2 < distTo_itr)
							{
								if (distTo_itr2 < distTo_choosenTile)
								{
									choosenTile = itr2->returnThis();
								}
							}
							else
							{
								std::cout << "Player control - (choosenTile != null) "
								          "ray predicted 2 tiles that are not the same, and have the same distance?";
								choosenTile = itr->returnThis();
							}
						}
					}
				}
			}
		}
		else if (tilesSelected.size() == 1)
		{
			choosenTile = tilesSelected.at(0).returnThis();
		}

		/* Now choosenTile should represent the highest chosen y valued tile.
		 * If y values were equal in ray selection, then it represents the closest one to the camera
		 */
		if (choosenTile != NULL)
		{
			std::cout << "Player Control - tile choosen" << std::endl;
			selectionForStates(choosenTile); // in "State Machine.cpp"
		}
		else
		{
			std::cout << "Player Control - tile not choosen" << std::endl;
		}

//		cout << "Mouse - information " << endl;
//		cout << "  button      : [" << button << "], state: [" << state << "]" << endl;
//		cout << "  press       : (" << x << ", " << y << ")" << endl;
//		cout << "  world (near): (" << near_x << ", " << near_y << ", " << near_z << ")" << endl;
//	    cout << "  world (far) : (" << far_x << ", " << far_y << ", " << far_z << ")" << endl << endl;
	}
}
