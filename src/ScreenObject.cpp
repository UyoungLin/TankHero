#include "header.h"
#include "BaseEngine.h"
#include "ScreenObject.h"
#include "UtilCollisionDetection.h"
#include "FourDirection.h"
#include <cmath>

ScreenObject::ScreenObject(Scyyl7Engine* pEngine, int iID, int iSize)
    :DisplayableObject(iSize, iSize, pEngine, iSize, iSize, false)
    , m_pEngine(pEngine)
    , m_iID(iID)
    , m_iSize(iSize)
{
    setVisible(true);
}

ScreenObject::~ScreenObject(void)
{
}

// Draw the shape of objects
void ScreenObject::virtDraw()
{
    if (!isVisible())
        return;

    if (1)
    {

        getEngine()->drawForegroundRectangle(
            m_iCurrentScreenX, m_iCurrentScreenY,
            m_iCurrentScreenX + m_iDrawWidth - 1,
            m_iCurrentScreenY + m_iDrawHeight - 1,
            0xd9bd50);

        getEngine()->drawForegroundRectangle(
            m_iCurrentScreenX + m_iDrawWidth/2 - 10, 
            m_iCurrentScreenY + m_iDrawHeight/2 - 10,
            m_iCurrentScreenX + m_iDrawWidth/2 + 10,
            m_iCurrentScreenY + m_iDrawHeight/2 + 10,
            0xb0832c);

        getEngine()->drawForegroundRectangle(
            m_iCurrentScreenX + m_iDrawWidth / 2 - 3, m_iCurrentScreenY - 8,
            m_iCurrentScreenX + m_iDrawWidth / 2 + 3,
            m_iCurrentScreenY + 15,
            0xac9751);

        getEngine()->drawForegroundRectangle(
            m_iCurrentScreenX, m_iCurrentScreenY,
            m_iCurrentScreenX + 6,
            m_iCurrentScreenY + m_iDrawHeight - 1,
            0x553e1d);

        getEngine()->drawForegroundRectangle(
            m_iCurrentScreenX + m_iDrawWidth - 7, m_iCurrentScreenY,
            m_iCurrentScreenX + m_iDrawWidth - 1,
            m_iCurrentScreenY + m_iDrawHeight - 1,
            0x553e1d);
    }
    else if (22)
    {
        getEngine()->drawForegroundRectangle(
            m_iCurrentScreenX, m_iCurrentScreenY,
            m_iCurrentScreenX + m_iDrawWidth - 1,
            m_iCurrentScreenY + m_iDrawHeight - 1,
            0x553e1d);

        getEngine()->drawForegroundPolygon(
            m_iCurrentScreenX, m_iCurrentScreenY,
            m_iCurrentScreenX + m_iDrawWidth / 3, m_iCurrentScreenY,
            m_iCurrentScreenX + m_iDrawWidth / 2, m_iCurrentScreenY - m_iDrawWidth / 2,
            m_iCurrentScreenX + 2*m_iDrawWidth / 3, m_iCurrentScreenY,
            m_iCurrentScreenX + m_iDrawWidth, m_iCurrentScreenY,
            m_iCurrentScreenX + m_iDrawWidth * 1.2, m_iCurrentScreenY + m_iDrawWidth / 2,
            m_iCurrentScreenX - 20, m_iCurrentScreenY + m_iDrawWidth / 2,
            0x03dac5);
    }
   
    
    int iCentreX = m_iCurrentScreenX + m_iStartDrawPosX + m_iDrawWidth;
    int iCentreY = m_iCurrentScreenY + m_iStartDrawPosY + m_iDrawHeight;

    //if ((m_szLabel != NULL) && (strlen(m_szLabel) > 0))
    //{
    //   getEngine()->drawForegroundString(iCentreX + m_iXLabelOffset, iCentreY + m_iYLabelOffset, m_szLabel, 0xffffff);
    //}
}

void ScreenObject::virtDoUpdate(int iCurrentTime)
{
    
    this->redrawDisplay();
}

