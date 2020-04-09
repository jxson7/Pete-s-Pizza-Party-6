/* Author: Jason Jay Dookarun
With the inspiration of parrallel realities concept of a homescreen, the following file consists of a homepage creation that will be 
displayed to the user upon running the program. 
*/

#include "common.h"

static void logic(void);
static void draw(void);
static void messageboxC(void);
static void messageboxYesNo(void);

static void messageboxH(void);
static SDL_Texture* sdl2Texture;
static SDL_Texture* logo;
static SDL_Texture* space;
static int reveal = 0;
static int timeout;
static int backgroundX;
static SDL_Texture* background;
static int backgroundX = 0;


static void logic(void)
{
	if (--backgroundX < -SCREEN_WIDTH){
		backgroundX = 0;
	}

	if (reveal < SCREEN_HEIGHT){
		reveal++;
	}

	if (app.keyboard[SDL_SCANCODE_SPACE]){
		initStage();
	}
	if (app.keyboard[SDL_SCANCODE_H]) {
		messageboxH();
	}
	if (app.keyboard[SDL_SCANCODE_C]) {
		messageboxC();

	}
	if (app.keyboard[SDL_SCANCODE_Q]) {
		messageboxYesNo();
	}

}


static void draw(void)
{
	SDL_Rect screen;
	int x;

	for (x = backgroundX; x < SCREEN_WIDTH; x += SCREEN_WIDTH){
		screen.x = x;
		screen.y = 0;
		screen.w = SCREEN_WIDTH;
		screen.h = SCREEN_HEIGHT;
		SDL_RenderCopy(app.renderer, background, NULL, &screen);
	}
	SDL_Rect r;
	r.x = 0;
	r.y = 0;

	SDL_QueryTexture(logo, NULL, NULL, &r.w, &r.h);
	r.h = MIN(reveal, r.h);
	loadText(logo, &r, (SCREEN_WIDTH / 2) - (r.w / 2), 250);
	drawText(SCREEN_WIDTH / 2, 450, 255, 255, 255, TEXT_CENTER, "PRESS SPACE TO PLAY!");
	drawText(SCREEN_WIDTH / 2, 500, 255, 255, 255, TEXT_CENTER, "PRESS C FOR CONTROLS");
	drawText(SCREEN_WIDTH / 2, 550, 255, 255, 255, TEXT_CENTER, "PRESS H FOR CONTROLS AND HELP");
}

void initTitle(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;
	background = loadTexture("gfx/backgroundNew.png");
	logo = loadTexture("gfx/logo.png");
}

void messageboxH(void) {
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Welcome!" ,"Hi and welcome To Pete's Pizza Hunt! We have lost 11 slices of pizza and your mission is to find them! To check your progress, look at the HUD on top right-hand side. Good luck!", NULL);
}

void messageboxC(void) {
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Controls", " Left: LEFT Key or A, Right : RIGHT Key, Jump: SPACE or W, Reset: R, Quit: Q.", NULL);

}

void messageboxYesNo(void) {
	// referenced from https://wiki.libsdl.org/SDL_ShowMessageBox#Version

	const SDL_MessageBoxButtonData buttons[] = {
	{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "No" },
	{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Yes" },
	};

	const SDL_MessageBoxData messageboxdata = {
		SDL_MESSAGEBOX_INFORMATION,NULL,"Exit Game","Do you wish to exit the game?",SDL_arraysize(buttons),buttons };
	int buttonid;
	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
		SDL_Log("error displaying message box");
		return 1;
	}
	if (buttonid == 1) {
		exit(0);
	}
	else {
		return;

	}
}
