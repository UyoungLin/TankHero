#pragma once
#include "TileManager.h"

class NewTileManager :
    public TileManager
{
public:
    NewTileManager();

    virtual void virtDrawTileAt(
        BaseEngine* pEngine,
        DrawingSurface* pSurface,
        int iMapX, int iMapY,
        int iStartPositionScreenX, int iStartPositionScreenY) const override;

    ~NewTileManager();

private:
    SimpleImage wall1;
    SimpleImage wall2;
    SimpleImage grass1;
    SimpleImage tree1;
    SimpleImage ice1;
    SimpleImage button;
    SimpleImage tunnel;
};

