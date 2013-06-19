#ifndef PRIMITIVE_DRAWING_H_INCLUDE
#define PRIMITIVE_DRAWING_H_INCLUDE

#define PI 3.14159265359

void drawSolidCubeCenter(GLfloat x, GLfloat y, GLfloat z,
                         GLfloat size,
                         GLfloat* color);

void drawSolidCubeBottom(GLfloat x, GLfloat y, GLfloat z,
                         GLfloat size,
                         GLfloat* color);

void drawGrid();

void drawHexagon(GLfloat center_x, GLfloat center_y, GLfloat center_z,
                 GLfloat size, GLfloat height,
                 GLfloat* color);

void drawTestTriangle();

#endif
