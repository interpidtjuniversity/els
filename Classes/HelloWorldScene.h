//
//  MainScene.hpp
//  helloworld
//
//  Created by apple on 16/9/19.
//
//

#ifndef MainScene_hpp
#define MainScene_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
using namespace cocos2d;
//定义一个场景类

class MainScene : public cocos2d::Layer{

private:
	// 成员变量(私有的)
	Size size;//注意不能用auto关键字
	Sprite *sprite1, *sprite2;//定义两个成员变量的精灵(注意不能用auto关键字
	Label *label;//全局变量Label->显示碰撞与未碰撞(注意不能用auto关键字)
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
public:
	virtual void onKeyPressed(EventKeyboard::KeyCode keycode, Event *event);

	//virtual void onKeyReleased(EventKeyboard::KeyCode keycode, Event *event);

	virtual bool init(); // 虚函数，返回值为布尔类型，没有函数

	static cocos2d::Scene* createScene();//static是一个类方法返回场景
	//声明点击手势
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	//声明拖动手势
	virtual void onTouchMoved(Touch *touch, Event *unused_event);

	cocos2d::Sprite *hero;
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void update(float delta) override;
	// implement the "static create()" method manually	
	bool MainScene::isKeyPressed(EventKeyboard::KeyCode keyCode);
	void MainScene::keyPressedDuration(EventKeyboard::KeyCode code);
	CREATE_FUNC(MainScene);

};


#endif /* MainScene_hpp */
