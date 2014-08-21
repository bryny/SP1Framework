#include "game.h"
#include "objects.h"
#include "systems.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>

Type Object[10]; //Shannon : Type - Object[MaxNumber]
int Number = 0; //Shannon : Test
int timer = 20; //Shannon : Timer - Number of frames per object movement
int idtype;
int timerlimit;
COORD ObjectStart;
void ImplementObjects()
{
	// Shannon : Implement Objects
	for (int i = 0; i < 10; ++i)
	{
	Object[i].State = UNCREATED;
	}
	//Shannon : Implement Timer
	int timerlimit = timer;
}

void UpdateObjects()
{
	//Shannon : Timer starts
	if (timerlimit != 0)
	{
		--timerlimit;
	}
	//Only works on timer end
	if (timerlimit == 0)
	{
		timerlimit = timer;
		//Shannon : Objects randomly appear based on starting location
		if (Number < 10)
		{
			ObjectStart.X = rand() % 50;
			idtype = rand() % 10 + 1;
			if (Object[Number].State == UNCREATED)
			{
				Object[Number].Location.X = ObjectStart.X;
				Object[Number].Location.Y = 0;
				Object[Number].State = CREATED;
				//Shannon : Define Object
				if (idtype <= 5)
				{
					Object[Number].id = APPLE;
				}
				else
				{
					Object[Number].id = BOMB;
				}
			}
		}
		++Number;
		if (Number == 10)
		{
			Number = 0;
		}
	//	Shannon : Objects slowly descend to player
		for (int ii = 0; ii < 10; ++ii)
		{
			if (Object[ii].State == CREATED)
			{
				if (Object[ii].Location.Y < consoleSize.Y - 1)
				{
					Object[ii].Location.Y++ ;
				}
			}
		}
	}
	// Shannon : Objects are 'recycled' after touching player or bottom of screen
	for (int ii = 0; ii < 10; ++ii)
	{
		if (Object[ii].Location.Y == consoleSize.Y - 1)
		{
			Object[ii].State = UNCREATED;
		}
		//Shannon : How objects affect the player when collision happens
		if (Object[ii].State == CREATED && charLocation.X == Object[ii].Location.X && charLocation.Y == Object[ii].Location.Y)
		{
			Object[ii].State = UNCREATED;
			if (Object[ii].id == APPLE)
			{
				score += 10;
			}
			if (Object[ii].id == BOMB)
			{
				--Life.Value;
			}
		}
	}
}

void RenderObjects()
{
	// Shannon : Render objects if created
	for (int i = 0; i < 10; ++i)
	{
		if (Object[i].State == CREATED)
		{
			gotoXY(Object[i].Location);
			if (Object[i].id == APPLE)
			{
				colour(0x0C);
				std::cout << (char)65;
			}
			else if (Object[i].id == BOMB)
			{
				colour(0x59);
				std::cout << (char)66;
			}
		}
	}
}




