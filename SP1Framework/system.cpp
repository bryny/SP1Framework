#include "game.h"
#include "objects.h"
#include "systems.h"

//Life System
System Life; //Shannon : Life System
void ImplementLife()
{
	//Shannon : Implement Life System
	Life.Value = 3;
	Life.Location.X = ConsoleSize.X - 2;
	Life.Location.Y = ConsoleSize.Y - 53;
	
}

void RenderLife()
{
	// Shannon : Render Life System
	// Jenny: heart
	char heart = 3;
	COORD C;
	for (int i = 0; i < Life.Value; ++i)
	{
		C.X = Life.Location.X;
		C.Y = Life.Location.Y + 2*i;
		writeToBuffer(C,heart,0x0C);
	}
}

// Jenny: Border of x on the right
void RenderBorder()
{
	COORD C;
	C.X = 68;
	for (int y = 2; y <= 52; y++)
	{
		C.Y = y;
		writeToBuffer(C,'x',0x1A);
	}
}

//Jeffrey : Score System
unsigned long long score;
void displayscore()
{
	if(score == 1000000000 || score > 1000000000)
	{
		COORD WinWord1 = {32,10};
		writeToBuffer(WinWord1,"Congratulations",0x0C);
		COORD WinWord2 = {36,11};
		writeToBuffer(WinWord2,"You Won",0x0C);
	}
	if (Life.Value != 0)
	{
		COORD Score = {70,2};
		std::string ScoreDisplay = "Score:" + std::to_string(score);
		writeToBuffer(Score,ScoreDisplay,0x1A);
	}
	else if(Life.Value == 0)
	{
		COORD LoseWord = {35,10};
		writeToBuffer(LoseWord,"GAME OVER",0x0c);

		//Jenny : call for score.cpp
		//scoreboard();
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
int Timer_Active = 100; //Set to number of FPS
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
		bananaChance = 100;

		fallSpeed = 1;
		if (Timer_Set == false)
		{
		Lv_Time_Min = 2;
		Lv_Time_Sec = 00;
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
COORD TimerLocation = {ConsoleSize.X/2 - 2,0};
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
	std::string Timer= std::to_string(static_cast<long long>(Lv_Time_Min)) + ":" + std::to_string(static_cast<long long>(Lv_Time_Sec));
	writeToBuffer(TimerLocation,Timer,0x0C);
}
