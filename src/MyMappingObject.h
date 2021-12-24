#pragma once

#include "DisplayableObject.h"
#include "BaseEngine.h"
#include "ImagePixelMapping.h"

class MyMappingObject 
	: public DisplayableObject
{
public:
	// Constructors
	MyMappingObject(ImagePixelMapping* pMapping, BaseEngine* pEngine, std::string strURL, bool useTopLeftFor00 = true, bool bVisible = true)
		: DisplayableObject(pEngine, 0, 0, useTopLeftFor00)
		, m_pMapping(pMapping)
		, image(ImageManager::get()->getImagebyURL(strURL, true/*Load*/, false/*Keep it loaded*/))
	{
		m_iDrawWidth = image.getWidth();
		m_iDrawHeight = image.getHeight();
		// Offset within the drawing area to draw at - need to reset since width and height changed:
		m_iStartDrawPosX = useTopLeftFor00 ? 0 : -m_iDrawWidth / 2;
		m_iStartDrawPosY = useTopLeftFor00 ? 0 : -m_iDrawHeight / 2;
		pEngine->notifyObjectsAboutMouse(true); // Tell BaseEngine to send us the mouse events because we use them
		setVisible(bVisible);

	}

	MyMappingObject(ImagePixelMapping* pMapping, int xStart, int yStart, BaseEngine* pEngine, std::string strURL, bool useTopLeftFor00 = true, bool bVisible = true)
		: DisplayableObject(xStart, yStart, pEngine, 100, 100, useTopLeftFor00)
		, m_pMapping(pMapping)
		, image(ImageManager::get()->getImagebyURL(strURL, true/*Load*/, false/*Keep it loaded*/))
	{
		m_iDrawWidth = image.getWidth();
		m_iDrawHeight = image.getHeight();
		// Offset within the drawing area to draw at - need to reset since width and height changed:
		m_iStartDrawPosX = useTopLeftFor00 ? 0 : -m_iDrawWidth / 2;
		m_iStartDrawPosY = useTopLeftFor00 ? 0 : -m_iDrawHeight / 2;
		pEngine->notifyObjectsAboutMouse(true); // Tell BaseEngine to send us the mouse events because we use them
		setVisible(bVisible);
	}

	// Draw the object - override to implement the actual drawing of the correct object
	virtual void virtDraw()
	{
		if (isVisible())
		{
			image.renderImageApplyingMapping(getEngine(), getEngine()->getForegroundSurface(),
				m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight,
				m_pMapping);
		}
	}

	// Set the transparency colour
	void setTransparencyColour(int colour) { image.setTransparencyColour(colour); }

	// Retrieve the colour of a pixel - primarily used so we can get pixel 0,0 to set the transparency
	int getPixelColour(int x, int y) { return image.getPixelColour(x, y); }

	// Return the width of the loaded image
	int getImageWidth() { return image.getWidth(); }

	// Return the height of the loaded image
	int getImageHeight() { return image.getHeight(); }

protected:
	ImagePixelMapping* m_pMapping;
	SimpleImage image;
};


