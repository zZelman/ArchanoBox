#ifndef CALCULATIONS_H_INCLUDE
#define CALCULATIONS_H_INCLUDE

void translate_HexToGrid_XYZ(GLfloat& x, GLfloat& y, GLfloat& z);
void translate_HexToGrid_X(GLfloat& x);
void translate_HexToGrid_Y(GLfloat& y);
void translate_HexToGrid_Z(GLfloat& z);

void translate_GridToHex_XYZ(GLfloat& x, GLfloat& y, GLfloat& z);
void translate_GridToHex_X(GLfloat& x);
void translate_GridToHex_Y(GLfloat& y);
void translate_GridToHex_Z(GLfloat& z);

#endif
