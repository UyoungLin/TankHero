#include "header.h"
#include "GameState.h"
#include "ScreenObject.h"
#include "Scyyl7Engine.h"
#include "DrawingSurface.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

GameState::GameState(Scyyl7Engine* engine)
	: m_engine(engine), tObj(NULL)
	, bull1(NULL), bull2(NULL), bull3(NULL), bull4(NULL)
	, ghost1(NULL), ghost2(NULL), ghost3(NULL), monster1(NULL)
	, level(1), score(0)
{
}

GameState::~GameState()
{
}

void GameState::virtSetupBackgroundBuffer()
{
	m_engine->lockBackgroundForDrawing();
	m_engine->fillBackground(0x73d13d);
	for (int iX = 0; iX < m_engine->getWindowWidth(); iX++)
		for (int iY = 0; iY < this->m_engine->getWindowHeight(); iY++)
			switch (rand() % 10)
			{
			case 0: m_engine->setBackgroundPixel(iX, iY, 0x73d13d); break;
			case 1: m_engine->setBackgroundPixel(iX, iY, 0x2f9e44); break;
			case 2: m_engine->setBackgroundPixel(iX, iY, 0x8ce99a); break;
			case 3: m_engine->setBackgroundPixel(iX, iY, 0xb2f2bb); break;
			case 4: m_engine->setBackgroundPixel(iX, iY, 0x37b24d); break;
			case 5: m_engine->setBackgroundPixel(iX, iY, 0x73d13d); break;
			}
	{
		if (m_engine->getIsLoad())
		{
			loadGame();
		}

		if (level == 1)
		{
			loadMap("resources/level1.txt");
		}
		else if (level == 2)
		{
			loadMap("resources/level2.txt");
		}

		std::vector<std::string> mapData = this->getMapStr();

		// Specify how many tiles wide and high
		tm.setMapSize(26, 16);
		// Set up the tiles
		for (int y = 0; y < 16; y++)
			for (int x = 0; x < 26; x++)
			{
				if (m_engine->getTheme() == 2)
				{
					tm.setMapValue(x, y, mapData[y][x] - 'a' + 5);
				}
				else
				{
					tm.setMapValue(x, y, mapData[y][x] - 'a');
				}
			}
				
		for (int y = 0; y < 16; y++)
		{
			for (int x = 0; x < 26; x++)
				std::cout << tm.getMapValue(x, y);
			std::cout << std::endl;
		}

		tm.drawAllTiles(m_engine, m_engine->getBackgroundSurface());
		clearMap();
	}
	m_engine->unlockBackgroundForDrawing();

	virtInitialiseObjects();
	
}

