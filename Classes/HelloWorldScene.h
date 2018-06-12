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
//����һ��������

class MainScene : public cocos2d::Layer{

private:
	// ��Ա����(˽�е�)
	Size size;//ע�ⲻ����auto�ؼ���
	Sprite *sprite1, *sprite2;//����������Ա�����ľ���(ע�ⲻ����auto�ؼ���
	Label *label;//ȫ�ֱ���Label->��ʾ��ײ��δ��ײ(ע�ⲻ����auto�ؼ���)
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
public:
	virtual void onKeyPressed(EventKeyboard::KeyCode keycode, Event *event);

	//virtual void onKeyReleased(EventKeyboard::KeyCode keycode, Event *event);

	virtual bool init(); // �麯��������ֵΪ�������ͣ�û�к���

	static cocos2d::Scene* createScene();//static��һ���෽�����س���
	//�����������
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	//�����϶�����
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
