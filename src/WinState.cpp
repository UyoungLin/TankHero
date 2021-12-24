#include "header.h"
#include "WinState.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

WinState::WinState(Scyyl7Engine* pEngine)
	: m_engine(pEngine), choose(10)
	, bg(ImageManager::loadImage("images/StartBg.png", true))
{
}

WinState::~WinState()
{
}

void WinState::virtSetupBackgroundBuffer()
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

void WinState::mouseHover(int x, int y)
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

void WinState::virtDrawStringsOnTop()
{
	m_engine->lockBackgroundForDrawing();
	m_engine->drawForegroundString(550, 310, "YOU! WIN!", 0xffc53d,
		m_engine->getFont("resources/newFont.ttf", 60));

	m_engine->drawForegroundString(530, 455, "HISTORY HIGHEST", 0xffc53d,
		m_engine->getFont("resources/newFont.ttf", 60));

	ifstream savedScore("resources/high_score.txt");
	string name;
	getline(savedScore, name);
	string score;
	getline(savedScore, score);
	savedScore.close();
	string pr = name + " " + score;
	m_engine->drawForegroundString(530, 495, pr.c_str(), 0xffc53d,
		m_engine->getFont("resources/newFont.ttf", 55));
	
	
	if (choose == 1)
	{
		m_engine->drawForegroundString(586, 580, " QUIT", 0xffffff,
			m_engine->getFont("resources/newFont.ttf", 55));
	}
	else
	{
		m_engine->drawForegroundString(596, 580, " QUIT", 0xffc53d,
			m_engine->getFont("resources/newFont.ttf", 45));
	}
}

void WinState::virtKeyDown(int iKeyCode)
{
	if (iKeyCode == SDLK_ESCAPE)
	{
		m_engine->setExitWithCode(0);
	}
}

void WinState::virtMouseDown(int button, int x, int y)
{
	if (x >= 575 && y >= 580 && x < 800 && y < 640)
	{
		choose = 1;
		m_engine->setExitWithCode(0);
	}
}
