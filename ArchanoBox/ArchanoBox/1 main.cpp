#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <string.h>
#include <vector>
#include <memory>

#include "Camera.h"
#include "Primitive Drawing.h"
#include "Player Control.h"
#include "HUD.h"
#include "Tile_Grassland.h"
#include "Ray.h"
#include "Unit.h"
#include "Calculations.h"
#include "State Machine.h"
#include "Fonts.h"

// colors (initializations are in "Primitive Drawing.cpp")
extern GLfloat red[];
extern GLfloat white[];
extern GLfloat blue[];
extern GLfloat yellow[];
extern GLfloat green[];
//extern GLfloat green_light[];
//extern GLfloat brown[];

Camera* camera;

// window info
static GLfloat fps  	= 60;
GLint window_width  	= 800;
GLint window_height 	= 800;
GLfloat viewPlane_close	= 1;
GLfloat viewPlane_far	= 100;

// hex & marker info (global b/c one computation needed -> performance)
GLfloat hexSize_horizontal 	= 1; 	// distance from center to corner
GLfloat hexSize_vertical	= 1; 	// distance between top and bot hex's
GLfloat cubeSize 			= 0.08;	// markers

GLfloat distEdge 			= hexSize_horizontal * cos(0.523598776); 	// from the center to the side (non vertex) intersecting at 90 degrees
GLfloat offset 				= 1.02; // gap between hex's (1.15 = 15%)
GLfloat zOffset				= (distEdge / hexSize_horizontal); 			// offset for the z axis specifically

GLfloat startCoords_x		= 0; 	// where the first hex apears in grid coords
GLfloat startCoords_y		= 0;
GLfloat startCoords_z		= 0;
GLfloat numHexagonX 		= 20 + startCoords_x; 	// how many hex's will be in each direction (LENGTH)
GLfloat numHexagonZ 		= 25 + startCoords_z;	// added because what if you want to start at (1,y,1)?

// used for debuging the selection rays
typedef std::vector<std::unique_ptr<Ray>> defRayVector;
defRayVector rayVector;

// the units on the board
typedef std::vector<std::unique_ptr<Unit>> defUnitVector;
defUnitVector unitVector_team1;
defUnitVector unitVector_team2;

// container for the tiles
typedef std::vector<std::unique_ptr<Tile>> defTileVector;
defTileVector tileVector;

// this function contains all of the setup required before 3D rendering
void init3D()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(camera->getAngle(), window_width / window_height, .001, 100000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// this is the call that makes it 3D (interchangeable with glFrustum and matrix manipulation)
	gluLookAt(camera->getIndex_position(0), camera->getIndex_position(1), 	camera->getIndex_position(2),
	          camera->getIndex_looking(0),	camera->getIndex_looking(1),	camera->getIndex_looking(2),
	          0, 							-1,  							0);

	// rendering beginning after this function call....
}

// this function contains all the setup required before 2D rendering (HUD)
void init2D()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, window_width, window_height, 0); // this is the thing that makes it 2D

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// rendering begins after this function call....
}

void gameRender()
{
	// set up for 3D rendering
	init3D();
	{
		//drawTestTriangle();
		drawGrid(); // have colors and cords already in function

//		int begHexDraw = glutGet(GLUT_ELAPSED_TIME);
		for (auto itr = tileVector.begin(); itr != tileVector.end(); ++itr)
		{
			(*itr)->drawTile();
			drawSolidCubeBottom((*itr)->getIndex_hex(0), (*itr)->getIndex_hex(1), (*itr)->getIndex_hex(2),
			                    0.15,
			                    white);
		}
//		int endHexDraw = glutGet(GLUT_ELAPSED_TIME);
//		double elapsedHexDraw = (double)(endHexDraw - begHexDraw);
//		std::cout << "hex draw time: " << elapsedHexDraw << " ms" << std::endl;

		// debug ray drawing
		for (auto itr = rayVector.begin(); itr != rayVector.end(); ++itr)
		{
			(*itr)->drawRay();
		}

		//###################
		//##### team 1 ######
		//###################
		for (auto itr = unitVector_team1.begin(); itr != unitVector_team1.end(); ++itr)
		{
			(*itr)->drawUnit();
		}
		//###################
		//##### team 2 ######
		//###################
		for (auto itr = unitVector_team2.begin(); itr != unitVector_team2.end(); ++itr)
		{
			(*itr)->drawUnit();
		}
	}

	// HUD rendering
	init2D();
	{
		drawHUD();
	}

	glFlush();
	glutSwapBuffers();
}

void gameUpdate(int v)
{
	chooseState(); // enters the state machine.cpp and defines what actions can be performed at a given time
	glutPostRedisplay();
	glutTimerFunc(1000 / fps, gameUpdate, v);
}

// keeps animations going when the window is minimized, or not focused
void gameIdle()
{
	glutPostRedisplay();
}

void windowReshape(int w, int h)
{
	window_width  = w;
	window_height = h;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(camera->getAngle(), (float)w / (float)h, viewPlane_close, viewPlane_far);
}

