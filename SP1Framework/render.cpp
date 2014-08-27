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

//Shannon : Final Render

//Shannon : Render objects from bottom to top
void Render_Apple(int num)
{
	if (Object[num].RenderTime > 0)
	{
		writeToBuffer(Object[num].Area[1][0],"   ",red);
	}
	
	if (Object[num].RenderTime > 1)
	{
		writeToBuffer(Object[num].Area[0][1],"     ",red);
	}

	if (Object[num].RenderTime > 2)
	{
		writeToBuffer(Object[num].Area[0][2],"     ",red);
	}

	if (Object[num].RenderTime > 3)
	{
		writeToBuffer(Object[num].Area[0][3]," ",red);
		writeToBuffer(Object[num].Area[1][3]," ",white);
		writeToBuffer(Object[num].Area[2][3],"   ",red);
	}

	if (Object[num].RenderTime > 4)
	{
		writeToBuffer(Object[num].Area[1][4],"   ",red);
	}

	if (Object[num].RenderTime > 5)
	{
		writeToBuffer(Object[num].Area[2][5],"   ",d_green);
	}

	if (Object[num].RenderTime > 6)
	{
		writeToBuffer(Object[num].Area[3][6],"  ",d_green);
	}
}

void Render_Bomb(int num)
{
	if (Object[num].RenderTime > 0)
	{
		writeToBuffer(Object[num].Area[1][0],"   ",black);
	}

	if (Object[num].RenderTime > 1)
	{
		writeToBuffer(Object[num].Area[0][1],"     ",black);
	}

	if (Object[num].RenderTime > 2)
	{
		writeToBuffer(Object[num].Area[0][2],"     ",black);
	}

	if (Object[num].RenderTime > 3)
	{
		writeToBuffer(Object[num].Area[0][3]," ",black);
		writeToBuffer(Object[num].Area[1][3]," ",white);
		writeToBuffer(Object[num].Area[2][3],"   ",black);
	}

	if (Object[num].RenderTime > 4)
	{
		writeToBuffer(Object[num].Area[1][4],"   ",black);
	}

	if (Object[num].RenderTime > 5)
	{
		writeToBuffer(Object[num].Area[2][5]," ",red);
		writeToBuffer(Object[num].Area[4][5]," ",yellow);
	}

	if (Object[num].RenderTime > 6)
	{
		writeToBuffer(Object[num].Area[2][6]," ",red);
		writeToBuffer(Object[num].Area[3][6]," ",brown);
	}
}

void Render_Cherry(int num)
{
	if (Object[num].RenderTime > 0)
	{
		writeToBuffer(Object[num].Area[0][0],"   ",red);
		writeToBuffer(Object[num].Area[4][0],"   ",red);
	}
	
	if (Object[num].RenderTime > 1)
	{
		writeToBuffer(Object[num].Area[0][1],"   ",red);
		writeToBuffer(Object[num].Area[4][1],"   ",red);
	}

	if (Object[num].RenderTime > 2)
	{
		writeToBuffer(Object[num].Area[0][2]," ",red);
		writeToBuffer(Object[num].Area[1][2]," ",d_red);
		writeToBuffer(Object[num].Area[2][2]," ",red);
		writeToBuffer(Object[num].Area[4][2]," ",red);
		writeToBuffer(Object[num].Area[5][2]," ",d_red);
		writeToBuffer(Object[num].Area[6][2]," ",red);
	}

	if (Object[num].RenderTime > 3)
	{
		writeToBuffer(Object[num].Area[2][3]," ",d_red);
		writeToBuffer(Object[num].Area[4][3]," ",d_red);
	}

	if (Object[num].RenderTime > 4)
	{
		writeToBuffer(Object[num].Area[0][4]," ",d_green);
		writeToBuffer(Object[num].Area[3][4]," ",d_red);
		writeToBuffer(Object[num].Area[6][4]," ",d_green);
	}

	if (Object[num].RenderTime > 5)
	{
		writeToBuffer(Object[num].Area[0][5],"  ",d_green);
		writeToBuffer(Object[num].Area[3][5]," ",d_red);
		writeToBuffer(Object[num].Area[5][5],"  ",d_green);
	}

	if (Object[num].RenderTime > 6)
	{
		writeToBuffer(Object[num].Area[1][6],"  ",d_green);
		writeToBuffer(Object[num].Area[4][6],"  ",d_green);
	}
}

void Render_Banana(int num)
{
	if (Object[num].RenderTime > 0)
	{
		writeToBuffer(Object[num].Area[2][0],"   ",yellow);
	}
	
	if (Object[num].RenderTime > 1)
	{
		writeToBuffer(Object[num].Area[0][1]," ",brown);
		writeToBuffer(Object[num].Area[1][1],"     ",yellow);
	}

	if (Object[num].RenderTime > 2)
	{
		writeToBuffer(Object[num].Area[3][2],"   ",yellow);
	}

	if (Object[num].RenderTime > 3)
	{
		writeToBuffer(Object[num].Area[4][3],"  ",yellow);
	}

	if (Object[num].RenderTime > 4)
	{
		writeToBuffer(Object[num].Area[4][4],"  ",yellow);
	}

	if (Object[num].RenderTime > 5)
	{
		writeToBuffer(Object[num].Area[4][5]," ",yellow);
	}

	if (Object[num].RenderTime > 6)
	{
		writeToBuffer(Object[num].Area[3][6],"   ",brown);
	}
}

