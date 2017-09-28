#include "header.h"
#include "templates.h"
#include "bloodObject.h"
#include "Mario_bulletObject.h"
#include "DemoAMain.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

/*
	This class is for displaying the blood block.
*/
bloodObject::bloodObject(BaseEngine* pEngine, int x)
	: DisplayableObject(pEngine),
	decreaseBlood(0)
	, xPos(x)
{
}


bloodObject::~bloodObject()
{
}


void bloodObject::Draw()
{
	this->GetEngine()->DrawScreenRectangle(xPos, 460, xPos + 300 - decreaseBlood , 485, 0xff0000);
}


void bloodObject::DoUpdate(int changeBlood)
{
	/*
		Tortoise blood decrease
	*/
	if (changeBlood == 10){
		decreaseBlood += 10;
		/*
			If superbullet equals to 1, that means the Mario becomes the super hero, the damage of attack increases,
			else, that means it was a common attack.
		*/
		if (Mario_bulletObject::superbullet == 1){
			decreaseBlood += 10;
		}
		RedrawObjects();
	}
	/*
		Mario blood decrease
	*/
	if (changeBlood == 20){
		decreaseBlood += 50;
		RedrawObjects();
	}

	/*
		If the blood is less or equal than zero, means that Object dies, so we finishes the game, and sets the winner.
	*/
	if ((300 - decreaseBlood) < 1){
		DemoAMain::state_init = 4;
		if (changeBlood == 10){
			DemoAMain::winner = 0;
		}
		else{
			DemoAMain::winner = 1;
		}
	}
}
