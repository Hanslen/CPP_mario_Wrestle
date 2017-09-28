#pragma once
#include "DisplayableObject.h"

class Demo2Main;

class Psyjc3_1Object :
	public DisplayableObject
{
public:
	Psyjc3_1Object(BaseEngine* pEngine);
	~Psyjc3_1Object(void);
	void Draw();
	void DoUpdate(int iCurrentTime);
};