void Render_Orange(int num)
{
	if (Object[num].RenderTime > 0)
	{
		writeToBuffer(Object[num].Area[1][0],"   ",brown);
	}

	if (Object[num].RenderTime > 1)
	{
		writeToBuffer(Object[num].Area[0][1],"     ",brown);
	}

	if (Object[num].RenderTime > 2)
	{
		writeToBuffer(Object[num].Area[0][2],"     ",brown);
	}

	if (Object[num].RenderTime > 3)
	{
		writeToBuffer(Object[num].Area[0][3]," ",brown);
		writeToBuffer(Object[num].Area[1][3]," ",white);
		writeToBuffer(Object[num].Area[2][3],"   ",brown);
	}

	if (Object[num].RenderTime > 4)
	{
		writeToBuffer(Object[num].Area[1][4],"   ",brown);
	}

	if (Object[num].RenderTime > 5)
	{
		writeToBuffer(Object[num].Area[2][5],"   ",d_green);
	}

	if (Object[num].RenderTime > 6)
	{
		writeToBuffer(Object[num].Area[3][6],"  ",d_green);
	}
}

void Render_Pear(int num)
{
	if (Object[num].RenderTime > 0)
	{
		writeToBuffer(Object[num].Area[1][0],"   ",green);
	}
	
	if (Object[num].RenderTime > 1)
	{
		writeToBuffer(Object[num].Area[0][1],"     ",green);
	}

	if (Object[num].RenderTime > 2)
	{
		writeToBuffer(Object[num].Area[0][2]," ",green);
		writeToBuffer(Object[num].Area[1][2]," ",white);
		writeToBuffer(Object[num].Area[2][2],"   ",green);
	}

	if (Object[num].RenderTime > 3)
	{
		writeToBuffer(Object[num].Area[1][3],"   ",green);
	}

	if (Object[num].RenderTime > 4)
	{
		writeToBuffer(Object[num].Area[1][4],"   ",green);
	}

	if (Object[num].RenderTime > 5)
	{
		writeToBuffer(Object[num].Area[2][5]," ",green);
		writeToBuffer(Object[num].Area[3][5],"  ",d_green);
	}

	if (Object[num].RenderTime > 6)
	{
		writeToBuffer(Object[num].Area[2][6],"  ",d_green);
	}
}

void Render_Pineapple(int num)
{
	if (Object[num].RenderTime > 0)
	{
		writeToBuffer(Object[num].Area[1][0]," ",brown);
		writeToBuffer(Object[num].Area[2][0]," ",yellow);
		writeToBuffer(Object[num].Area[3][0]," ",brown);
	}
	
	if (Object[num].RenderTime > 1)
	{
		writeToBuffer(Object[num].Area[1][1]," ",yellow);
		writeToBuffer(Object[num].Area[2][1]," ",brown);
		writeToBuffer(Object[num].Area[3][1]," ",yellow);
	}

	if (Object[num].RenderTime > 2)
	{
		writeToBuffer(Object[num].Area[1][2]," ",brown);
		writeToBuffer(Object[num].Area[2][2]," ",yellow);
		writeToBuffer(Object[num].Area[3][2]," ",brown);
	}

	if (Object[num].RenderTime > 3)
	{
		writeToBuffer(Object[num].Area[1][3]," ",yellow);
		writeToBuffer(Object[num].Area[2][3]," ",brown);
		writeToBuffer(Object[num].Area[3][3]," ",yellow);
	}

	if (Object[num].RenderTime > 4)
	{
		writeToBuffer(Object[num].Area[2][4]," ",d_green);
	}

	if (Object[num].RenderTime > 5)
	{
		writeToBuffer(Object[num].Area[1][5]," ",d_green);
		writeToBuffer(Object[num].Area[3][5]," ",d_green);
	}
	
	if (Object[num].RenderTime > 6)
	{
		writeToBuffer(Object[num].Area[0][6]," ",d_green);
		writeToBuffer(Object[num].Area[2][6]," ",d_green);
		writeToBuffer(Object[num].Area[4][6]," ",d_green);
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
	writeToBuffer(Rat.Area[2][0]," ",black);
	writeToBuffer(Rat.Area[1][1],"   ",grey);
	writeToBuffer(Rat.Area[1][2]," ",black);
	writeToBuffer(Rat.Area[2][2]," ",grey);
	writeToBuffer(Rat.Area[3][2]," ",black);
	writeToBuffer(Rat.Area[0][3]," ",pink);
	writeToBuffer(Rat.Area[1][3],"   ",grey);
	writeToBuffer(Rat.Area[4][3]," ",pink);
	writeToBuffer(Rat.Area[0][4],"  ",grey);
	writeToBuffer(Rat.Area[3][4],"  ",grey);
}
