#include <iostream>
#include <iomanip>
#include "game.h"
#include "Framework\console.h"
#include "render.h"
#include "objects.h"

//Shannon : Simplifying the colour creation
void black(int num)
{
	colour(0);
	for (int number = 0; number < num; ++number)
	{
		std::cout << " ";
	}
}
void d_blue(int num)
{
	colour(16);
	for (int number = 0; number < num; ++number)
	{
		std::cout << " ";
	}
};
void d_green(int num)
{
	colour(32);
	for (int number = 0; number < num; ++number)
	{
		std::cout << " ";
	}
};
void d_cyan(int num)
{
	colour(48);
	for (int number = 0; number < num; ++number)
	{
		std::cout << " ";
	}
};
void d_red(int num)
{
	colour(64);
	for (int number = 0; number < num; ++number)
	{
		std::cout << " ";
	}
};
void purple(int num)
{
	colour(80);
	for (int number = 0; number < num; ++number)
	{
		std::cout << " ";
	}
};
void brown(int num)
{
	colour(96);
	for (int number = 0; number < num; ++number)
	{
		std::cout << " ";
	}
};
void grey(int num)
{
	colour(112);
	for (int number = 0; number < num; ++number)
	{
		std::cout << " ";
	}
};
void d_grey(int num)
{
	colour(128);
	for (int number = 0; number < num; ++number)
	{
		std::cout << " ";
	}
};
void blue(int num)
{
	colour(144);
	for (int number = 0; number < num; ++number)
	{
		std::cout << " ";
	}
};
void green(int num)
{
	colour(160);
	for (int number = 0; number < num; ++number)
	{
		std::cout << " ";
	}
};
void cyan(int num)
{
	colour(176);
	for (int number = 0; number < num; ++number)
	{
		std::cout << " ";
	}
};
void red(int num)
{
	colour(192);
	for (int number = 0; number < num; ++number)
	{
		std::cout << " ";
	}
};
void pink(int num)
{
	colour(208);
	for (int number = 0; number < num; ++number)
	{
		std::cout << " ";
	}
};
void yellow(int num)
{
	colour(224);
	for (int number = 0; number < num; ++number)
	{
		std::cout << " ";
	}
};
void white(int num)
{
	colour(240);
	for (int number = 0; number < num; ++number)
	{
		std::cout << " ";
	}
};

//Shannon : Final Render

//Render apple from bottom to top
void Render_Apple(int num)
{
	gotoXY(Object[num].LeftSide[0].X + 1,Object[num].LeftSide[0].Y);
	red(3);
	
	gotoXY(Object[num].LeftSide[1]);
	red(5);

	gotoXY(Object[num].LeftSide[2]);
	red(5);

	gotoXY(Object[num].LeftSide[3]);
	red(1);
	white(1);
	red(3);

	gotoXY(Object[num].LeftSide[4].X + 1,Object[num].LeftSide[4].Y);
	red(3);

	gotoXY(Object[num].LeftSide[5].X + 2,Object[num].LeftSide[5].Y);
	d_green(3);

	gotoXY(Object[num].LeftSide[6].X + 3,Object[num].LeftSide[6].Y);
	d_green(2);
}

void Render_Bomb(int num)
{
	gotoXY(Object[num].LeftSide[0].X + 1,Object[num].LeftSide[0].Y);
	black(3);
	
	gotoXY(Object[num].LeftSide[1]);
	black(5);

	gotoXY(Object[num].LeftSide[2]);
	black(5);

	gotoXY(Object[num].LeftSide[3]);
	black(1);
	white(1);
	black(3);

	gotoXY(Object[num].LeftSide[4].X + 1,Object[num].LeftSide[4].Y);
	black(3);

	gotoXY(Object[num].LeftSide[5].X + 2,Object[num].LeftSide[5].Y);
	red(1);
	gotoXY(Object[num].LeftSide[5].X + 4,Object[num].LeftSide[5].Y);
	yellow(1);

	gotoXY(Object[num].LeftSide[6].X + 2,Object[num].LeftSide[6].Y);
	red(1);
	brown(1);
}

