#include "header.h"
#include "InfoState.h"

InfoState::InfoState(Scyyl7Engine* pEngine)
	: m_engine(pEngine), base()
	, bg(ImageManager::loadImage("images/info.png", true))
	, ghost(ImageManager::loadImage("images/ghost.png", true))
	, mons(ImageManager::loadImage("images/monster.png", true))
{
}

InfoState::~InfoState()
{
}

void InfoState::virtMainLoopDoBeforeUpdate()
{
}

void InfoState::virtSetupBackgroundBuffer()
{
	m_engine->fillBackground(0x000000);
	/*for (int iX = 0; iX < m_engine->getWindowWidth(); iX++)
		for (int iY = 0; iY < this->m_engine->getWindowHeight(); iY++)
			switch (rand() % 237)
			{
			case 0: m_engine->setBackgroundPixel(iX, iY, 0xffffff); break;
			case 1: m_engine->setBackgroundPixel(iX, iY, 0xffffff); break;
			}*/
	m_engine->lockBackgroundForDrawing();
	bg.renderImageWithMask(m_engine->getBackgroundSurface(), 0, 0, 420, 60, bg.getWidth(), bg.getHeight());
	int iTick = m_engine->getModifiedTime() / 300;
	int iFrame = iTick % 4;
	ghost.renderImageWithMask(m_engine->getBackgroundSurface(), ghost.getWidth() / 4 * iFrame, 0,
		700, 400, ghost.getWidth() / 4, ghost.getHeight());
	mons.renderImageWithMask(m_engine->getBackgroundSurface(), mons.getWidth() / 3 * iFrame, 0,
		800, 400, mons.getWidth() / 3, mons.getHeight());
	
	m_engine->unlockBackgroundForDrawing();
}

int InfoState::virtInitialiseObjects()
{
	m_engine->notifyObjectsAboutMouse(true);
	m_engine->drawableObjectsChanged();
	m_engine->destroyOldObjects(true);
	
	return 0;
}

void InfoState::mouseHover(int x, int y)
{
}

void InfoState::virtDrawStringsOnTop()
{
	m_engine->drawForegroundString(596, 580, " BACK", 0xffc53d,
		m_engine->getFont("resources/newFont.ttf", 45));
}

void InfoState::virtKeyDown(int iKeyCode)
{
	if (iKeyCode == SDLK_ESCAPE)
	{
		m_engine->setExitWithCode(0);
	}

	if (iKeyCode == SDLK_UP)
	{
		m_engine->changeOffset(0, -15);
	}
	else if (iKeyCode == SDLK_DOWN)
	{
		m_engine->changeOffset(0, 15);
	}
	else if (iKeyCode == SDLK_RIGHT)
	{
		m_engine->changeOffset(-15, 0);
	}
	else if (iKeyCode == SDLK_LEFT)
	{
		m_engine->changeOffset(15, 0);
	}
}

void InfoState::virtMouseDown(int button, int x, int y)
{
	if (x >= 575 && y >= 580 && x < 800 && y < 640)
	{
		m_engine->switchState(0);
		m_engine->redrawDisplay();
	}
}

void InfoState::virtMouseWheel(int x, int y, int which, int timestamp)
{
	int iOldCentreX = m_engine->convertClickedToVirtualPixelXPosition(m_engine->getWindowWidth() / 2);
	int iOldCentreY = m_engine->convertClickedToVirtualPixelYPosition(m_engine->getWindowHeight() / 2);

	if (y < 0)
	{
		m_engine->compress();
	}
	else if (y > 0)
	{
		m_engine->stretch();
	}

	int iNewCentreX = m_engine->convertClickedToVirtualPixelXPosition(m_engine->getWindowWidth() / 2);
	int iNewCentreY = m_engine->convertClickedToVirtualPixelYPosition(m_engine->getWindowHeight() / 2);

	m_engine->changeOffset(iNewCentreX - iOldCentreX, iNewCentreY - iOldCentreY);

	m_engine->redrawDisplay();
}
