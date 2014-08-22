#ifndef _OBJECTS_H
#define _OBJECTS_H

#include "systems.h"
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>

//Objects Variable Declarations
struct Type //Shannon : Objects' Struct System
{
	COORD Location;
	int State;
	int id;
};
enum ObjectState //Shannon : State of Objects
{
	UNCREATED,
	CREATED,
	RECYCLED
};
enum ObjectType //Shannon : Type of Object
{
	APPLE,
	BOMB
};
enum ObjectDropRate //Shannon : Sets chance at which different objects drop
{
	//Shannon : NOTE - Sum of chance HAS TO EQUAL Randomizer
	RANDOMIZER = 100, //Shannon : Sets the random value for Object Chance as 1 ~ RANDOMIZER (e.g. 1~100)
	APPLECHANCE = 80, //Shannon : Chance of Apple appearing = APPLECHANCE/RANDOMIZER
	BOMBCHANCE = 20 //Shannon : Chance of Bomb appearing = BOMBCHANCE/RANDOMIZER
};
extern Type Object[10]; //Shannon : Type - Object[MaxNumber]
extern COORD ObjectStart; //Shannon : Object Starting Location
extern int timerlimit;
extern int timer;

//Shannon : The Rat
void UpdateRat();

//Object Functions Declaration
void ImplementObjects();
void UpdateObjects();
void RenderObjects();


#endif // _OBJECTS_H