BulletObject::BulletObject(Scyyl7Engine* pEngine, int iID, int iSize, 
    bool useTopLeftFor00, bool bVisible, 
    TankObject* tObj, NewTileManager* pTileManager)
    : ScreenObject(pEngine, iID, iSize)
    , m_dX(iSize), m_dY(iSize), m_dSX(0), m_dSY(0)
    , m_tank(tObj), m_tm(pTileManager)
{
    iUp = ImageManager::loadImage("images/bulletUp.png", true);
    iDown = ImageManager::loadImage("images/bulletDown.png", true);
    iLeft = ImageManager::loadImage("images/bulletLeft.png", true);
    iRight = ImageManager::loadImage("images/bulletRight.png", true);

    dir = 0;
    m_bullet = &iUp;
    m_iDrawWidth = m_bullet->getWidth();
    m_iDrawHeight = m_bullet->getHeight();
    // Offset within the drawing area to draw at - need to reset since width and height changed:
    m_iStartDrawPosX = useTopLeftFor00 ? 0 : -m_iDrawWidth / 2;
    m_iStartDrawPosY = useTopLeftFor00 ? 0 : -m_iDrawHeight / 2;
    pEngine->notifyObjectsAboutKeys(true);
    setVisible(bVisible);
}

void BulletObject::setPosition(double dX, double dY)
{
    m_dX = dX;
    m_dY = dY;
}

double BulletObject::getPositionX()
{
    return m_iCurrentScreenX;
}

double BulletObject::getPositionY()
{
    return m_iCurrentScreenY;
}

void BulletObject::setDirection(int direction)
{
    dir = direction;
    switch (direction)
    {
    case 0:
        m_bullet = &iUp;
        break;
    case 1:
        m_bullet = &iRight;
        break;
    case 2:
        m_bullet = &iDown;
        break;
    case 3:
        m_bullet = &iLeft;
        break;
    default:
        break;
    }
}

void BulletObject::setSpeed(double dSX, double dSY)
{
    m_dSX = dSX;
    m_dSY = dSY;
}

void BulletObject::virtDraw()
{
    if (isVisible())
    {
        m_bullet->renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0,
            m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY,
            m_iDrawWidth, m_iDrawHeight);
    }
}

// Use keyboard arrow key to control the object C
void BulletObject::virtDoUpdate(int iCurrentTime)
{
    if (isVisible())
    {   
        GhostObject* ghost;
        MonsterObject* monster;
        int oIndex = 5;

        while (oIndex <= 7)
        {
            ghost = (GhostObject*)getEngine()->getDisplayableObject(oIndex);
            if (ghost != NULL && ghost->isVisible())
            {  
                if (CollisionDetection::checkRectangles((int)(ghost->getPositionX()), (int)(ghost->getPositionX() + 50),
                    (int)(ghost->getPositionY()), (int)(ghost->getPositionY() + 50),
                    (int)(m_dX), (int)(m_dX + 20),
                    (int)(m_dY), (int)(m_dY + 20)))
                {
                    if (ghost->isVisible())
                        m_tank->setScore(m_tank->getScore() + 20);
                    ghost->setVisible(false);
                    setVisible(false);
                    
                    return;
                }
            }  
            oIndex++;
        }

        monster = (MonsterObject*)getEngine()->getDisplayableObject(oIndex);
        if (monster != NULL && monster->isVisible())
        {
            if (CollisionDetection::checkRectangles((int)(monster->getPositionX()), (int)(monster->getPositionX() + 50),
                (int)(monster->getPositionY()), (int)(monster->getPositionY() + 50),
                (int)(m_dX), (int)(m_dX + 20),
                (int)(m_dY), (int)(m_dY + 20)))
            {

                if (monster->getHP() >= 0)
                {
                    if (monster->isVisible())
                        m_tank->setScore(m_tank->getScore() + 20);
                    monster->minusHP();
                    setVisible(false);
                    return;
                }
                else
                {
                    if (monster->isVisible())
                        m_tank->setScore(m_tank->getScore() + 10);
                    monster->setVisible(false);
                    setVisible(false);
                    return;
                }

            }
        }

        ghost = NULL;
        monster = NULL;

        m_dX += m_dSX;
        m_dY += m_dSY;

        m_iCurrentScreenX = (int)(m_dX + 0.5);
        m_iCurrentScreenY = (int)(m_dY + 0.5);

        int pos = m_tm->getMapValue(floor(m_dX / 50), floor(m_dY / 50));
        if (pos == 1 || pos == 6)
        {
            setVisible(false);
        }

        if (m_iCurrentScreenX < 0)
        {
            m_iCurrentScreenX = 0;
            setVisible(false);
        }
        if (m_iCurrentScreenX >= getEngine()->getWindowWidth() - m_iDrawWidth)
        {
            m_iCurrentScreenX = getEngine()->getWindowWidth() - m_iDrawWidth;
            setVisible(false);
        }
            
        if (m_iCurrentScreenY < 0) 
        {
            m_iCurrentScreenY = 0;
            setVisible(false);
        }
            
        if (m_iCurrentScreenY >= getEngine()->getWindowHeight() - m_iDrawHeight)
        {
            m_iCurrentScreenY = getEngine()->getWindowHeight() - m_iDrawHeight;
            setVisible(false);
        }
        
    }
    redrawDisplay();
}