void initialize_camera()
{
	glEnable(GL_DEPTH_TEST);

	// set background color
	glClearColor(0.0, 0.0, 0.0, 1.0);

	/* Sets the camera to be centered at <5,5,5> with a movement of <1,1,1> and looking at <0,0,0>.
	 * Camera angle at -60 degrees for all other views, and a 5 degree change
	 *
	 * With a screen aspect ratio of 4/3 (think monitor proportions).
	 * Clipping set at 1 close, and 40 far (will not see anything beyond/below that)
	 */
	camera = new Camera(17, 22, 43,			// location
	                    17, 21, 42.1727, 	// lookAt
	                    1, 1, 1, 			// Change per button
	                    -60.5699, .01);		// angle & change

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(camera->getAngle(), window_width / window_height, viewPlane_close, viewPlane_far);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera->look_Zneg();
}

void initialize_lighting()
{
	// light characteristics
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };

	// light direction & type
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);
//	glLightfv(GL_LIGHT0, GL_POSITION, );

	// light enabling
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void initialize_board()
{
	for (int z = startCoords_z; z < numHexagonZ; ++z)
	{
		for (int x = startCoords_x; x < numHexagonX; ++x)
		{
			GLint y = startCoords_y;

			// http://stackoverflow.com/questions/17181331/c-how-to-iterate-over-a-vector-defined-as-a-super-class-but-call-sub-class-me#17181427
			tileVector.push_back(std::unique_ptr<Tile_Grassland>(new Tile_Grassland(x, y, z)));

			if (x % 2 != 0)
			{

			}
			else
			{

			}
		}
	}
}

void initialize_units()
{
	GLfloat x = 0;
	GLfloat y = 0;
	GLfloat z = 0;

	//###################
	//##### team 1 ######
	/* ###################
	Unit* ranged_1 = new Unit(0, 0, 0, 		// x, y, z (grid)
							  100,			// health
							  5,			// movePoints
							  20, 4,		// damage, damage_range
							  5,			// Defense
							  false, 0, 0,	// isHealer, healing, healing range
							  tileVector,	// pointer to the tile container
							  1,			// team
							  green);		// color
	ranged_1->updateStats();
	unitVector_team1.push_back(ranged_1);

	Unit* melee_1 = new Unit(1, 0, 0, 		// x, y, z (grid)
							 100,			// health
							 5,				// movePoints
							 25, 1,			// damage, damage_range
							 10,			// Defense
							 false, 0, 0,	// isHealer, healing, healing range
							 tileVector,	// pointer to the tile container
							 1,				// team
							 green);		// color
	melee_1->updateStats();
	unitVector_team1.push_back(melee_1);

	Unit* healer_1 = new Unit(2, 0, 0, 		// x, y, z (grid)
							  100,			// health
							  5,			// movePoints
							  0, 0,			// damage, damage_range
							  5,			// Defense
							  true, 10, 2,	// isHealer, healing, healing range
							  tileVector,	// pointer to the tile container
							  1,			// team
							  green);		// color
	healer_1->updateStats();
	unitVector_team1.push_back(healer_1);

	//###################
	//##### team 2 ######
	//###################
	Unit* ranged_2 = new Unit(0, 0, 1, 		// x, y, z (grid)
							  100,				// health
							  5,				// movePoints
							  20, 4,			// damage, damage_range
							  5,				// Defense
							  false, 0, 0,		// isHealer, healing, healing range
							  tileVector,		// pointer to the tile container
							  1,				// team
							  yellow);			// color
	ranged_2->updateStats();
	unitVector_team2.push_back(ranged_2);

	Unit* melee_2 = new Unit(1, 0, 1, 		// x, y, z (grid)
							 100,			// health
							 5,				// movePoints
							 25, 1,			// damage, damage_range
							 10,			// Defense
							 false, 0, 0,	// isHealer, healing, healing range
							 tileVector,	// pointer to the tile container
							 1,				// team
							 yellow);		// color
	melee_2->updateStats();
	unitVector_team2.push_back(melee_2);

	Unit* healer_2 = new Unit(2, 0, 1, 		// x, y, z (grid)
							  100,			// health
							  5,			// movePoints
							  0, 0,			// damage, damage_range
							  5,			// Defense
							  true, 10, 2,	// isHealer, healing, healing range
							  tileVector,	// pointer to the tile container
							  1,			// team
							  yellow);		// color
	healer_2->updateStats();
	unitVector_team2.push_back(healer_2);
	*/
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// initialize window information
	glutInitWindowSize(window_width, window_height);
	glutInitWindowPosition(325, 100);
	glutCreateWindow("Grid Test");

	// initialize which functions are used
	glutDisplayFunc(gameRender);
	glutReshapeFunc(windowReshape);
	glutTimerFunc(100, gameUpdate, 0);
	glutIdleFunc(gameIdle);
	glutKeyboardFunc(proccess_Keyboard);
	glutSpecialFunc(proccess_SpecialKey);
	glutMouseFunc(proccess_Mouse);

	// other initializations
	initialize_camera();
//	initialize_lighting();
	initialize_board();
//	initialize_units();

	glutMainLoop();
}
