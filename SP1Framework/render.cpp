#include <iostream>
#include <iomanip>
#include "game.h"
#include "Framework\console.h"
#include "render.h"
#include "objects.h"

//Shannon : Simplifying the colour creation
WORD black = 0;
WORD d_blue = 16;
WORD d_green = 32;
WORD d_cyan = 48;
WORD d_red = 64;
WORD purple = 80;
WORD brown = 96;
WORD grey = 112;
WORD d_grey = 128;
WORD blue = 144;
WORD green = 160;
WORD cyan = 176;
WORD red = 192;
WORD pink = 208;
WORD yellow = 224;
WORD white = 240;
COORD C;
WORD Apple[35] = 
	{16,16,16,192,192,192,16, //1st column
	 16,16,192,240,192,192,192, //2nd column
	 16,32,192,192,192,192,192, //3rd column
	 32, 32, 192, 192, 192, 192, 192, //4th column
	 32, 32, 16, 192, 192, 192, 16}; //5th column
WORD Bomb[35] =
	{16,16,16,0,0,0,16,
	 16,16,0,240,0,0,0,
	 192,192,0,0,0,0,0,
	 96,16,0,0,0,0,0,
	 16,224,16,0,0,0,16};
WORD Cherry[49] =
	{16,32,32,16,192,192,192,
	 32,32,16,16,64,192,192,
	 32,16,16,64,192,192,192,
	 16,64,64,16,16,16,16,
	 32,16,16,64,192,192,192,
	 32,32,16,16,64,192,192,
	 16,32,32,16,192,192,192};
WORD Banana[42] =
	{16,16,16,16,16,96,16,
	 16,16,16,16,16,224,16,
	 16,16,16,16,16,224,244,
	 96,16,16,16,224,224,224,
	 96,224,224,224,224,224,224,
	 96,16,224,224,224,224,16};
WORD Orange[35] = 
	{16,16,16,96,96,96,16, //1st column
	 16,16,96,240,96,96,96, //2nd column
	 16,32,96,96,96,96,96, //3rd column
	 32, 32, 96, 96, 96, 96, 96, //4th column
	 32, 32, 16, 96, 96, 96, 16}; //5th column
WORD Pear[35] = {16,16,16,16,160,160,16,16,16,160,160,240,160,160,32,160,160,160,160,160,160,32,32,160,160,160,160,160,16,32,16,16,160,160,16};
WORD Pineapple[35] =
	{32,16,16,16,16,16,16,
	 16,32,16,224,96,224,96,
	 32,16,32,96,224,96,224,
	 16,32,16,224,96,224,96,
	 32,16,16,16,16,16,16};
WORD RatColour[25] = 
	{112,208,16,16,16,
	 112,112,0,112,16,
	 16,112,112,112,0,
	 112,112,0,112,16,
	 112,208,16,16,16};

//Shannon : Final Render

//Shannon : Render objects from bottom to top
void Render_Apple(int num)
{
	for (int x = 0; x < 5; ++x)
	{
		for (int y = 0; y < 7; ++y)
		{
			C.X = Object[num].Location.X + x;
			C.Y = Object[num].Location.Y + y;
			writeToBuffer(C," ",Apple[7*x+y]);
		}
	}
}

void Render_Bomb(int num)
{
	for (int x = 0; x < 5; ++x)
	{
		for (int y = 0; y < 7; ++y)
		{
			C.X = Object[num].Location.X + x;
			C.Y = Object[num].Location.Y + y;
			writeToBuffer(C," ",Bomb[7*x+y]);
		}
	}
}

void Render_Cherry(int num)
{
	for (int x = 0; x < 7; ++x)
	{
		for (int y = 0; y < 7; ++y)
		{
			C.X = Object[num].Location.X + x;
			C.Y = Object[num].Location.Y + y;
			writeToBuffer(C, " ", Cherry[7*x+y]);
		}
	}
}

void Render_Banana(int num)
{
	for (int x = 0; x < 6; ++x)
	{
		for (int y = 0; y < 7; ++y)
		{
			C.X = Object[num].Location.X + x;
			C.Y = Object[num].Location.Y + y;
			writeToBuffer(C," ",Banana[7*x+y]);
		}
	}
}

