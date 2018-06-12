#ifndef  HelloWorld_hpp
#define  HelloWorld_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "Box2D.h"
USING_NS_CC;
using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
public:
	PhysicsWorld* m_world;
	static b2World *world;
	void setPhyWorld(PhysicsWorld* world) { m_world = world; };
    static b2World createWorld();
	void initSprite();
	void myupdata(float dt);
	void initGround();
	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