BulletObject::~BulletObject()
{
}


GhostObject::GhostObject(Scyyl7Engine* pEngine, int iID, int iSize
    , TankObject* obj)
    : ScreenObject(pEngine, iID, iSize)
    , m_dX(iSize), m_dY(iSize), m_dSX(5), m_dSY(5), tObj(obj)
    , m_iLastUpdatedTime(0)    
{
    m_ghost = ImageManager::loadImage("images/ghost.png", true);
}

void GhostObject::setPosition(double dX, double dY)
{
    m_dX = dX;
    m_dY = dY;
}

double GhostObject::getPositionX()
{
    return m_iCurrentScreenX;
}

double GhostObject::getPositionY()
{
    return m_iCurrentScreenY;
}

void GhostObject::setSpeed(double dSX, double dSY)
{
    m_dSX = dSX;
    m_dSY = dSY;
}

void GhostObject::virtDraw()
{
    if (isVisible())
    {
        int iTick = m_pEngine->getModifiedTime() / 300;
        int iFrame = iTick % 4;
        m_ghost.renderImageWithMask(m_pEngine->getForegroundSurface(), m_ghost.getWidth() / 4 * iFrame, 0,
            m_iCurrentScreenX, m_iCurrentScreenY, m_ghost.getWidth() / 4, m_ghost.getHeight());
    }
    
}

void GhostObject::virtDoUpdate(int iCurrentTime)
{
    if (isVisible())
    {
        // Check collision
        bool isCol = false;
        if (iCurrentTime > m_iLastUpdatedTime + 200)
        {
            m_iLastUpdatedTime = iCurrentTime;
            if (CollisionDetection::checkRectangles((int)(tObj->getPositionX()), (int)(tObj->getPositionX() + 50),
                (int)(tObj->getPositionY()), (int)(tObj->getPositionY() + 50),
                (int)(m_dX), (int)(m_dX + 50),
                (int)(m_dY), (int)(m_dY + 50)) && isCol == false)
            {
                isCol = true;
                if (tObj->getHp() > 1)
                {
                    (*tObj) = (*tObj) - 1;
                }
                else
                {
                    (*tObj) = (*tObj) - 1;
                    m_pEngine->setAllObjectsVisible(false);
                    m_pEngine->switchState(3);  // LostState
                }
            }
            else
            {
                isCol = false;
            }
        }

        m_dX += m_dSX;
        m_dY += m_dSY;

        if (m_dX < 50)
        {
            m_dX = 50;
            if (m_dSX < 0)
                m_dSX = -m_dSX;
        }

        if (m_dX > (getEngine()->getWindowWidth() - 75))
        {
            m_dX = getEngine()->getWindowWidth() - 75;
            if (m_dSX > 0)
                m_dSX = -m_dSX;
        }

        if (m_dY < 100)
        {
            m_dY = 100;
            if (m_dSY < 0)
                m_dSY = -m_dSY;
        }

        if (m_dY > (getEngine()->getWindowHeight() - 75))
        {
            m_dY = getEngine()->getWindowHeight() - 75;
            if (m_dSY > 0)
                m_dSY = -m_dSY;
        }

        m_iCurrentScreenX = (int)(m_dX + 0.5);
        m_iCurrentScreenY = (int)(m_dY + 0.5);
    }
    
    redrawDisplay();
}

