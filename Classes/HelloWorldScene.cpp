#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"


cocos2d::Scene * MainScene::createScene()
{
	auto scene = Scene::create();
	//    CCScene * scene = CCScene::create();// 创建场景
	//创建层
	MainScene *layer = MainScene::create();
	scene->addChild(layer);
	return scene;
}
bool MainScene::init(){
	if (!Layer::init()) {
		return false;

	}

	//获取屏幕大小
	size = Director::getInstance()->getVisibleSize();
	//auto size = Director::getInstance()->getWinSize();
	//添加一个图片精灵
	hero = Sprite::create("1.png");
	hero->setPosition(Vec2(size.width / 3, size.height / 3));
	this->addChild(hero);

	sprite1 = Sprite::create("CloseNormal.png");
	sprite1->setPosition(Vec2(size.width / 2, size.height / 2));
	this->addChild(sprite1);

	sprite2 = Sprite::create("CloseNormal.png");
	sprite2->setPosition(Vec2(size.width*0.4, size.height / 2));
	this->addChild(sprite2);

	label = Label::createWithSystemFont("No collision", "Marker Felt", 50);
	label->setPosition(Vec2(size.width / 2, size.height*0.7));
	this->addChild(label);//直接把Label显示在屏幕上

	//创建监听事件对象
	auto listener = EventListenerTouchOneByOne::create();
	auto listener1 = EventListenerKeyboard::create();
	//定义监听事件的回调函数
	listener->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(MainScene::onTouchMoved, this);
	listener1->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event){
		log("key pressed");
	};
	listener1->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event){
		log("key release");
		listener1->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event){
			keys[keyCode] = true;
		};

		listener1->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event){
			keys[keyCode] = false;
		};
	};
	//在事件分发器中注册
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
	this->scheduleUpdate();


	//创建一个盒子，用来碰撞  
	/*	 Sprite* edgeSpace = Sprite::create();
	PhysicsBody* boundBody = PhysicsBody::createEdgeBox(size, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	boundBody->getShape(0)->setFriction(0.0f);
	boundBody->getShape(0)->setRestitution(1.0f);

	edgeSpace->setPhysicsBody(boundBody);
	edgeSpace->setPosition(Point(size.width / 2, size.height / 2));
	this->addChild(edgeSpace);
	edgeSpace->setTag(0);     */

	return true;

}

//点击移动精事件回调方法
bool MainScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	//获取触屏位置（坐标）
	Point pos = touch->getLocation();

	sprite2->setPosition(pos);//把点击屏幕的触摸点（坐标）给赋值给精灵2

	log("TouchBegan");

	return true;
}
//拖动手势执行事件方法
void MainScene::onTouchMoved(Touch *touch, Event *unused_event)
{
	//获取当前拖动手势的坐标与位置
	Point pos = touch->getLocation();

	sprite2->setPosition(pos);//让精灵跟着拖动点移动

	//判断两个精灵是否相交
	if (sprite2->getBoundingBox().intersectsRect(sprite1->getBoundingBox())){    //3.0改变处
		label->setString("Collision!");//改变屏幕上Label的文字

	}
	else{
		label->setString("No collision");//改变屏幕上Label的文字

		log("TouchMoved");

	}
}
void MainScene::onKeyPressed(EventKeyboard::KeyCode keycode, Event *event) {
	if (keycode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
		CCLOG("按下了：上方向键");
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		CCLOG("按下了：左方向键");
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
		CCLOG("按下了：右方向键");
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		CCLOG("按下了：下方向键");
	}
}
void MainScene::update(float delta) {
	Node::update(delta);
	auto leftArrow = EventKeyboard::KeyCode::KEY_LEFT_ARROW, rightArrow = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
	auto upArrow = EventKeyboard::KeyCode::KEY_UP_ARROW, downArrow = EventKeyboard::KeyCode::KEY_DOWN_ARROW;
	if (isKeyPressed(leftArrow)) {
		keyPressedDuration(leftArrow);
	}
	else if (isKeyPressed(rightArrow)) {
		keyPressedDuration(rightArrow);
	}
	else if (isKeyPressed(upArrow)) {
		keyPressedDuration(upArrow);
	}
	else if (isKeyPressed(downArrow)) {
		keyPressedDuration(downArrow);
	}
}

bool MainScene::isKeyPressed(EventKeyboard::KeyCode keyCode) {
	if (keys[keyCode]) {
		return true;
	}
	else {
		return false;
	}
}
void MainScene::keyPressedDuration(EventKeyboard::KeyCode code) {
	int offsetX = 0, offsetY = 0;
	switch (code) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		offsetX = -5;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		offsetX = 5;
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		offsetY = 5;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		offsetY = -5;
		break;
	default:
		offsetY = offsetX = 0;
		break;
	}
	// 0.3s代表着动作从开始到结束所用的时间，从而显得不会那么机械。
	auto moveTo = MoveTo::create(0.3, Vec2(hero->getPositionX() + offsetX, hero->getPositionY() + offsetY));
	hero->runAction(moveTo);
}
