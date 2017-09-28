#pragma once
#include "DisplayableObject.h"
#include "JPGImage.h"
class SelectMashroom :
	public DisplayableObject
{
public:
	SelectMashroom(BaseEngine* pEngin);
	~SelectMashroom();
private:
	ImageData mushroom, mushroom1;
	int mushRoompos;
public:
	void Draw();
	void DoUpdate(int iCurrentTime);
};

