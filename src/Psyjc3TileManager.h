#pragma once
#include "TileManager.h"
class Psyjc3TileManager :
	public TileManager
{
public:
	Psyjc3TileManager();
	~Psyjc3TileManager();
	virtual void DrawTileAt(
		BaseEngine* pEngine,
		SDL_Surface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY);
};

