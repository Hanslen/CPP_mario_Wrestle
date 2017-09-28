#pragma once
#include "DisplayableObject.h"
#include "JPGImage.h"

class welcomeMario :
	public DisplayableObject
{
public:
	welcomeMario(BaseEngine* pEngine);
	~welcomeMario();
	void Draw();
	void DoUpdate(int iCurrentTime);
private:
	ImageData drive;
	int right;
};

