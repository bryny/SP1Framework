#include "game.h"
#include "objects.h"
#include "systems.h"
#include "Framework\console.h"
#include "render.h"
#include <iostream>
#include <iomanip>



Type Object[NumberLimit]; //Shannon : Type - Object[MaxNumber + Minimum requirement]
int Number = 0; //Shannon : Test
int timer = 10; //Shannon : Timer - Number of frames before objects are updated (excluding Rat)
int timerlimit;
int ObjectChance;
COORD ObjectStart;
int ObjectSpawnTimer; //Shannon : Timer for when objects are next created

//Shannon : The Rat
Type Rat;
int RatChance;

//Shannon : Initialize Objects & Rat
void ImplementObjects()
{
	// Shannon : Implement Objects
	for (int i = 0; i < 20; ++i)
	{
		Object[i].State = UNCREATED;
	}
	ObjectSpawnTimer = 0;
	//Shannon : Implement Timer
	int timerlimit = timer;

	// Shannon : Implement Rat
	Rat.State = UNCREATED;
	Rat.Location.Y = charLocation.Y;
	Rat.Location.X = 0;

	// Shannon : Implement the randomizer
	srand((unsigned)time(NULL));
}

int randomizer, appleChance, bombChance, cherryChance, bananaChance, orangeChance, pearChance, pineappleChance, fallSpeed;

//Shannon : Create Objects
void CreateObjects()
{
	//Shannon : Objects randomly appear based on starting location on top of screen
	ObjectStart.X = rand() % 50; //Shannon : Sets the X-coordinate of the Object
	ObjectChance = rand() % randomizer + 1; //Shannon : Creates a random number that is used to determine the type of Object created.

	if (Object[Number].State == UNCREATED && ObjectSpawnTimer <= 0)
	{
		ObjectSpawnTimer = rand() % 6 + 5; //Shannon : Objects will spawn 5~10 frames after the previous object.

		//Shannon : Prevent objects from spawning in collision range of previous objects
		while (ObjectStart.X < Object[Number-1].Location.X + 7 && ObjectStart.X > Object[Number-1].Location.X - 7)
		{
			ObjectStart.X = rand() % 50; //Shannon : Re-roll if collision detected
		}
		
		//Shannon : Objects spawn at the top
		Object[Number].Location.X = ObjectStart.X;
		Object[Number].Location.Y = 0;
		Object[Number].EndLocation.Y = 0;
		Object[Number].State = CREATED;
		Object[Number].RenderTime = 0; //Shannon : Initialized for Object to Render as it falls

		//Shannon : Define Objects based on ObjectChance
		if (ObjectChance <= appleChance)
		{
			Object[Number].id = APPLE;
			Object[Number].EndLocation.X = Object[Number].Location.X + 4;
		}
		else if (ObjectChance <= appleChance + bombChance)
		{
			Object[Number].id = BOMB;
			Object[Number].EndLocation.X = Object[Number].Location.X + 4;
		}
		else if (ObjectChance < appleChance + bombChance + cherryChance)
		{
			Object[Number].id = CHERRY;
			Object[Number].EndLocation.X = Object[Number].Location.X + 6;
		}
		else if (ObjectChance < appleChance + bombChance + cherryChance + bananaChance)
		{
			Object[Number].id = BANANA;
			Object[Number].EndLocation.X = Object[Number].Location.X + 5;
		}
		else if (ObjectChance < appleChance + bombChance + cherryChance + bananaChance + orangeChance)
		{
			Object[Number].id = ORANGE;
			Object[Number].EndLocation.X = Object[Number].Location.X + 4;
		}
		else if (ObjectChance < appleChance + bombChance + cherryChance + bananaChance + orangeChance + pearChance)
		{
			Object[Number].id = PEAR;
			Object[Number].EndLocation.X = Object[Number].Location.X + 4;
		}
		else if (ObjectChance < appleChance + bombChance + cherryChance + bananaChance + orangeChance + pearChance + pineappleChance)
		{
			Object[Number].id = PINEAPPLE;
			Object[Number].EndLocation.X = Object[Number].Location.X + 4;
		}
		++Number;
	} //Shannon : End of Object Creation
	

		

	//When all objects have been used,
	if (Number == NumberLimit)
	{
		Number = 0;
	}
}

//Shannon : Update Objects
void UpdateObjects()
{
	//Shannon : Timer counts down per frame
	if (timerlimit != 0)
	{
		--timerlimit;
	}


	//Shannon : When timer reaches 0, objects are updated and timer is reset
	if (timerlimit == 0)
	{
		timerlimit = timer;
		--ObjectSpawnTimer; //Shannon : Spawn Countdown ticks down

		//	Shannon : Objects slowly descend to player if 
		//	they are in play and have not touched the bottom.
		for (int ii = 0; ii < NumberLimit; ++ii)
		{
			if (Object[ii].State == CREATED)
			{
				if (Object[ii].Location.Y < ConsoleSize.Y - 1)
				{
					//Shannon : Objects displace based on fallspeed
					Object[ii].Location.Y += fallSpeed;
					//Shannon : Increase amount rendered if Object is not fully rendered
					if (Object[ii].RenderTime < 7)
					{
						++Object[ii].RenderTime;
					}
				}
			}
		}
	} //Shannon : End of timer
	
	for (int ii = 0; ii < NumberLimit; ++ii)
	{
		// Shannon : Objects are 'recycled' after touching player or bottom of screen
		if (Object[ii].Location.Y >= ConsoleSize.Y - 1)
		{
			//Shannon : Bonus Level also counts objects that reach the bottom
			if (Object[ii].id != BOMB && Object[ii].State == CREATED && MiniLevel == 4)
			{
				LevelCounter += 1;
			}

			//
			Object[ii].State = UNCREATED;
		}

		//Shannon : Check collision for the object with basket
		COORD Basket = {charLocation.X, charLocation.Y - 10};

		//Shannon : How objects affect the player when collision happens
		if (Object[ii].State == CREATED && Object[ii].Location.X > Basket.X && Object[ii].Location.X < Basket.X + 10 && Basket.Y == Object[ii].Location.Y && Object[ii].EndLocation.X > Basket.X && Object[ii].EndLocation.X < Basket.X + 10)
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
	RatChance = rand() % 100 + 1;
	if (Rat.State == UNCREATED)
	{
		if (RatChance <= 5)
		{
			Rat.State = CREATED;
		}
	}
	//Shannon : If Rat is created, it will move to the other side of the screen
	if (Rat.State == CREATED && Rat.Location.X != ConsoleSize.X - 1)
	{
		++Rat.Location.X;
	}
	//Shannon : If the Rat touches the player, lose score and Rat disappears
	if (Rat.State == CREATED && Rat.Location.X >= charLocation.X - 4 && Rat.Location.X <= charLocation.X + 10 && Rat.Location.Y == charLocation.Y)
	{
		Rat.State = UNCREATED;
		Rat.Location.X = 0;
		if (score >= 100)
		{
			score -= 100;
		}
	}
	//Shannon : When it reaches the other side, it disappears
	if (Rat.Location.X == ConsoleSize.X - 5)
	{
		Rat.State = UNCREATED;
		Rat.Location.X = 0;
	}
}



void RenderObjects()
{
	// Shannon : Render objects if created
	for (int i = 0; i < NumberLimit; ++i)	
	{
		if (Object[i].State == CREATED)
		{
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
			else if (Object[i].id == PEAR)
			{
				Render_Pear(i);
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
		Render_Rat();
	}
}




