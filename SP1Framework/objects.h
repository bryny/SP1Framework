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
	COORD Location; //Starting location to base render around
	COORD EndLocation; //Bottom right of the Object
	int RenderTime; //Timer to render each row of the object
	int State; //State whether the Object is in play or not
	int id; //Identify what type of Object it is
};
enum ObjectState //Shannon : State of Objects
{
	UNCREATED,
	CREATED
};
enum ObjectType //Shannon : Type of Object
{
	APPLE, // SCORE = 100, COMMON
	BOMB, 
	CHERRY, // SCORE = 150, COMMON
	BANANA, // SCORE = 250, COMMON
	ORANGE, // SCORE = 500, RARE
	PEAR, // SCORE = 750, RARE
	PINEAPPLE //SCORE = 1000, VERY RARE
};

extern int randomizer, appleChance, bombChance, cherryChance, bananaChance, orangeChance, pearChance, pineappleChance, fallSpeed;

const int NumberLimit = 10; // Shannon : Maximum number of objects on screen at any time
extern Type Object[NumberLimit]; //Shannon : Type - Object[MaxNumber]
extern COORD ObjectStart; //Shannon : Object Starting Location
extern int timerlimit;
extern int timer;

//Shannon : Rat Variables & Functions
void UpdateRat();
extern Type Rat;

//Object Functions Declaration
void ImplementObjects();
void CreateObjects();
void UpdateObjects();
void RenderObjects();


#endif // _OBJECTS_H