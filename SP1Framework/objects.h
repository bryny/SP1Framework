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
//enum ObjectDropRate //Shannon : Sets chance at which different objects drop
//{
//	//Shannon : NOTE - Sum of chance HAS TO EQUAL Randomizer
//	RANDOMIZER = 100, //Shannon : Sets the random value for Object Chance as 1 ~ RANDOMIZER (e.g. 1~100)
//	APPLECHANCE = 80, //Shannon : Chance of Apple appearing = APPLECHANCE/RANDOMIZER
//	BOMBCHANCE = 20 //Shannon : Chance of Bomb appearing = BOMBCHANCE/RANDOMIZER
//};

//Yi Yang: These values should not be Enum constant.
//		   The appleChance value will decrease and the
//		   bombChance value will increase as the level
//		   increases, so I changed them to int instead.
//         (otherwise a constant value cannot be modified)
extern int randomizer, appleChance, bombChance, cherryChance, bananaChance, orangeChance, pearChance, pineappleChance, fallSpeed;

const int NumberLimit = 10; // Shannon : Max number of objects to be falling
const int TotalLimit = 20; //Shannon : NumberLimit + Minimum Requirement
extern Type Object[TotalLimit]; //Shannon : Type - Object[MaxNumber]
extern COORD ObjectStart; //Shannon : Object Starting Location
extern int timerlimit;
extern int timer;

//Shannon : The Rat
void UpdateRat();
extern Type Rat;

//Object Functions Declaration
void ImplementObjects();
void UpdateObjects();
void RenderObjects();


#endif // _OBJECTS_H