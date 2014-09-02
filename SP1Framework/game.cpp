// This is the main file for the game logic and function
//
//
#include "game.h"
#include "objects.h"
#include "systems.h"
#include "highscore.h"
#include "Framework\console.h"
#include "render.h"
#include <iostream>   
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>

// Console size, width by height
COORD ConsoleSize = {80, 59};

int delay = 0;
int arrowX[6]={0,17,19,17,23,27};
int arrowY[6]={0,28,31,34,37,40};
int lockdown = 0;
int change = 1;
double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];
StopWatch Mg_timer;

// Game specific variables here
COORD charLocation;

//Shannon : Jump function
enum jumpability
{
	ENABLED
};
int jump = ENABLED; //Shannon : Sets whether player can jump
int jumptime = 20; //Shannon : Number of frames player will float after jumping

int statechange = 0;

void init()
{
    // Set precision for floating point output
    elapsedTime = 0.0;

    initConsole(ConsoleSize, "Fruit Bomb");

	// Sets Character's starting coordinates
    charLocation.X = (ConsoleSize.X - 10) / 2;
    charLocation.Y = ConsoleSize.Y - 2;
	
	//Shannon : Initializes Objects
    ImplementObjects();

	//Shannon : Initializes Life System
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
	keyPressed[K_RETURN] = isKeyPressed(VK_RETURN);
	//keyPressed[K_UP] = isKeyPressed(65) => Pressing 'A' = Up
	//'A' ~ 'Z' = 65~90
}

void update(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;
	if(statechange == 0)
	{
		
		if (keyPressed[K_UP] && change > 1&& delay == 0)
		{
			
			change -= 1;
			gotoXY(arrowX[change],arrowY[change]);
			delay = 15;

		}
		if (keyPressed[K_DOWN]&& change < 5 && delay == 0)
		{
			change += 1;
			gotoXY(arrowX[change],arrowY[change]);
			delay = 15;

		}
		if (keyPressed[K_RETURN]&& change != 0)
		{
			statechange = change;
		}
		if(delay > 0)
		{
			--delay;
		}
		
	}
	if (statechange == 5)
	{
	g_quitGame = true;   
	}

	if (statechange == 4||statechange == 3)
	{
		if (keyPressed[K_ESCAPE])
		{
			statechange = 0;
		}
	}

	if(statechange == 1)
	{
	// quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
        g_quitGame = true;    

	//Shannon : Game will continue updating as long as the player has 1 Life
	if (Life.Value < 0)
	{
		return;
	}

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
		charLocation.X--;
    }
    if (keyPressed[K_DOWN] && charLocation.Y < ConsoleSize.Y - 1)
    {
        charLocation.Y++; 
    }
    if (keyPressed[K_RIGHT] && charLocation.X < ConsoleSize.X - 29)
    {
        charLocation.X++; 
    }
	
	//Shannon : Updates the level based on LevelCounter
	UpdateLevel();

	//Yi Yang : Updates the level difficulty based on difficultyEnum and Level
	updateDifficulty();

	//Shannon : Updates the objects & rats for coordinates and collision detection
	UpdateObjects();
	UpdateRat();

	//Shannon : Create Objects
	CreateObjects();

	//Shannon : Updates Level Timer
	UpdateLvTimer();   
}
}


void render()
{
    // Clears the buffer with this colour attribute
    clearBuffer(0x1F);
	if(statechange == 0)
	{
		rendermenu();
		renderarrow();
		COORD MEnua;
		COORD MEnub;
		COORD MEnur;
		COORD MEnum;
     	MEnua.X = 5;
	    MEnua.Y = 30;
		Render_Menuapple(MEnua);
		MEnua.X = 71;
	    MEnua.Y = 5;
		Render_Menuapple(MEnua);
		MEnub.X = 3;
	    MEnub.Y = 13;
		Render_Menubomb(MEnub);
		MEnub.X = 71;
	    MEnub.Y = 34;
		Render_Menubomb(MEnub);
		MEnur.X = 51;
	    MEnur.Y = 51;
		Render_Menurat(MEnur);
		MEnum.X = 35;
		MEnum.Y = 46;
		Render_Menuman(MEnum);
		flushBufferToConsole();
	}
	if(statechange == 4)
	{
		credits();
				COORD MEnua;
		COORD MEnub;
		COORD MEnur;
		COORD MEnum;
     	MEnua.X = 40;
	    MEnua.Y = 16;
		Render_Menuapple(MEnua);
		MEnua.X = 48;
	    MEnua.Y = 31;
		Render_Menuapple(MEnua);
		MEnub.X = 45;
	    MEnub.Y = 9;
		Render_Menubomb(MEnub);
		MEnub.X = 53;
	    MEnub.Y = 23;
		Render_Menubomb(MEnub);
		MEnub.X = 43;
	    MEnub.Y = 40;
		Render_Menubomb(MEnub);
		MEnur.X = 60;
	    MEnur.Y = 51;
		Render_Menurat(MEnur);
		MEnum.X = 24;
		MEnum.Y = 46;
		Render_Menuman(MEnum);
		flushBufferToConsole();
	}
	if(statechange == 3)
	{
		sblayout();
	    score = 0;
		scoreboard(score);
        flushBufferToConsole();
	}

	if(statechange == 1)
	{
	//Jenny : if there's life, render; else render leaderboard
	if (Life.Value == 3 || Life.Value > 0)
	{
    // render time taken to calculate this frame
	COORD F_P_S = {66,0};
	std::string FPS_String = std::to_string(static_cast<long double>(1.0 / deltaTime)) + "fps";
	writeToBuffer(F_P_S,FPS_String);

	// elapsed running time of file
	COORD EL_TIME = {0,0};
	std::string TIME_String = std::to_string(static_cast<long double>(elapsedTime)) + "secs";
	writeToBuffer(EL_TIME,TIME_String);
	
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
	}

	else if (Life.Value == 0)
	{
		clearBuffer();
		scoreboard(score);
		int statechange = 0;
		int lockdown = 1;
		//returnmenu(statechange);
	}
	
	// Writes the buffer to the console, hence you will see what you have written
    flushBufferToConsole();
}
}