#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"


cocos2d::Scene * MainScene::createScene()
{
	auto scene = Scene::create();
	//    CCScene * scene = CCScene::create();// ��������
	//������
	MainScene *layer = MainScene::create();
	scene->addChild(layer);
	return scene;
}
bool MainScene::init(){
	if (!Layer::init()) {
		return false;

	}

	//��ȡ��Ļ��С
	size = Director::getInstance()->getVisibleSize();
	//auto size = Director::getInstance()->getWinSize();
	//���һ��ͼƬ����
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
	this->addChild(label);//ֱ�Ӱ�Label��ʾ����Ļ��

	//���������¼�����
	auto listener = EventListenerTouchOneByOne::create();
	auto listener1 = EventListenerKeyboard::create();
	//��������¼��Ļص�����
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
	//���¼��ַ�����ע��
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
	this->scheduleUpdate();


	//����һ�����ӣ�������ײ  
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

//����ƶ����¼��ص�����
bool MainScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	//��ȡ����λ�ã����꣩
	Point pos = touch->getLocation();

	sprite2->setPosition(pos);//�ѵ����Ļ�Ĵ����㣨���꣩����ֵ������2

	log("TouchBegan");

	return true;
}
//�϶�����ִ���¼�����
void MainScene::onTouchMoved(Touch *touch, Event *unused_event)
{
	//��ȡ��ǰ�϶����Ƶ�������λ��
	Point pos = touch->getLocation();

	sprite2->setPosition(pos);//�þ�������϶����ƶ�

	//�ж����������Ƿ��ཻ
	if (sprite2->getBoundingBox().intersectsRect(sprite1->getBoundingBox())){    //3.0�ı䴦
		label->setString("Collision!");//�ı���Ļ��Label������

	}
	else{
		label->setString("No collision");//�ı���Ļ��Label������

		log("TouchMoved");

	}
}
void MainScene::onKeyPressed(EventKeyboard::KeyCode keycode, Event *event) {
	if (keycode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
		CCLOG("�����ˣ��Ϸ����");
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		CCLOG("�����ˣ������");
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
		CCLOG("�����ˣ��ҷ����");
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		CCLOG("�����ˣ��·����");
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
	// 0.3s�����Ŷ����ӿ�ʼ���������õ�ʱ�䣬�Ӷ��Եò�����ô��е��
	auto moveTo = MoveTo::create(0.3, Vec2(hero->getPositionX() + offsetX, hero->getPositionY() + offsetY));
	hero->runAction(moveTo);
}
