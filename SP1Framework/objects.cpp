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
}

//Yi Yang: These values should not be Enum constant.
//		   The appleChance value will decrease and the
//		   bombChance value will increase as the level
//		   increases, so I changed them to int instead.
//         (otherwise a constant value cannot be modified)
int randomizer, appleChance, bombChance, cherryChance, bananaChance, orangeChance, pearChance, pineappleChance, fallSpeed;

//Create the minimum objects based on Level Counter
void MinimumObjects()
{
	//Create Objects
	Object[Number2].State = CREATED;
	if (ObjectStart.X + 5 < consoleSize.X - 1 )
	{
	Object[Number2].Location.X = ObjectStart.X + 5; //Lack of Collision, makedo system
	}
	else
	{
	Object[Number2].Location.X = ObjectStart.X - 5; //Lack of Collision, makedo system
	}
	Object[Number2].Location.Y = 0;
	//ID Objects as anything but bombs
	if (ObjectChance <= appleChance + bombChance)
				{
					Object[Number2].id = APPLE;
				}
				else if (ObjectChance < appleChance + bombChance + cherryChance)
				{
					Object[Number2].id = CHERRY;
				}
				else if (ObjectChance < appleChance + bombChance + cherryChance + bananaChance)
				{
					Object[Number2].id = BANANA;
				}
				else if (ObjectChance < appleChance + bombChance + cherryChance + bananaChance + orangeChance)
				{
					Object[Number2].id = ORANGE;
				}
				else if (ObjectChance < appleChance + bombChance + cherryChance + bananaChance + orangeChance + pearChance)
				{
					Object[Number2].id = PEAR;
				}
				else if (ObjectChance < appleChance + bombChance + cherryChance + bananaChance + orangeChance + pearChance + pineappleChance)
				{
					Object[Number2].id = PINEAPPLE;
				}
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
		if (Number < NumberLimit)
		{
			ObjectStart.X = rand() % 50; //Shannon : Sets the X-coordinate of Object
			ObjectChance = rand() % randomizer + 1; //Shannon : Sets the randomizer for objects
			if (Object[Number].State == UNCREATED)
			{
				Object[Number].Location.X = ObjectStart.X;
				Object[Number].Location.Y = 0;
				Object[Number].State = CREATED;

				//Shannon : Define Objects based on ObjectChance
				if (ObjectChance <= appleChance)
				{
					Object[Number].id = APPLE;
				}
				else if (ObjectChance <= appleChance + bombChance)
				{
					Object[Number].id = BOMB;
				}
				else if (ObjectChance < appleChance + bombChance + cherryChance)
				{
					Object[Number].id = CHERRY;
				}
				else if (ObjectChance < appleChance + bombChance + cherryChance + bananaChance)
				{
					Object[Number].id = BANANA;
				}
				else if (ObjectChance < appleChance + bombChance + cherryChance + bananaChance + orangeChance)
				{
					Object[Number].id = ORANGE;
				}
				else if (ObjectChance < appleChance + bombChance + cherryChance + bananaChance + orangeChance + pearChance)
				{
					Object[Number].id = PEAR;
				}
				else if (ObjectChance < appleChance + bombChance + cherryChance + bananaChance + orangeChance + pearChance + pineappleChance)
				{
					Object[Number].id = PINEAPPLE;
				}
			}
		}
		++Number;
		if (Number == NumberLimit)
		{
			Number = 0;
		}
		if (Number2 < TotalLimit)
		{
		MinimumObjects(); //Create the minimum Objects required
		++Number2;
		}

		//	Shannon : Objects slowly descend to player
		for (int ii = 0; ii < TotalLimit; ++ii)
		{
			if (Object[ii].State == CREATED)
			{
				if (Object[ii].Location.Y < consoleSize.Y - 1)
				{
					Object[ii].Location.Y += fallSpeed;
				}
			}
		}
	}
	
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

void renderBomb()
{
	for (int i=0; i < 10; i++)
	{
		if(Object[i].id == BOMB)
		{
		gotoXY(Object[i].Location.X+2, Object[i].Location.Y+1);
		yellow(1);
		red(1);

		gotoXY(Object[i].Location.X+2, Object[i].Location.Y+2);
		red(1);
		gotoXY(Object[i].Location.X+4, Object[i].Location.Y+2);
		yellow(1);
		
		gotoXY(Object[i].Location.X+1, Object[i].Location.Y+3);
		black(3);

		gotoXY(Object[i].Location.X, Object[i].Location.Y+4);
		black(1);
		white(1);
		black(3);

		gotoXY(Object[i].Location.X, Object[i].Location.Y+5);
		black(5);

		gotoXY(Object[i].Location.X, Object[i].Location.Y+6);
		black(5);

		gotoXY(Object[i].Location.X+1, Object[i].Location.Y+7);
		black(3);
		}
	}
}

void renderRat()
{
	gotoXY(Rat.Location.X, Rat.Location.Y-4);
	grey(2);
	gotoXY(Rat.Location.X+3, Rat.Location.Y-4);
	grey(2);

	gotoXY(Rat.Location.X, Rat.Location.Y-3);
	pink(1);
	grey(3);
	pink(1);

	gotoXY(Rat.Location.X+1, Rat.Location.Y-2);
	black(1);
	grey(1);
	black(1);

	gotoXY(Rat.Location.X+1, Rat.Location.Y-1);
	grey(3);

	gotoXY(Rat.Location.X +2, Rat.Location.Y);
	black(1);

}

