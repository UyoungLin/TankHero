#pragma once
#include "BaseEngine.h"
#include "State.h"
#include "NewFilterPoints.h"

class BulletObject;
class GhostObject;
class TankObject;

class Scyyl7Engine :
    public BaseEngine
{
public:
    Scyyl7Engine();
    ~Scyyl7Engine();

    int virtInitialise() override;
    void virtSetupBackgroundBuffer() override;
    void virtMainLoopDoBeforeUpdate() override;
    void copyAllBackgroundBuffer() override;
    int virtInitialiseObjects() override;
    void virtDrawStringsOnTop() override;
    void virtMouseDown(int iButton, int iX, int iY) override;
    void virtKeyDown(int iKeyCode) override;
    void virtMouseWheel(int x, int y, int which, int timestamp);

    void virtMouseMoved(int iX, int iY);

    void switchState(int state);

    void setTheme(int theme);
    int getTheme();

    void setIsLoad(bool isL);
    bool getIsLoad();

    void setPlayerName(std::string name);
    std::string getPlayerName();

    void changeOffset(int x, int y);
    void compress();
    void stretch();

private:
    State* current;
    State* states[6];

    int m_theme;
    bool isLoad;
    std::string playerName;

    FPScaling m_filterScaling;
    FPTranslation m_filterTranslation;
};

