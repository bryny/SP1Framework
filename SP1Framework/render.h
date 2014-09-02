#ifndef _RENDER_H
#define _RENDER_H

#include <string>
using std :: string;
//Shannon : Object Render
void Render_Apple(int num);
void Render_Bomb(int num);
void Render_Cherry(int num);
void Render_Banana(int num);
void Render_Orange(int num);
void Render_Pear(int num);
void Render_Pineapple(int num);

void over();

void Render_Menuapple(COORD MEnu);
void Render_Menubomb(COORD MEnu);
void Render_Menurat(COORD MEnu);
void Render_Menuman(COORD MEnu);

//Jenny : Player Render
void Render_Man();

//Jenny : Rat Render
void Render_Rat();

#endif // _RENDER_H