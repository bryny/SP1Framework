#ifndef _SYSTEMS_H
#define _SYSTEMS_H

#include "objects.h"
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>

//Life System
struct System //Shannon : System Struct Draft
{
	int Value;
	COORD Location[3];
};
extern System Life; //Shannon : Life System
void ImplementLife();
void RenderLife();

//Score System
extern unsigned long long score;
void displayscore();

#endif // _SYSTEMS_H