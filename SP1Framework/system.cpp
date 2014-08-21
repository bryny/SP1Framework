#include "game.h"
#include "objects.h"
#include "systems.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>


//Life System
System Life; //Shannon : Life System
void ImplementLife()
{
	//Shannon : Implement Life System
	Life.Value = 3;
	for (int i = 0; i < 3; ++i)
	{
		Life.Location[i].X = consoleSize.X - 2*(i+1);
		Life.Location[i].Y = consoleSize.Y - 20;
	}
}

void RenderLife()
{
	// Shannon : Render Life System
	for (int i = 0; i < 3; ++i)
	{
		if (Life.Value > i)
		{
			gotoXY(Life.Location[i]);
			colour(0x0C);
			std::cout <<(char)1;
		}
	}
}




//Score System
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