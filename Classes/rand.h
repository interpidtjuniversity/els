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
	void newSquareType();//�����µķ���
	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	Sprite* m_pSquare[LINE][COLUME];	//���鵥Ԫ��
	int m_nCurline;						//����������ǰ��
	int m_nCurcolume;					//����������ǰ��
	int m_nCurSquareType;				//��ǰ��������
	int m_nCurScore;		//��ǰ��Ϸ����
	void addNewSpriteAtPosition(Point p,int i);
	Sprite*ballOne;
	Sprite *box[20];
	CCLabelTTF* m_pLabel;

	// implement the "static create()" method manually
	CREATE_FUNC(MainScene4);
};

#endif // __HELLOWORLD_SCENE_H__
