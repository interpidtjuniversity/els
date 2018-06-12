#ifndef _jia_H__
#define _jia_H__

#include "cocos2d.h"
USING_NS_CC;

#define LINE 24
#define COLUME 10

class HelloWorld : public cocos2d::CCLayerColor
{
public:
	HelloWorld();
	~HelloWorld();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	void onWin32KeyEvent(UINT message, WPARAM wParam, LPARAM lParam);
#endif

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();

	// a selector callback
	void menuCloseCallback(CCObject* pSender);

	// implement the "static node()" method manually
	CREATE_FUNC(HelloWorld);

	//�������
	void clearLine(int nLineStart, int nLineEnd);
	//���¿���һ��
	void copyLine(int nlineNum);
	//�����Ϸ�Ƿ����
	void checkFail();
	//��Ϸ��������
	void gameOver();
	//���·�����ʾ
	void updateScore();
	//����һ���µķ���
	void newSquareType();
	//�����һ����������
	void nextSquareType();
	//�����½�
	void updateDown(float dt);
	//��������
	void updateLeft();
	//��������
	void updateRight();

	CCSprite* m_pSquare[LINE][COLUME];	//���鵥Ԫ��
	int m_nCurline;						//����������ǰ��
	int m_nCurcolume;					//����������ǰ��
	int m_nCurSquareType;				//��ǰ��������
	int m_nCurScore;					//��ǰ��Ϸ����
	CCLabelTTF* m_pLabel;
};

#endif // __HELLOWORLD_SCENE_H__
