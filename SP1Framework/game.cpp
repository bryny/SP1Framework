// This is the main file for the game logic and function
//
//
#include "game.h"
#include "objects.h"
#include "systems.h"
#include "Framework\console.h"
#include "render.h"
#include <iostream>
#include <iomanip>


double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];
COORD charLocation;
COORD consoleSize;

//Shannon : Jump function
enum jumpability
{
	ENABLED
};
int jump = ENABLED; //Shannon : Sets whether player can jump
int jumptime = 5; //Shannon : Number of frames player will float after jumping

void init()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

	SetConsoleTitle(L"Fruit Bomb");

	// Sets the console size, this is the biggest so far.
	setConsoleSize(79, 58);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set the character to be in the center of the screen.
    charLocation.X = (consoleSize.X - 10) / 2;
    charLocation.Y = consoleSize.Y - 2;// Mr Sim's

	ImplementObjects();

	ImplementLife();


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
	//keyPressed[K_UP] = isKeyPressed(65) => Pressing 'A' = Up
	//'A' ~ 'Z' = 65~90
}

void update(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

	//Shannon : If the player has 0 lives, game stops
	if (Life.Value > 0)
	{

	// Updating the location of the character based on the key press

	//Shannon : If the player is on the ground (jump == 0 || ENABLED), jumping is enabled
    if (keyPressed[K_UP] && charLocation.Y > 0 && jump == ENABLED)
    {
		 Beep(1440, 30);
		 charLocation.Y-= 6; 
		 jump = jumptime;
    }
	//Shannon : Player will stay in the air for number of frames of jumptime
	if (jump > 0)
	{
		--jump;
	}
	//Shannon : Player will fall just before jumping is enabled again
	if (jump == 1)
	{
		charLocation.Y+=6;
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
    if (keyPressed[K_RIGHT] && charLocation.X < consoleSize.X - 29)
    {
        Beep(1440, 30);
        charLocation.X++; 
    }
	
	
	//Shannon : Updates the level based on LevelCounter
	UpdateLevel();

	//Yi Yang : Updates the level difficulty base on difficultyEnum and Level
	updateDifficulty();

	//Shannon : Updates the objects & rats for coordinates and collision detection
	UpdateObjects();
	UpdateRat();

	//Shannon : Update Level Timer
	UpdateLvTimer();

	} //Shannon : End of Life Detection


    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
        g_quitGame = true;    
}

//Jenny : print man
void man()
{
	gotoXY(charLocation.X, charLocation.Y-11);
	grey(1);
	gotoXY(charLocation.X+10, charLocation.Y-11);
	grey(1);
	
	gotoXY(charLocation.X, charLocation.Y-10);
	grey(1);
	gotoXY(charLocation.X+10, charLocation.Y-10);
	grey(1);
	
	gotoXY(charLocation.X, charLocation.Y-9);
	grey(11);

	gotoXY(charLocation.X, charLocation.Y-8);
	d_red(1);
	grey(9);
	
	//Head
	gotoXY(charLocation.X, charLocation.Y-7);
	d_red(2);
	gotoXY(charLocation.X+3, charLocation.Y-7);
	d_red(5);
	
	gotoXY(charLocation.X+1, charLocation.Y-6);
	d_red(1);
	gotoXY(charLocation.X+3, charLocation.Y-6);
	d_red(1);
	black(1);
	d_red(1);
	black(1);
	d_red(1);

	gotoXY(charLocation.X+1, charLocation.Y-5);
	d_red(1);
	gotoXY(charLocation.X+3, charLocation.Y-5);
	d_red(1);
	black(1);
	d_red(1);
	black(1);
	d_red(1);

	gotoXY(charLocation.X+1, charLocation.Y-4);
	d_red(1);
	blue(1);
	pink(1);
	d_red(3);
	pink(1);
	blue(1);
	d_red(1);

	gotoXY(charLocation.X+1, charLocation.Y-3);
	d_red(1);
	blue(1);
	d_red(2);
	red(1);
	d_red(2);
	blue(1);
	d_red(1);
	
	//Shirt
	gotoXY(charLocation.X+3, charLocation.Y-2);
	blue(5);

	gotoXY(charLocation.X+9, charLocation.Y-2);
	d_red(1);
	
	//Pants
	gotoXY(charLocation.X+4, charLocation.Y-1);
	black(3);

	gotoXY(charLocation.X+9, charLocation.Y-1);
	d_red(2);

	//Feet
	gotoXY(charLocation.X+3, charLocation.Y);
	d_red(2);

	gotoXY(charLocation.X+6, charLocation.Y);
	d_red(2);
}

void render()
{
    // clear previous screen
    colour(0x3C);
    cls();

    // render time taken to calculate this frame
    gotoXY(70, 0);
    colour(0x1A);
    std::cout << 1.0 / deltaTime << "fps" << std::endl;
  
    gotoXY(0, 0);
    colour(0x59);
    std::cout << elapsedTime << "secs" << std::endl;

    //Jenny : render character
    gotoXY(charLocation.X, charLocation.Y-59);
	man();

	//Shannon : Render Score System
	displayscore();

	//Shannon : Render Objects & Rat
   	RenderObjects();

	//Shannon : Render Life System
	RenderLife();

	//Jenny: Render border
	RenderBorder();

	//Shannon : Render Level System
	RenderLevel();

	//Shannon : Render Level Timer
	RenderLvTimer();
}
