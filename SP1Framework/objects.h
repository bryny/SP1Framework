#ifndef _OBJECTS_H
#define _OBJECTS_H

#include "systems.h"
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>

//Objects Variable Declaration
struct Type //Shannon : Object Struct Draft
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
enum ObjectType //Type of Object
{
	APPLE,
	BOMB
};
extern Type Object[10]; //Shannon : Type - Object[MaxNumber]
extern COORD ObjectStart; //Shannon : Object Starting Location
extern int timerlimit;
extern int timer;
extern int idtype;

//Shannon : The Rat
void UpdateRat();

//Object Functions Declaration
void ImplementObjects();
void UpdateObjects();
void RenderObjects();


#endif // _OBJECTS_H