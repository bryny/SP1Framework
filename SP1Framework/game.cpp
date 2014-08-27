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
#include <sstream>

// Console size, width by height
COORD ConsoleSize = {80, 59};


double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];


// Game specific variables here
COORD charLocation;

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
    elapsedTime = 0.0;

    initConsole(ConsoleSize, "Fruit Bomb");

    charLocation.X = (ConsoleSize.X - 10) / 2;
    charLocation.Y = ConsoleSize.Y - 2;

    ImplementObjects();

	ImplementLife();
}

void shutdown()
{
    // Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    shutDownConsole();
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
		 charLocation.Y -= 6; 
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
		charLocation.Y +=6;
	}

    if (keyPressed[K_LEFT] && charLocation.X > 0)
    {

		Beep(1440, 30);
		charLocation.X--; 

    }
    if (keyPressed[K_DOWN] && charLocation.Y < ConsoleSize.Y - 1)
    {
        Beep(1440, 30);
        charLocation.Y++; 
    }
    if (keyPressed[K_RIGHT] && charLocation.X < ConsoleSize.X - 29)
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



void render()
{
    // Clears the buffer with this colour attribute
    clearBuffer(0x1F);

    // render time taken to calculate this frame
    gotoXY(70, 0);
    colour(0x1A);
    std::cout << 1.0 / deltaTime << "fps" << std::endl;
  
    gotoXY(0, 0);
    colour(0x59);
    std::cout << elapsedTime << "secs" << std::endl;

    //Jenny : Render Character
	Render_Man();

	//Jeffrey : Render Score System
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

	// Writes the buffer to the console, hence you will see what you have written
    flushBufferToConsole();
}
