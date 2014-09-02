#ifndef _HIGHSCORE_H
#define _HIGHSCORE_H

#include "game.h"
#include "systems.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using std :: string; 

struct board
{	
	string name;
	int highScore;
};

void Read(string fileName, board* pHigh);
int Write(string fileName, board* pHigh);
int scoreboard(int playerScore);
//Jenny : render layout
void sblayout();
void enterS();
void renderName();
void nameTab();
void displayScore(board * highScore);
void sortScore(int playerScore);

#endif