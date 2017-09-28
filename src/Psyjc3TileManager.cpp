#include "header.h"
#include "templates.h"
#include "Psyjc3TileManager.h"


Psyjc3TileManager::Psyjc3TileManager()
	: TileManager(40, 40)
{
}


Psyjc3TileManager::~Psyjc3TileManager()
{
}

void Psyjc3TileManager::DrawTileAt(
	BaseEngine* pEngine,
	SDL_Surface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY)
{
	pEngine->DrawOval(
		iStartPositionScreenX,
		iStartPositionScreenY,
		iStartPositionScreenX + GetTileWidth() - 1,
		iStartPositionScreenY + GetTileHeight() - 1,
		pEngine->GetColour(GetValue(iMapX, iMapY)),
		pSurface);
}
