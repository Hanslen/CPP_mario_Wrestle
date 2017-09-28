#pragma once
#include "DisplayableObject.h"
#include "JPGImage.h"
class Mario_bulletObject :
	public DisplayableObject
{
public:
	Mario_bulletObject(BaseEngine* pEngine, int x, int y, bool left);
	~Mario_bulletObject();
	void Draw();
	ImageData fireBullet, fireBullet2,explosion;
	void DoUpdate(int iCurrentTime);
	int posX;
	int posY;
	bool posLeft;
	int getPosX();
	int over;
	static int superbullet;
};

