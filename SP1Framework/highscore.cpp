#include "game.h"
#include "systems.h"
#include "menu.h"
#include "render.h"
#include "highscore.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using std::string;
board High[10];
string enteredName = "";
COORD sconsoleSize;

int k = 0;
char arr[] = {'A','A','A','A','A'};
extern bool keyPressed[];

COORD arcadescore = {35,10};
COORD arcadescoreletter = {35,10};
COORD c;
COORD X = { 36, 13 };

void Read(string fileName, board* pHigh)
{
	std :: ifstream myFile(fileName);
	int i = 0;

	if (myFile.is_open())
	{ 
		while(!myFile.eof())
		{
			myFile >> pHigh[i].name;
			myFile >> pHigh[i].highScore;
			i++;
		}
	}
	myFile.close();
}

int Write(string fileName, board* pHigh)
{
	std :: ofstream myFile(fileName);
	int i =0;

	if(myFile.is_open() && score > 0)
	{
		while (i < 10)
		{
			myFile << pHigh[i].name << "  " <<pHigh[i].highScore << std :: endl;
			i++;
		}
	}
	return i;
}
 

//Jenny : Render layouts
void sblayout()
{
	clearBuffer();
	std::ifstream ins;
	string background;
	ins.open("leaderboard.txt");

	if (ins.is_open())
	{
		COORD bg_loc = {5,5};
		while(!ins.eof())
		{
			getline(ins, background);
			writeToBuffer(bg_loc,background);
			bg_loc.Y++;
		}
		ins.close();
	}  
}

void enterS()
{
	clearBuffer();
	std :: ifstream input;
	string enter;
	input.open("enter.txt");
	if (input.is_open())
	{
	COORD enter_loc = {0,0};
	while(!input.eof())
	{
		getline (input, enter);
		writeToBuffer(enter_loc,enter);
		enter_loc.Y++;
	}
	input.close();
	}
}

void nameTab()
{
	c.Y = 10;
	c.X = 20;

	c.Y++;
	c.X -= 12;

	writeToBuffer(arcadescore, arr);
	writeToBuffer(arcadescoreletter, arr[k], 0xf0);

	if (arr[k] >= 'A' && arr[k] <= 'Z')
	{
		if (keyPressed[K_UP])
		{
			arr[k]--;
		}


		if (keyPressed[K_DOWN])
		{
			arr[k]++;
		}

		if (arr[k] == '@')
		{	
			arr[k] = 'Z';
		}
		if (arr[k] == '[')
		{
			arr[k] = 'A';
		}
		
		if (keyPressed[K_RIGHT] && k < 4)
		{
			arcadescoreletter.X++;
			X.X++;
			k++;
		}
		if (keyPressed[K_LEFT] && k > 0)
		{
			arcadescoreletter.X--;
			X.X--;
			k--;
		}	

	}

}

void sortScore(int playerScore)
{
	board temp[10];

	for (int i = 0; i < 5; i++)
	{
		enteredName += arr[i];
	}

	for (int i = 0; i < 10; i++)
	{
		if (playerScore > High[i].highScore)
		{
			for (int j = 0; j < 10; j++)
			{
				temp[j].highScore = High[j].highScore;
				temp[j].name = High[j].name;
				
			}
			High[i].highScore = playerScore;
			High[i].name = enteredName;

			for (int k = i; k < 10; k++, i++)
			{
				High[i+1].highScore = temp[k].highScore;
				High[i+1].name = temp[k].name;
			}
			break;
		}
	}
}

void displayScore(board * highScore)
{
	const int NUMBERP = 10;
	int printStart = sconsoleSize.X+15;

	for (int i =0; i < NUMBERP; i++)
	{
		COORD number = {printStart-5, i+15};
		std::string a = std::to_string(static_cast<long double>(i + 1));
		writeToBuffer(number, (string) (a));

		COORD name = {printStart + 5, i + 15};
		writeToBuffer(name,highScore[i].name);

		COORD score = {printStart + 30, i + 15};
		std::string b = std :: to_string(static_cast<long double>(highScore[i].highScore));
		writeToBuffer(score, b);
	}
}

int scoreboard(int playerScore)
{
	if (playerScore > High[9].highScore)
	{
		enterS();
		nameTab();
		if (keyPressed[K_RETURN])
		{
			clearBuffer();
			Read("highscore.txt", High);
			sortScore(playerScore);	
			sblayout();
			displayScore(High);
			Write("highscore.txt",High);
		}
	}
	else
	{
		Read("highscore.txt", High);
		sblayout();
		displayScore(High);
	}
	return 0;
}