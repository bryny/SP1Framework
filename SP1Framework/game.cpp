// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>

struct System //Shannon : Struct Draft
{
	int Value;
	COORD Location[3];
};
struct Object //Shannon : Object Struct Draft
{
	COORD Location;
	int State;
};
enum ObjectState //Shannon : State of Objects
{
	UNCREATED,
	CREATED,
	RECYCLED
};
System Life; //Shannon : Life System
Object Apple[10]; //Shannon : Apples
Object Bomb; //Shannon : Bombs
double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];
COORD charLocation;
COORD consoleSize;
COORD enemyLocation[3]; //Shannon : Dummy Enemies
COORD ObjectStart; //Shannon : Object Starting Location
int Number; //Shannon : Test
int timer; //Shannon : A timer for when objects move

void init()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set the character to be in the center of the screen.
    charLocation.X = consoleSize.X / 2;
    charLocation.Y = consoleSize.Y / 2;

	//Shannon : Implement Dummy Enemies
	for (int i = 0; i < 3; ++i)
	{
		enemyLocation[i].X = consoleSize.X - 2*(i+1);
		enemyLocation[i].Y = consoleSize.Y - 2*(i+1);
	}

	//Shannon : Implement Life System
	Life.Value = 3;
	for (int i = 0; i < 3; ++i)
	{
		Life.Location[i].X = consoleSize.X - 2*(i+1);
		Life.Location[i].Y = consoleSize.Y - 20;
	}

	// Shannon : Implement Objects starting Location
	for (int i = 0; i < 10; ++i)
	{
	Apple[i].State = UNCREATED;
	}
	int Number = 0;
	// Shannon : Implement Object timer countdown
	int timer = 5;

    elapsedTime = 0.0;
}

void shutdown()
{
    // Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void getInput()
{    
    keyPressed[K_UP] = isKeyPressed(VK_UP);
    keyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
    keyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
    keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
    keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
}

void update(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

    // Updating the location of the character based on the key press
    if (keyPressed[K_UP] && charLocation.Y > 0)
    {
        Beep(1440, 30);
        charLocation.Y--; 
    }
    if (keyPressed[K_LEFT] && charLocation.X > 0)
    {
        Beep(1440, 30);
        charLocation.X--; 
    }
    if (keyPressed[K_DOWN] && charLocation.Y < consoleSize.Y - 1)
    {
        Beep(1440, 30);
        charLocation.Y++; 
    }
    if (keyPressed[K_RIGHT] && charLocation.X < consoleSize.X - 1)
    {
        Beep(1440, 30);
        charLocation.X++; 
    }
	
	
	// Shannon Touching an enemy results in losing life and removal of enemy
	for (int i = 0; i < 3; ++i)
	{
		if (charLocation.X == enemyLocation[i].X && charLocation.Y == enemyLocation[i].Y)
		{
			--Life.Value;
			enemyLocation[i].X = 0;
			enemyLocation[i].Y = 0;
		}
	}
		//Shannon timer decrease
	if (timer != 0)
	{
		--timer;
	}
	//Only works on timer
	else if (timer == 0)
	{
		timer = 5;
		//Shannon : Objects randomly appear based on starting location
		if (Number < 10)
		{
			ObjectStart.X = rand() % 50;
			if (Apple[Number].State == UNCREATED)
			{
				Apple[Number].Location.X = ObjectStart.X;
				Apple[Number].Location.Y = 0;
				Apple[Number].State = CREATED;
			}
		}
		++Number;
		if (Number == 10)
		{
			Number = 0;
		}
	

	
	//	Shannon : Objects slowly descend to player
		for (int ii = 0; ii < 10; ++ii)
		{
			if (Apple[ii].State == CREATED)
			{
				if (Apple[ii].Location.Y < consoleSize.Y - 1)
				{
					Apple[ii].Location.Y++ ;
				}
			}
			


		}
	}
	//When objects reach the end or touch the player
	for (int ii = 0; ii < 10; ++ii)
	{
				if (Apple[ii].Location.Y == consoleSize.Y - 1)
			{
				Apple[ii].Location.X = ObjectStart.X;
				Apple[ii].Location.Y = 0;
			}
			else if (charLocation.X == Apple[ii].Location.X && charLocation.Y == Apple[ii].Location.Y)
		{
			Apple[ii].Location.X = ObjectStart.X;
			Apple[ii].Location.Y = 0;
		}
	}
    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
        g_quitGame = true;    
}

void render()
{
    // clear previous screen
    colour(0x0F);
    cls();

    //render the game

    //render test screen code (not efficient at all)
    const WORD colors[] =   {
	                        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
	                        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
	                        };
	
	for (int i = 0; i < 12; ++i)
	{
		gotoXY(3*i,i+1);
		colour(colors[i]);
		std::cout << "WOW";
	}

    // render time taken to calculate this frame
    gotoXY(70, 0);
    colour(0x1A);
    std::cout << 1.0 / deltaTime << "fps" << std::endl;
  
    gotoXY(0, 0);
    colour(0x59);
    std::cout << elapsedTime << "secs" << std::endl;

    // render character
    gotoXY(charLocation);
    colour(0x0C);
    std::cout << (char)1;

	// Shannon : Render Enemy
	for (int i = 0; i < 3; ++i)
	{
			gotoXY(enemyLocation[i]);
			colour(0x1A);
			std::cout <<(char)1;
	}

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

    	// render objects
	for (int i = 0; i < 10; ++i)
	{
		gotoXY(Apple[i].Location);
		colour(0x0C);
		std::cout << (char)65+i;
	}
}
