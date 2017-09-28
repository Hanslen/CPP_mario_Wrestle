#pragma once
#include "DisplayableObject.h"
#include "JPGImage.h"
class DamageMushroom :
	public DisplayableObject
{
private:
	ImageData mushroom, mushroom1;
public:
	DamageMushroom(BaseEngine* pEngin);
	int mushRoomOver;
	~DamageMushroom();
public:
	void Draw();
	void DoUpdate(int iCurrentTime);
};