GhostObject::~GhostObject()
{
}

TankObject::TankObject(Scyyl7Engine* pEngine, GameState* state, int iID, int iSize,
    bool useTopLeftFor00, bool bVisible, NewTileManager* pTileManager)
    : ScreenObject(pEngine, iID, iSize)
    , m_dX(iSize), m_dY(100), state(state)
    , image(ft.setUp()), m_tm(pTileManager)
    , m_direction(0), hp(4), m_iLastUpdatedTime(0), score(state->getGameScore())
{
    m_iDrawWidth = image->getWidth();
    m_iDrawHeight = image->getHeight();
    // Offset within the drawing area to draw at - need to reset since width and height changed:
    m_iStartDrawPosX = useTopLeftFor00 ? 0 : -m_iDrawWidth / 2;
    m_iStartDrawPosY = useTopLeftFor00 ? 0 : -m_iDrawHeight / 2;
    pEngine->notifyObjectsAboutMouse(true); // Tell BaseEngine to send us the mouse events because we use them
    setVisible(bVisible);
}

void TankObject::setPosition(double dX, double dY)
{
    m_dX = dX;
    m_dY = dY;
}

double TankObject::getPositionX()
{
    return m_iCurrentScreenX;
}

double TankObject::getPositionY()
{
    return m_iCurrentScreenY;
}


void TankObject::virtDraw()
{
    if (isVisible())
        image->renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0,
            m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY,
            m_iDrawWidth, m_iDrawHeight);

    displayHP();
    m_pEngine->lockForegroundForDrawing();
    char buf[20];
    sprintf(buf, "%d", score);
    if (hp <= 0)
    {
        m_pEngine->drawForegroundString(620, 20, " ", 0xe6d082,
            m_pEngine->getFont("resources/newFont.ttf", 65));
    }
    else
    {
        m_pEngine->drawForegroundString(620, 20, buf, 0xe6d082,
            m_pEngine->getFont("resources/newFont.ttf", 65));
    }
    m_pEngine->unlockForegroundForDrawing();

    redrawDisplay();
}

