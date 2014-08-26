#include "game.h"
#include "objects.h"
#include "systems.h"
#include "Framework\console.h"
#include "render.h"
#include <iostream>
#include <iomanip>



Type Object[TotalLimit]; //Shannon : Type - Object[MaxNumber + Minimum requirement]
int Number = 0; //Shannon : Test
int Number2 = NumberLimit;
int timer = 10; //Shannon : Timer - Number of frames before objects are updated (excluding Rat)
int ObjectChance;
int timerlimit;
COORD ObjectStart;


int xyz;

//Shannon : The Rat
Type Rat;
int RatChance;

void ImplementObjects()
{
	// Shannon : Implement Objects
	for (int i = 0; i < 20; ++i)
	{
		Object[i].State = UNCREATED;
	}
	//Shannon : Implement Timer
	int timerlimit = timer;

	// Shannon : Implement Rat
	Rat.State = UNCREATED;
	Rat.Location.Y = charLocation.Y;
	Rat.Location.X = 0;

	xyz = 0;
}

//Yi Yang: These values should not be Enum constant.
//		   The appleChance value will decrease and the
//		   bombChance value will increase as the level
//		   increases, so I changed them to int instead.
//         (otherwise a constant value cannot be modified)
int randomizer, appleChance, bombChance, cherryChance, bananaChance, orangeChance, pearChance, pineappleChance, fallSpeed;

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
		if (Number < NumberLimit)
		{
			ObjectStart.X = rand() % 50; //Shannon : Sets the X-coordinate of Object
			ObjectChance = rand() % randomizer + 1; //Shannon : Sets the randomizer for objects

			if (Object[Number].State == UNCREATED && xyz <= 0)
			{
				xyz = 5;
				//Shannon : Collision Detection , Prevent objects from spawning in collision range of previous objects
				while (ObjectStart.X < Object[Number-1].RightSide[0].X && ObjectStart.X > Object[Number-1].Location.X - 7)
				{
					ObjectStart.X = rand() % 50; //Shannon : Re-Randomize if colliding
				}

				Object[Number].Location.X = ObjectStart.X;
				Object[Number].Location.Y = 0;
				Object[Number].State = CREATED;
				Object[Number].RenderTime = 0; //Shannon : Initialized to height of object

				for (int i = 0; i < 7; ++i)
				{
					//Shannon : Set collision detection field
					Object[Number].LeftSide[i].Y = Object[Number].Location.Y - i;
					Object[Number].RightSide[i].Y = Object[Number].Location.Y - i;
					Object[Number].LeftSide[i].X = Object[Number].Location.X;
				}

				//Shannon : Define Objects based on ObjectChance
				if (ObjectChance <= appleChance)
				{
					Object[Number].id = APPLE;
					for (int i = 0; i < 7; ++i)
					{
						Object[Number].RightSide[i].X = Object[Number].Location.X + 4;
					}
				}
				else if (ObjectChance <= appleChance + bombChance)
				{
					Object[Number].id = BOMB;
					for (int i = 0; i < 7; ++i)
					{
						Object[Number].RightSide[i].X = Object[Number].Location.X + 4;
					}
				}
				else if (ObjectChance < appleChance + bombChance + cherryChance)
				{
					Object[Number].id = CHERRY;
					for (int i = 0; i < 7; ++i)
					{
						Object[Number].RightSide[i].X = Object[Number].Location.X + 6;
					}
				}
				else if (ObjectChance < appleChance + bombChance + cherryChance + bananaChance)
				{
					Object[Number].id = BANANA;
					for (int i = 0; i < 7; ++i)
					{
						Object[Number].RightSide[i].X = Object[Number].Location.X + 5;
					}
				}
				else if (ObjectChance < appleChance + bombChance + cherryChance + bananaChance + orangeChance)
				{
					Object[Number].id = ORANGE;
					for (int i = 0; i < 7; ++i)
					{
						Object[Number].RightSide[i].X = Object[Number].Location.X + 4;
					}
				}
				else if (ObjectChance < appleChance + bombChance + cherryChance + bananaChance + orangeChance + pearChance)
				{
					Object[Number].id = PEAR;
					for (int i = 0; i < 7; ++i)
					{
						Object[Number].RightSide[i].X = Object[Number].Location.X + 4;
					}
				}
				else if (ObjectChance < appleChance + bombChance + cherryChance + bananaChance + orangeChance + pearChance + pineappleChance)
				{
					Object[Number].id = PINEAPPLE;
					for (int i = 0; i < 7; ++i)
					{
						Object[Number].RightSide[i].X = Object[Number].Location.X + 4;
					}
				}
				++Number;
			} //Shannon : End of Object Creation
			--xyz;
		} //Shannon : End of Object Creation Number Reset

		

		
		if (Number == NumberLimit)
		{
			Number = 0;
		}

		//	Shannon : Objects slowly descend to player
		for (int ii = 0; ii < TotalLimit; ++ii)
		{
			if (Object[ii].State == CREATED)
			{
				if (Object[ii].Location.Y < consoleSize.Y - 1)
				{
					Object[ii].Location.Y += fallSpeed;
					for (int i = 0; i < 7; ++i)
					{
						Object[ii].LeftSide[i].Y += fallSpeed;
						Object[ii].RightSide[i].Y += fallSpeed;
					}
					++Object[ii].RenderTime;
				}
			}
		}
	} //Shannon : End of timer
	
	for (int ii = 0; ii < TotalLimit; ++ii)
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
				score += 100;
			}

			//Shannon : Bombs make the Player lose 1 Life
			if (Object[ii].id == BOMB)
			{
				--Life.Value;
			}

			if (Object[ii].id == CHERRY)
			{
				score += 150;
			}
			if (Object[ii].id == BANANA)
			{
				score += 250;
			}
			if (Object[ii].id == ORANGE)
			{
				score += 500;
			}
			if (Object[ii].id == PEAR)
			{
				score += 750;
			}
			if (Object[ii].id == PINEAPPLE)
			{
				score += 1000;
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
	for (int i = 0; i < TotalLimit; ++i)
	{
		if (Object[i].State == CREATED)
		{
			gotoXY(Object[i].Location);
			if (Object[i].id == APPLE)
			{
				Render_Apple(i);
			}
			else if (Object[i].id == BOMB)
			{
				Render_Bomb(i);
			}
			else if (Object[i].id == CHERRY)
			{
				Render_Cherry(i);
			}
			else if (Object[i].id == BANANA)
			{
				Render_Banana(i);
			}
			else if (Object[i].id == ORANGE)
			{
				Render_Orange(i);
			}
			else if (Object[i].id == PINEAPPLE)
			{
				Render_Pineapple(i);
			}
		}
	}
	// Shannon : Render Rat if created
	if (Rat.State == CREATED)
	{
		gotoXY(Rat.Location);
		Render_Rat();
	}
}




