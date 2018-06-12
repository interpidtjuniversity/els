#ifndef MainScene5_hpp
#define MainScene5_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
using namespace cocos2d;

class MainScene5 : public cocos2d::Scene
{
public:
	SpriteBatchNode* _spriteSheet;                                           //???

	void spawnCar();

	void spawnCat();

	void secondUpadte(float dt);

	void spriteDone(Node* sender);

	void onEnter();

	bool onContactBegin(EventCustom* event, const PhysicsContact& contact);

	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(MainScene5);
};

#endif // __HELLOWORLD_SCENE_H__