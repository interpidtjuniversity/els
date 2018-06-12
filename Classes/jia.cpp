#include "jia.h"
#include "SimpleAudioEngine.h"
#include "Over.h"
#include <vector>
using namespace std;


HelloWorld::HelloWorld()
{
	for (int i = 0; i < LINE; i++)
	{
		for (int j = 0; j < COLUME; j++)
		{
			m_pSquare[i][j] = NULL;
		}
	}

	m_pLabel = NULL;
	m_nCurScore = 0;
	newSquareType();
}

HelloWorld::~HelloWorld()
{

}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
void HelloWorld::onWin32KeyEvent(UINT message, WPARAM wParam, LPARAM lParam)
{
	//CCLog("onWin32KeyEvent message %d wParam %d lParam %d", message, wParam, lParam);  

	// Up  
	/*Win32KeyHook message 256 wParam 38 lParam 21495809
	onWin32KeyEvent message 256 wParam 38 lParam 21495809
	Win32KeyHook message 257 wParam 38 lParam -1052246015
	onWin32KeyEvent message 257 wParam 38 lParam -1052246015*/
	// Down  
	/*Win32KeyHook message 256 wParam 40 lParam 22020097
	onWin32KeyEvent message 256 wParam 40 lParam 22020097
	Win32KeyHook message 257 wParam 40 lParam -1051721727
	onWin32KeyEvent message 257 wParam 40 lParam -1051721727*/
	// Left  
	/*Win32KeyHook message 256 wParam 37 lParam 21692417
	onWin32KeyEvent message 256 wParam 37 lParam 21692417
	Win32KeyHook message 257 wParam 37 lParam -1052049407
	onWin32KeyEvent message 257 wParam 37 lParam -1052049407*/
	// Right  
	/*Win32KeyHook message 256 wParam 39 lParam 21823489
	onWin32KeyEvent message 256 wParam 39 lParam 21823489
	Win32KeyHook message 257 wParam 39 lParam -1051918335
	onWin32KeyEvent message 257 wParam 39 lParam -1051918335*/

	if (message == 256)  //��������
	{
		switch (wParam)
		{
		case 32:  //space
			nextSquareType();
			break;
		case 40:  //down
			updateDown(0.0);
			break;
		case 37:  //left
			updateLeft();
			break;
		case 39:  //right
			updateRight();
			break;
		}
	}
	else if (message == 257)  //��������
	{

	}
}
#endif

CCScene* HelloWorld::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	extern void Win32SetKeyLayer(HelloWorld *layer);
	Win32SetKeyLayer(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!CCLayerColor::initWithColor(ccc4(255, 255, 255, 255)))
	{
		return false;
	}

	//��ʼ��������ʾ
	char buf[4] = { 0 };
	m_nCurScore = 0;
	sprintf(buf, "%d", m_nCurScore);
	m_pLabel = CCLabelTTF::create(buf, "Arial", 15);
	m_pLabel->setColor(ccc3(0, 0, 0));
	m_pLabel->setAnchorPoint(ccp(0, 0));
	m_pLabel->setPosition(ccp(0, 508));
	this->addChild(m_pLabel, 1);

	//��ʼ������(10*18��)
	for (int i = 0; i < LINE; i++)
	{
		for (int j = 0; j < COLUME; j++)
		{
			m_pSquare[i][j] = CCSprite::create("square.png");
			m_pSquare[i][j]->setPosition(CCDirector::sharedDirector()->convertToGL(ccp(j * 20 + j * 2 + 10, i * 20 + i * 2 + 10)));
			m_pSquare[i][j]->setTag(0);
			m_pSquare[i][j]->setColor(ccc3(255, 255, 255));
			this->addChild(m_pSquare[i][j]);
		}
	}

	this->schedule(schedule_selector(HelloWorld::updateDown), 1.0);

	return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
#else
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}

void HelloWorld::updateScore()
{
	char buf[8] = { 0 };
	sprintf(buf, "%d", m_nCurScore);
	m_pLabel->setString(buf);
}

void HelloWorld::clearLine(int nLineStart, int nLineEnd)
{
	//�����Ϸ�Ƿ����
	checkFail();

	for (int i = nLineStart; i <= nLineEnd; i++)
	{
		int j;
		for (j = 0; j < COLUME; j++)
		{
			if (i > -1 && m_pSquare[i][j]->getTag() == 0)
			{
				break;
			}
		}

		if (COLUME == j)
		{
			//���һ��
			for (int k = i - 1; k >= 0; k--)
			{
				copyLine(k);
			}
			for (int x = 0; x < COLUME; x++)
			{
				m_pSquare[0][x]->setColor(ccc3(255, 255, 255));
				m_pSquare[0][x]->setTag(0);
			}
			m_nCurScore++;
		}
	}

	updateScore();
}

void HelloWorld::copyLine(int nlineNum)
{
	for (int i = 0; i < COLUME; i++)
	{
		m_pSquare[nlineNum + 1][i]->setColor(m_pSquare[nlineNum][i]->getColor());
		m_pSquare[nlineNum + 1][i]->setTag(m_pSquare[nlineNum][i]->getTag());
	}
}

void HelloWorld::newSquareType()
{
	m_nCurSquareType = rand() % 19 + 1;
	switch (m_nCurSquareType)
	{
	case 1:
	case 3:
	case 4:
	case 9:
	case 10:
	case 11:
	case 12:
	case 15:
	case 16:
		m_nCurline = 0;
		m_nCurcolume = 3;
		break;
	case 2:
	case 5:
	case 6:
	case 7:
	case 8:
	case 13:
	case 14:
	case 17:
	case 18:
	case 19:
		m_nCurline = 0;
		m_nCurcolume = 4;
		break;
	}
}

