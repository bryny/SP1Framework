#include "game.h"
#include "objects.h"
#include "highscore.h"
#include "systems.h"
#include "Framework\console.h"
#include <iostream>   
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>

void highscore()
{
	std::ifstream inData;
	std::string data;

	COORD L= {0,0};
	inData.open("highscore.txt");
	if (inData.is_open())
	{
		while(!inData.eof())
		{
			getline (inData, data);
			writeToBuffer(L,data,0x1F);
			L.Y++;

		}
		inData.close();
	}
}

void rendermenu()
{
	std::ifstream inData;
	std::string data;

	COORD J= {0,0};
	inData.open("Menu.txt");
	if (inData.is_open())
	{
		while(!inData.eof())
		{
			getline (inData, data);
			writeToBuffer(J,data,0x1F);
			J.Y++;

		}
		inData.close();
	}
}

void credits()
{
	std::ifstream inData;
	std::string data;

	COORD K= {0,0};
	inData.open("credits.txt");
	if (inData.is_open())
	{
		while(!inData.eof())
		{
			getline (inData, data);
			writeToBuffer(K,data,0x1F);
			K.Y++;

		}
		inData.close();
	}
	
}

void renderarrow()
{
	COORD Arrow; 
	Arrow.X=arrowX[change];
	Arrow.Y=arrowY[change];
	COORD Arrow2;
	Arrow2.X=arrowX[change];
	Arrow2.Y=(arrowY[change]+1);
	writeToBuffer(Arrow,"==\\",0x0C);
	writeToBuffer(Arrow2,"==/",0x0C);
}
