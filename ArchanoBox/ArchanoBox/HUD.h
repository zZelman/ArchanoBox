#ifndef HUD_H_INCLUDE
#define HUD_H_INCLUDE

class HUD
{
	private:
		GLfloat infoBar_height;
		GLfloat infoBar_width;
		GLint infoBar_ID;

		GLfloat playerSidebar_height;
		GLfloat playerSidebar_width;
		GLint playerSideBar_ID;

		GLfloat opponentSidebar_height;
		GLfloat opponentSidebar_width;
		GLint opponentSidebar_ID;

	public:
		HUD();
		~HUD();

		// creates/draws all of the different bars
		void HUD_create();
		void HUD_draw();

		// bottom bar
		void infoBar_create();
		void infoBar_draw();

		// left bar
		void playerSidebar_create();
		void playerSidebar_draw();

		// right bar
		void opponentSidebar_create();
		void opponentSidebar_draw();

};

void drawInfoBar();

void drawPlayerPiecesSidebar();

void drawOpponentPiecesSidebar();

void drawHUD();

#endif
