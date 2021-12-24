#pragma once
#include "State.h"
#include "Scyyl7Engine.h"
#include "SimpleImage.h"

class InfoState :
    public State
{
public:
    InfoState(Scyyl7Engine* pEngine);
    ~InfoState();

    void virtMainLoopDoBeforeUpdate();
    void virtSetupBackgroundBuffer();
    int virtInitialiseObjects();
    void mouseHover(int x, int y);
    void virtDrawStringsOnTop();
    void virtKeyDown(int iKeyCode);
    void virtMouseDown(int button, int x, int y);
    void virtMouseWheel(int x, int y, int which, int timestamp);

protected:
    Scyyl7Engine* m_engine;
    BaseEngine base;
    SimpleImage bg;
    SimpleImage ghost;
    SimpleImage mons;

};

