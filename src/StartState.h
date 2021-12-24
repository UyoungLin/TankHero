#pragma once
#include "State.h"
#include "Scyyl7Engine.h"
#include "ImagePixelMapping.h"

class Scyyl7Engine;

class StartState :
    public State, public ImagePixelMapping
{
public:
    StartState(Scyyl7Engine* engine);
    ~StartState();

	void virtSetupBackgroundBuffer();
	int virtInitialiseObjects();
	void mouseHover(int x, int y);
	void virtDrawStringsOnTop();
	void virtMainLoopDoBeforeUpdate();
	void copyAllBackgroundBuffer();
	void virtMouseDown(int button, int x, int y);

	bool mapCoordinates(double& x, double& y, const SimpleImage& image) override;

protected:
	Scyyl7Engine* m_engine;
	int choose;
	SimpleImage bg;
	ImagePixelMappingRotate rotator;
	int m_iOffset;
};