void TankObject::virtDoUpdate(int iCurrentTime)
{
    if (iCurrentTime > m_iLastUpdatedTime + 15)
    {
        m_iLastUpdatedTime = iCurrentTime;
        if (getEngine()->isKeyPressed(SDLK_UP))
        {
            m_direction = 0;
            image = ft.setUp();
            m_dY -= 5;
            int mapPos1 = m_tm->getMapValue(floor(m_dX / 50), floor(m_dY / 50));
            int mapPos2 = m_tm->getMapValue(floor(m_dX / 50) + 1, floor(m_dY / 50));
            if (floor(m_dX / 50) == (m_dX / 50))
            {
                if (!(mapPos1 == 0 || mapPos1 == 5 || mapPos1 == 3
                    || mapPos1 == 4 || mapPos1 == 8 || mapPos1 == 9))
                    m_dY += 5;
            }
            else
            {
                if (!(mapPos1 == 0 || mapPos1 == 5 || mapPos1 == 3
                    || mapPos1 == 4 || mapPos1 == 8 || mapPos1 == 9)
                    || !(mapPos2 == 0 || mapPos2 == 5 || mapPos2 == 3
                        || mapPos2 == 4 || mapPos2 == 8 || mapPos2 == 9))
                    m_dY += 5;
            }
        }

        if (getEngine()->isKeyPressed(SDLK_DOWN))
        {
            m_direction = 2;
            image = ft.setDown();
            m_dY += 5;
            int mapPos1 = m_tm->getMapValue(floor(m_dX / 50), ceil(m_dY / 50));
            int mapPos2 = m_tm->getMapValue(floor(m_dX / 50) + 1, ceil(m_dY / 50));
            if (floor(m_dX / 50) == (m_dX / 50))
            {
                if (!(mapPos1 == 0 || mapPos1 == 5 || mapPos1 == 3
                    || mapPos1 == 4 || mapPos1 == 8 || mapPos1 == 9))
                    m_dY -= 5;
            }
            else
            {
                if (!(mapPos1 == 0 || mapPos1 == 5 || mapPos1 == 3
                    || mapPos1 == 4 || mapPos1 == 8 || mapPos1 == 9)
                    || !(mapPos2 == 0 || mapPos2 == 5 || mapPos2 == 3
                        || mapPos2 == 4 || mapPos2 == 8 || mapPos2 == 9))
                    m_dY -= 5;
            }
        }

        if (getEngine()->isKeyPressed(SDLK_LEFT))
        {
            m_direction = 3;
            image = ft.setLeft();
            m_dX -= 5;
            int mapPos1 = m_tm->getMapValue(floor(m_dX / 50), floor(m_dY / 50));
            int mapPos2 = m_tm->getMapValue(floor(m_dX / 50), floor(m_dY / 50) + 1);
            if (floor(m_dY / 50) == (m_dY / 50))
            {
                if (!(mapPos1 == 0 || mapPos1 == 5 || mapPos1 == 3
                    || mapPos1 == 4 || mapPos1 == 8 || mapPos1 == 9))
                    m_dX += 5;
            }
            else
            {
                if (!(mapPos1 == 0 || mapPos1 == 5 || mapPos1 == 3
                    || mapPos1 == 4 || mapPos1 == 8 || mapPos1 == 9)
                    || !(mapPos2 == 0 || mapPos2 == 5 || mapPos2 == 3
                        || mapPos2 == 4 || mapPos2 == 8 || mapPos2 == 9))
                    m_dX += 5;
            }
        }

        if (getEngine()->isKeyPressed(SDLK_RIGHT))
        {
            m_direction = 1;
            image = ft.setRight();
            m_dX += 5;
            int mapPos1 = m_tm->getMapValue(ceil(m_dX / 50), floor(m_dY / 50));
            int mapPos2 = m_tm->getMapValue(ceil(m_dX / 50), floor(m_dY / 50) + 1);
            if (floor(m_dY / 50) == (m_dY / 50))
            {
                if (!(mapPos1 == 0 || mapPos1 == 5 || mapPos1 == 3
                    || mapPos1 == 4 || mapPos1 == 8 || mapPos1 == 9))
                    m_dX -= 5;
            }
            else
            {
                if (!(mapPos1 == 0 || mapPos1 == 5 || mapPos1 == 3
                    || mapPos1 == 4 || mapPos1 == 8 || mapPos1 == 9)
                    || !(mapPos2 == 0 || mapPos2 == 5 || mapPos2 == 3
                        || mapPos2 == 4 || mapPos2 == 8 || mapPos2 == 9))
                    m_dX -= 5;
            }
    }
    
    }
        

    m_iCurrentScreenX = (int)(m_dX + 0.5);
    m_iCurrentScreenY = (int)(m_dY + 0.5);

    if (m_iCurrentScreenX < 0)
        m_iCurrentScreenX = 0;
    if (m_iCurrentScreenX >= getEngine()->getWindowWidth() - m_iDrawWidth)
        m_iCurrentScreenX = getEngine()->getWindowWidth() - m_iDrawWidth;
    if (m_iCurrentScreenY < 0) m_iCurrentScreenY = 0;
    if (m_iCurrentScreenY >= getEngine()->getWindowHeight() - m_iDrawHeight)
        m_iCurrentScreenY = getEngine()->getWindowHeight() - m_iDrawHeight;

    if (m_tm->getMapValue(floor(m_dX / 50), floor(m_dY / 50)) == 3 
        || m_tm->getMapValue(floor(m_dX / 50), floor(m_dY / 50)) == 8)
    {
        if (m_pEngine->getTheme() == 1)
        {
            //printf("theme: %d\n", m_pEngine->getTheme());
            m_tm->setAndRedrawMapValueAt(5, 6, 0, m_pEngine,
                m_pEngine->getBackgroundSurface());
        }
        else
        {
            m_tm->setAndRedrawMapValueAt(5, 6, 5, m_pEngine,
                m_pEngine->getBackgroundSurface());
        }
        
    }

    if (m_tm->isValidTilePosition(m_iCurrentScreenX, m_iCurrentScreenY))
    {
        if (m_tm->getMapValue(m_iCurrentScreenX / 50, m_iCurrentScreenY / 50) == 4 ||
            m_tm->getMapValue(m_iCurrentScreenX / 50, m_iCurrentScreenY / 50) == 9)
        {
            setScore(score + 20 * hp);
            state->setGameScore(this->score);
            state->NextLevel();
            setPosition(50, 100);
        }
    }
}

