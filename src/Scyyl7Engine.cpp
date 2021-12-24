#include "header.h"
#include "Scyyl7Engine.h"
#include "ImageManager.h"
#include "ScreenObject.h"
#include "NewTileManager.h"

#include "StartState.h"
#include "PrepState.h"
#include "GameState.h"
#include "LostState.h"
#include "InfoState.h"
#include "WinState.h"

Scyyl7Engine::Scyyl7Engine()
	: BaseEngine(), m_theme(1), playerName("P1"), isLoad(false)
	, m_filterScaling(0, 0, this), m_filterTranslation(0, 0, &m_filterScaling)
{
	states[0] = new StartState(this);
	states[1] = new PrepState(this);
	states[2] = new GameState(this);
	states[3] = new LostState(this);
	states[4] = new InfoState(this);
	states[5] = new WinState(this);


	current = states[0];
}

Scyyl7Engine::~Scyyl7Engine()
{
	delete (StartState*)states[0];
	delete (PrepState*)states[1];
	delete (GameState*)states[2];
	delete (LostState*)states[3];
	delete (InfoState*)states[4];
	delete (WinState*)states[5];
}

int Scyyl7Engine::virtInitialise()
{
	getBackgroundSurface()->setDrawPointsFilter(&m_filterTranslation);
	getForegroundSurface()->setDrawPointsFilter(&m_filterTranslation);

	// Call base class version
	return BaseEngine::virtInitialise();
}

void Scyyl7Engine::virtSetupBackgroundBuffer()
{
	current->virtSetupBackgroundBuffer();
}

void Scyyl7Engine::virtMainLoopDoBeforeUpdate() {
	current->virtMainLoopDoBeforeUpdate();
	this->copyBackgroundPixels(0, 0, this->getWindowWidth(), this->getWindowHeight());
}

void Scyyl7Engine::copyAllBackgroundBuffer()
{
	current->copyAllBackgroundBuffer();
}

int Scyyl7Engine::virtInitialiseObjects()
{
	return current->virtInitialiseObjects();
}

// Draw a foreground string to show the position of the object C
void Scyyl7Engine::virtDrawStringsOnTop()
{
	current->virtDrawStringsOnTop();
	
}

void Scyyl7Engine::virtMouseDown(int iButton, int iX, int iY)
{
	current->virtMouseDown(iButton, iX, iY);
}

void Scyyl7Engine::virtKeyDown(int iKeyCode)
{
	current->virtKeyDown(iKeyCode);
}

void Scyyl7Engine::virtMouseWheel(int x, int y, int which, int timestamp)
{
	current->virtMouseWheel(x, y, which, timestamp);
}

void Scyyl7Engine::virtMouseMoved(int iX, int iY) {
	current->mouseHover(iX, iY);
}

void Scyyl7Engine::switchState(int state)
{
	current = states[state];
	lockAndSetupBackground();
	redrawDisplay();
}

void Scyyl7Engine::setTheme(int theme)
{
	this->m_theme = theme;
}

int Scyyl7Engine::getTheme()
{
	return m_theme;
}

void Scyyl7Engine::setIsLoad(bool isL)
{
	isLoad = isL;
}

bool Scyyl7Engine::getIsLoad()
{
	return isLoad;
}

void Scyyl7Engine::setPlayerName(std::string name)
{
	this->playerName = name;
}

std::string Scyyl7Engine::getPlayerName()
{
	return playerName;
}


void Scyyl7Engine::changeOffset(int x, int y)
{
	m_filterTranslation.changeOffset(x, y);
	virtSetupBackgroundBuffer();
	redrawDisplay();
}

void Scyyl7Engine::compress()
{
	m_filterScaling.compress();
}

void Scyyl7Engine::stretch()
{
	m_filterScaling.stretch();
}