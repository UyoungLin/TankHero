#include "header.h"
#include "StartState.h"
#include "MyMappingObject.h"

StartState::StartState(Scyyl7Engine* engine)
	: m_engine(engine), choose(10), bg(ImageManager::loadImage("images/StartBg.png", true))
	, rotator(0), m_iOffset(0)
{
}

StartState::~StartState()
{
}

void StartState::virtSetupBackgroundBuffer()
{
	m_engine->fillBackground(0x000000);
	m_engine->copyBackgroundPixels(0, 0, m_engine->getWindowWidth(), m_engine->getWindowHeight());
	/*for (int iX = 0; iX < m_engine->getWindowWidth(); iX++)
		for (int iY = 0; iY < this->m_engine->getWindowHeight(); iY++)
			switch (rand() % 237)
			{
			case 0: m_engine->setBackgroundPixel(iX, iY, 0xffffff); break;
			case 1: m_engine->setBackgroundPixel(iX, iY, 0xffffff); break;
			}*/
	bg.renderImageWithMask(m_engine->getBackgroundSurface(), 0, 0, 415, 0, bg.getWidth(), bg.getHeight());
	
	virtInitialiseObjects();
}

int StartState::virtInitialiseObjects()
{
	m_engine->notifyObjectsAboutMouse(true);
	m_engine->drawableObjectsChanged();
	m_engine->destroyOldObjects(true);
	m_engine->createObjectArray(1);
	MyMappingObject* ob = new MyMappingObject(this, 1050, 450, m_engine, "images/start_bomb.png", false);
	ob->setTransparencyColour(ob->getPixelColour(10, 10));
	m_engine->storeObjectInArray(0, ob);

	return 0;
}

void StartState::mouseHover(int x, int y)
{
	if (x >= 575 && y >= 330 && x < 800 && y < 390) 
	{
		choose = 0;
		m_engine->redrawDisplay();
	}
	else if (x >= 575 && y >= 455 && x < 800 && y < 515) 
	{
		choose = 1;
		m_engine->redrawDisplay();
	}
	else if (x >= 575 && y >= 580 && x < 800 && y < 640) 
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



void StartState::virtDrawStringsOnTop()
{
	m_engine->lockBackgroundForDrawing();
	m_engine->copyBackgroundPixels(0, 0, m_engine->getWindowWidth(), 50);
	if (choose == 0)
	{
		m_engine->drawForegroundString(565, 330, "NEW GAME", 0xffffff, 
			m_engine->getFont("resources/newFont.ttf", 55));
	}
	else
	{
		m_engine->drawForegroundString(577, 330, "NEW GAME", 0xffc53d, 
			m_engine->getFont("resources/newFont.ttf", 45));
	}
	if (choose == 1)
	{
		m_engine->drawForegroundString(558, 455, "LOAD GAME", 0xffffff,
			m_engine->getFont("resources/newFont.ttf", 55));
	}
	else
	{
		m_engine->drawForegroundString(572, 455, "LOAD GAME", 0xffc53d,
			m_engine->getFont("resources/newFont.ttf", 45));
	}
	if (choose == 2)
	{
		m_engine->drawForegroundString(605, 580, "INFO", 0xffffff,
			m_engine->getFont("resources/newFont.ttf", 55));
	}
	else
	{
		m_engine->drawForegroundString(610, 580, "INFO", 0xffc53d,
			m_engine->getFont("resources/newFont.ttf", 45));
	}
	if (choose == 3)
	{
		m_engine->drawForegroundString(605, 705, "QUIT", 0xffffff,
			m_engine->getFont("resources/newFont.ttf", 55));
	}
	else
	{
		m_engine->drawForegroundString(610, 705, "QUIT", 0xffc53d,
			m_engine->getFont("resources/newFont.ttf", 45));
	}
	m_engine->unlockBackgroundForDrawing();
}

void StartState::virtMainLoopDoBeforeUpdate()
{
	int iOffset = m_engine->getModifiedTime() / 10;

	rotator.setRotation((double)iOffset / -100.0);
	m_engine->redrawDisplay();
}

void StartState::copyAllBackgroundBuffer()
{
}

void StartState::virtMouseDown(int button, int x, int y)
{
	if (x >= 575 && y >= 330 && x < 800 && y < 390) 
	{
		choose = 0;
		m_engine->switchState(1);
		m_engine->redrawDisplay();
	}

	if (x >= 575 && y >= 455 && x < 800 && y < 515)
	{
		choose = 1;
		m_engine->setIsLoad(true);
		m_engine->switchState(2);
	}

	if (x >= 575 && y >= 580 && x < 800 && y < 640)
	{
		choose = 2;
		m_engine->switchState(4);
		m_engine->setAllObjectsVisible(false);
		m_engine->redrawDisplay();
	}

	if (x >= 575 && y >= 705 && x < 800 && y < 765)
	{
		choose = 3;
		m_engine->setExitWithCode(0);
	}
	
}

bool StartState::mapCoordinates(double& x, double& y, const SimpleImage& image)
{
	int iOffset = m_engine->getModifiedTime() / 10;

	if (x < 0) return false;
	if (y < 0) return false;
	if (x >= (image.getWidth() - 0.5)) return false;
	if (y >= (image.getHeight() - 0.5)) return false;

	x -= image.getWidth() / 2;
	y -= image.getHeight() / 2;

	// Rotate it
	//double dAngle = (double)iOffset / 100;
	double dAngle = atan(y / (x + 0.0001));
	if (x < 0)
		dAngle += M_PI;
	double hyp = ::sqrt(x * x + y * y);
	dAngle += (double)iOffset / 100;

	x = hyp * ::cos(dAngle);
	y = hyp * ::sin(dAngle);

	// Shift offset back to the corner
	x += image.getWidth() / 2;
	y += image.getHeight() / 2;

	if (x < 0) return false;
	if (y < 0) return false;
	if (x >= (image.getWidth() - 0.5)) return false;
	if (y >= (image.getHeight() - 0.5)) return false;

	return true;
}
