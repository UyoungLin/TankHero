#pragma once
#include "DisplayableObject.h"
class MyObjectB :
    public DisplayableObject
{
public:
    MyObjectB(BaseEngine* pEngine);

    void virtDraw();
    void virtDoUpdate(int iCurrentTime);
};

