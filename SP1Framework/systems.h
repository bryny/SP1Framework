#ifndef _SYSTEMS_H
#define _SYSTEMS_H

#include "Framework\console.h"
#include <iostream>
#include <iomanip>

//Shannon : Life System
struct System //Shannon : System Struct Draft
{
	int Value;
	COORD Location;
};
extern System Life; //Shannon : Life System
void ImplementLife();
void RenderLife();

//Jeffrey : Score System
extern unsigned long long score;
void displayscore();

//Shannon : Level System
extern int LevelCounter;
extern int MiniLevel;
void UpdateLevel();
void RenderLevel();
void RenderBorder();

//Shannon : Level Timer
void UpdateLvTimer();
void RenderLvTimer();

//Yi Yang: Level System
enum Difficulty 
{
	EASY,
	MEDIUM,
	HARD,
	INSANE, //Placeholder in case we want to add more levels
	GODLIKE //Placeholder in case we want to add more levels
};
extern Difficulty levelDifficulty; //Yi Yang : Create a difficulty variable for our game
void updateDifficulty(); //Yi Yang : Update Difficulty


#endif // _SYSTEMS_H