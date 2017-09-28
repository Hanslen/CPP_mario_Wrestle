#pragma once
#include "DisplayableObject.h"
#include "JPGImage.h"

class Tortoise_Object :
	public DisplayableObject
{
public:
	Tortoise_Object(BaseEngine* pEngine);
	~Tortoise_Object();
	void Draw();
	ImageData tortoise, tortoise2;
	ImageData subTortoise1, subTortoise;
	int left;
	bool up;
	bool fly;
	bool direction; //0 for left, 1 for right
	static int hasSub;
	static int subX;
	static int canJump;
	int subY;
	static int subOver;
	static int wantJump;
	void DoUpdate(int iCurrentTime);

private:
	int action;
	int randAction;
	int size;
	int rotate_val;
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveShake();
	void moveFly();
	void moveBig();
	void moveSmall();
	void moveRocket();
};

