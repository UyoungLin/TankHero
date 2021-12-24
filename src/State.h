#pragma once
#include "NewTileManager.h"

class Scyyl7Engine;

class State
{
public:
	State();
	State(Scyyl7Engine* engine);
	virtual ~State();

	virtual void virtDrawStringsOnTop() {};
	virtual void UndrawStrings() {};
	virtual int virtInitialise() { return 0; }
	virtual void virtMainLoopDoBeforeUpdate() {};
	virtual void copyAllBackgroundBuffer() {};
	virtual int virtInitialiseObjects() { return 0; }
	virtual void virtKeyDown(int keyCode) {};
	virtual void virtMouseDown(int button, int x, int y) {};
	virtual void virtMouseWheel(int x, int y, int which, int timestamp) {};
	virtual void mouseHover(int x, int y) {};
	virtual void virtSetupBackgroundBuffer() {};

	void loadMap(char* fileName);
	std::vector<std::string> getMapStr();
	void clearMap();

protected:
	BaseEngine* m_engine;
	std::vector<std::string> mapStr;
};