int TankObject::getDirection()
{
    return this->m_direction;
}

void TankObject::setDirection(int dir)
{
    this->m_direction = dir;
}

int TankObject::getHp()
{
    return hp;
}

void TankObject::setHp(int ihp)
{
    hp = ihp;
}

void TankObject::displayHP()
{
    SimpleImage hpDis = ImageManager::loadImage("images/tankUp.png", true);
    hpDis.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0,
            1050, 20, m_iDrawWidth * hp, m_iDrawHeight);
}

int TankObject::getScore()
{
    return score;
}

void TankObject::setScore(int score)
{
    this->score = score;
}

MonsterObject::MonsterObject(Scyyl7Engine* pEngine, int iID, int iSize, 
    TankObject* obj, NewTileManager* tm) 
    : ScreenObject(pEngine, iID, iSize)
    , m_dX(iSize), m_dY(iSize), m_dSX(0), m_dSY(0), tObj(obj)
    , m_iLastUpdatedTime(0), m_tm(tm), mHP(5)
{
    m_monster = ImageManager::loadImage("images/monster.png", true);
}

void MonsterObject::setPosition(double dX, double dY)
{
    m_dX = dX;
    m_dY = dY;
}

double MonsterObject::getPositionX()
{
    return m_iCurrentScreenX;
}

double MonsterObject::getPositionY()
{
    return m_iCurrentScreenY;
}

void MonsterObject::virtDraw()
{
    if (isVisible())
    {
        int iTick = m_pEngine->getModifiedTime() / 100;
        int iFrame = iTick % 3;
        m_monster.renderImageWithMask(m_pEngine->getForegroundSurface(), m_monster.getWidth() / 3 * iFrame, 0,
            m_iCurrentScreenX, m_iCurrentScreenY, m_monster.getWidth() / 3, m_monster.getHeight());
    }
}

