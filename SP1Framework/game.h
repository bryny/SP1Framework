#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"

extern StopWatch g_timer;
extern bool g_quitGame;

enum Keys
{
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
	K_RETURN,
    K_COUNT
};

enum GSNM
{
	MENU = 0,
	SINGLEPLAYER,
	MULTIPLAYER,
	LEADERBOARD,
	CREDITS,
	EXIT
};

void highscore();
void displayScore();
void credits();
void renderarrow();
void rendermenu();
void menu();

void init();                // initialize your variables, allocate memory, etc
void getInput();            // get input from player
void update(double dt);     // update the game and the state of the game
void render();              // renders the current state of the game to the console
void shutdown();            // do clean up, free memory

extern COORD charLocation;	// The character's coordinates (based as bottom-left)
extern COORD ConsoleSize;	// The console's bottom-rightmost coordinates
extern int delay;
extern int arrowX[6];
extern int arrowY[6];
extern int lockdown;
extern int change;

#endif // _GAME_H