void HelloWorld::nextSquareType()
{
	switch (m_nCurSquareType)
	{
	case 1:
		//�ж��Ƿ���Ա任
		if (m_nCurline + 1 > LINE - 1)
		{
			return;
		}
		for (int i = 0; i < 4; i++)
		{
			if (i != 1 && m_nCurline - 2 + i > -1 && m_pSquare[m_nCurline - 2 + i][m_nCurcolume + 1]->getTag() == 1)
			{
				return;
			}
		}

		for (int i = 0; i < 4; i++)
		{
			if (i != 1 && m_nCurline - 1 > -1)
			{
				m_pSquare[m_nCurline - 1][m_nCurcolume + i]->setColor(ccc3(255, 255, 255));
				m_pSquare[m_nCurline - 1][m_nCurcolume + i]->setTag(0);
			}
			if (i != 1 && m_nCurline - 2 + i > -1)
			{
				m_pSquare[m_nCurline - 2 + i][m_nCurcolume + 1]->setColor(ccc3(52, 228, 249));
				m_pSquare[m_nCurline - 2 + i][m_nCurcolume + 1]->setTag(1);
			}
		}

		m_nCurline += 2;
		m_nCurcolume++;
		m_nCurSquareType = 2;
		break;
	case 2:
		//�ж��Ƿ���Ա任
		if (m_nCurcolume - 1 < 0 || m_nCurcolume + 2 > COLUME - 1)
		{
			return;
		}
		for (int i = 0; i < 4; i++)
		{
			if (i != 1 && m_nCurline - 2 > -1 && m_pSquare[m_nCurline - 2][m_nCurcolume - 1 + i]->getTag() == 1)
			{
				return;
			}
		}

		for (int i = 0; i < 4; i++)
		{
			if (i != 2 && m_nCurline - 4 + i > -1)
			{
				m_pSquare[m_nCurline - 4 + i][m_nCurcolume]->setColor(ccc3(255, 255, 255));
				m_pSquare[m_nCurline - 4 + i][m_nCurcolume]->setTag(0);
			}
			if (i != 1 && m_nCurline - 2 > -1)
			{
				m_pSquare[m_nCurline - 2][m_nCurcolume - 1 + i]->setColor(ccc3(52, 228, 249));
				m_pSquare[m_nCurline - 2][m_nCurcolume - 1 + i]->setTag(1);
			}
		}

		m_nCurline--;
		m_nCurcolume--;
		m_nCurSquareType = 1;
		break;
	case 3:
		//�ж��Ƿ���Ա任
		if (m_nCurline > LINE - 1)
		{
			return;
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 2 > -1 && m_pSquare[m_nCurline - 2][m_nCurcolume + 1 + i]->getTag() == 1)
			{
				return;
			}
		}
		if (m_pSquare[m_nCurline][m_nCurcolume + 1]->getTag() == 1)
		{
			return;
		}

		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 2 + i > -1)
			{
				m_pSquare[m_nCurline - 2 + i][m_nCurcolume]->setColor(ccc3(255, 255, 255));
				m_pSquare[m_nCurline - 2 + i][m_nCurcolume]->setTag(0);
			}
		}
		if (m_nCurline - 1 > -1)
		{
			m_pSquare[m_nCurline - 1][m_nCurcolume + 2]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 1][m_nCurcolume + 2]->setTag(0);
		}
		m_pSquare[m_nCurline][m_nCurcolume + 1]->setColor(ccc3(245, 30, 217));
		m_pSquare[m_nCurline][m_nCurcolume + 1]->setTag(1);
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 2 > -1)
			{
				m_pSquare[m_nCurline - 2][m_nCurcolume + 1 + i]->setColor(ccc3(245, 30, 217));
				m_pSquare[m_nCurline - 2][m_nCurcolume + 1 + i]->setTag(1);
			}
		}

		m_nCurline++;
		m_nCurcolume++;
		m_nCurSquareType = 4;
		break;
	case 4:
		//�ж��Ƿ���Ա任
		if (m_nCurcolume - 1 < 0)
		{
			return;
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 2 + i > -1 && m_pSquare[m_nCurline - 2 + i][m_nCurcolume + 1]->getTag() == 1)
			{
				return;
			}
		}
		if (m_nCurline - 2 > -1 && m_pSquare[m_nCurline - 2][m_nCurcolume - 1]->getTag() == 1)
		{
			return;
		}

		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 3 > -1)
			{
				m_pSquare[m_nCurline - 3][m_nCurcolume + i]->setColor(ccc3(255, 255, 255));
				m_pSquare[m_nCurline - 3][m_nCurcolume + i]->setTag(0);
			}
		}
		if (m_nCurline - 1 > -1)
		{
			m_pSquare[m_nCurline - 1][m_nCurcolume]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 1][m_nCurcolume]->setTag(0);
		}
		if (m_nCurline - 2 > -1)
		{
			m_pSquare[m_nCurline - 2][m_nCurcolume - 1]->setColor(ccc3(245, 30, 217));
			m_pSquare[m_nCurline - 2][m_nCurcolume - 1]->setTag(1);
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 2 + i > -1)
			{
				m_pSquare[m_nCurline - 2 + i][m_nCurcolume + 1]->setColor(ccc3(245, 30, 217));
				m_pSquare[m_nCurline - 2 + i][m_nCurcolume + 1]->setTag(1);
			}
		}

		m_nCurcolume--;
		m_nCurSquareType = 5;
		break;
	case 5:
		//�ж��Ƿ���Ա任
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 1 > -1 && m_pSquare[m_nCurline - 1][m_nCurcolume + i]->getTag() == 1)
			{
				return;
			}
		}
		if (m_nCurline - 3 > -1 && m_pSquare[m_nCurline - 3][m_nCurcolume + 1]->getTag() == 1)
		{
			return;
		}

		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 2 + i > -1)
			{
				m_pSquare[m_nCurline - 2 + i][m_nCurcolume + 2]->setColor(ccc3(255, 255, 255));
				m_pSquare[m_nCurline - 2 + i][m_nCurcolume + 2]->setTag(0);
			}
		}
		if (m_nCurline - 2 > -1)
		{
			m_pSquare[m_nCurline - 2][m_nCurcolume]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 2][m_nCurcolume]->setTag(0);
		}
		if (m_nCurline - 3 > -1)
		{
			m_pSquare[m_nCurline - 3][m_nCurcolume + 1]->setColor(ccc3(245, 30, 217));
			m_pSquare[m_nCurline - 3][m_nCurcolume + 1]->setTag(1);
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 1 > -1)
			{
				m_pSquare[m_nCurline - 1][m_nCurcolume + i]->setColor(ccc3(245, 30, 217));
				m_pSquare[m_nCurline - 1][m_nCurcolume + i]->setTag(1);
			}
		}

		m_nCurSquareType = 6;
		break;
	case 6:
		//�ж��Ƿ���Ա任
		if (m_nCurcolume + 2 > COLUME - 1)
		{
			return;
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 3 + i > -1 && m_pSquare[m_nCurline - 3 + i][m_nCurcolume]->getTag() == 1)
			{
				return;
			}
		}
		if (m_nCurline - 2 > -1 && m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->getTag() == 1)
		{
			return;
		}

		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 1 > -1)
			{
				m_pSquare[m_nCurline - 1][m_nCurcolume + i]->setColor(ccc3(255, 255, 255));
				m_pSquare[m_nCurline - 1][m_nCurcolume + i]->setTag(0);
			}
		}
		if (m_nCurline - 3 > -1)
		{
			m_pSquare[m_nCurline - 3][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 3][m_nCurcolume + 1]->setTag(0);
		}
		if (m_nCurline - 2 > -1)
		{
			m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->setColor(ccc3(245, 30, 217));
			m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->setTag(1);
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 3 + i > -1)
			{
				m_pSquare[m_nCurline - 3 + i][m_nCurcolume]->setColor(ccc3(245, 30, 217));
				m_pSquare[m_nCurline - 3 + i][m_nCurcolume]->setTag(1);
			}
		}

		m_nCurline--;
		m_nCurSquareType = 3;
		break;
	case 7:
		//�ж��Ƿ���Ա任
		if (m_nCurline > LINE - 1)
		{
			return;
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_pSquare[m_nCurline][m_nCurcolume + 1 + i]->getTag() == 1)
			{
				return;
			}
		}
		if (m_nCurline - 2 > -1 && m_pSquare[m_nCurline - 2][m_nCurcolume + 1]->getTag() == 1)
		{
			return;
		}

		if (m_nCurline - 1 > -1)
		{
			m_pSquare[m_nCurline - 1][m_nCurcolume]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 1][m_nCurcolume]->setTag(0);
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 2 + i > -1)
			{
				m_pSquare[m_nCurline - 2 + i][m_nCurcolume + 2]->setColor(ccc3(255, 255, 255));
				m_pSquare[m_nCurline - 2 + i][m_nCurcolume + 2]->setTag(0);
			}
		}
		for (int i = 0; i < 2; i++)
		{
			m_pSquare[m_nCurline][m_nCurcolume + 1 + i]->setColor(ccc3(245, 30, 217));
			m_pSquare[m_nCurline][m_nCurcolume + 1 + i]->setTag(1);
		}
		if (m_nCurline - 2 > -1)
		{
			m_pSquare[m_nCurline - 2][m_nCurcolume + 1]->setColor(ccc3(245, 30, 217));
			m_pSquare[m_nCurline - 2][m_nCurcolume + 1]->setTag(1);
		}

		m_nCurline++;
		m_nCurcolume++;
		m_nCurSquareType = 8;
		break;
	case 8:
		//�ж��Ƿ���Ա任
		if (m_nCurcolume - 1 < 0)
		{
			return;
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 2 + i > -1 && m_pSquare[m_nCurline - 2 + i][m_nCurcolume - 1]->getTag() == 1)
			{
				return;
			}
		}
		if (m_nCurline - 2 > -1 && m_pSquare[m_nCurline - 2][m_nCurcolume + 1]->getTag() == 1)
		{
			return;
		}

		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 1 > -1)
			{
				m_pSquare[m_nCurline - 1][m_nCurcolume + i]->setColor(ccc3(255, 255, 255));
				m_pSquare[m_nCurline - 1][m_nCurcolume + i]->setTag(0);
			}
		}
		if (m_nCurline - 3 > -1)
		{
			m_pSquare[m_nCurline - 3][m_nCurcolume]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 3][m_nCurcolume]->setTag(0);
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 2 + i > -1)
			{
				m_pSquare[m_nCurline - 2 + i][m_nCurcolume - 1]->setColor(ccc3(245, 30, 217));
				m_pSquare[m_nCurline - 2 + i][m_nCurcolume - 1]->setTag(1);
			}
		}
		if (m_nCurline - 2 > -1)
		{
			m_pSquare[m_nCurline - 2][m_nCurcolume + 1]->setColor(ccc3(245, 30, 217));
			m_pSquare[m_nCurline - 2][m_nCurcolume + 1]->setTag(1);
		}

		m_nCurcolume--;
		m_nCurSquareType = 9;
		break;
	case 9:
		//�ж��Ƿ���Ա任
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 3 > -1 && m_pSquare[m_nCurline - 3][m_nCurcolume + i]->getTag() == 1)
			{
				return;
			}
		}
		if (m_nCurline - 1 > -1 && m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->getTag() == 1)
		{
			return;
		}

		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 2 + i > -1)
			{
				m_pSquare[m_nCurline - 2 + i][m_nCurcolume]->setColor(ccc3(255, 255, 255));
				m_pSquare[m_nCurline - 2 + i][m_nCurcolume]->setTag(0);
			}
		}
		if (m_nCurline - 2 > -1)
		{
			m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->setTag(0);
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 3 > -1)
			{
				m_pSquare[m_nCurline - 3][m_nCurcolume + i]->setColor(ccc3(245, 30, 217));
				m_pSquare[m_nCurline - 3][m_nCurcolume + i]->setTag(1);
			}
		}
		if (m_nCurline - 1 > -1)
		{
			m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setColor(ccc3(245, 30, 217));
			m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setTag(1);
		}

		m_nCurSquareType = 10;
		break;
	case 10:
		//�ж��Ƿ���Ա任
		if (m_nCurcolume + 2 > COLUME - 1)
		{
			return;
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 3 + i > -1 && m_pSquare[m_nCurline - 3 + i][m_nCurcolume + 2]->getTag() == 1)
			{
				return;
			}
		}
		if (m_nCurline - 2 > -1 && m_pSquare[m_nCurline - 2][m_nCurcolume]->getTag() == 1)
		{
			return;
		}

		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 3 > -1)
			{
				m_pSquare[m_nCurline - 3][m_nCurcolume + i]->setColor(ccc3(255, 255, 255));
				m_pSquare[m_nCurline - 3][m_nCurcolume + i]->setTag(0);
			}
		}
		if (m_nCurline - 1 > -1)
		{
			m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setTag(0);
		}
		if (m_nCurline - 2 > -1)
		{
			m_pSquare[m_nCurline - 2][m_nCurcolume]->setColor(ccc3(245, 30, 217));
			m_pSquare[m_nCurline - 2][m_nCurcolume]->setTag(1);
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 3 + i > -1)
			{
				m_pSquare[m_nCurline - 3 + i][m_nCurcolume + 2]->setColor(ccc3(245, 30, 217));
				m_pSquare[m_nCurline - 3 + i][m_nCurcolume + 2]->setTag(1);
			}
		}

		m_nCurline--;
		m_nCurSquareType = 7;
		break;
	case 11:
		//�ж��Ƿ���Ա任
		if (m_nCurline > LINE - 1)
		{
			return;
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 1 + i > -1 && m_pSquare[m_nCurline - 1 + i][m_nCurcolume + 2]->getTag() == 1)
			{
				return;
			}
		}

		if (m_nCurline - 1 > -1)
		{
			m_pSquare[m_nCurline - 1][m_nCurcolume]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 1][m_nCurcolume]->setTag(0);
		}
		if (m_nCurline - 2 > -1)
		{
			m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->setTag(0);
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 1 + i > -1)
			{
				m_pSquare[m_nCurline - 1 + i][m_nCurcolume + 2]->setColor(ccc3(26, 242, 26));
				m_pSquare[m_nCurline - 1 + i][m_nCurcolume + 2]->setTag(1);
			}
		}

		m_nCurline++;
		m_nCurcolume++;
		m_nCurSquareType = 12;
		break;
	case 12:
		//�ж��Ƿ���Ա任
		if (m_nCurcolume - 1 < 0)
		{
			return;
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 1 > -1 && m_pSquare[m_nCurline - 1][m_nCurcolume - 1 + i]->getTag() == 1)
			{
				return;
			}
		}

		if (m_nCurline - 3 > -1)
		{
			m_pSquare[m_nCurline - 3][m_nCurcolume]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 3][m_nCurcolume]->setTag(0);
		}
		if (m_nCurline - 1 > -1)
		{
			m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setTag(0);
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 1 > -1)
			{
				m_pSquare[m_nCurline - 1][m_nCurcolume - 1 + i]->setColor(ccc3(26, 242, 26));
				m_pSquare[m_nCurline - 1][m_nCurcolume - 1 + i]->setTag(1);
			}
		}

		m_nCurcolume--;
		m_nCurSquareType = 11;
		break;
	case 13:
		//�ж��Ƿ���Ա任
		if (m_nCurline > LINE - 1)
		{
			return;
		}
		if (m_pSquare[m_nCurline][m_nCurcolume + 1]->getTag() == 1)
		{
			return;
		}
		if (m_nCurline - 2 > -1 && m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->getTag() == 1)
		{
			return;
		}

		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 2 > -1)
			{
				m_pSquare[m_nCurline - 2][m_nCurcolume + i]->setColor(ccc3(255, 255, 255));
				m_pSquare[m_nCurline - 2][m_nCurcolume + i]->setTag(0);
			}
		}
		m_pSquare[m_nCurline][m_nCurcolume + 1]->setColor(ccc3(26, 242, 26));
		m_pSquare[m_nCurline][m_nCurcolume + 1]->setTag(1);
		if (m_nCurline - 2 > -1)
		{
			m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->setColor(ccc3(26, 242, 26));
			m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->setTag(1);
		}

		m_nCurline++;
		m_nCurcolume++;
		m_nCurSquareType = 14;
		break;
	case 14:
		//�ж��Ƿ���Ա任
		if (m_nCurcolume - 1 < 0)
		{
			return;
		}
		if (m_nCurline - 2 > -1 && m_pSquare[m_nCurline - 2][m_nCurcolume - 1]->getTag() == 1)
		{
			return;
		}
		if (m_nCurline - 1 > -1 && m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->getTag() == 1)
		{
			return;
		}

		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 3 + i > -1)
			{
				m_pSquare[m_nCurline - 3 + i][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
				m_pSquare[m_nCurline - 3 + i][m_nCurcolume + 1]->setTag(0);
			}
		}
		if (m_nCurline - 2 > -1)
		{
			m_pSquare[m_nCurline - 2][m_nCurcolume - 1]->setColor(ccc3(26, 242, 26));
			m_pSquare[m_nCurline - 2][m_nCurcolume - 1]->setTag(1);
		}
		if (m_nCurline - 1 > -1)
		{
			m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setColor(ccc3(26, 242, 26));
			m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setTag(1);
		}

		m_nCurcolume--;
		m_nCurSquareType = 13;
		break;
	case 15:
		//�ж��Ƿ���Ա任
		if (m_nCurline > LINE - 1)
		{
			return;
		}
		if (m_pSquare[m_nCurline][m_nCurcolume + 1]->getTag() == 1)
		{
			return;
		}

		if (m_nCurline - 1 > -1)
		{
			m_pSquare[m_nCurline - 1][m_nCurcolume]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 1][m_nCurcolume]->setTag(0);
		}
		m_pSquare[m_nCurline][m_nCurcolume + 1]->setColor(ccc3(233, 178, 11));
		m_pSquare[m_nCurline][m_nCurcolume + 1]->setTag(1);

		m_nCurline++;
		m_nCurcolume++;
		m_nCurSquareType = 16;
		break;
	case 16:
		//�ж��Ƿ���Ա任
		if (m_nCurcolume - 1 < 0)
		{
			return;
		}
		if (m_nCurline - 2 > -1 && m_pSquare[m_nCurline - 2][m_nCurcolume - 1]->getTag() == 1)
		{
			return;
		}

		if (m_nCurline - 3 > -1)
		{
			m_pSquare[m_nCurline - 3][m_nCurcolume]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 3][m_nCurcolume]->setTag(0);
		}
		if (m_nCurline - 2 > -1)
		{
			m_pSquare[m_nCurline - 2][m_nCurcolume - 1]->setColor(ccc3(233, 178, 11));
			m_pSquare[m_nCurline - 2][m_nCurcolume - 1]->setTag(1);
		}

		m_nCurcolume--;
		m_nCurSquareType = 17;
		break;
	case 17:
		//�ж��Ƿ���Ա任
		if (m_nCurline - 3 > -1 && m_pSquare[m_nCurline - 3][m_nCurcolume + 1]->getTag() == 1)
		{
			return;
		}

		if (m_nCurline - 2 > -1)
		{
			m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->setTag(0);
		}
		if (m_nCurline - 3 > -1)
		{
			m_pSquare[m_nCurline - 3][m_nCurcolume + 1]->setColor(ccc3(233, 178, 11));
			m_pSquare[m_nCurline - 3][m_nCurcolume + 1]->setTag(1);
		}

		m_nCurSquareType = 18;
		break;
	case 18:
		//�ж��Ƿ���Ա任
		if (m_nCurcolume + 2 > COLUME - 1)
		{
			return;
		}
		if (m_nCurline - 2 > -1 && m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->getTag() == 1)
		{
			return;
		}

		if (m_nCurline - 1 > -1)
		{
			m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setTag(0);
		}
		if (m_nCurline - 2 > -1)
		{
			m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->setColor(ccc3(233, 178, 11));
			m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->setTag(1);
		}

		m_nCurline--;
		m_nCurSquareType = 15;
		break;
	case 19:
		break;
	}
}