void Render_Orange(int num)
{
	for (int x = 0; x < 5; ++x)
	{
		for (int y = 0; y < 7; ++y)
		{
			C.X = Object[num].Location.X + x;
			C.Y = Object[num].Location.Y + y;
			writeToBuffer(C," ",Orange[7*x+y]);
		}
	}
}

void Render_Pear(int num)
{
	for (int x = 0; x < 5; ++x)
	{
		for (int y = 0; y < 7; ++y)
		{
			C.X = Object[num].Location.X + x;
			C.Y = Object[num].Location.Y + y;
			writeToBuffer(C," ",Pear[7*x+y]);
		}
	}
}

void Render_Pineapple(int num)
{
	for (int x = 0; x < 5; ++x)
	{
		for (int y = 0; y < 7; ++y)
		{
			C.X = Object[num].Location.X + x;
			C.Y = Object[num].Location.Y + y;
			writeToBuffer(C," ",Pineapple[7*x+y]);
		}
	}
}


//Jenny : Render Man
void Render_Man()
{
	writeToBuffer(charArea[0][11]," ",grey);
	writeToBuffer(charArea[10][11]," ",grey);
	
	writeToBuffer(charArea[0][10]," ",grey);
	writeToBuffer(charArea[10][10]," ",grey);

	writeToBuffer(charArea[0][9],"           ",grey);

	writeToBuffer(charArea[0][8]," ",d_red);
	writeToBuffer(charArea[1][8],"         ",grey);
	
	//Head
	writeToBuffer(charArea[0][7],"  ",d_red);
	writeToBuffer(charArea[3][7],"     ",d_red);
	
	writeToBuffer(charArea[1][6]," ",d_red);
	writeToBuffer(charArea[3][6]," ",d_red);
	writeToBuffer(charArea[4][6]," ",black);
	writeToBuffer(charArea[5][6]," ",d_red);
	writeToBuffer(charArea[6][6]," ",black);
	writeToBuffer(charArea[7][6]," ",d_red);

	writeToBuffer(charArea[1][5]," ",d_red);
	writeToBuffer(charArea[3][5]," ",d_red);
	writeToBuffer(charArea[4][5]," ",black);
	writeToBuffer(charArea[5][5]," ",d_red);
	writeToBuffer(charArea[6][5]," ",black);
	writeToBuffer(charArea[7][5]," ",d_red);
	
	writeToBuffer(charArea[1][4]," ",d_red);
	writeToBuffer(charArea[2][4]," ",blue);
	writeToBuffer(charArea[3][4]," ",pink);
	writeToBuffer(charArea[4][4],"   ",d_red);
	writeToBuffer(charArea[7][4]," ",pink);
	writeToBuffer(charArea[8][4]," ",blue);
	writeToBuffer(charArea[9][4]," ",d_red);

	writeToBuffer(charArea[1][3]," ",d_red);
	writeToBuffer(charArea[2][3]," ",blue);
	writeToBuffer(charArea[3][3],"  ",d_red);
	writeToBuffer(charArea[5][3]," ",red);
	writeToBuffer(charArea[6][3],"  ",d_red);
	writeToBuffer(charArea[8][3]," ",blue);
	writeToBuffer(charArea[9][3]," ",d_red);
	
	//Shirt
	writeToBuffer(charArea[3][2],"     ",blue);
	writeToBuffer(charArea[9][2]," ",d_red);
	
	//Pants
	writeToBuffer(charArea[4][1],"   ",black);
	writeToBuffer(charArea[9][1],"  ",d_red);

	//Feet
	writeToBuffer(charArea[3][0],"  ",d_red);
	writeToBuffer(charArea[6][0],"  ",d_red);
}

//Jenny : Render Rat
void Render_Rat()
{
	for (int x = 0; x < 5; ++x)
	{
		for (int y = 0; y < 5; ++y)
		{
			C.X = Rat.Location.X + x;
			C.Y = Rat.Location.Y + y;
			writeToBuffer(C," ",RatColour[5*x+y]);
		}
	}
}
