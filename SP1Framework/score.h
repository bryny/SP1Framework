#ifndef _SCORE_H
#define _SCORE_H

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

int Read(string fileName, highscore* pHS);
int Write(string fileName, highscore* pHS);
void scoreboard();
int playerScore;
string enteredName;
#endif