#ifndef MainScene1_hpp
#define MainScene1_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "Box2d.h"
#include<vector>
USING_NS_CC;
using namespace cocos2d;
using namespace std;

class MainScene1 : public cocos2d::Layer
{
public:
	PhysicsWorld* m_world;
	void setPhyWorld(PhysicsWorld* world) { m_world = world; };

	static cocos2d::Scene* createScene();
	virtual bool init();
 //   void add();
//	virtual void onEnter();
//	virtual void onExit();

	CREATE_FUNC(MainScene1);
	//¼üÅÌ¼àÌý
	void update(float delta);
	void onKeyPressed(EventKeyboard::KeyCode keycode, Event *event);
	bool isKeyPressed(EventKeyboard::KeyCode keyCode);
	void keyPressedDuration(EventKeyboard::KeyCode code);
//
	Sprite*fun(vector<Vec2*>*shapeVecs, vector<int>* shapeVecAmount, int shapeAmount, int number, Point p);
	Sprite*addBlock(int number, Point p);
//
	void addbaseblock(Sprite* mmm,int rotations,int X,int Y,int number);

//
	Sprite* sp;
	Sprite* sss;
    Sprite* addNewSpriteAtPosition(Vec2 p);
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
    void updates(float dt);
    Sprite* sprites[1000];
	int i = 0;
	int j = 0;
	int area=0;
	int shapeAmount = 4;
	int rands[1000];
//ÅÐ¶Ïshijian
};


#endif // __HELLOWORLD_SCENE_H__  