void HelloWorld::gameOver()
{
	GameOverScene *gameOverScene = GameOverScene::create();
	gameOverScene->getLayer()->getLabel()->setString("You Lose!");
	CCDirector::sharedDirector()->replaceScene(gameOverScene);
}

void HelloWorld::checkFail()
{
	switch (m_nCurSquareType)
	{
	case 1:
		if (m_nCurline - 1 < 0)
		{
			gameOver();
		}
		break;
	case 2:
		if (m_nCurline - 4 < 0)
		{
			gameOver();
		}
		break;
	case 3:
	case 5:
	case 7:
	case 9:
	case 11:
	case 13:
	case 15:
	case 17:
	case 19:
		if (m_nCurline - 2 < 0)
		{
			gameOver();
		}
		break;
	case 4:
	case 6:
	case 8:
	case 10:
	case 12:
	case 14:
	case 16:
	case 18:
		if (m_nCurline - 3 < 0)
		{
			gameOver();
		}
		break;
	}
}

void HelloWorld::updateDown(float dt)
{
	switch (m_nCurSquareType)
	{
	case 1:
		//�ж��Ƿ���������½�
		if (m_nCurline >= LINE)
		{
			clearLine(LINE - 1, LINE - 1);
			newSquareType();
			return;
		}
		for (int i = 0; i < 4; i++)
		{
			if (m_pSquare[m_nCurline][m_nCurcolume + i]->getTag() == 1)
			{
				clearLine(m_nCurline - 1, m_nCurline - 1);
				newSquareType();
				return;
			}
		}

		//�½�һ��
		for (int i = 0; i < 4; i++)
		{
			//����ԭɫ
			if (m_nCurline < LINE && m_nCurline - 1 > -1)
			{
				m_pSquare[m_nCurline - 1][m_nCurcolume + i]->setColor(ccc3(255, 255, 255));
				m_pSquare[m_nCurline - 1][m_nCurcolume + i]->setTag(0);
			}
			//��ʾ��ɫ
			if (m_nCurline < LINE)
			{
				m_pSquare[m_nCurline][m_nCurcolume + i]->setColor(ccc3(52, 228, 249));
				m_pSquare[m_nCurline][m_nCurcolume + i]->setTag(1);
			}
		}

		m_nCurline++;
		break;
	case 2:
		//�ж��Ƿ���������½�
		if (m_nCurline >= LINE)
		{
			clearLine(LINE - 4, LINE - 1);
			newSquareType();
			return;
		}
		if (m_pSquare[m_nCurline][m_nCurcolume]->getTag() == 1)
		{
			clearLine(m_nCurline - 4, m_nCurline - 1);
			newSquareType();
			return;
		}

		//�½�һ��
		//����ԭɫ
		if (m_nCurline < LINE && m_nCurline - 4 > -1)
		{
			m_pSquare[m_nCurline - 4][m_nCurcolume]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 4][m_nCurcolume]->setTag(0);
		}
		//��ʾ��ɫ
		if (m_nCurline < LINE)
		{
			m_pSquare[m_nCurline][m_nCurcolume]->setColor(ccc3(52, 228, 249));
			m_pSquare[m_nCurline][m_nCurcolume]->setTag(1);
		}

		m_nCurline++;
		break;
	case 3:
		//�ж��Ƿ���������½�
		if (m_nCurline >= LINE)
		{
			clearLine(LINE - 2, LINE - 1);
			newSquareType();
			return;
		}
		for (int i = 0; i < 3; i++)
		{
			if (m_pSquare[m_nCurline][m_nCurcolume + i]->getTag() == 1)
			{
				clearLine(m_nCurline - 2, m_nCurline - 1);
				newSquareType();
				return;
			}
		}

		//�½�һ��
		for (int i = 0; i < 3; i++)
		{
			//����ԭɫ
			if (i != 0 && m_nCurline < LINE && m_nCurline - 1 > -1)
			{
				m_pSquare[m_nCurline - 1][m_nCurcolume + i]->setColor(ccc3(255, 255, 255));
				m_pSquare[m_nCurline - 1][m_nCurcolume + i]->setTag(0);
			}
			//��ʾ��ɫ
			if (m_nCurline < LINE)
			{
				m_pSquare[m_nCurline][m_nCurcolume + i]->setColor(ccc3(245, 30, 217));
				m_pSquare[m_nCurline][m_nCurcolume + i]->setTag(1);
			}
		}
		if (m_nCurline - 2 > -1)
		{
			m_pSquare[m_nCurline - 2][m_nCurcolume]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 2][m_nCurcolume]->setTag(0);
		}

		m_nCurline++;
		break;
	case 4:
		//�ж��Ƿ���������½�
		if (m_nCurline >= LINE)
		{
			clearLine(LINE - 3, LINE - 1);
			newSquareType();
			return;
		}
		if (m_pSquare[m_nCurline][m_nCurcolume]->getTag() == 1 ||
			(m_nCurline - 2 > -1 && m_pSquare[m_nCurline - 2][m_nCurcolume + 1]->getTag() == 1))
		{
			clearLine(m_nCurline - 3, m_nCurline - 1);
			newSquareType();
			return;
		}

		//�½�һ��
		for (int i = 0; i < 2; i++)
		{
			//����ԭɫ
			if (m_nCurline - 3 > -1)
			{
				m_pSquare[m_nCurline - 3][m_nCurcolume + i]->setColor(ccc3(255, 255, 255));
				m_pSquare[m_nCurline - 3][m_nCurcolume + i]->setTag(0);
			}
		}
		//��ʾ��ɫ
		if (m_nCurline - 2 > -1)
		{
			m_pSquare[m_nCurline - 2][m_nCurcolume + 1]->setColor(ccc3(245, 30, 217));
			m_pSquare[m_nCurline - 2][m_nCurcolume + 1]->setTag(1);
		}
		m_pSquare[m_nCurline][m_nCurcolume]->setColor(ccc3(245, 30, 217));
		m_pSquare[m_nCurline][m_nCurcolume]->setTag(1);

		m_nCurline++;
		break;
	case 5:
		//�ж��Ƿ���������½�
		if (m_nCurline >= LINE)
		{
			clearLine(LINE - 2, LINE - 1);
			newSquareType();
			return;
		}
		if (m_pSquare[m_nCurline][m_nCurcolume + 2]->getTag() == 1)
		{
			clearLine(m_nCurline - 2, m_nCurline - 1);
			newSquareType();
			return;
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 1 > -1 && m_pSquare[m_nCurline - 1][m_nCurcolume + i]->getTag() == 1)
			{
				clearLine(m_nCurline - 2, m_nCurline - 1);
				newSquareType();
				return;
			}
		}

		//�½�һ��
		for (int i = 0; i < 2; i++)
		{
			//����ԭɫ
			if (m_nCurline - 2 > -1)
			{
				m_pSquare[m_nCurline - 2][m_nCurcolume + i]->setColor(ccc3(255, 255, 255));
				m_pSquare[m_nCurline - 2][m_nCurcolume + i]->setTag(0);
			}
			//��ʾ��ɫ
			if (m_nCurline - 1 > -1)
			{
				m_pSquare[m_nCurline - 1][m_nCurcolume + i]->setColor(ccc3(245, 30, 217));
				m_pSquare[m_nCurline - 1][m_nCurcolume + i]->setTag(1);
			}
		}
		m_pSquare[m_nCurline][m_nCurcolume + 2]->setColor(ccc3(245, 30, 217));
		m_pSquare[m_nCurline][m_nCurcolume + 2]->setTag(1);
		if (m_nCurline - 2 > -1)
		{
			m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->setTag(0);
		}

		m_nCurline++;
		break;
	case 6:
		//�ж��Ƿ���������½�
		if (m_nCurline >= LINE)
		{
			clearLine(LINE - 3, LINE - 1);
			newSquareType();
			return;
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_pSquare[m_nCurline][m_nCurcolume + i]->getTag() == 1)
			{
				clearLine(m_nCurline - 3, m_nCurline - 1);
				newSquareType();
				return;
			}
		}

		//�½�һ��
		for (int i = 0; i < 2; i++)
		{
			m_pSquare[m_nCurline][m_nCurcolume + i]->setColor(ccc3(245, 30, 217));
			m_pSquare[m_nCurline][m_nCurcolume + i]->setTag(1);
		}
		if (m_nCurline - 1 > -1)
		{
			m_pSquare[m_nCurline - 1][m_nCurcolume]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 1][m_nCurcolume]->setTag(0);
		}
		if (m_nCurline - 3 > -1)
		{
			m_pSquare[m_nCurline - 3][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 3][m_nCurcolume + 1]->setTag(0);
		}

		m_nCurline++;
		break;
	case 7:
		//�ж��Ƿ���������½�
		if (m_nCurline >= LINE)
		{
			clearLine(LINE - 2, LINE - 1);
			newSquareType();
			return;
		}
		for (int i = 0; i < 3; i++)
		{
			if (m_pSquare[m_nCurline][m_nCurcolume + i]->getTag() == 1)
			{
				clearLine(m_nCurline - 2, m_nCurline - 1);
				newSquareType();
				return;
			}
		}

		//�½�һ��
		for (int i = 0; i < 3; i++)
		{
			m_pSquare[m_nCurline][m_nCurcolume + i]->setColor(ccc3(245, 30, 217));
			m_pSquare[m_nCurline][m_nCurcolume + i]->setTag(1);
		}
		if (m_nCurline - 2 > -1)
		{
			m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->setTag(0);
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 1 > -1)
			{
				m_pSquare[m_nCurline - 1][m_nCurcolume + i]->setColor(ccc3(255, 255, 255));
				m_pSquare[m_nCurline - 1][m_nCurcolume + i]->setTag(0);
			}
		}

		m_nCurline++;
		break;
	case 8:
		//�ж��Ƿ���������½�
		if (m_nCurline >= LINE)
		{
			clearLine(LINE - 3, LINE - 1);
			newSquareType();
			return;
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_pSquare[m_nCurline][m_nCurcolume + i]->getTag() == 1)
			{
				clearLine(m_nCurline - 3, m_nCurline - 1);
				newSquareType();
				return;
			}
		}

		//�½�һ��
		for (int i = 0; i < 2; i++)
		{
			m_pSquare[m_nCurline][m_nCurcolume + i]->setColor(ccc3(245, 30, 217));
			m_pSquare[m_nCurline][m_nCurcolume + i]->setTag(1);
		}
		if (m_nCurline - 3 > -1)
		{
			m_pSquare[m_nCurline - 3][m_nCurcolume]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 3][m_nCurcolume]->setTag(0);
		}
		if (m_nCurline - 1 > -1)
		{
			m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setTag(0);
		}

		m_nCurline++;
		break;
	case 9:
		//�ж��Ƿ���������½�
		if (m_nCurline >= LINE)
		{
			clearLine(LINE - 2, LINE - 1);
			newSquareType();
			return;
		}
		if (m_pSquare[m_nCurline][m_nCurcolume]->getTag() == 1)
		{
			clearLine(m_nCurline - 2, m_nCurline - 1);
			newSquareType();
			return;
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 1 > -1 && m_pSquare[m_nCurline - 1][m_nCurcolume + 1 + i]->getTag() == 1)
			{
				clearLine(m_nCurline - 2, m_nCurline - 1);
				newSquareType();
				return;
			}
		}

		//�½�һ��
		for (int i = 0; i < 2; i++)
		{
			//����ԭɫ
			if (m_nCurline - 2 > -1)
			{
				m_pSquare[m_nCurline - 2][m_nCurcolume + 1 + i]->setColor(ccc3(255, 255, 255));
				m_pSquare[m_nCurline - 2][m_nCurcolume + 1 + i]->setTag(0);
			}
			//��ʾ��ɫ
			if (m_nCurline - 1 > -1)
			{
				m_pSquare[m_nCurline - 1][m_nCurcolume + 1 + i]->setColor(ccc3(245, 30, 217));
				m_pSquare[m_nCurline - 1][m_nCurcolume + 1 + i]->setTag(1);
			}
		}
		m_pSquare[m_nCurline][m_nCurcolume]->setColor(ccc3(245, 30, 217));
		m_pSquare[m_nCurline][m_nCurcolume]->setTag(1);
		if (m_nCurline - 2 > -1)
		{
			m_pSquare[m_nCurline - 2][m_nCurcolume]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 2][m_nCurcolume]->setTag(0);
		}

		m_nCurline++;
		break;
	case 10:
		//�ж��Ƿ���������½�
		if (m_nCurline >= LINE)
		{
			clearLine(LINE - 3, LINE - 1);
			newSquareType();
			return;
		}
		if (m_pSquare[m_nCurline][m_nCurcolume + 1]->getTag() == 1 ||
			(m_nCurline - 2 > -1 && m_pSquare[m_nCurline - 2][m_nCurcolume]->getTag() == 1))
		{
			clearLine(m_nCurline - 3, m_nCurline - 1);
			newSquareType();
			return;
		}

		//�½�һ��
		for (int i = 0; i < 2; i++)
		{
			//����ԭɫ
			if (m_nCurline - 3 > -1)
			{
				m_pSquare[m_nCurline - 3][m_nCurcolume + i]->setColor(ccc3(255, 255, 255));
				m_pSquare[m_nCurline - 3][m_nCurcolume + i]->setTag(0);
			}
		}
		//��ʾ��ɫ
		if (m_nCurline - 2 > -1)
		{
			m_pSquare[m_nCurline - 2][m_nCurcolume]->setColor(ccc3(245, 30, 217));
			m_pSquare[m_nCurline - 2][m_nCurcolume]->setTag(1);
		}
		m_pSquare[m_nCurline][m_nCurcolume + 1]->setColor(ccc3(245, 30, 217));
		m_pSquare[m_nCurline][m_nCurcolume + 1]->setTag(1);

		m_nCurline++;
		break;
	case 11:
		//�ж��Ƿ���������½�
		if (m_nCurline >= LINE)
		{
			clearLine(LINE - 2, LINE - 1);
			newSquareType();
			return;
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_pSquare[m_nCurline][m_nCurcolume + i]->getTag() == 1)
			{
				clearLine(m_nCurline - 2, m_nCurline - 1);
				newSquareType();
				return;
			}
		}
		if (m_nCurline - 1 > -1 && m_pSquare[m_nCurline - 1][m_nCurcolume + 2]->getTag() == 1)
		{
			clearLine(m_nCurline - 2, m_nCurline - 1);
			newSquareType();
			return;
		}

		//�½�һ��
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 2 > -1)
			{
				m_pSquare[m_nCurline - 2][m_nCurcolume + 1 + i]->setColor(ccc3(255, 255, 255));
				m_pSquare[m_nCurline - 2][m_nCurcolume + 1 + i]->setTag(0);
			}
			m_pSquare[m_nCurline][m_nCurcolume + i]->setColor(ccc3(26, 242, 26));
			m_pSquare[m_nCurline][m_nCurcolume + i]->setTag(1);
		}
		if (m_nCurline - 1 > -1)
		{
			m_pSquare[m_nCurline - 1][m_nCurcolume]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 1][m_nCurcolume]->setTag(0);
			m_pSquare[m_nCurline - 1][m_nCurcolume + 2]->setColor(ccc3(26, 242, 26));
			m_pSquare[m_nCurline - 1][m_nCurcolume + 2]->setTag(1);
		}

		m_nCurline++;
		break;
	case 12:
		//�ж��Ƿ���������½�
		if (m_nCurline >= LINE)
		{
			clearLine(LINE - 3, LINE - 1);
			newSquareType();
			return;
		}
		if (m_pSquare[m_nCurline][m_nCurcolume + 1]->getTag() == 1)
		{
			clearLine(m_nCurline - 3, m_nCurline - 1);
			newSquareType();
			return;
		}
		if (m_nCurline - 1 > -1 && m_pSquare[m_nCurline - 1][m_nCurcolume]->getTag() == 1)
		{
			clearLine(m_nCurline - 3, m_nCurline - 1);
			newSquareType();
			return;
		}

		//�½�һ��
		if (m_nCurline - 3 > -1)
		{
			m_pSquare[m_nCurline - 3][m_nCurcolume]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 3][m_nCurcolume]->setTag(0);
		}
		if (m_nCurline - 1 > -1)
		{
			m_pSquare[m_nCurline - 1][m_nCurcolume]->setColor(ccc3(26, 242, 26));
			m_pSquare[m_nCurline - 1][m_nCurcolume]->setTag(1);
		}
		if (m_nCurline - 2 > -1)
		{
			m_pSquare[m_nCurline - 2][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 2][m_nCurcolume + 1]->setTag(0);
		}
		m_pSquare[m_nCurline][m_nCurcolume + 1]->setColor(ccc3(26, 242, 26));
		m_pSquare[m_nCurline][m_nCurcolume + 1]->setTag(1);

		m_nCurline++;
		break;
	case 13:
		//�ж��Ƿ���������½�
		if (m_nCurline >= LINE)
		{
			clearLine(LINE - 2, LINE - 1);
			newSquareType();
			return;
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_pSquare[m_nCurline][m_nCurcolume + 1 + i]->getTag() == 1)
			{
				clearLine(m_nCurline - 2, m_nCurline - 1);
				newSquareType();
				return;
			}
		}
		if (m_nCurline - 1 > -1 && m_pSquare[m_nCurline - 1][m_nCurcolume]->getTag() == 1)
		{
			clearLine(m_nCurline - 2, m_nCurline - 1);
			newSquareType();
			return;
		}

		//�½�һ��
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 2 > -1)
			{
				m_pSquare[m_nCurline - 2][m_nCurcolume + i]->setColor(ccc3(255, 255, 255));
				m_pSquare[m_nCurline - 2][m_nCurcolume + i]->setTag(0);
			}
			m_pSquare[m_nCurline][m_nCurcolume + 1 + i]->setColor(ccc3(26, 242, 26));
			m_pSquare[m_nCurline][m_nCurcolume + 1 + i]->setTag(1);
		}
		if (m_nCurline - 1 > -1)
		{
			m_pSquare[m_nCurline - 1][m_nCurcolume + 2]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 1][m_nCurcolume + 2]->setTag(0);
			m_pSquare[m_nCurline - 1][m_nCurcolume]->setColor(ccc3(26, 242, 26));
			m_pSquare[m_nCurline - 1][m_nCurcolume]->setTag(1);
		}

		m_nCurline++;
		break;
	case 14:
		//�ж��Ƿ���������½�
		if (m_nCurline >= LINE)
		{
			clearLine(LINE - 3, LINE - 1);
			newSquareType();
			return;
		}
		if (m_pSquare[m_nCurline][m_nCurcolume]->getTag() == 1)
		{
			clearLine(m_nCurline - 3, m_nCurline - 1);
			newSquareType();
			return;
		}
		if (m_nCurline - 1 > -1 && m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->getTag() == 1)
		{
			clearLine(m_nCurline - 3, m_nCurline - 1);
			newSquareType();
			return;
		}

		//�½�һ��
		if (m_nCurline - 3 > -1)
		{
			m_pSquare[m_nCurline - 3][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 3][m_nCurcolume + 1]->setTag(0);
		}
		if (m_nCurline - 1 > -1)
		{
			m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setColor(ccc3(26, 242, 26));
			m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setTag(1);
		}
		if (m_nCurline - 2 > -1)
		{
			m_pSquare[m_nCurline - 2][m_nCurcolume]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 2][m_nCurcolume]->setTag(0);
		}
		m_pSquare[m_nCurline][m_nCurcolume]->setColor(ccc3(26, 242, 26));
		m_pSquare[m_nCurline][m_nCurcolume]->setTag(1);

		m_nCurline++;
		break;
	case 15:
		//�ж��Ƿ���������½�
		if (m_nCurline >= LINE)
		{
			clearLine(LINE - 2, LINE - 1);
			newSquareType();
			return;
		}
		for (int i = 0; i < 3; i++)
		{
			if (m_pSquare[m_nCurline][m_nCurcolume + i]->getTag() == 1)
			{
				clearLine(m_nCurline - 2, m_nCurline - 1);
				newSquareType();
				return;
			}
		}

		//�½�һ��
		for (int i = 0; i < 3; i++)
		{
			m_pSquare[m_nCurline][m_nCurcolume + i]->setColor(ccc3(233, 178, 11));
			m_pSquare[m_nCurline][m_nCurcolume + i]->setTag(1);
			if (m_nCurline - 1 > -1 && i != 1)
			{
				m_pSquare[m_nCurline - 1][m_nCurcolume + i]->setColor(ccc3(255, 255, 255));
				m_pSquare[m_nCurline - 1][m_nCurcolume + i]->setTag(0);
			}
		}
		if (m_nCurline - 2 > -1)
		{
			m_pSquare[m_nCurline - 2][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 2][m_nCurcolume + 1]->setTag(0);
		}

		m_nCurline++;
		break;
	case 16:
		//�ж��Ƿ���������½�
		if (m_nCurline >= LINE)
		{
			clearLine(LINE - 3, LINE - 1);
			newSquareType();
			return;
		}
		if (m_pSquare[m_nCurline][m_nCurcolume]->getTag() == 1)
		{
			clearLine(m_nCurline - 3, m_nCurline - 1);
			newSquareType();
			return;
		}
		if (m_nCurline - 1 > -1 && m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->getTag() == 1)
		{
			clearLine(m_nCurline - 3, m_nCurline - 1);
			newSquareType();
			return;
		}

		//�½�һ��
		if (m_nCurline - 3 > -1)
		{
			m_pSquare[m_nCurline - 3][m_nCurcolume]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 3][m_nCurcolume]->setTag(0);
		}
		m_pSquare[m_nCurline][m_nCurcolume]->setColor(ccc3(233, 178, 11));
		m_pSquare[m_nCurline][m_nCurcolume]->setTag(1);
		if (m_nCurline - 2 > -1)
		{
			m_pSquare[m_nCurline - 2][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 2][m_nCurcolume + 1]->setTag(0);
		}
		if (m_nCurline - 1 > -1)
		{
			m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setColor(ccc3(233, 178, 11));
			m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setTag(1);
		}

		m_nCurline++;
		break;
	case 17:
		//�ж��Ƿ���������½�
		if (m_nCurline >= LINE)
		{
			clearLine(LINE - 2, LINE - 1);
			newSquareType();
			return;
		}
		if (m_pSquare[m_nCurline][m_nCurcolume + 1]->getTag() == 1)
		{
			clearLine(m_nCurline - 2, m_nCurline - 1);
			newSquareType();
			return;
		}
		if (m_nCurline - 1 > -1 && m_pSquare[m_nCurline - 1][m_nCurcolume]->getTag() == 1)
		{
			clearLine(m_nCurline - 2, m_nCurline - 1);
			newSquareType();
			return;
		}
		if (m_nCurline - 1 > -1 && m_pSquare[m_nCurline - 1][m_nCurcolume + 2]->getTag() == 1)
		{
			clearLine(m_nCurline - 2, m_nCurline - 1);
			newSquareType();
			return;
		}

		//�½�һ��
		for (int i = 0; i < 3; i++)
		{
			if (m_nCurline - 2 > -1)
			{
				m_pSquare[m_nCurline - 2][m_nCurcolume + i]->setColor(ccc3(255, 255, 255));
				m_pSquare[m_nCurline - 2][m_nCurcolume + i]->setTag(0);
			}
			if (i != 1 && m_nCurline - 1 > -1)
			{
				m_pSquare[m_nCurline - 1][m_nCurcolume + i]->setColor(ccc3(233, 178, 11));
				m_pSquare[m_nCurline - 1][m_nCurcolume + i]->setTag(1);
			}
		}
		m_pSquare[m_nCurline][m_nCurcolume + 1]->setColor(ccc3(233, 178, 11));
		m_pSquare[m_nCurline][m_nCurcolume + 1]->setTag(1);

		m_nCurline++;
		break;
	case 18:
		//�ж��Ƿ���������½�
		if (m_nCurline >= LINE)
		{
			clearLine(LINE - 3, LINE - 1);
			newSquareType();
			return;
		}
		if (m_pSquare[m_nCurline][m_nCurcolume + 1]->getTag() == 1)
		{
			clearLine(m_nCurline - 3, m_nCurline - 1);
			newSquareType();
			return;
		}
		if (m_nCurline - 1 > -1 && m_pSquare[m_nCurline - 1][m_nCurcolume]->getTag() == 1)
		{
			clearLine(m_nCurline - 3, m_nCurline - 1);
			newSquareType();
			return;
		}

		//�½�һ��
		if (m_nCurline - 3 > -1)
		{
			m_pSquare[m_nCurline - 3][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 3][m_nCurcolume + 1]->setTag(0);
		}
		m_pSquare[m_nCurline][m_nCurcolume + 1]->setColor(ccc3(233, 178, 11));
		m_pSquare[m_nCurline][m_nCurcolume + 1]->setTag(1);
		if (m_nCurline - 2 > -1)
		{
			m_pSquare[m_nCurline - 2][m_nCurcolume]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 2][m_nCurcolume]->setTag(0);
		}
		if (m_nCurline - 1 > -1)
		{
			m_pSquare[m_nCurline - 1][m_nCurcolume]->setColor(ccc3(233, 178, 11));
			m_pSquare[m_nCurline - 1][m_nCurcolume]->setTag(1);
		}

		m_nCurline++;
		break;
	case 19:
		//�ж��Ƿ���������½�
		if (m_nCurline >= LINE)
		{
			clearLine(LINE - 2, LINE - 1);
			newSquareType();
			return;
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_pSquare[m_nCurline][m_nCurcolume]->getTag() == 1)
			{
				clearLine(m_nCurline - 2, m_nCurline - 1);
				newSquareType();
				return;
			}
		}

		//�½�һ��
		for (int i = 0; i < 2; i++)
		{
			m_pSquare[m_nCurline][m_nCurcolume + i]->setColor(ccc3(244, 69, 46));
			m_pSquare[m_nCurline][m_nCurcolume + i]->setTag(1);
			if (m_nCurline - 2 > -1)
			{
				m_pSquare[m_nCurline - 2][m_nCurcolume + i]->setColor(ccc3(255, 255, 255));
				m_pSquare[m_nCurline - 2][m_nCurcolume + i]->setTag(0);
			}
		}

		m_nCurline++;
		break;
	}
}

