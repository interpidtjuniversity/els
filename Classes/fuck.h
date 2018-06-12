#ifndef MainScene2_hpp
#define MainScene2_hpp

#define LINE 43
#define COLUME 60
#include <stdio.h>
#include "cocos2d.h"
#include <vector>
USING_NS_CC;
using namespace cocos2d;
using namespace std;

class MainScene2 : public cocos2d::Layer
{
public:
	Sprite* m_pSquare[LINE][COLUME];
	PhysicsWorld* m_world;
	void setPhyWorld(PhysicsWorld* world) { m_world = world; };
	static cocos2d::Scene* createScene();
	virtual bool init();
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void onTouchesEnded(const std::vector<Touch*>& touches, Event *event);
	void addNewSpriteAtPosition(Point p);
	void keyPressedDuration(EventKeyboard::KeyCode code);
	bool isKeyPressed(EventKeyboard::KeyCode keyCode);
	void update(float delta);
	void onKeyPressed(EventKeyboard::KeyCode keycode, Event *event);
	//
	Sprite* fun(vector<Vec2*>*shapeVecs, vector<int>* shapeVecAmount, int shapeAmount, int number, Point p);
	Sprite* addBlock(int number, Point p);
	//
	//
	void postStepRemove(cpSpace *space, cpShape *shape, void *unused);
	//
	//void onEnter();
	// implement the "static create()" method manually
	CREATE_FUNC(MainScene2);
private:
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
	Sprite* ballOne, *hero, *hero1;
	Sprite* sprites[];
};

#endif // __HELLOWORLD_SCENE_H__