int GameState::virtInitialiseObjects()
{
	m_engine->notifyObjectsAboutMouse(true);
	m_engine->drawableObjectsChanged();
	m_engine->destroyOldObjects(true);

	tObj = new TankObject(m_engine, this, 1, 50, true, true, &tm);
	bull1 = new BulletObject(m_engine, 2, 20, true, false, tObj, &tm);
	bull2 = new BulletObject(m_engine, 2, 20, true, false, tObj, &tm);
	bull3 = new BulletObject(m_engine, 2, 20, true, false, tObj, &tm);
	bull4 = new BulletObject(m_engine, 2, 20, true, false, tObj, &tm);
	ghost1 = new GhostObject(m_engine, 3, 50, tObj);
	ghost2 = new GhostObject(m_engine, 3, 50, tObj);
	ghost3 = new GhostObject(m_engine, 3, 50, tObj);
	monster1 = new MonsterObject(m_engine, 4, 50, tObj, &tm);

	m_engine->createObjectArray(10);
	m_engine->storeObjectInArray(0, tObj);
	m_engine->storeObjectInArray(1, bull1);
	m_engine->storeObjectInArray(2, bull2);
	m_engine->storeObjectInArray(3, bull3);
	m_engine->storeObjectInArray(4, bull4);
	m_engine->storeObjectInArray(5, ghost1);
	ghost1->setPosition(200, 500);
	m_engine->storeObjectInArray(6, ghost2);
	ghost2->setPosition(900, 500);
	ghost2->setSpeed(-2, 3);
	m_engine->storeObjectInArray(7, ghost3);
	ghost3->setPosition(900, 500);
	ghost3->setSpeed(-5, -5);
	m_engine->storeObjectInArray(8, monster1);
	monster1->setPosition(1000, 700);

	if (level == 2)
	{
		delete ghost3;
		ghost3 = new GhostObject(m_engine, 3, 50, tObj);
		m_engine->storeObjectInArray(7, ghost3);

		ghost3->setSpeed(2, 6);
		delete monster1;
		monster1 = new MonsterObject(m_engine, 4, 50, tObj, &tm);
		m_engine->storeObjectInArray(8, monster1);
		monster1->setPosition(500, 700);
	}

	if (m_engine->getIsLoad())
	{
		tObj->setHp(stoi(record[0]));
		tObj->setPosition(stod(record[1]), stod(record[2]));
		tObj->setDirection(stoi(record[3]));
		tObj->setScore(stoi(record[4]));
		monster1->setHP(stoi(record[5]));
		monster1->setPosition(stod(record[6]), stod(record[7]));
		monster1->setVisible(stoi(record[8]));
		ghost1->setPosition(stod(record[9]), stod(record[10]));
		ghost1->setVisible(stoi(record[11]));
		ghost2->setPosition(stod(record[12]), stod(record[13]));
		ghost2->setVisible(stoi(record[14]));
		ghost3->setPosition(stod(record[15]), stod(record[16]));
		ghost3->setVisible(stoi(record[17]));

	}
	//m_engine->setAllObjectsVisible(true);
	return 0;
}

void GameState::virtDrawStringsOnTop()
{
	char buf[128];
	sprintf(buf, m_engine->getPlayerName().c_str());
	m_engine->drawForegroundString(30, 20, buf, 0xe6d082,
		m_engine->getFont("resources/newFont.ttf", 65));	

	m_engine->drawForegroundString(980, 20, "HP:", 0xe6d082,
		m_engine->getFont("resources/newFont.ttf", 65));
	m_engine->drawForegroundString(420, 20, "Score:", 0xe6d082,
		m_engine->getFont("resources/newFont.ttf", 65));
}

void GameState::virtKeyDown(int iKeyCode)
{
	switch (iKeyCode)
	{
	case SDLK_SPACE:
		if (bull1->isVisible() == false)
		{
			int tdir = tObj->getDirection();
			bull1->setDirection(tdir);
			bull1->setPosition(tObj->getPositionX() + 15, tObj->getPositionY() + 15);
			if (tdir == 0)
			{
				bull1->setSpeed(0, -10);
			}
			else if (tdir == 1)
			{
				bull1->setSpeed(10, 0);
			}
			else if (tdir == 2)
			{
				bull1->setSpeed(0, 10);
			}
			else
			{
				bull1->setSpeed(-10, 0);
			}
			bull1->setVisible(true);
		}
		else if (bull2->isVisible() == false)
		{
			int tdir = tObj->getDirection();
			bull2->setDirection(tdir);
			bull2->setPosition(tObj->getPositionX() + 15, tObj->getPositionY() + 15);
			if (tdir == 0)
			{
				bull2->setSpeed(0, -10);
			}
			else if (tdir == 1)
			{
				bull2->setSpeed(10, 0);
			}
			else if (tdir == 2)
			{
				bull2->setSpeed(0, 10);
			}
			else
			{
				bull2->setSpeed(-10, 0);
			}
			bull2->setVisible(true);
		}
		else if (bull3->isVisible() == false)
		{
			int tdir = tObj->getDirection();
			bull3->setDirection(tdir);
			bull3->setPosition(tObj->getPositionX() + 15, tObj->getPositionY() + 15);
			if (tdir == 0)
			{
				bull3->setSpeed(0, -10);
			}
			else if (tdir == 1)
			{
				bull3->setSpeed(10, 0);
			}
			else if (tdir == 2)
			{
				bull3->setSpeed(0, 10);
			}
			else
			{
				bull3->setSpeed(-10, 0);
			}
			bull3->setVisible(true);
		}
		else if (bull4->isVisible() == false)
		{
			int tdir = tObj->getDirection();
			bull4->setDirection(tdir);
			bull4->setPosition(tObj->getPositionX() + 15, tObj->getPositionY() + 15);
			if (tdir == 0)
			{
				bull4->setSpeed(0, -10);
			}
			else if (tdir == 1)
			{
				bull4->setSpeed(10, 0);
			}
			else if (tdir == 2)
			{
				bull4->setSpeed(0, 10);
			}
			else
			{
				bull4->setSpeed(-10, 0);
			}
			bull4->setVisible(true);
		}
		break;
	case SDLK_s:
		saveGame();
		m_engine->setExitWithCode(0);
		break;
	case SDLK_ESCAPE:
		m_engine->setExitWithCode(0);
		break;
	}
}