void HelloWorld::updateLeft()
{
	switch (m_nCurSquareType)
	{
	case 1:
		//�ж��Ƿ������������
		if (m_nCurline - 1 < 0 || m_nCurcolume <= 0 || m_pSquare[m_nCurline - 1][m_nCurcolume - 1]->getTag() == 1)
		{
			return;
		}

		//����һ��
		m_pSquare[m_nCurline - 1][m_nCurcolume - 1]->setColor(ccc3(52, 228, 249));
		m_pSquare[m_nCurline - 1][m_nCurcolume - 1]->setTag(1);
		m_pSquare[m_nCurline - 1][m_nCurcolume + 3]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 1][m_nCurcolume + 3]->setTag(0);

		m_nCurcolume--;
		break;
	case 2:
		//�ж��Ƿ������������
		if (m_nCurcolume <= 0)
		{
			return;
		}
		for (int i = 0; i < 4; i++)
		{
			if (m_nCurline - 4 + i < 0 || m_pSquare[m_nCurline - 4 + i][m_nCurcolume - 1]->getTag() == 1)
			{
				return;
			}
		}

		//����һ��
		for (int i = 0; i < 4; i++)
		{
			m_pSquare[m_nCurline - 4 + i][m_nCurcolume - 1]->setColor(ccc3(52, 228, 249));
			m_pSquare[m_nCurline - 4 + i][m_nCurcolume - 1]->setTag(1);
			m_pSquare[m_nCurline - 4 + i][m_nCurcolume]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 4 + i][m_nCurcolume]->setTag(0);
		}

		m_nCurcolume--;
		break;
	case 3:
		//�ж��Ƿ������������
		if (m_nCurcolume <= 0)
		{
			return;
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 2 + i < 0 || m_pSquare[m_nCurline - 2 + i][m_nCurcolume - 1]->getTag() == 1)
			{
				return;
			}
		}

		//����һ��
		for (int i = 0; i < 2; i++)
		{
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume - 1]->setColor(ccc3(245, 30, 217));
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume - 1]->setTag(1);
		}
		m_pSquare[m_nCurline - 2][m_nCurcolume]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 2][m_nCurcolume]->setTag(0);
		m_pSquare[m_nCurline - 1][m_nCurcolume + 2]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 1][m_nCurcolume + 2]->setTag(0);

		m_nCurcolume--;
		break;
	case 4:
		//�ж��Ƿ������������
		if (m_nCurcolume <= 0)
		{
			return;
		}
		for (int i = 0; i < 3; i++)
		{
			if (m_nCurline - 3 + i < 0 || m_pSquare[m_nCurline - 3 + i][m_nCurcolume - 1]->getTag() == 1)
			{
				return;
			}
		}

		//����һ��
		for (int i = 0; i < 3; i++)
		{
			m_pSquare[m_nCurline - 3 + i][m_nCurcolume - 1]->setColor(ccc3(245, 30, 217));
			m_pSquare[m_nCurline - 3 + i][m_nCurcolume - 1]->setTag(1);

			if (i != 2 && m_nCurline - 2 + i > -1)
			{
				m_pSquare[m_nCurline - 2 + i][m_nCurcolume]->setColor(ccc3(255, 255, 255));
				m_pSquare[m_nCurline - 2 + i][m_nCurcolume]->setTag(0);
			}
		}
		m_pSquare[m_nCurline - 3][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 3][m_nCurcolume + 1]->setTag(0);

		m_nCurcolume--;
		break;
	case 5:
		//�ж��Ƿ������������
		if (m_nCurcolume <= 0)
		{
			return;
		}
		if (m_nCurline - 2 < 0 || m_pSquare[m_nCurline - 2][m_nCurcolume - 1]->getTag() == 1)
		{
			return;
		}
		if (m_nCurline - 1 < 0 || m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->getTag() == 1)
		{
			return;
		}

		//����һ��
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 2 + i > -1)
			{
				m_pSquare[m_nCurline - 2 + i][m_nCurcolume + 2]->setColor(ccc3(255, 255, 255));
				m_pSquare[m_nCurline - 2 + i][m_nCurcolume + 2]->setTag(0);
			}
		}
		m_pSquare[m_nCurline - 2][m_nCurcolume - 1]->setColor(ccc3(245, 30, 217));
		m_pSquare[m_nCurline - 2][m_nCurcolume - 1]->setTag(1);
		m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setColor(ccc3(245, 30, 217));
		m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setTag(1);

		m_nCurcolume--;
		break;
	case 6:
		//�ж��Ƿ������������
		if (m_nCurcolume <= 0)
		{
			return;
		}
		if (m_nCurline - 1 < 0 || m_pSquare[m_nCurline - 1][m_nCurcolume - 1]->getTag() == 1)
		{
			return;
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 3 + i < 0 || m_pSquare[m_nCurline - 3 + i][m_nCurcolume]->getTag() == 1)
			{
				return;
			}
		}

		//����һ��
		for (int i = 0; i < 2; i++)
		{
			m_pSquare[m_nCurline - 3 + i][m_nCurcolume]->setColor(ccc3(245, 30, 217));
			m_pSquare[m_nCurline - 3 + i][m_nCurcolume]->setTag(1);
			m_pSquare[m_nCurline - 3 + i][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 3 + i][m_nCurcolume + 1]->setTag(0);
		}
		m_pSquare[m_nCurline - 1][m_nCurcolume - 1]->setColor(ccc3(245, 30, 217));
		m_pSquare[m_nCurline - 1][m_nCurcolume - 1]->setTag(1);
		m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setTag(0);

		m_nCurcolume--;
		break;
	case 7:
		//�ж��Ƿ������������
		if (m_nCurcolume <= 0)
		{
			return;
		}
		if (m_nCurline - 1 < 0 || m_pSquare[m_nCurline - 1][m_nCurcolume - 1]->getTag() == 1)
		{
			return;
		}
		if (m_nCurline - 2 < 0 || m_pSquare[m_nCurline - 2][m_nCurcolume + 1]->getTag() == 1)
		{
			return;
		}

		//����һ��
		for (int i = 0; i < 2; i++)
		{
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume + 2]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume + 2]->setTag(0);
		}
		m_pSquare[m_nCurline - 2][m_nCurcolume + 1]->setColor(ccc3(245, 30, 217));
		m_pSquare[m_nCurline - 2][m_nCurcolume + 1]->setTag(1);
		m_pSquare[m_nCurline - 1][m_nCurcolume - 1]->setColor(ccc3(245, 30, 217));
		m_pSquare[m_nCurline - 1][m_nCurcolume - 1]->setTag(1);

		m_nCurcolume--;
		break;
	case 8:
		//�ж��Ƿ������������
		if (m_nCurcolume <= 0)
		{
			return;
		}
		for (int i = 0; i < 3; i++)
		{
			if (m_nCurline - 3 + i < 0 || m_pSquare[m_nCurline - 3 + i][m_nCurcolume - 1]->getTag() == 1)
			{
				return;
			}
		}

		//����һ��
		for (int i = 0; i < 3; i++)
		{
			m_pSquare[m_nCurline - 3 + i][m_nCurcolume - 1]->setColor(ccc3(245, 30, 217));
			m_pSquare[m_nCurline - 3 + i][m_nCurcolume - 1]->setTag(1);
			if (i != 2)
			{
				m_pSquare[m_nCurline - 3 + i][m_nCurcolume]->setColor(ccc3(255, 255, 255));
				m_pSquare[m_nCurline - 3 + i][m_nCurcolume]->setTag(0);
			}
		}
		m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setTag(0);

		m_nCurcolume--;
		break;
	case 9:
		//�ж��Ƿ������������
		if (m_nCurcolume <= 0)
		{
			return;
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 2 + i < 0 || m_pSquare[m_nCurline - 2 + i][m_nCurcolume - 1]->getTag() == 1)
			{
				return;
			}
		}

		//����һ��
		for (int i = 0; i < 2; i++)
		{
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume - 1]->setColor(ccc3(245, 30, 217));
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume - 1]->setTag(1);
		}
		m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->setTag(0);
		m_pSquare[m_nCurline - 1][m_nCurcolume]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 1][m_nCurcolume]->setTag(0);

		m_nCurcolume--;
		break;
	case 10:
		//�ж��Ƿ������������
		if (m_nCurcolume <= 0)
		{
			return;
		}
		if (m_nCurline - 3 < 0 || m_pSquare[m_nCurline - 3][m_nCurcolume - 1]->getTag() == 1)
		{
			return;
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 2 + i < 0 || m_pSquare[m_nCurline - 2 + i][m_nCurcolume]->getTag() == 1)
			{
				return;
			}
		}

		//����һ��
		for (int i = 0; i < 2; i++)
		{
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume]->setColor(ccc3(245, 30, 217));
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume]->setTag(1);
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume + 1]->setTag(0);
		}
		m_pSquare[m_nCurline - 3][m_nCurcolume - 1]->setColor(ccc3(245, 30, 217));
		m_pSquare[m_nCurline - 3][m_nCurcolume - 1]->setTag(1);
		m_pSquare[m_nCurline - 3][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 3][m_nCurcolume + 1]->setTag(0);

		m_nCurcolume--;
		break;
	case 11:
		//�ж��Ƿ������������
		if (m_nCurcolume <= 0)
		{
			return;
		}
		if (m_nCurline - 1 < 0 || m_pSquare[m_nCurline - 1][m_nCurcolume - 1]->getTag() == 1)
		{
			return;
		}
		if (m_nCurline - 2 < 0 || m_pSquare[m_nCurline - 2][m_nCurcolume]->getTag() == 1)
		{
			return;
		}

		//����һ��
		m_pSquare[m_nCurline - 1][m_nCurcolume - 1]->setColor(ccc3(26, 242, 26));
		m_pSquare[m_nCurline - 1][m_nCurcolume - 1]->setTag(1);
		m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setTag(0);
		m_pSquare[m_nCurline - 2][m_nCurcolume]->setColor(ccc3(26, 242, 26));
		m_pSquare[m_nCurline - 2][m_nCurcolume]->setTag(1);
		m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->setTag(0);

		m_nCurcolume--;
		break;
	case 12:
		//�ж��Ƿ������������
		if (m_nCurcolume <= 0)
		{
			return;
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 3 + i < 0 || m_pSquare[m_nCurline - 3 + i][m_nCurcolume - 1]->getTag() == 1)
			{
				return;
			}
		}
		if (m_nCurline - 1 < 0 || m_pSquare[m_nCurline - 1][m_nCurcolume]->getTag() == 1)
		{
			return;
		}

		//����һ��
		for (int i = 0; i < 2; i++)
		{
			m_pSquare[m_nCurline - 3 + i][m_nCurcolume - 1]->setColor(ccc3(26, 242, 26));
			m_pSquare[m_nCurline - 3 + i][m_nCurcolume - 1]->setTag(1);
		}
		for (int i = 0; i < 2; i++)
		{
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume + 1]->setTag(0);
		}
		m_pSquare[m_nCurline - 1][m_nCurcolume]->setColor(ccc3(26, 242, 26));
		m_pSquare[m_nCurline - 1][m_nCurcolume]->setTag(1);
		m_pSquare[m_nCurline - 3][m_nCurcolume]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 3][m_nCurcolume]->setTag(0);

		m_nCurcolume--;
		break;
	case 13:
		//�ж��Ƿ������������
		if (m_nCurcolume <= 0)
		{
			return;
		}
		if (m_nCurline - 2 < 0 || m_pSquare[m_nCurline - 2][m_nCurcolume - 1]->getTag() == 1)
		{
			return;
		}
		if (m_nCurline - 1 < 0 || m_pSquare[m_nCurline - 1][m_nCurcolume]->getTag() == 1)
		{
			return;
		}

		//����һ��
		m_pSquare[m_nCurline - 2][m_nCurcolume - 1]->setColor(ccc3(26, 242, 26));
		m_pSquare[m_nCurline - 2][m_nCurcolume - 1]->setTag(1);
		m_pSquare[m_nCurline - 2][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 2][m_nCurcolume + 1]->setTag(0);
		m_pSquare[m_nCurline - 1][m_nCurcolume]->setColor(ccc3(26, 242, 26));
		m_pSquare[m_nCurline - 1][m_nCurcolume]->setTag(1);
		m_pSquare[m_nCurline - 1][m_nCurcolume + 2]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 1][m_nCurcolume + 2]->setTag(0);

		m_nCurcolume--;
		break;
	case 14:
		//�ж��Ƿ������������
		if (m_nCurcolume <= 0)
		{
			return;
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 2 + i < 0 || m_pSquare[m_nCurline - 2 + i][m_nCurcolume - 1]->getTag() == 1)
			{
				return;
			}
		}
		if (m_nCurline - 3 < 0 || m_pSquare[m_nCurline - 3][m_nCurcolume]->getTag() == 1)
		{
			return;
		}

		//����һ��
		for (int i = 0; i < 2; i++)
		{
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume - 1]->setColor(ccc3(26, 242, 26));
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume - 1]->setTag(1);
		}
		for (int i = 0; i < 2; i++)
		{
			m_pSquare[m_nCurline - 3 + i][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 3 + i][m_nCurcolume + 1]->setTag(0);
		}
		m_pSquare[m_nCurline - 3][m_nCurcolume]->setColor(ccc3(26, 242, 26));
		m_pSquare[m_nCurline - 3][m_nCurcolume]->setTag(1);
		m_pSquare[m_nCurline - 1][m_nCurcolume]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 1][m_nCurcolume]->setTag(0);

		m_nCurcolume--;
		break;
	case 15:
		//�ж��Ƿ������������
		if (m_nCurcolume <= 0)
		{
			return;
		}
		if (m_nCurline - 1 < 0 || m_pSquare[m_nCurline - 1][m_nCurcolume - 1]->getTag() == 1)
		{
			return;
		}
		if (m_nCurline - 2 < 0 || m_pSquare[m_nCurline - 2][m_nCurcolume]->getTag() == 1)
		{
			return;
		}

		//����һ��
		m_pSquare[m_nCurline - 1][m_nCurcolume - 1]->setColor(ccc3(233, 178, 11));
		m_pSquare[m_nCurline - 1][m_nCurcolume - 1]->setTag(1);
		m_pSquare[m_nCurline - 1][m_nCurcolume + 2]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 1][m_nCurcolume + 2]->setTag(0);
		m_pSquare[m_nCurline - 2][m_nCurcolume]->setColor(ccc3(233, 178, 11));
		m_pSquare[m_nCurline - 2][m_nCurcolume]->setTag(1);
		m_pSquare[m_nCurline - 2][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 2][m_nCurcolume + 1]->setTag(0);

		m_nCurcolume--;
		break;
	case 16:
		//�ж��Ƿ������������
		if (m_nCurcolume <= 0)
		{
			return;
		}
		for (int i = 0; i < 3; i++)
		{
			if (m_nCurline - 3 + i < 0 || m_pSquare[m_nCurline - 3 + i][m_nCurcolume - 1]->getTag() == 1)
			{
				return;
			}
		}

		//����һ��
		for (int i = 0; i < 3; i++)
		{
			m_pSquare[m_nCurline - 3 + i][m_nCurcolume - 1]->setColor(ccc3(233, 178, 11));
			m_pSquare[m_nCurline - 3 + i][m_nCurcolume - 1]->setTag(1);
			if (i != 1)
			{
				m_pSquare[m_nCurline - 3 + i][m_nCurcolume]->setColor(ccc3(255, 255, 255));
				m_pSquare[m_nCurline - 3 + i][m_nCurcolume]->setTag(0);
			}
		}
		m_pSquare[m_nCurline - 2][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 2][m_nCurcolume + 1]->setTag(0);

		m_nCurcolume--;
		break;
	case 17:
		//�ж��Ƿ������������
		if (m_nCurcolume <= 0)
		{
			return;
		}
		if (m_nCurline - 2 < 0 || m_pSquare[m_nCurline - 2][m_nCurcolume - 1]->getTag() == 1)
		{
			return;
		}
		if (m_nCurline - 1 < 0 || m_pSquare[m_nCurline - 1][m_nCurcolume]->getTag() == 1)
		{
			return;
		}

		//����һ��
		m_pSquare[m_nCurline - 1][m_nCurcolume]->setColor(ccc3(233, 178, 11));
		m_pSquare[m_nCurline - 1][m_nCurcolume]->setTag(1);
		m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setTag(0);
		m_pSquare[m_nCurline - 2][m_nCurcolume - 1]->setColor(ccc3(233, 178, 11));
		m_pSquare[m_nCurline - 2][m_nCurcolume - 1]->setTag(1);
		m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->setTag(0);

		m_nCurcolume--;
		break;
	case 18:
		//�ж��Ƿ������������
		if (m_nCurcolume <= 0)
		{
			return;
		}
		if (m_nCurline - 2 < 0 || m_pSquare[m_nCurline - 2][m_nCurcolume - 1]->getTag() == 1)
		{
			return;
		}
		if (m_nCurline - 3 < 0 || m_pSquare[m_nCurline - 3][m_nCurcolume]->getTag() == 1)
		{
			return;
		}
		if (m_nCurline - 1 < 0 || m_pSquare[m_nCurline - 1][m_nCurcolume]->getTag() == 1)
		{
			return;
		}

		//����һ��
		for (int i = 0; i < 3; i++)
		{
			m_pSquare[m_nCurline - 3 + i][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 3 + i][m_nCurcolume + 1]->setTag(0);
			if (i != 1)
			{
				m_pSquare[m_nCurline - 3 + i][m_nCurcolume]->setColor(ccc3(233, 178, 11));
				m_pSquare[m_nCurline - 3 + i][m_nCurcolume]->setTag(1);
			}
		}
		m_pSquare[m_nCurline - 2][m_nCurcolume - 1]->setColor(ccc3(233, 178, 11));
		m_pSquare[m_nCurline - 2][m_nCurcolume - 1]->setTag(1);

		m_nCurcolume--;
		break;
	case 19:
		//�ж��Ƿ������������
		if (m_nCurcolume <= 0)
		{
			return;
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 2 + i < 0 || m_pSquare[m_nCurline - 2 + i][m_nCurcolume - 1]->getTag() == 1)
			{
				return;
			}
		}

		//����һ��
		for (int i = 0; i < 2; i++)
		{
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume - 1]->setColor(ccc3(244, 69, 46));
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume - 1]->setTag(1);
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume + 1]->setTag(0);
		}

		m_nCurcolume--;
		break;
	}
}

