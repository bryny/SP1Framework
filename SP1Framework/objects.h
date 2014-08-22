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
	APPLE, // SCORE = 100, COMMON
	BOMB, 
	CHERRY, // SCORE = 150, COMMON
	BANANA, // SCORE = 250, COMMON
	COCONUT, // SCORE = 500, RARE
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
extern int randomizer, appleChance, bombChance, cherryChance, bananaChance, coconutChance, pearChance, pineappleChance, fallSpeed;


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