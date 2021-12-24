#pragma once
#include "State.h"
#include "Scyyl7Engine.h"
#include "ScreenObject.h"
#include "NewTileManager.h"

class Scyyl7Engine;
class TankObject;
class BulletObject;
class GhostObject;
class MonsterObject;

class GameState :
    public State
{
public:
	GameState(Scyyl7Engine* engine);
	~GameState();

	void virtSetupBackgroundBuffer();
	int virtInitialiseObjects();
	void virtDrawStringsOnTop();
	void virtKeyDown(int iKeyCode);
	void virtMouseDown(int button, int x, int y);

	void NextLevel();
	void setGameScore(int score);
	int getGameScore();
	void setLevel(int level);
	int getLevel();

	void saveGame();
	void loadGame();

protected:
	NewTileManager tm;
	Scyyl7Engine* m_engine;
	TankObject* tObj;
	BulletObject* bull1;
	BulletObject* bull2;
	BulletObject* bull3;
	BulletObject* bull4;
	GhostObject* ghost1;
	GhostObject* ghost2;
	GhostObject* ghost3;
	MonsterObject* monster1;

	int level;
	int score;

	std::vector<std::string> record;
};

