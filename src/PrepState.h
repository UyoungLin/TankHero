#pragma once
#include "State.h"
#include "Scyyl7Engine.h"

class PrepState :
    public State
{
public:
    PrepState(Scyyl7Engine* engine);
    ~PrepState();

	void virtSetupBackgroundBuffer();
	int virtInitialiseObjects();
	void mouseHover(int x, int y);
	void virtDrawStringsOnTop();
	void virtMainLoopDoBeforeUpdate();
	void copyAllBackgroundBuffer();
	void virtMouseDown(int button, int x, int y);
	void virtKeyDown(int iKeyCode);

protected:
	Scyyl7Engine* m_engine;
	SimpleImage bg;
	SimpleImage defaultTheme;
	SimpleImage snowTheme;
	int choose;
	std::string inputName;
};

