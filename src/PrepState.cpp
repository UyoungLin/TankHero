#include "header.h"
#include "PrepState.h"

PrepState::PrepState(Scyyl7Engine* engine)
	: m_engine(engine), choose(10), inputName(" ")
	, bg(ImageManager::loadImage("images/StartBg.png", true))
	, defaultTheme(ImageManager::loadImage("images/default.png", true))
	, snowTheme(ImageManager::loadImage("images/snow.png", true))
{
}

PrepState::~PrepState()
{
}

void PrepState::virtSetupBackgroundBuffer()
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

	defaultTheme.renderImageWithMask(m_engine->getBackgroundSurface(), 0, 0, 543, 365, defaultTheme.getWidth(), defaultTheme.getHeight());
	snowTheme.renderImageWithMask(m_engine->getBackgroundSurface(), 0, 0, 663, 365, snowTheme.getWidth(), snowTheme.getHeight());

	
	virtInitialiseObjects();
}

int PrepState::virtInitialiseObjects()
{
	m_engine->notifyObjectsAboutMouse(true);
	m_engine->drawableObjectsChanged();
	m_engine->destroyOldObjects(true);
	return 0;
}

void PrepState::mouseHover(int x, int y)
{
	if (x >= 543 && y >= 365 && x < 643 && y < 465) 
	{
		choose = 0;
		m_engine->redrawDisplay();
	}
	else if (x >= 663 && y >= 365 && x < 763 && y < 465) 
	{
		choose = 1;
		m_engine->redrawDisplay();
	}
	else if (x >= 575 && y >= 610 && x < 800 && y < 670) 
	{
		choose = 2;
		m_engine->redrawDisplay();
	}
	else if (x >= 575 && y >= 705 && x < 800 && y < 765) 
	{
		choose = 3;
		m_engine->redrawDisplay();
	}
	else
	{
		choose = 10;
		m_engine->redrawDisplay();
	}
}

void PrepState::virtDrawStringsOnTop()
{
	m_engine->lockBackgroundForDrawing();
	//m_engine->copyBackgroundPixels(0, 0, m_engine->getWindowWidth(), 50);

	m_engine->drawForegroundString(550, 310, "CHOOSE THEME", 0xffc53d,
		m_engine->getFont("resources/newFont.ttf", 45));
	m_engine->drawForegroundString(475, 475, "ENTER YOUR NAME BELOW:", 0xffc53d,
		m_engine->getFont("resources/newFont.ttf", 45));
	m_engine->drawForegroundString(488, 525, inputName.data(), 0xffc53d,
		m_engine->getFont("resources/newFont.ttf", 45));

	if (choose == 0)
	{
		
	}
	if (choose == 1)
	{
	
	}

	if (choose == 2)
	{
		m_engine->drawForegroundString(592, 610, "START", 0xffffff,
			m_engine->getFont("resources/newFont.ttf", 65));
	}
	else
	{
		m_engine->drawForegroundString(595, 610, "START", 0xffc53d,
			m_engine->getFont("resources/newFont.ttf", 55));
	}
	if (choose == 3)
	{
		m_engine->drawForegroundString(605, 705, "BACK", 0xffffff,
			m_engine->getFont("resources/newFont.ttf", 55));
	}
	else
	{
		m_engine->drawForegroundString(610, 705, "BACK", 0xffffff,
			m_engine->getFont("resources/newFont.ttf", 45));
	}
	m_engine->unlockBackgroundForDrawing();
}

void PrepState::virtMainLoopDoBeforeUpdate()
{
	m_engine->redrawDisplay();
}

void PrepState::copyAllBackgroundBuffer()
{
}

void PrepState::virtMouseDown(int button, int x, int y)
{
	if (x >= 543 && y >= 365 && x < 643 && y < 465) {
		m_engine->setTheme(1);
		m_engine->redrawDisplay();
	}
	else if (x >= 663 && y >= 365 && x < 763 && y < 465) {
		m_engine->setTheme(2);
		m_engine->redrawDisplay();
	}

	if (x >= 575 && y >= 610 && x < 800 && y < 670) {
		//choose = 2;
		if (inputName.size() > 1)
		{
			m_engine->setPlayerName(inputName.substr(1));
		}
		m_engine->switchState(2);
		m_engine->redrawDisplay();
	}

	if (x >= 575 && y >= 705 && x < 800 && y < 765)
	{
		m_engine->switchState(0);
		m_engine->redrawDisplay();
	}
}

void PrepState::virtKeyDown(int iKeyCode)
{
	if ((iKeyCode >= '0' && iKeyCode <= '9') || (iKeyCode >= 'A' && iKeyCode <= 'z') 
		|| iKeyCode == SDLK_SPACE)
	{
		inputName.push_back(iKeyCode);
	}
	if (iKeyCode == SDLK_BACKSPACE)
	{
		if (inputName.size() > 1)
		{
			inputName.erase(inputName.end() - 1);
		}
	}
	if (iKeyCode == SDLK_ESCAPE)
	{
		m_engine->setExitWithCode(0);
	}
	if (iKeyCode == SDLK_RETURN)
	{
		m_engine->switchState(2);
	}

	m_engine->redrawDisplay();
}
