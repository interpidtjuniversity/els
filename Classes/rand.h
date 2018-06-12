#ifndef MainScene4_hpp
#define MainScene4_hpp

#define LINE 42
#define COLUME 45
#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
using namespace cocos2d;

class MainScene4 : public cocos2d::Layer
{
public:
	PhysicsWorld* m_world;
	void setPhyWorld(PhysicsWorld* world) { m_world = world; };
	static cocos2d::Scene* createScene();
	void newSquareType();//产生新的方块
	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	Sprite* m_pSquare[LINE][COLUME];	//方块单元格
	int m_nCurline;						//方块所处当前行
	int m_nCurcolume;					//方块所处当前列
	int m_nCurSquareType;				//当前方块类型
	int m_nCurScore;		//当前游戏分数
	void addNewSpriteAtPosition(Point p,int i);
	Sprite*ballOne;
	Sprite *box[20];
	CCLabelTTF* m_pLabel;

	// implement the "static create()" method manually
	CREATE_FUNC(MainScene4);
};

#endif // __HELLOWORLD_SCENE_H__
