#include "game.h"
#include "systems.h"
#include "score.h"
#include "Framework\console.h"
#include "render.h"
#include <iostream>
#include <iomanip>
#include <fstream>

int Read(string fileName, highscore* pHS)
	{
		ifstream myFile(fileName);
		int i = 0;

		if (myFile.is_open())
		{
			while(!myFile.eof))
			{
				myFile >> pHS[i].name;
				myFile >> pHS[i].playerScore;
				i++;
			}
		}
		return i;
	}

int Write(string fileName, highscore* pHS)
	{
		ofstream myFile(fileName);
		int i =0;

		if(myFile.is_open())
		{
			while (pHS[name])
			{
				myFile << pHS[i].name << "  " <<pHS[i].playerScore << endl;
				i++;
					pHS++;
			}
		}
		return i;
	}

void scoreboard()
{
	ifstream input;
	string background;
	input.open("leaderboard.txt");
	while(!input.eof())
	{
		input>>background;
		cout << background;
	}
	input.close();

	scoreboard HS[5];
	Read("highscore.txt", HS);
	if (score > HS[4].highScore)
	{
		std :: cout << "Enter your name: ";
		std :: cin >> name;
	}

	for (int i = 0; i < 5; i++)
	{
		if (score > HS[i].highScore)
		{
			scoreboard temp[5];
			for (int j = 0; j < 5; j++)
			{
				temp[j].highScore = HS[j].highScore;
				temp[j].name = HS[j].name;
			}

			HS[i].highScore = score;
			HS[i].name = name;
			
			for ( int k = 0; k < 5; k++, i++)
			{
			HS[i+1].highScore = temp[k].highScore;
			HS[i+1].name = temp[k].name;
			}
		break;
		}
	}


	for (int c = 0; c < 5; c++)
	{
		std :: cout << HS[c].name << " " << HS[c].highScore << std :: endl;
	}

	Write("highscore.txt",HS);


}
