#pragma once
#include "State.h"
#include "Scyyl7Engine.h"
#include "SimpleImage.h"

class LostState :
    public State
{
public:
    LostState(Scyyl7Engine* pEngine);
    ~LostState();
    
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

