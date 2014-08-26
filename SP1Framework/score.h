#ifndef _SCORE_H
#define _SCORE_H

#include "objects.h"
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using std :: string; 

struct scoreboard
{	
	string name;
	int highScore;
};

void scoreboard();

#endif