void MonsterObject::virtDoUpdate(int iCurrentTime)
{
    if (isVisible())
    {
        

        if (iCurrentTime > m_iLastUpdatedTime + 100)
        {
            m_iLastUpdatedTime = iCurrentTime;

            if (CollisionDetection::checkRectangles((int)(tObj->getPositionX()), (int)(tObj->getPositionX() + 50),
                (int)(tObj->getPositionY()), (int)(tObj->getPositionY() + 50),
                (int)(m_dX), (int)(m_dX + 50),
                (int)(m_dY), (int)(m_dY + 50)))
            {
             
                if (tObj->getHp() > 1)
                {
                    (*tObj) = (*tObj) - 1;
                    m_dX += -m_dSX;
                    m_dY += -m_dSY;
                }
                else
                {
                    (*tObj) = (*tObj) - 1;
                    m_pEngine->setAllObjectsVisible(false);
                    m_pEngine->switchState(3);  // LostState
                }
            }

            double disUp = calcDistance(tObj->getPositionX(), m_dX, tObj->getPositionY(), m_dY - 5);
            double disRight = calcDistance(tObj->getPositionX(), m_dX + 5, tObj->getPositionY(), m_dY);
            double disDown = calcDistance(tObj->getPositionX(), m_dX, tObj->getPositionY(), m_dY + 5);
            double disLeft = calcDistance(tObj->getPositionX(), m_dX - 5, tObj->getPositionY(), m_dY);
            
            double min = tempMin(disUp, disRight, disDown, disLeft);

            if (min == disUp)
            {
                m_dSX = 0;
                m_dSY = -10;
                m_dX += m_dSX;
                m_dY += m_dSY;
                if (m_tm->isValidTilePosition(m_dX + 25, m_dY))
                {
                    int pos = m_tm->getMapValue((m_dX + 25) / 50, (m_dY) / 50);
                    if (pos == 1 || pos == 6)
                    {
                        m_dSX = -m_dSX;
                        m_dSY = -m_dSY;
                        m_dX += m_dSX;
                        m_dY += m_dSY;
                    }
                }
            }
            else if (min == disRight)
            {
                m_dSX = 10;
                m_dSY = 0;
                m_dX += m_dSX;
                m_dY += m_dSY;
                if (m_tm->isValidTilePosition(m_dX + 50, m_dY + 25))
                {
                    int pos = m_tm->getMapValue((m_dX + 50) / 50, (m_dY + 25) / 50);
                    if (pos == 1 || pos == 6)
                    {
                        m_dSX = -m_dSX;
                        m_dSY = -m_dSY;
                        m_dX += m_dSX;
                        m_dY += m_dSY;
                    }
                }
            }
            else if (min == disDown)
            {
                m_dSX = 0;
                m_dSY = 10;
                m_dX += m_dSX;
                m_dY += m_dSY;
                if (m_tm->isValidTilePosition(m_dX + 25, m_dY + 50))
                {
                    int pos = m_tm->getMapValue((m_dX + 25) / 50, (m_dY + 50) / 50);
                    if (pos == 1 || pos == 6)
                    {
                        m_dSX = -m_dSX;
                        m_dSY = -m_dSY;
                        m_dX += m_dSX;
                        m_dY += m_dSY;
                    }
                }
            }
            else if (min == disLeft)
            {
                m_dSX = -10;
                m_dSY = 0;
                m_dX += m_dSX;
                m_dY += m_dSY;
                if (m_tm->isValidTilePosition(m_dX, m_dY + 25))
                {
                    int pos = m_tm->getMapValue((m_dX) / 50, (m_dY + 25) / 50);
                    if (pos == 1 || pos == 6)
                    {
                        m_dSX = -m_dSX;
                        m_dSY = -m_dSY;
                        m_dX += m_dSX;
                        m_dY += m_dSY;
                    }
                }
            }
        }

        if (m_dX < 50)
        {
            m_dX = 50;
            if (m_dSX < 0)
                m_dSX = -m_dSX;
        }

        if (m_dX > (getEngine()->getWindowWidth() - 75))
        {
            m_dX = getEngine()->getWindowWidth() - 75;
            if (m_dSX > 0)
                m_dSX = -m_dSX;
        }

        if (m_dY < 100)
        {
            m_dY = 100;
            if (m_dSY < 0)
                m_dSY = -m_dSY;
        }

        if (m_dY > (getEngine()->getWindowHeight() - 75))
        {
            m_dY = getEngine()->getWindowHeight() - 75;
            if (m_dSY > 0)
                m_dSY = -m_dSY;
        }

        m_iCurrentScreenX = (int)(m_dX + 0.5);
        m_iCurrentScreenY = (int)(m_dY + 0.5);
    }
}

double MonsterObject::calcDistance(double x1, double x2, double y1, double y2)
{
    double dis = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    return dis;
}

int MonsterObject::getHP()
{
    return mHP;
}

void MonsterObject::setHP(int hp)
{
    mHP = hp;
}

void MonsterObject::minusHP()
{
    mHP--;
}

MonsterObject::~MonsterObject()
{
}