void renderPineapple()
{
	for (int i=0; i < 10; i++)
	{
		if(Object[i].id == PINEAPPLE)
		{
		gotoXY(Object[i].Location.X, Object[i].Location.Y+1);
		d_green(1);
		gotoXY(Object[i].Location.X+2, Object[i].Location.Y+1);
		d_green(1);
		gotoXY(Object[i].Location.X+4, Object[i].Location.Y+1);
		d_green(1);

		gotoXY(Object[i].Location.X+1, Object[i].Location.Y+2);
		d_green(1);
		gotoXY(Object[i].Location.X+3, Object[i].Location.Y+2);
		d_green(1);

		gotoXY(Object[i].Location.X+2, Object[i].Location.Y+3);
		d_green(1);

		gotoXY(Object[i].Location.X, Object[i].Location.Y+4);
		brown(1);
		yellow(1);
		brown(1);

		gotoXY(Object[i].Location.X, Object[i].Location.Y+5);
		yellow(1);
		brown(1);
		yellow(1);

		gotoXY(Object[i].Location.X, Object[i].Location.Y+6);
		brown(1);
		yellow(1);
		brown(1);

		gotoXY(Object[i].Location.X, Object[i].Location.Y+7);
		yellow(1);
		brown(1);
		yellow(1);

		}
	}
}

void renderCherry()
{
	for (int i=0; i < 10; i++)
	{
		if(Object[i].id == CHERRY)
		{
		gotoXY(Object[i].Location.X+1, Object[i].Location.Y+1);
		d_green(2);
		gotoXY(Object[i].Location.X+4, Object[i].Location.Y+1);
		d_green(2);

		gotoXY(Object[i].Location.X, Object[i].Location.Y+2);
		d_green(2);
		gotoXY(Object[i].Location.X+3, Object[i].Location.Y+2);
		d_red(1);
		gotoXY(Object[i].Location.X+5, Object[i].Location.Y+2);
		d_green(2);

		gotoXY(Object[i].Location.X, Object[i].Location.Y+3);
		d_green(1);
		gotoXY(Object[i].Location.X+3, Object[i].Location.Y+3);
		d_red(1);
		gotoXY(Object[i].Location.X+6, Object[i].Location.Y+3);
		d_green(1);

		gotoXY(Object[i].Location.X+2, Object[i].Location.Y+4);
		d_red(3);

		gotoXY(Object[i].Location.X, Object[i].Location.Y+5);
		red(1);
		d_red(1);
		red(1);
		gotoXY(Object[i].Location.X+4, Object[i].Location.Y+5);
		red(1);
		d_red(1);
		red(1);

		gotoXY(Object[i].Location.X, Object[i].Location.Y+6);
		red(3);
		gotoXY(Object[i].Location.X+4, Object[i].Location.Y+6);
		red(3);

		gotoXY(Object[i].Location.X, Object[i].Location.Y+7);
		red(3);
		gotoXY(Object[i].Location.X+4, Object[i].Location.Y+7);
		red(3);
		}
	}
}

void renderBanana()
{
	char a[] =   {","};
	char b[] =   {"\\`.__."};
	char c[] =   {" `._,'"};

	for (int i=0; i < 10; i++)
	{
		if(Object[i].id == BANANA)
		{
		gotoXY(Object[i].Location.X, Object[i].Location.Y+1);
		std  :: cout << a<<std::endl;
		gotoXY(Object[i].Location.X, Object[i].Location.Y+2);
		std :: cout << b<<std::endl;
		gotoXY(Object[i].Location.X, Object[i].Location.Y+3);
		std :: cout << c<<std::endl;
		}
	}
}

void pear()
{
	char a[] =   {"  ("};
	char b[] =   {" / \\"};
	char c[] =   {"(   )"};
	char d[] =   {" `""'"};

	for (int i=0; i < 10; i++)
	{
		if(Object[i].id == PEAR)
		{
		gotoXY(Object[i].Location.X, Object[i].Location.Y+1);
		std  :: cout << a<<std::endl;
		gotoXY(Object[i].Location.X, Object[i].Location.Y+2);
		std :: cout << b<<std::endl;
		gotoXY(Object[i].Location.X, Object[i].Location.Y+3);
		std :: cout << c<<std::endl;
		gotoXY(Object[i].Location.X, Object[i].Location.Y+4);
		std :: cout << d<<std::endl;
		}
	}
}

void orange()
{
	char a[] =   {" ,,+.."};
	char b[] =   {"//|||\\\\"};
	char c[] =   {"|||||||"};
	char d[] =   {"\\\\|||//"};
	char e[] =   {" ``+''"};
	for (int i=0; i < 10; i++)
	{
		if(Object[i].id == ORANGE)
		{
		gotoXY(Object[i].Location.X, Object[i].Location.Y+1);
		std  :: cout << a<<std::endl;
		gotoXY(Object[i].Location.X, Object[i].Location.Y+2);
		std :: cout << b<<std::endl;
		gotoXY(Object[i].Location.X, Object[i].Location.Y+3);
		std :: cout << c<<std::endl;
		gotoXY(Object[i].Location.X, Object[i].Location.Y+4);
		std :: cout << d<<std::endl;
		gotoXY(Object[i].Location.X, Object[i].Location.Y+5);
		std :: cout << e<<std::endl;
		}
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
				colour(0x0C);
				std::cout << (char)65;
			}
			else if (Object[i].id == BOMB)
			{
				renderBomb();
			}
			else if (Object[i].id == CHERRY)
			{
				colour(0x59);
				std::cout << (char)67;
			}
			else if (Object[i].id == BANANA)
			{
				colour(0x59);
				std::cout << (char)68;
			}
			else if (Object[i].id == ORANGE)
			{
				colour(0x59);
				std::cout << (char)69;
			}
			else if (Object[i].id == PINEAPPLE)
			{
				renderPineapple();
			}
		}
	}
	// Shannon : Render Rat if created
	if (Rat.State == CREATED)
	{
		gotoXY(Rat.Location);
		renderRat();
	}
}




