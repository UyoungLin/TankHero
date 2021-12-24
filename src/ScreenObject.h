#pragma once
#include "DisplayableObject.h"
#include "UtilMovementPosition.h"
#include "Scyyl7Engine.h"
#include "FourDirection.h"
#include "GameState.h"

class GameState;

class ScreenObject :
    public DisplayableObject
{
public:
    ScreenObject(Scyyl7Engine* pEngine, int iID, int iSize);

    virtual ~ScreenObject(void);

    void virtDraw();
    
    void virtDoUpdate(int iCurrentTime);

protected:
    Scyyl7Engine* m_pEngine;
	int m_iID;
    int m_iSize;
};

class BulletObject :
    public ScreenObject
{
public:
    BulletObject(Scyyl7Engine* pEngine, int iID, int iSize, 
        bool useTopLeftFor00, bool bVisible, 
        TankObject* tObj, NewTileManager* pTileManager);

    void setPosition(double dX, double dY);
    double getPositionX();
    double getPositionY();
    void setDirection(int direction);
    void setSpeed(double dSX, double dSY);
    void virtDraw() override;
    void virtDoUpdate(int iCurrentTime) override;

    ~BulletObject();

protected:
    double m_dX;
    double m_dY;
    double m_dSX;
    double m_dSY;
    TankObject* m_tank;
    int dir;

    SimpleImage iUp;
    SimpleImage iDown;
    SimpleImage iLeft;
    SimpleImage iRight;
    SimpleImage* m_bullet;
    NewTileManager* m_tm;
};

class GhostObject
    : public ScreenObject
{
public:
    GhostObject(Scyyl7Engine* pEngine, int iID, int iSize, 
        TankObject* obj);

    void setPosition(double dX, double dY);
    double getPositionX();
    double getPositionY();
    void setSpeed(double dSX, double dSY);
    void virtDraw() override;
    void virtDoUpdate(int iCurrentTime) override;

    ~GhostObject();

protected:
    double m_dX;
    double m_dY;
    double m_dSX;
    double m_dSY;

    TankObject* tObj;
    SimpleImage m_ghost;

    int m_iLastUpdatedTime;
};

class MonsterObject
    : public ScreenObject
{
public:
    MonsterObject(Scyyl7Engine* pEngine, int iID, int iSize,
        TankObject* obj, NewTileManager* tm);

    void setPosition(double dX, double dY);
    double getPositionX();
    double getPositionY();
    void virtDraw() override;
    void virtDoUpdate(int iCurrentTime) override;
    double calcDistance(double x1, double x2, double y1, double y2);
    int getHP();
    void setHP(int hp);
    void minusHP();

    template <typename T>
    T const& tempMin(T const& a, T const& b, T const& c, T const& d)
    {
        T tmin = a;
        T tmin2 = c;
        tmin = (a < b ? a : b);
        tmin2 = (c < d ? c : d);
        return tmin < tmin2 ? tmin : tmin2;
    }

    ~MonsterObject();

protected:
    double m_dX;
    double m_dY;
    double m_dSX;
    double m_dSY;

    TankObject* tObj;
    SimpleImage m_monster;
    NewTileManager* m_tm;
    int mHP;

    int m_iLastUpdatedTime;
};

class TankObject
    : public ScreenObject
{
public:
    TankObject(Scyyl7Engine* pEngine, GameState* state, int iID, int iSize,
        bool useTopLeftFor00, bool bVisible, NewTileManager* pTileManager);

    void setPosition(double dX, double dY);
    double getPositionX();
    double getPositionY();
    void virtDraw() override;
    void virtDoUpdate(int iCurrentTime) override;

    int getDirection();
    void setDirection(int dir);
    int getHp();
    void setHp(int ihp);
    void displayHP();
    int getScore();
    void setScore(int score);

    friend TankObject& operator-(TankObject& tank, int n) {
        tank.hp -= n;
        return tank;
    }


protected:
    double m_dX;
    double m_dY;

    GameState* state;
    FourDirection ft;
    SimpleImage* image;
    NewTileManager* m_tm;
    int m_direction;
    int hp;
    int score;

    int m_iLastUpdatedTime;
};


