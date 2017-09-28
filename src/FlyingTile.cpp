#include "header.h"
#include "FlyingTile.h"


/*
	Flying tiles are flying flowers, they flash all the time
*/
FlyingTile::FlyingTile()
	: TileManager(50, 50)
{
}


FlyingTile::~FlyingTile()
{
}



void FlyingTile::DrawTileAt(
	BaseEngine* pEngine,
	SDL_Surface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	ImageData im1, im;
	/*
		the following code works for the flashing
	*/
	switch (rand()%2)
	{
	case 0:
		im1.LoadImage("img/block.png");
		im.ShrinkFrom(&im1, 2);
		im.RenderImageWithMask(pEngine->GetBackground(), 0, 0, iStartPositionScreenX, iStartPositionScreenY, im.GetWidth(), im.GetHeight());
		im1.LoadImage("img/flowernew.png");
		im.ShrinkFrom(&im1, 2);
		im.RenderImageWithMask(pEngine->GetBackground(), 0, 0, iStartPositionScreenX, iStartPositionScreenY, im.GetWidth(), im.GetHeight());

		break;
	case 1:
		im1.LoadImage("img/block.png");
		im.ShrinkFrom(&im1, 2);
		im.RenderImageWithMask(pEngine->GetBackground(), 0, 0, iStartPositionScreenX, iStartPositionScreenY, im.GetWidth(), im.GetHeight());
		im1.LoadImage("img/flowernew.png");
		im.ShrinkFrom(&im1, 3);
		im.RenderImageWithMask(pEngine->GetBackground(), 0, 0, iStartPositionScreenX, iStartPositionScreenY, im.GetWidth(), im.GetHeight());

		break;
	}
}

