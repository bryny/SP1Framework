#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>


//Objects Declaration
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
Type Objects[10]; //Shannon : Object - Objects[MaxNumber]
COORD ObjectStart; //Shannon : Object Starting Location
int Number = 0; //Shannon : Test
int timer = 20; //Shannon : Timer - Number of frames per object movement
int timerlimit;
int idtype;

void ImplementObjects()
{
	// Shannon : Implement Objects
	for (int i = 0; i < 10; ++i)
	{
	Objects[i].State = UNCREATED;
	}
	//Shannon : Implement Timer
	int timerlimit = timer;
}

void UpdateObjects(COORD charLocation, COORD consoleSize, int& Life)
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
			if (Objects[Number].State == UNCREATED)
			{
				Objects[Number].Location.X = ObjectStart.X;
				Objects[Number].Location.Y = 0;
				Objects[Number].State = CREATED;
				//Shannon : Define Object
				if (idtype <= 5)
				{
					Objects[Number].id = APPLE;
				}
				else
				{
					Objects[Number].id = BOMB;
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
			if (Objects[ii].State == CREATED)
			{
				if (Objects[ii].Location.Y < consoleSize.Y - 1)
				{
					Objects[ii].Location.Y++ ;
				}
			}
		}
	}
	// Shannon : Objects are 'recycled' after touching player or bottom of screen
	for (int ii = 0; ii < 10; ++ii)
	{
		if (Objects[ii].Location.Y == consoleSize.Y - 1)
		{
			Objects[ii].State = UNCREATED;
		}
		if (Objects[ii].State == CREATED && charLocation.X == Objects[ii].Location.X && charLocation.Y == Objects[ii].Location.Y)
		{
			Objects[ii].State = UNCREATED;
			if (Objects[ii].id == APPLE)
			{
				//+points
			}
			if (Objects[ii].id == BOMB)
			{
				--Life;
			}
		}
	}
}

void RenderObjects()
{
	// Shannon : Render objects if created
	for (int i = 0; i < 10; ++i)
	{
		if (Objects[i].State == CREATED)
		{
			gotoXY(Objects[i].Location);
			if (Objects[i].id == APPLE)
			{
				colour(0x0C);
				std::cout << (char)65;
			}
			else if (Objects[i].id == BOMB)
			{
				colour(0x59);
				std::cout << (char)66;
			}
		}
	}
}

unsigned long long score;

void displayscore()
{
	if(score == 1000000000 || score > 1000000000)
	{
		gotoXY(32, 10);
		colour(0x0C);
		std::cout << "Congratulations";
		gotoXY(36, 11);
		colour(0x0C);
		std::cout << "You Won";
	}
	else if (Life.Value != 0)
	{
		gotoXY(70,2);
		colour(0x1A);
		std::cout << "highscore:";
		gotoXY(70,3);
		colour(0x1A);
		std::cout << score;
	}
	else if(Life.Value == 0)
	{
		gotoXY(35, 10);
		colour(0x0C);
		std::cout << "GAME OVER";
		gotoXY(32, 11);
		colour(0x0C);
		std::cout << "Your score is "<< score;
	}

}