void GameState::virtMouseDown(int button, int x, int y)
{
}

void GameState::NextLevel()
{
	if (level < 2)
	{
		level++;
		this->virtSetupBackgroundBuffer();
	}
	else
	{
		ifstream savedScore("resources/high_score.txt");
		string n, s;
		getline(savedScore, n);
		getline(savedScore, s);
		int high = stoi(s);
		savedScore.close();
		ofstream saveScore("resources/high_score.txt");
		if (score > high)
		{
			saveScore << m_engine->getPlayerName() << endl << score << endl;
		}
		else
		{
			saveScore << n << endl << s << endl;
		}
		saveScore.close();
		m_engine->setAllObjectsVisible(false);
		m_engine->switchState(5);
	}
}

void GameState::setGameScore(int score)
{
	this->score = score;
}

int GameState::getGameScore()
{
	return this->score;
}

void GameState::setLevel(int level)
{
	this->level = level;
}

int GameState::getLevel()
{
	return this->level;
}

void GameState::saveGame()
{
	ofstream myFile("resources/record.txt");
	myFile << this->getLevel() << endl;
	myFile << m_engine->getTheme() << endl;
	myFile << m_engine->getPlayerName() << endl;
	myFile << tObj->getHp() << endl;
	myFile << tObj->getPositionX() << endl;
	myFile << tObj->getPositionY() << endl;
	myFile << tObj->getDirection() << endl;
	myFile << tObj->getScore() << endl;
	myFile << monster1->getHP() << endl;
	myFile << monster1->getPositionX() << endl;
	myFile << monster1->getPositionY() << endl;
	myFile << monster1->isVisible() << endl;
	myFile << ghost1->getPositionX() << endl;
	myFile << ghost1->getPositionY() << endl;
	myFile << ghost1->isVisible() << endl;
	myFile << ghost2->getPositionX() << endl;
	myFile << ghost2->getPositionY() << endl;
	myFile << ghost2->isVisible() << endl;
	myFile << ghost3->getPositionX() << endl;
	myFile << ghost3->getPositionY() << endl;
	myFile << ghost3->isVisible() << endl;
	myFile.close();
	m_engine->drawableObjectsChanged();
	m_engine->destroyOldObjects(true);
}

void GameState::loadGame()
{
	ifstream saved;
	string line;
	saved.open("resources/record.txt");
	if (saved.is_open() == false)
	{
		cout << "Fail to open!" << endl;
		return;
	}

	getline(saved, line);
	this->setLevel(stoi(line));
	getline(saved, line);
	m_engine->setTheme(stoi(line));
	getline(saved, line);
	m_engine->setPlayerName(line);
	
	while (getline(saved, line))
	{
		record.push_back(line);
	}

	saved.close();
}