void Render_Cherry(int num)
{
	gotoXY(Object[num].LeftSide[0]);
	red(3);
	gotoXY(Object[num].LeftSide[0].X + 4,Object[num].LeftSide[0].Y);
	red(3);
	
	gotoXY(Object[num].LeftSide[1]);
	red(3);
	gotoXY(Object[num].LeftSide[1].X + 4,Object[num].LeftSide[1].Y);
	red(3);

	gotoXY(Object[num].LeftSide[2]);
	red(1);
	d_red(1);
	red(1);
	gotoXY(Object[num].LeftSide[2].X + 4,Object[num].LeftSide[2].Y);
	red(1);
	d_red(1);
	red(1);

	gotoXY(Object[num].LeftSide[3].X + 2,Object[num].LeftSide[3].Y);
	d_red(1);
	gotoXY(Object[num].LeftSide[3].X + 4,Object[num].LeftSide[3].Y);
	d_red(1);

	gotoXY(Object[num].LeftSide[4]);
	d_green(1);
	gotoXY(Object[num].LeftSide[4].X + 3,Object[num].LeftSide[4].Y);
	d_red(1);
	gotoXY(Object[num].LeftSide[4].X + 6,Object[num].LeftSide[4].Y);
	d_green(1);

	gotoXY(Object[num].LeftSide[5]);
	d_green(2);
	gotoXY(Object[num].LeftSide[5].X + 3,Object[num].LeftSide[5].Y);
	d_red(1);
	gotoXY(Object[num].LeftSide[5].X + 5,Object[num].LeftSide[5].Y);
	d_green(2);

	gotoXY(Object[num].LeftSide[6].X + 1,Object[num].LeftSide[6].Y);
	d_green(2);
	gotoXY(Object[num].LeftSide[6].X + 4,Object[num].LeftSide[6].Y);
	d_green(2);
}

void Render_Banana(int num)
{
	gotoXY(Object[num].LeftSide[0].X + 2,Object[num].LeftSide[0].Y);
	yellow(3);
	
	gotoXY(Object[num].LeftSide[1]);
	brown(1);
	yellow(5);

	gotoXY(Object[num].LeftSide[2].X + 3,Object[num].LeftSide[2].Y);
	yellow(3);

	gotoXY(Object[num].LeftSide[3].X + 4,Object[num].LeftSide[3].Y);
	yellow(2);

	gotoXY(Object[num].LeftSide[4].X + 4,Object[num].LeftSide[4].Y);
	yellow(2);

	gotoXY(Object[num].LeftSide[5].X + 4,Object[num].LeftSide[5].Y);
	yellow(1);

	gotoXY(Object[num].LeftSide[6].X + 3,Object[num].LeftSide[6].Y);
	brown(3);
}

void Render_Orange(int num)
{
	gotoXY(Object[num].LeftSide[0].X + 1,Object[num].LeftSide[0].Y);
	brown(3);
	
	gotoXY(Object[num].LeftSide[1]);
	brown(5);

	gotoXY(Object[num].LeftSide[2]);
	brown(5);

	gotoXY(Object[num].LeftSide[3]);
	brown(1);
	white(1);
	brown(3);

	gotoXY(Object[num].LeftSide[4].X + 1,Object[num].LeftSide[4].Y);
	brown(3);

	gotoXY(Object[num].LeftSide[5].X + 2,Object[num].LeftSide[5].Y);
	d_green(3);

	gotoXY(Object[num].LeftSide[6].X + 3,Object[num].LeftSide[6].Y);
	d_green(2);
}

void Render_Pear(int num)
{
	gotoXY(Object[num].LeftSide[0].X + 1,Object[num].LeftSide[0].Y);
	green(3);
	
	gotoXY(Object[num].LeftSide[1]);
	green(5);

	gotoXY(Object[num].LeftSide[2]);
	green(1);
	white(1);
	green(3);

	gotoXY(Object[num].LeftSide[3].X + 1,Object[num].LeftSide[0].Y);
	green(3);

	gotoXY(Object[num].LeftSide[4].X + 1,Object[num].LeftSide[4].Y);
	green(3);

	gotoXY(Object[num].LeftSide[5].X + 2,Object[num].LeftSide[5].Y);
	green(1);
	d_green(2);

	gotoXY(Object[num].LeftSide[6].X + 2,Object[num].LeftSide[6].Y);
	d_green(2);
}

void Render_Pineapple(int num)
{
	gotoXY(Object[num].LeftSide[0].X + 1,Object[num].LeftSide[0].Y);
	brown(1);
	yellow(1);
	brown(1);
	
	gotoXY(Object[num].LeftSide[1].X + 1,Object[num].LeftSide[1].Y);
	yellow(1);
	brown(1);
	yellow(1);

	gotoXY(Object[num].LeftSide[2].X + 1,Object[num].LeftSide[2].Y);
	brown(1);
	yellow(1);
	brown(1);

	gotoXY(Object[num].LeftSide[3].X + 1,Object[num].LeftSide[3].Y);
	yellow(1);
	brown(1);
	yellow(1);

	gotoXY(Object[num].LeftSide[4].X + 2,Object[num].LeftSide[4].Y);
	d_green(1);

	gotoXY(Object[num].LeftSide[5].X + 1,Object[num].LeftSide[5].Y);
	d_green(1);
	gotoXY(Object[num].LeftSide[5].X + 3,Object[num].LeftSide[5].Y);
	d_green(1);
	
	gotoXY(Object[num].LeftSide[6]);
	d_green(1);
	gotoXY(Object[num].LeftSide[6].X + 2,Object[num].LeftSide[6].Y);
	d_green(1);
	gotoXY(Object[num].LeftSide[6].X + 4,Object[num].LeftSide[6].Y);
	d_green(1);
}