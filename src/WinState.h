#pragma once
#include "State.h"
#include "Scyyl7Engine.h"
#include "SimpleImage.h"

class WinState :
    public State
{
public:
    WinState(Scyyl7Engine* pEngine);
    ~WinState();

    void virtSetupBackgroundBuffer();
    void mouseHover(int x, int y);
    void virtDrawStringsOnTop();
    void virtKeyDown(int iKeyCode);
    void virtMouseDown(int button, int x, int y);

protected:
    Scyyl7Engine* m_engine;
    SimpleImage bg;
    int choose;
};

