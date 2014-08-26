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
		Life.Location[i].X = consoleSize.X - 2*(i+2);
		Life.Location[i].Y = consoleSize.Y - 53;
	}
}

void RenderLife()
{
	// Shannon : Render Life System
	// Jenny: heart
	char heart = 3;
	for (int i = 0; i < 3; ++i)
	{
		if (Life.Value > i)
		{
			gotoXY(Life.Location[i]);
			colour(0x0C);
			std::cout << heart;
		}
	}
}

void RenderBorder()
{
	// Jenny: Border of x on the right
	for (int y = 2; y <= 52; y++)
	{
		gotoXY(68,y);
		colour(0x1A);
		std::cout << 'x';
	}
}

//Jeffrey : Score System
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
	if (Life.Value != 0)
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


//Level System

//Shannon : Implement Main Level and Mini Level
int Level = 1;
int MiniLevel = 1;
int LevelCounter = 0;

//Shannon : Implement Level Timer
int Lv_Time_Min;
int Lv_Time_Sec;
bool Timer_Set = false; //Sets when to reset the timer
int Timer_Active = 5; //Set to number of FPS
int Timer_Reset = Timer_Active;

//Shannon : Increase Level at certain requirements
void UpdateLevel()
{
	//Shannon : On level up, update level, reset counter
	if (MiniLevel <= 3 && LevelCounter == 2)
	{
		//Level 1
		if (Level == 1)
		{
			switch (MiniLevel)
			{
			case 1:
				//Condition
				//if (...)
				//{
					Timer_Set = false;
					++MiniLevel;
					LevelCounter = 0;
				//}
				break;
			case 2:
				//Condition
				//if (...)
				//{
					Timer_Set = false;
					++MiniLevel;
					LevelCounter = 0;
				//}
				break;
			}
		} //Level 1 End

		//Level 2
		if (Level == 2)
		{
			switch (MiniLevel)
			{
			case 1:
				//Condition
				//if (...)
				//{
					Timer_Set = false;
					++MiniLevel;
					LevelCounter = 0;
				//}
				break;
			case 2:
				//Condition
				//if (...)
				//{
					Timer_Set = false;
					++MiniLevel;
					LevelCounter = 0;
				//}
				break;
			}
		} //Level 2 End

		//End so on...
	}
	//Shannon : Transition from 'Bonus' to next Main Level
	if (MiniLevel > 3 && LevelCounter >= 2)
	{
		timer -= 5;
		++Level;
		MiniLevel = 1;
		LevelCounter = 0;
	}
}

//Yi Yang : Update Difficulty
Difficulty levelDifficulty;
void updateDifficulty()
{
	//Yi Yang : Set Level's Difficulty
	switch (Level)
	{
	case 1:
		levelDifficulty = EASY;
		break;
	case 2:
		if (MiniLevel == 1)
			levelDifficulty = EASY;
		else
			levelDifficulty = MEDIUM;
		break;
	case 3:
		if (MiniLevel == 1)
			levelDifficulty = MEDIUM;
		else
			levelDifficulty = HARD;
		break;
	}
	
	/*
	Chance list :
	-bombChance
	-appleChance	 100pts
	-cherryChance	 150pts
	-bananaChance	 250pts
	-orangeChance	 500pts
	-pearChance		 750pts
	-pineappleChance 1000pts
	
	Set the actual Difficulty by modifying these values below */
	randomizer = 100; //this will always be 100
	if (levelDifficulty == EASY)
	{
		appleChance = 30;
		bombChance = 20;
		cherryChance = 15;
		bananaChance = 15;
		orangeChance = 8;
		pearChance = 7;
		pineappleChance = 5;

		fallSpeed = 1;
		if (Timer_Set == false)
		{
		Lv_Time_Min = 2;
		Lv_Time_Sec = 30;
		Timer_Set = true;
		}
	}
	else if (levelDifficulty == MEDIUM)
	{
		appleChance = 70;
		bombChance = 30;
		fallSpeed = 1;
		if (Timer_Set == false)
		{
		Lv_Time_Min = 2;
		Lv_Time_Sec = 0;
		Timer_Set = true;
		}
	}
	else if (levelDifficulty == HARD)
	{
		appleChance = 60;
		bombChance = 40;
		fallSpeed = 2;
		if (Timer_Set == false)
		{
		Lv_Time_Min = 1;
		Lv_Time_Sec = 30;
		Timer_Set = true;
		}
	}
	else if (levelDifficulty == INSANE)
	{
		appleChance = 55;
		bombChance = 45;
		fallSpeed = 2;
		if (Timer_Set == false)
		{
		Lv_Time_Min = 1;
		Lv_Time_Sec = 0;
		Timer_Set = true;
		}
	}
	else if (levelDifficulty == GODLIKE)
	{
		appleChance = 50;
		bombChance = 50;
		fallSpeed = 2;
		if (Timer_Set == false)
		{
		Lv_Time_Min = 0;
		Lv_Time_Sec = 30;
		Timer_Set = true;
		}
	}
}

//Shannon : Countdown Timer
void UpdateLvTimer()
{
	
	--Timer_Reset;
	if (Timer_Reset == 0)
	{
	if (Lv_Time_Sec >= 0)
	{
		--Lv_Time_Sec;
	}
	if (Lv_Time_Sec < 0 && Lv_Time_Min > 0)
	{
		Lv_Time_Sec = 59;
		--Lv_Time_Min;
	}
	else if (Lv_Time_Sec == 0 && Lv_Time_Min == 0)
	{
		Life.Value = 0;
	}
	Timer_Reset = Timer_Active;
	}

}



//Shannon : Display the level
void RenderLevel() 
{
	//Shannon : Display for normal levels
	if (MiniLevel <= 3)
	{
		gotoXY(75,10);
		colour(0x0C);
		std::cout << Level << '-' << MiniLevel;
	}

	//Shannon : Display for Bonus Level
	if (MiniLevel == 4)
	{
		gotoXY(75,10);
		colour(0x0C);
		std::cout << "Bonus";
		gotoXY(75,11);
		colour(0x0C);
		std::cout << "Level";
	}
}

//Shannon : Display Countdown Timer
void RenderLvTimer()
{
	gotoXY(consoleSize.X/2 - 2,0);
	colour(0x0C);
	std::cout << Lv_Time_Min << ":" << Lv_Time_Sec;
}
