#ifndef HelloWorld_hpp
#define HelloWorld_hpp

#include "cocos2d.h"
#include "Box2D.h"
#include "min.h"	

#define PTM_RATIO 32


class HelloWorld : public cocos2d::Scene
{
private:
	b2World* world;
	MainScene6* contactListener;											


public:


	~HelloWorld();

	static cocos2d::Scene* createScene();
	virtual bool init();


	virtual void update(float dt);
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	CREATE_FUNC(HelloWorld);

	void initPhysics();
	void addNewSpriteAtPosition(cocos2d::Vec2 p);
	void menuCloseCallback(Ref* pSender);

};


#endif // __HELLOWORLD_SCENE_H__