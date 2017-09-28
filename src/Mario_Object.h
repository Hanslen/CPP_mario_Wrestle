#pragma once
#include "DisplayableObject.h"
#include "JPGImage.h"

class Demo2Main;

class Mario_Object :
	public DisplayableObject
{
public:
	Mario_Object(BaseEngine* pEngine);
	~Mario_Object();
	void Draw();
	void DoUpdate(int iCurrentTime);
	bool left;
	bool jump;
	int bullet;
	ImageData mario, marioB;
	void KeyDown(int iKeyCode);
	int super;
};

