#include "header.h"
#include "LostState.h"

LostState::LostState(Scyyl7Engine* pEngine)
	: m_engine(pEngine), choose(10)
	, bg(ImageManager::loadImage("images/StartBg.png", true))
{
}

LostState::~LostState()
{
}

void LostState::virtSetupBackgroundBuffer()
{
	m_engine->fillBackground(0x000000);
	/*for (int iX = 0; iX < m_engine->getWindowWidth(); iX++)
		for (int iY = 0; iY < this->m_engine->getWindowHeight(); iY++)
			switch (rand() % 237)
			{
			case 0: m_engine->setBackgroundPixel(iX, iY, 0xffffff); break;
			case 1: m_engine->setBackgroundPixel(iX, iY, 0xffffff); break;
			}*/
	bg.renderImageWithMask(m_engine->getBackgroundSurface(), 0, 0, 415, 0, bg.getWidth(), bg.getHeight());

}

void LostState::mouseHover(int x, int y)
{
	if (x >= 575 && y >= 455 && x < 800 && y < 515) 
	{
		choose = 0;
		m_engine->redrawDisplay();
	}
	else if (x >= 575 && y >= 580 && x < 800 && y < 640)
	{
		choose = 1;
		m_engine->redrawDisplay();
	}
	else
	{
		choose = 10;
		m_engine->redrawDisplay();
	}
}

void LostState::virtDrawStringsOnTop()
{
	m_engine->lockBackgroundForDrawing();
	m_engine->drawForegroundString(550, 310, "GAME OVER", 0xffc53d,
		m_engine->getFont("resources/newFont.ttf", 60));
	if (choose == 0)
	{
		m_engine->drawForegroundString(558, 455, "QUIT GAME", 0xffffff,
			m_engine->getFont("resources/newFont.ttf", 55));
	}
	else
	{
		m_engine->drawForegroundString(572, 455, "QUIT GAME", 0xffc53d,
			m_engine->getFont("resources/newFont.ttf", 45));
	}
	if (choose == 1)
	{
		m_engine->drawForegroundString(586, 580, "REPLAY", 0xffffff,
			m_engine->getFont("resources/newFont.ttf", 55));
	}
	else
	{
		m_engine->drawForegroundString(596, 580, "REPLAY", 0xffc53d,
			m_engine->getFont("resources/newFont.ttf", 45));
	}
}

void LostState::virtKeyDown(int iKeyCode)
{
	if (iKeyCode == SDLK_ESCAPE)
	{
		m_engine->setExitWithCode(0);
	}
}

void LostState::virtMouseDown(int button, int x, int y)
{
	if (x >= 575 && y >= 455 && x < 800 && y < 515)
	{
		choose = 0;
		m_engine->setExitWithCode(0);
		
	}

	if (x >= 575 && y >= 580 && x < 800 && y < 640)
	{
		choose = 1;
		m_engine->switchState(1);
		m_engine->redrawDisplay();
	}
}

