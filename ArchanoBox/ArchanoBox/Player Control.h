#ifndef PLAYER_CONTROL_H_INCLUDE
#define PLAYER_CONTROL_H_INCLUDE

void proccess_Keyboard(unsigned char key, int x, int y);

void proccess_SpecialKey(int key, int, int);

void proccess_Mouse(int button, int state, int sX, int sY);

#endif
