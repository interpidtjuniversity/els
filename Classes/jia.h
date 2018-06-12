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

	//清除整行
	void clearLine(int nLineStart, int nLineEnd);
	//向下拷贝一行
	void copyLine(int nlineNum);
	//检查游戏是否结束
	void checkFail();
	//游戏结束场景
	void gameOver();
	//更新分数显示
	void updateScore();
	//产生一个新的方块
	void newSquareType();
	//变成下一个方块类型
	void nextSquareType();
	//方块下降
	void updateDown(float dt);
	//方块左移
	void updateLeft();
	//方块右移
	void updateRight();

	CCSprite* m_pSquare[LINE][COLUME];	//方块单元格
	int m_nCurline;						//方块所处当前行
	int m_nCurcolume;					//方块所处当前列
	int m_nCurSquareType;				//当前方块类型
	int m_nCurScore;					//当前游戏分数
	CCLabelTTF* m_pLabel;
};

#endif // __HELLOWORLD_SCENE_H__
