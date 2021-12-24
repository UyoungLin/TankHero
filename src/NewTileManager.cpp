#include "header.h"
#include "NewTileManager.h"

NewTileManager::NewTileManager()
	: TileManager(50, 50)
{
	wall1 = ImageManager::loadImage("images/wall1.png", true);
	wall2 = ImageManager::loadImage("images/wall2.png", true);
	grass1 = ImageManager::loadImage("images/grass1.png", true);
	tree1 = ImageManager::loadImage("images/tree1.png", true);
	ice1 = ImageManager::loadImage("images/ice1.png", true);
	button = ImageManager::loadImage("images/button.png", true);
	tunnel = ImageManager::loadImage("images/tunnel.png", true);
}

void NewTileManager::virtDrawTileAt(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY, int iStartPositionScreenX, int iStartPositionScreenY) const
{
	switch (getMapValue(iMapX, iMapY))
	{
	case 0:
		grass1.renderImage(pSurface, 0, 0, 
			iStartPositionScreenX, iStartPositionScreenY,
			getTileWidth(), getTileHeight());
		break;
	case 1:
		wall1.renderImage(pSurface, 0, 0,
			iStartPositionScreenX, iStartPositionScreenY,
			getTileWidth(), getTileHeight());
		break;
	case 2:
		grass1.renderImage(pSurface, 0, 0,
			iStartPositionScreenX, iStartPositionScreenY,
			getTileWidth(), getTileHeight());
		tree1.renderImageWithMask(pSurface, 0, 0,
			iStartPositionScreenX, iStartPositionScreenY,
			getTileWidth(), getTileHeight());
		break;
	case 3:
		button.renderImageWithMask(pSurface, 0, 0,
			iStartPositionScreenX, iStartPositionScreenY,
			getTileWidth(), getTileHeight());
		break;
	case 4:
		grass1.renderImage(pSurface, 0, 0,
			iStartPositionScreenX, iStartPositionScreenY,
			getTileWidth(), getTileHeight());
		tunnel.renderImageWithMask(pSurface, 0, 0,
			iStartPositionScreenX, iStartPositionScreenY,
			getTileWidth(), getTileHeight());
		break;
	case 5:
		ice1.renderImage(pSurface, 0, 0,
			iStartPositionScreenX, iStartPositionScreenY,
			getTileWidth(), getTileHeight());
		break;
	case 6:
		wall2.renderImage(pSurface, 0, 0,
			iStartPositionScreenX, iStartPositionScreenY,
			getTileWidth(), getTileHeight());
		break;
	case 7:
		ice1.renderImage(pSurface, 0, 0,
			iStartPositionScreenX, iStartPositionScreenY,
			getTileWidth(), getTileHeight());
		tree1.renderImageWithMask(pSurface, 0, 0,
			iStartPositionScreenX, iStartPositionScreenY,
			getTileWidth(), getTileHeight());
		break;
	case 8:
		button.renderImageWithMask(pSurface, 0, 0,
			iStartPositionScreenX, iStartPositionScreenY,
			getTileWidth(), getTileHeight());
		break;
	case 9:
		ice1.renderImage(pSurface, 0, 0,
			iStartPositionScreenX, iStartPositionScreenY,
			getTileWidth(), getTileHeight());
		tunnel.renderImageWithMask(pSurface, 0, 0,
			iStartPositionScreenX, iStartPositionScreenY,
			getTileWidth(), getTileHeight());
		break;
	}
}

NewTileManager::~NewTileManager()
{
}