void HelloWorld::updateRight()
{
	switch (m_nCurSquareType)
	{
	case 1:
		//�ж��Ƿ������������
		if (m_nCurline - 1 < 0 || m_nCurcolume + 3 >= COLUME - 1 || m_pSquare[m_nCurline - 1][m_nCurcolume + 3 + 1]->getTag() == 1)
		{
			return;
		}

		//����һ��
		m_pSquare[m_nCurline - 1][m_nCurcolume + 3 + 1]->setColor(ccc3(52, 228, 249));
		m_pSquare[m_nCurline - 1][m_nCurcolume + 3 + 1]->setTag(1);
		m_pSquare[m_nCurline - 1][m_nCurcolume]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 1][m_nCurcolume]->setTag(0);

		m_nCurcolume++;
		break;
	case 2:
		//�ж��Ƿ������������
		if (m_nCurcolume >= COLUME - 1)
		{
			return;
		}
		for (int i = 0; i < 4; i++)
		{
			if (m_nCurline - 4 + i < 0 || m_pSquare[m_nCurline - 4 + i][m_nCurcolume + 1]->getTag() == 1)
			{
				return;
			}
		}

		//����һ��
		for (int i = 0; i < 4; i++)
		{
			m_pSquare[m_nCurline - 4 + i][m_nCurcolume + 1]->setColor(ccc3(52, 228, 249));
			m_pSquare[m_nCurline - 4 + i][m_nCurcolume + 1]->setTag(1);
			m_pSquare[m_nCurline - 4 + i][m_nCurcolume]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 4 + i][m_nCurcolume]->setTag(0);
		}

		m_nCurcolume++;
		break;
	case 3:
		//�ж��Ƿ������������
		if (m_nCurcolume + 2 >= COLUME - 1)
		{
			return;
		}
		if (m_nCurline - 1 < 0 || m_pSquare[m_nCurline - 1][m_nCurcolume + 3]->getTag() == 1)
		{
			return;
		}
		if (m_nCurline - 2 < 0 || m_pSquare[m_nCurline - 2][m_nCurcolume + 1]->getTag() == 1)
		{
			return;
		}

		//����һ��
		for (int i = 0; i < 2; i++)
		{
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume]->setTag(0);
		}
		m_pSquare[m_nCurline - 2][m_nCurcolume + 1]->setColor(ccc3(245, 30, 217));
		m_pSquare[m_nCurline - 2][m_nCurcolume + 1]->setTag(1);
		m_pSquare[m_nCurline - 1][m_nCurcolume + 3]->setColor(ccc3(245, 30, 217));
		m_pSquare[m_nCurline - 1][m_nCurcolume + 3]->setTag(1);

		m_nCurcolume++;
		break;
	case 4:
		//�ж��Ƿ������������
		if (m_nCurcolume + 1 >= COLUME - 1)
		{
			return;
		}
		if (m_nCurline - 3 < 0 || m_pSquare[m_nCurline - 3][m_nCurcolume + 2]->getTag() == 1)
		{
			return;
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 2 + i < 0 || m_pSquare[m_nCurline - 2 + i][m_nCurcolume + 1]->getTag() == 1)
			{
				return;
			}
		}

		//����һ��
		for (int i = 0; i < 2; i++)
		{
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume + 1]->setColor(ccc3(245, 30, 217));
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume + 1]->setTag(1);
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume]->setTag(0);
		}
		m_pSquare[m_nCurline - 3][m_nCurcolume]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 3][m_nCurcolume]->setTag(0);
		m_pSquare[m_nCurline - 3][m_nCurcolume + 2]->setColor(ccc3(245, 30, 217));
		m_pSquare[m_nCurline - 3][m_nCurcolume + 2]->setTag(1);

		m_nCurcolume++;
		break;
	case 5:
		//�ж��Ƿ������������
		if (m_nCurcolume + 2 >= COLUME - 1)
		{
			return;
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 2 + i < 0 || m_pSquare[m_nCurline - 2 + i][m_nCurcolume + 3]->getTag() == 1)
			{
				return;
			}
		}

		//����һ��
		for (int i = 0; i < 2; i++)
		{
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume + 3]->setColor(ccc3(245, 30, 217));
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume + 3]->setTag(1);
		}
		m_pSquare[m_nCurline - 2][m_nCurcolume]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 2][m_nCurcolume]->setTag(0);
		m_pSquare[m_nCurline - 1][m_nCurcolume + 2]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 1][m_nCurcolume + 2]->setTag(0);

		m_nCurcolume++;
		break;
	case 6:
		//�ж��Ƿ������������
		if (m_nCurcolume + 1 >= COLUME - 1)
		{
			return;
		}
		for (int i = 0; i < 3; i++)
		{
			if (m_nCurline - 3 + i < 0 || m_pSquare[m_nCurline - 3 + i][m_nCurcolume + 2]->getTag() == 1)
			{
				return;
			}
		}

		//����һ��
		for (int i = 0; i < 3; i++)
		{
			m_pSquare[m_nCurline - 3 + i][m_nCurcolume + 2]->setColor(ccc3(245, 30, 217));
			m_pSquare[m_nCurline - 3 + i][m_nCurcolume + 2]->setTag(1);
			if (i != 2)
			{
				m_pSquare[m_nCurline - 3 + i][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
				m_pSquare[m_nCurline - 3 + i][m_nCurcolume + 1]->setTag(0);
			}
		}
		m_pSquare[m_nCurline - 1][m_nCurcolume]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 1][m_nCurcolume]->setTag(0);

		m_nCurcolume++;
		break;
	case 7:
		//�ж��Ƿ������������
		if (m_nCurcolume + 2 >= COLUME - 1)
		{
			return;
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 2 + i < 0 || m_pSquare[m_nCurline - 2 + i][m_nCurcolume + 3]->getTag() == 1)
			{
				return;
			}
		}

		//����һ��
		for (int i = 0; i < 2; i++)
		{
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume + 3]->setColor(ccc3(245, 30, 217));
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume + 3]->setTag(1);
		}
		m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->setTag(0);
		m_pSquare[m_nCurline - 1][m_nCurcolume]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 1][m_nCurcolume]->setTag(0);

		m_nCurcolume++;
		break;
	case 8:
		//�ж��Ƿ������������
		if (m_nCurcolume + 1 >= COLUME - 1)
		{
			return;
		}
		if (m_nCurline - 1 < 0 || m_pSquare[m_nCurline - 1][m_nCurcolume + 2]->getTag() == 1)
		{
			return;
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 3 + i < 0 || m_pSquare[m_nCurline - 3 + i][m_nCurcolume + 1]->getTag() == 1)
			{
				return;
			}
		}

		//����һ��
		for (int i = 0; i < 2; i++)
		{
			m_pSquare[m_nCurline - 3 + i][m_nCurcolume + 1]->setColor(ccc3(245, 30, 217));
			m_pSquare[m_nCurline - 3 + i][m_nCurcolume + 1]->setTag(1);
			m_pSquare[m_nCurline - 3 + i][m_nCurcolume]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 3 + i][m_nCurcolume]->setTag(0);
		}
		m_pSquare[m_nCurline - 1][m_nCurcolume]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 1][m_nCurcolume]->setTag(0);
		m_pSquare[m_nCurline - 1][m_nCurcolume + 2]->setColor(ccc3(245, 30, 217));
		m_pSquare[m_nCurline - 1][m_nCurcolume + 2]->setTag(1);

		m_nCurcolume++;
		break;
	case 9:
		//�ж��Ƿ������������
		if (m_nCurcolume + 2 >= COLUME - 1)
		{
			return;
		}
		if (m_nCurline - 2 < 0 || m_pSquare[m_nCurline - 2][m_nCurcolume + 3]->getTag() == 1)
		{
			return;
		}
		if (m_nCurline - 1 < 0 || m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->getTag() == 1)
		{
			return;
		}

		//����һ��
		for (int i = 0; i < 2; i++)
		{
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume]->setTag(0);
		}
		m_pSquare[m_nCurline - 2][m_nCurcolume + 3]->setColor(ccc3(245, 30, 217));
		m_pSquare[m_nCurline - 2][m_nCurcolume + 3]->setTag(1);
		m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setColor(ccc3(245, 30, 217));
		m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setTag(1);

		m_nCurcolume++;
		break;
	case 10:
		//�ж��Ƿ������������
		if (m_nCurcolume + 1 >= COLUME - 1)
		{
			return;
		}
		for (int i = 0; i < 3; i++)
		{
			if (m_nCurline - 3 + i < 0 || m_pSquare[m_nCurline - 3 + i][m_nCurcolume + 2]->getTag() == 1)
			{
				return;
			}
		}

		//����һ��
		for (int i = 0; i < 3; i++)
		{
			m_pSquare[m_nCurline - 3 + i][m_nCurcolume + 2]->setColor(ccc3(245, 30, 217));
			m_pSquare[m_nCurline - 3 + i][m_nCurcolume + 2]->setTag(1);
			if (i != 0)
			{
				m_pSquare[m_nCurline - 3 + i][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
				m_pSquare[m_nCurline - 3 + i][m_nCurcolume + 1]->setTag(0);
			}
		}
		m_pSquare[m_nCurline - 3][m_nCurcolume]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 3][m_nCurcolume]->setTag(0);

		m_nCurcolume++;
		break;
	case 11:
		//�ж��Ƿ������������
		if (m_nCurcolume + 2 >= COLUME - 1)
		{
			return;
		}
		if (m_nCurline - 2 < 0 || m_pSquare[m_nCurline - 2][m_nCurcolume + 3]->getTag() == 1)
		{
			return;
		}
		if (m_nCurline - 1 < 0 || m_pSquare[m_nCurline - 1][m_nCurcolume + 2]->getTag() == 1)
		{
			return;
		}

		//����һ��
		m_pSquare[m_nCurline - 2][m_nCurcolume + 3]->setColor(ccc3(26, 242, 26));
		m_pSquare[m_nCurline - 2][m_nCurcolume + 3]->setTag(1);
		m_pSquare[m_nCurline - 2][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 2][m_nCurcolume + 1]->setTag(0);
		m_pSquare[m_nCurline - 1][m_nCurcolume + 2]->setColor(ccc3(26, 242, 26));
		m_pSquare[m_nCurline - 1][m_nCurcolume + 2]->setTag(1);
		m_pSquare[m_nCurline - 1][m_nCurcolume]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 1][m_nCurcolume]->setTag(0);

		m_nCurcolume++;
		break;
	case 12:
		//�ж��Ƿ������������
		if (m_nCurcolume + 1 >= COLUME - 1)
		{
			return;
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 2 < 0 || m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->getTag() == 1)
			{
				return;
			}
		}
		if (m_nCurline - 3 < 0 || m_pSquare[m_nCurline - 3][m_nCurcolume + 1]->getTag() == 1)
		{
			return;
		}

		//����һ��
		for (int i = 0; i < 2; i++)
		{
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume + 2]->setColor(ccc3(26, 242, 26));
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume + 2]->setTag(1);
		}
		for (int i = 0; i < 2; i++)
		{
			m_pSquare[m_nCurline - 3 + i][m_nCurcolume]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 3 + i][m_nCurcolume]->setTag(0);
		}
		m_pSquare[m_nCurline - 3][m_nCurcolume + 1]->setColor(ccc3(26, 242, 26));
		m_pSquare[m_nCurline - 3][m_nCurcolume + 1]->setTag(1);
		m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setTag(0);

		m_nCurcolume++;
		break;
	case 13:
		//�ж��Ƿ������������
		if (m_nCurcolume + 2 >= COLUME - 1)
		{
			return;
		}
		if (m_nCurline - 1 < 0 || m_pSquare[m_nCurline - 1][m_nCurcolume + 3]->getTag() == 1)
		{
			return;
		}
		if (m_nCurline - 2 < 0 || m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->getTag() == 1)
		{
			return;
		}

		//����һ��
		m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->setColor(ccc3(26, 242, 26));
		m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->setTag(1);
		m_pSquare[m_nCurline - 2][m_nCurcolume]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 2][m_nCurcolume]->setTag(0);
		m_pSquare[m_nCurline - 1][m_nCurcolume + 3]->setColor(ccc3(26, 242, 26));
		m_pSquare[m_nCurline - 1][m_nCurcolume + 3]->setTag(1);
		m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setTag(0);

		m_nCurcolume++;
		break;
	case 14:
		//�ж��Ƿ������������
		if (m_nCurcolume + 1 >= COLUME - 1)
		{
			return;
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 3 < 0 || m_pSquare[m_nCurline - 3][m_nCurcolume + 2]->getTag() == 1)
			{
				return;
			}
		}
		if (m_nCurline - 1 < 0 || m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->getTag() == 1)
		{
			return;
		}

		//����һ��
		for (int i = 0; i < 2; i++)
		{
			m_pSquare[m_nCurline - 3 + i][m_nCurcolume + 2]->setColor(ccc3(26, 242, 26));
			m_pSquare[m_nCurline - 3 + i][m_nCurcolume + 2]->setTag(1);
		}
		for (int i = 0; i < 2; i++)
		{
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume]->setTag(0);
		}
		m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setColor(ccc3(26, 242, 26));
		m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setTag(1);
		m_pSquare[m_nCurline - 3][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 3][m_nCurcolume + 1]->setTag(0);

		m_nCurcolume++;
		break;
	case 15:
		//�ж��Ƿ������������
		if (m_nCurcolume + 2 >= COLUME - 1)
		{
			return;
		}
		if (m_nCurline - 1 < 0 || m_pSquare[m_nCurline - 1][m_nCurcolume + 3]->getTag() == 1)
		{
			return;
		}
		if (m_nCurline - 2 < 0 || m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->getTag() == 1)
		{
			return;
		}

		//����һ��
		m_pSquare[m_nCurline - 1][m_nCurcolume + 3]->setColor(ccc3(233, 178, 11));
		m_pSquare[m_nCurline - 1][m_nCurcolume + 3]->setTag(1);
		m_pSquare[m_nCurline - 1][m_nCurcolume]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 1][m_nCurcolume]->setTag(0);
		m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->setColor(ccc3(233, 178, 11));
		m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->setTag(1);
		m_pSquare[m_nCurline - 2][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 2][m_nCurcolume + 1]->setTag(0);

		m_nCurcolume++;
		break;
	case 16:
		//�ж��Ƿ������������
		if (m_nCurcolume + 1 >= COLUME - 1)
		{
			return;
		}
		if (m_nCurline - 2 < 0 || m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->getTag() == 1)
		{
			return;
		}
		if (m_nCurline - 3 < 0 || m_pSquare[m_nCurline - 3][m_nCurcolume + 1]->getTag() == 1)
		{
			return;
		}
		if (m_nCurline - 1 < 0 || m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->getTag() == 1)
		{
			return;
		}

		//����һ��
		for (int i = 0; i < 3; i++)
		{
			m_pSquare[m_nCurline - 3 + i][m_nCurcolume]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 3 + i][m_nCurcolume]->setTag(0);
			if (i != 1)
			{
				m_pSquare[m_nCurline - 3 + i][m_nCurcolume + 1]->setColor(ccc3(233, 178, 11));
				m_pSquare[m_nCurline - 3 + i][m_nCurcolume + 1]->setTag(1);
			}
		}
		m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->setColor(ccc3(233, 178, 11));
		m_pSquare[m_nCurline - 2][m_nCurcolume + 2]->setTag(1);

		m_nCurcolume++;
		break;
	case 17:
		//�ж��Ƿ������������
		if (m_nCurcolume + 2 >= COLUME - 1)
		{
			return;
		}
		if (m_nCurline - 2 < 0 || m_pSquare[m_nCurline - 2][m_nCurcolume + 3]->getTag() == 1)
		{
			return;
		}
		if (m_nCurline - 1 < 0 || m_pSquare[m_nCurline - 1][m_nCurcolume + 2]->getTag() == 1)
		{
			return;
		}

		//����һ��
		m_pSquare[m_nCurline - 2][m_nCurcolume + 3]->setColor(ccc3(233, 178, 11));
		m_pSquare[m_nCurline - 2][m_nCurcolume + 3]->setTag(1);
		m_pSquare[m_nCurline - 2][m_nCurcolume]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 2][m_nCurcolume]->setTag(0);
		m_pSquare[m_nCurline - 1][m_nCurcolume + 2]->setColor(ccc3(233, 178, 11));
		m_pSquare[m_nCurline - 1][m_nCurcolume + 2]->setTag(1);
		m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 1][m_nCurcolume + 1]->setTag(0);

		m_nCurcolume++;
		break;
	case 18:
		//�ж��Ƿ������������
		if (m_nCurcolume + 1 >= COLUME - 1)
		{
			return;
		}
		for (int i = 0; i < 3; i++)
		{
			if (m_nCurline - 3 + i < 0 || m_pSquare[m_nCurline - 3 + i][m_nCurcolume + 2]->getTag() == 1)
			{
				return;
			}
		}

		//����һ��
		for (int i = 0; i < 3; i++)
		{
			m_pSquare[m_nCurline - 3 + i][m_nCurcolume + 2]->setColor(ccc3(233, 178, 11));
			m_pSquare[m_nCurline - 3 + i][m_nCurcolume + 2]->setTag(1);
			if (i != 1)
			{
				m_pSquare[m_nCurline - 3 + i][m_nCurcolume + 1]->setColor(ccc3(255, 255, 255));
				m_pSquare[m_nCurline - 3 + i][m_nCurcolume + 1]->setTag(0);
			}
		}
		m_pSquare[m_nCurline - 2][m_nCurcolume]->setColor(ccc3(255, 255, 255));
		m_pSquare[m_nCurline - 2][m_nCurcolume]->setTag(0);

		m_nCurcolume++;
		break;
	case 19:
		//�ж��Ƿ������������
		if (m_nCurcolume + 1 >= COLUME - 1)
		{
			return;
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_nCurline - 2 + i < 0 || m_pSquare[m_nCurline - 2 + i][m_nCurcolume + 2]->getTag() == 1)
			{
				return;
			}
		}

		//����һ��
		for (int i = 0; i < 2; i++)
		{
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume + 2]->setColor(ccc3(244, 69, 46));
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume + 2]->setTag(1);
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume]->setColor(ccc3(255, 255, 255));
			m_pSquare[m_nCurline - 2 + i][m_nCurcolume]->setTag(0);
		}

		m_nCurcolume++;
		break;
	}
}