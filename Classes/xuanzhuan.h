#ifndef MainScene3_hpp
#define MainScene3_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "Box2d.h"
USING_NS_CC;
using namespace cocos2d;
using namespace std;

class MainScene3 : public cocos2d::Layer
{
public:
	PhysicsWorld* m_world;
	void setPhyWorld(PhysicsWorld* world) { m_world = world; };
	static cocos2d::Scene* createScene();
	void update(float delta);
	void onKeyPressed(EventKeyboard::KeyCode keycode, Event *event);
	bool isKeyPressed(EventKeyboard::KeyCode keyCode);
	void keyPressedDuration(EventKeyboard::KeyCode code);

	virtual bool init();
	void updates(float dt);
	void startupdate(float);

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	//add Block
    Sprite* fun(vector<Vec2*>*shapeVecs, vector<int>* shapeVecAmount, int shapeAmount,int number,Point p);
    Sprite* addBlock(int number,Point p);

	// implement the "static create()" method manually
	CREATE_FUNC(MainScene3);
private:
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
	Sprite*tower;
	Sprite* mama;
	Sprite*tower10;
};

#endif // __HELLOWORLD_SCENE_H__