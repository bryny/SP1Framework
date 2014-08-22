#include "game.h"
#include "objects.h"
#include "systems.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>

Type Object[10]; //Shannon : Type - Object[MaxNumber]
int Number = 0; //Shannon : Test
int timer = 10; //Shannon : Timer - Number of frames before objects are updated (excluding Rat)
int ObjectChance;
int timerlimit;
COORD ObjectStart;

//Shannon : The Rat
Type Rat;
int RatChance;

void ImplementObjects()
{
	// Shannon : Implement Objects
	for (int i = 0; i < 10; ++i)
	{
		Object[i].State = UNCREATED;
	}
	//Shannon : Implement Timer
	int timerlimit = timer;

	// Shannon : Implement Rat
	Rat.State = UNCREATED;
	Rat.Location.Y = charLocation.Y;
	Rat.Location.X = 0;
}

void UpdateObjects()
{
	//Shannon : Timer slowly countsdown
	if (timerlimit != 0)
	{
		--timerlimit;
	}
	//Shannon : When timer reaches 0, objects are updated and timer is reset
	if (timerlimit == 0)
	{
		timerlimit = timer;
		//Shannon : Objects randomly appear based on starting location on top of screen
		if (Number < 10)
		{
			ObjectStart.X = rand() % 50; //Shannon : Sets the X-coordinate of Object
			ObjectChance = rand() % RANDOMIZER + 1; //Shannon : Sets the randomizer for objects
			if (Object[Number].State == UNCREATED)
			{
				Object[Number].Location.X = ObjectStart.X;
				Object[Number].Location.Y = 0;
				Object[Number].State = CREATED;

				//Shannon : Define Objects based on ObjectChance
				if (ObjectChance <= APPLECHANCE)
				{
					Object[Number].id = APPLE;
				}
				else if (ObjectChance <= APPLECHANCE + BOMBCHANCE)
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
			else
			{
				if (Object[ii].State == CREATED)
				{
					Object[ii].Location.Y=Object[ii].Location.Y ;
				}
			}
		}
	}
	
	for (int ii = 0; ii < 10; ++ii)
	{
		// Shannon : Objects are 'recycled' after touching player or bottom of screen
		if (Object[ii].Location.Y == consoleSize.Y - 1)
		{
			//Shannon : Bonus Level also counts objects that reach the bottom
			if (Object[ii].id != BOMB && Object[ii].State == CREATED && MiniLevel == 4)
			{
				LevelCounter += 1;
			}

			//
			Object[ii].State = UNCREATED;
		}
		//Shannon : How objects affect the player when collision happens
		if (Object[ii].State == CREATED && charLocation.X == Object[ii].Location.X && charLocation.Y == Object[ii].Location.Y)
		{
			//Shannon : Object disappears after collision
			Object[ii].State = UNCREATED;

			//Shannon : If the object is not a bomb, LevelCounter increases
			if (Object[ii].id != BOMB)
			{
				LevelCounter += 1;
			}

			//Shannon : Apples increase score +200
			if (Object[ii].id == APPLE)
			{
				score += 200;
			}

			//Shannon : Bombs make the Player lose 1 Life
			if (Object[ii].id == BOMB)
			{
				--Life.Value;
			}
		}
	}
}

void UpdateRat()
{
	//Shannon : If Rat is uncreated, it has a chance to spawn
	RatChance = rand() % 50 + 1;
	if (Rat.State == UNCREATED)
	{
		if (RatChance <= 5)
		{
			Rat.State = CREATED;
		}
	}
	//Shannon : If Rat is created, it will move to the other side of the screen
	if (Rat.State == CREATED && Rat.Location.X != consoleSize.X - 1)
	{
		Rat.Location.X++;
	}
	//Shannon : If the Rat touches the player, lose score and Rat disappears
	if (Rat.State == CREATED && charLocation.X == Rat.Location.X && charLocation.Y == Rat.Location.Y)
	{
		Rat.State = UNCREATED;
		Rat.Location.X = 0;
		if (score > 0)
		{
			score -= 100;
		}
	}
	//Shannon : When it reaches the other side, it disappears
	if (Rat.Location.X == consoleSize.X - 1)
	{
		Rat.State = UNCREATED;
		Rat.Location.X = 0;
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
	// Shannon : Render Rat if created
	if (Rat.State == CREATED)
	{
		gotoXY(Rat.Location);
		colour(0x0C);
		std::cout <<(char)75;
	}
}




