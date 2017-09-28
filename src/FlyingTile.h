#pragma once
#include "TileManager.h"
#include "JPGImage.h"
class FlyingTile :
	public TileManager
{
public:
	FlyingTile();
	~FlyingTile();
	virtual void DrawTileAt(
		BaseEngine* pEngine,
		SDL_Surface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const;

public:
	void changeFlowerSize();
};

