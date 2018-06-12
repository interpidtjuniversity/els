#include "fuck.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"



Scene* MainScene2::createScene()
{
	// 'scene' is an autorelease object  
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);


	// 'layer' is an autorelease object  
	auto layer = MainScene2::create();
	layer->setPhyWorld(scene->getPhysicsWorld());
	// add layer as a child to scene  
	scene->addChild(layer);

	// return the scene  
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainScene2::init()
{
	//////////////////////////////  
	// 1. super init first  
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	//
	for (int i = 0; i < LINE; i++)
	{
		for (int j = 0; j <COLUME; j++)
		{
			m_pSquare[i][j] = Sprite::create("square.png");
			m_pSquare[i][j]->setPosition(Director::sharedDirector()->convertToGL(ccp(j * 20 + j * 2 + 10, i * 20 + i * 2 + 10)));//
			m_pSquare[i][j]->setTag(0);
			m_pSquare[i][j]->setColor(ccc3(255, 255, 255));
			this->addChild(m_pSquare[i][j]);
		}
	}
	//

	Sprite *mmm = Sprite::create("square.png");
	float k = mmm->getContentSize().width;
	ballOne = addBlock(3, Point(300+10+7, 400));
	hero = addBlock(15, Point(300+7, 500));
	hero1 = addBlock(1, Point(300+3*k+7, 600));
//	hero1->setColor(ccc3(0, 0, 0));
//	hero1->removeFromParentAndCleanup(true);
//	removeChild(hero1,true);
	m_pSquare[34][13]->setColor(ccc3(0, 255, 0));
	m_pSquare[35][13]->setColor(ccc3(0, 255, 0));
	//


	/////////////////////////////  

	auto edgeSp = Sprite::create();
	auto body1 = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT);
	edgeSp->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	edgeSp->setPhysicsBody(body1);
	this->addChild(edgeSp); edgeSp->setTag(0);


	auto listener1 = EventListenerKeyboard::create();
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
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
	this->scheduleUpdate();

	return true;
}

void MainScene2::menuCloseCallback(Object* pSender)
{
	if (m_world->getDebugDrawMask() != PhysicsWorld::DEBUGDRAW_NONE)
	{
		m_world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	}
	else
	{
		m_world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	}

}
void MainScene2::onTouchesEnded(const std::vector<Touch*>& touches, Event *event)
{
	for (auto touch : touches)
	{
		auto location = touch->getLocation();
		addNewSpriteAtPosition(location);
	}
}
void MainScene2::addNewSpriteAtPosition(Point p)
{
	Point origin = Director::getInstance()->getVisibleOrigin();
	ballOne = Sprite::create("1.png");
	ballOne->setPosition(p);
	//�������壬�����������״ΪԲ�Σ���һ����Ϊ�뾶���ڶ�������Ϊ�������  
	//����������Ϊ�ߵĺ��,������Debugģʽ�¿������������������ĺ�ȣ�Ĭ��Ϊ0  
	PhysicsBody* ballBodyOne = PhysicsBody::createCircle(ballOne->getContentSize().width / 2, PHYSICSBODY_MATERIAL_DEFAULT);
	//�Ƿ���������Ϊ��̬  
	ballBodyOne->setDynamic(true);
	//��������Ļָ���  
	ballBodyOne->getShape(0)->setRestitution(1.0f);
	//���������Ħ����  
	ballBodyOne->getShape(0)->setFriction(1000.0f);
	//���������ܶ�  
	ballBodyOne->getShape(0)->setDensity(1.0f);
	//��������  
	//ballBodyOne->getShape(0)->setMass(5000);  
	//���������Ƿ�������ϵ��Ӱ��  
	ballBodyOne->setGravityEnable(true);

	//��������ĳ���  
	Vect force = Vect(500000.0f, 500000.0f);
	ballBodyOne->applyImpulse(force);
	//��������ӵ�������  
	ballOne->setPhysicsBody(ballBodyOne);
	//���ñ�־  
	ballOne->setTag(1);
	this->addChild(ballOne);

}
/*
void MainScene2::onEnter()
{
Layer::onEnter();
auto listener = EventListenerPhysicsContact::create();
listener->onContactBegin = [=](EventCustom* event, const PhysicsContact& contact)
{
auto sp = (Sprite*)contact.getShapeA()->getBody()->getNode();
int tag = sp->getTag();
if (tag == 1)
{
Texture2D *texture = TextureCache::getInstance()->addImage("16.png");
sp->setTexture(texture);
}

sp = (Sprite*)contact.getShapeB()->getBody()->getNode();
tag = sp->getTag();
if (tag == 1)
{
Texture2D *texture = TextureCache::getInstance()->addImage("11.png");
sp->setTexture(texture);
}
return true;
};
Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 10); //�ڶ������������ȼ���10������д��
}*/
void MainScene2::keyPressedDuration(EventKeyboard::KeyCode code) {
	int offsetX = 0, offsetY = 0;
	switch (code) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		offsetX = -1;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		offsetX = 1;
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
	// 0.3s�����Ŷ����ӿ�ʼ���������õ�ʱ�䣬�Ӷ��Եò�����ô��е��                                                                  //fuckfuckfuckfuckfuckfuckfuckfuck
	auto moveTo = MoveTo::create(0, Vec2(ballOne->getPositionX() + offsetX, ballOne->getPositionY() + offsetY));
	ballOne->runAction(moveTo);
}
bool MainScene2::isKeyPressed(EventKeyboard::KeyCode keyCode) {
	if (keys[keyCode]) {
		return true;
	}
	else {
		return false;
	}
}
void MainScene2::update(float delta) {
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
void MainScene2::onKeyPressed(EventKeyboard::KeyCode keycode, Event *event) {
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


//
Sprite* MainScene2::fun(vector<Vec2*>*shapeVecs, vector<int>* shapeVecAmount, int shapeAmount, int number, Point p)
{
	PhysicsBody* body = PhysicsBody::create();
	Vect force = Vect(0.0f, 0.0f);
	body->applyImpulse(force);
	body->addMoment(999999999999999.9f);
	body->setMoment(999999999999999.9f);
	//	body->getShape(0)->setFriction(1000.0f);
	for (int i = 0; i < shapeAmount; i++)
	{
		auto shape = PhysicsShapePolygon::create(shapeVecs->at(i), shapeVecAmount->at(i));
		shape->setRestitution(0);
		body->addShape(shape);
	}
	Sprite * nima;
	if (number == 1)
	{
		nima = Sprite::create("1.png");
		nima->setPosition(p);
		nima->setPhysicsBody(body);
		this->addChild(nima);
	}
	else if (number == 2)
	{
		nima = Sprite::create("2.png");
		nima->setPosition(p);
		nima->setPhysicsBody(body);
		this->addChild(nima);
	}
	else if (number == 3)
	{
		nima = Sprite::create("3.png");
		nima->setPosition(p);
		nima->setPhysicsBody(body);
		this->addChild(nima);
	}
	else if (number == 4)
	{
		nima = Sprite::create("4.png");
		nima->setPosition(p);
		nima->setPhysicsBody(body);
		this->addChild(nima);
	}
	else if (number == 5)
	{
		nima = Sprite::create("5.png");
		nima->setPosition(p);
		nima->setPhysicsBody(body);
		this->addChild(nima);
	}
	else if (number == 6)
	{
		nima = Sprite::create("6.png");
		nima->setPosition(p);
		nima->setPhysicsBody(body);
		this->addChild(nima);
	}
	else if (number == 7)
	{
		nima = Sprite::create("7.png");
		nima->setPosition(p);
		nima->setPhysicsBody(body);
		this->addChild(nima);
	}
	else if (number == 8)
	{
		nima = Sprite::create("8.png");
		nima->setPosition(p);
		nima->setPhysicsBody(body);
		this->addChild(nima);
	}
	else if (number == 9)
	{
		nima = Sprite::create("9.png");
		nima->setPosition(p);
		nima->setPhysicsBody(body);
		this->addChild(nima);
	}
	else if (number == 10)
	{
		nima = Sprite::create("10.png");
		nima->setPosition(p);
		nima->setPhysicsBody(body);
		this->addChild(nima);
	}
	else if (number == 11)
	{
		nima = Sprite::create("11.png");
		nima->setPosition(p);
		nima->setPhysicsBody(body);
		this->addChild(nima);
	}
	else if (number == 12)
	{
		nima = Sprite::create("12.png");
		nima->setPosition(p);
		nima->setPhysicsBody(body);
		this->addChild(nima);
	}
	else if (number == 13)
	{
		nima = Sprite::create("13.png");
		nima->setPosition(p);
		nima->setPhysicsBody(body);
		this->addChild(nima);
	}
	else if (number == 14)
	{
		nima = Sprite::create("14.png");
		nima->setPosition(p);
		nima->setPhysicsBody(body);
		this->addChild(nima);
	}
	else
	{
		nima = Sprite::create("15.png");
		nima->setPosition(p);
		nima->setPhysicsBody(body);
		this->addChild(nima);
	}
	return nima;
}
Sprite* MainScene2::addBlock(int number, Point p)
{
	Sprite *square = Sprite::create("square.png");
	float k = square->getContentSize().width / 2;
	Vec2 *form1 = new Vec2[4];
	Vec2 *form2 = new Vec2[4];
	Vec2 *form3 = new Vec2[4];
	Vec2 *form4 = new Vec2[4];
	vector<Vec2*>* vec = new vector<Vec2*>[4];
	vector<int>*vecNumber = new vector<int>[4];
	if (number == 3)
	{
		form1[0].setPoint(-3 * k, 2 * k);
		form1[1].setPoint(-k, 2 * k);
		form1[2].setPoint(-k, 0);
		form1[3].setPoint(-3 * k, 0);
		form2[0].setPoint(-k, 0);
		form2[1].setPoint(-k, -2 * k);
		form2[2].setPoint(-3 * k, -2 * k);
		form2[3].setPoint(-3 * k, 0);
		form3[0].setPoint(-k, 0);
		form3[1].setPoint(k, 0);
		form3[2].setPoint(-k, -2 * k);
		form3[3].setPoint(k, -2 * k);
		form4[0].setPoint(k, 0);
		form4[1].setPoint(3 * k, 0);
		form4[2].setPoint(3 * k, -2 * k);
		form4[3].setPoint(k, -2 * k);
	}
	else if (number == 2)
	{
		form1[0].setPoint(-k, 4 * k);
		form1[1].setPoint(k, 4 * k);
		form1[2].setPoint(k, 2 * k);
		form1[3].setPoint(-k, 2 * k);
		form2[0].setPoint(k, 2 * k);
		form2[1].setPoint(-k, 2 * k);
		form2[2].setPoint(-k, 0);
		form2[3].setPoint(k, 0);
		form3[0].setPoint(-k, 0);
		form3[1].setPoint(k, 0);
		form3[2].setPoint(k, -2 * k);
		form3[3].setPoint(-k, -2 * k);
		form4[0].setPoint(k, -2 * k);
		form4[1].setPoint(-k, -2 * k);
		form4[2].setPoint(-k, -4 * k);
		form4[3].setPoint(k, -4 * k);
	}
	else if (number == 1)
	{
		form1[0].setPoint(-4 * k, k);
		form1[1].setPoint(-4 * k, -k);
		form1[2].setPoint(-2 * k, -k);
		form1[3].setPoint(-2 * k, k);
		form2[0].setPoint(-2 * k, k);
		form2[1].setPoint(-2 * k, -k);
		form2[2].setPoint(0, -k);
		form2[3].setPoint(0, k);
		form3[0].setPoint(0, -k);
		form3[1].setPoint(0, k);
		form3[2].setPoint(2 * k, k);
		form3[3].setPoint(2 * k, -k);
		form4[0].setPoint(2 * k, k);
		form4[1].setPoint(2 * k, -k);
		form4[2].setPoint(4 * k, -k);
		form4[3].setPoint(4 * k, k);
	}
	else if (number == 4)
	{
		form1[0].setPoint(-2 * k, 3 * k);
		form1[1].setPoint(0, 3 * k);
		form1[2].setPoint(0, k);
		form1[3].setPoint(-2 * k, k);
		form2[0].setPoint(0, 3 * k);
		form2[1].setPoint(2 * k, 3 * k);
		form2[2].setPoint(2 * k, k);
		form2[3].setPoint(0, k);
		form3[0].setPoint(0, -k);
		form3[1].setPoint(-2 * k, -k);
		form3[2].setPoint(-2 * k, k);
		form3[3].setPoint(0, k);
		form4[0].setPoint(0, -k);
		form4[1].setPoint(0, -3 * k);
		form4[2].setPoint(-2 * k, -3 * k);
		form4[3].setPoint(-2 * k, -k);
	}
	else if (number == 5)
	{
		form1[0].setPoint(-3 * k, 0);
		form1[1].setPoint(-3 * k, 2 * k);
		form1[2].setPoint(-k, 2 * k);
		form1[3].setPoint(-k, 0);
		form2[0].setPoint(-k, 2 * k);
		form2[1].setPoint(-k, 0);
		form2[2].setPoint(k, 0);
		form2[3].setPoint(k, 2 * k);
		form3[0].setPoint(k, 0);
		form3[1].setPoint(k, 2 * k);
		form3[2].setPoint(3 * k, 2 * k);
		form3[3].setPoint(3 * k, 0);
		form4[0].setPoint(k, 0);
		form4[1].setPoint(3 * k, 0);
		form4[2].setPoint(3 * k, -2 * k);
		form4[3].setPoint(k, -2 * k);
	}
	else if (number == 6)
	{
		form1[0].setPoint(0, 3 * k);
		form1[1].setPoint(2 * k, 3 * k);
		form1[2].setPoint(2 * k, k);
		form1[3].setPoint(0, k);
		form2[0].setPoint(0, k);
		form2[1].setPoint(2 * k, k);
		form2[2].setPoint(0, -k);
		form2[3].setPoint(2 * k, -k);
		form3[0].setPoint(0, -k);
		form3[1].setPoint(2 * k, -k);
		form3[2].setPoint(2 * k, -3 * k);
		form3[3].setPoint(0, -3 * k);
		form4[0].setPoint(0, -k);
		form4[1].setPoint(0, -3 * k);
		form4[2].setPoint(-2 * k, -3 * k);
		form4[3].setPoint(-2 * k, -k);
	}
	else if (number == 7)
	{
		form1[0].setPoint(-3 * k, 0);
		form1[1].setPoint(-3 * k, -2 * k);
		form1[2].setPoint(-k, -2 * k);
		form1[3].setPoint(-k, 0);
		form2[0].setPoint(-k, 0);
		form2[1].setPoint(-k, -2 * k);
		form2[2].setPoint(k, -2 * k);
		form2[3].setPoint(k, 0);
		form3[0].setPoint(k, 0);
		form3[1].setPoint(k, 2 * k);
		form3[2].setPoint(-k, 2 * k);
		form3[3].setPoint(-k, 0);
		form4[0].setPoint(k, 0);
		form4[1].setPoint(3 * k, 0);
		form4[2].setPoint(3 * k, 2 * k);
		form4[3].setPoint(k, 2 * k);
	}
	else if (number == 8)
	{
		form1[0].setPoint(-2 * k, 3 * k);
		form1[1].setPoint(0, 3 * k);
		form1[2].setPoint(0, k);
		form1[3].setPoint(-2 * k, k);
		form2[0].setPoint(-2 * k, k);
		form2[1].setPoint(-2 * k, -k);
		form2[2].setPoint(0, -k);
		form2[3].setPoint(0, k);
		form3[0].setPoint(0, -k);
		form3[1].setPoint(0, k);
		form3[2].setPoint(2 * k, k);
		form3[3].setPoint(2 * k, -k);
		form4[0].setPoint(0, -k);
		form4[1].setPoint(2 * k, -k);
		form4[2].setPoint(2 * k, -3 * k);
		form4[3].setPoint(0, -3 * k);
	}
	else if (number == 9)
	{
		form1[0].setPoint(-3 * k, 0);
		form1[1].setPoint(-3 * k, 2 * k);
		form1[2].setPoint(-k, 2 * k);
		form1[3].setPoint(-k, 0);
		form2[0].setPoint(-k, 0);
		form2[1].setPoint(-k, 2 * k);
		form2[2].setPoint(k, 2 * k);
		form2[3].setPoint(k, 0);
		form3[0].setPoint(-k, 0);
		form3[1].setPoint(k, 0);
		form3[2].setPoint(k, -2 * k);
		form3[3].setPoint(-k, -2 * k);
		form4[0].setPoint(k, 0);
		form4[1].setPoint(k, -2 * k);
		form4[2].setPoint(3 * k, -2 * k);
		form4[3].setPoint(3 * k, 0);
	}
	else if (number == 10)
	{
		form1[0].setPoint(0, 3 * k);
		form1[1].setPoint(2 * k, 3 * k);
		form1[2].setPoint(2 * k, k);
		form1[3].setPoint(0, k);
		form2[0].setPoint(0, k);
		form2[1].setPoint(2 * k, k);
		form2[2].setPoint(2 * k, -k);
		form2[3].setPoint(0, -k);
		form3[0].setPoint(0, -k);
		form3[1].setPoint(0, k);
		form3[2].setPoint(-2 * k, k);
		form3[3].setPoint(-2 * k, -k);
		form4[0].setPoint(-2 * k, -k);
		form4[1].setPoint(-2 * k, -3 * k);
		form4[2].setPoint(0, -3 * k);
		form4[3].setPoint(0, -k);
	}
	else if (number == 11)
	{
		form1[0].setPoint(-k, 0);
		form1[1].setPoint(k, 0);
		form1[2].setPoint(k, 2 * k);
		form1[3].setPoint(-k, 2 * k);
		form2[0].setPoint(-k, 0);
		form2[1].setPoint(k, 0);
		form2[2].setPoint(k, -2 * k);
		form2[3].setPoint(-k, -2 * k);
		form3[0].setPoint(-k, 0);
		form3[1].setPoint(-k, -2 * k);
		form3[2].setPoint(-3 * k, -2 * k);
		form3[3].setPoint(-3 * k, 0);
		form4[0].setPoint(k, 0);
		form4[1].setPoint(k, -2 * k);
		form4[2].setPoint(3 * k, -2 * k);
		form4[3].setPoint(3 * k, 0);
	}
	else if (number == 12)
	{
		form1[0].setPoint(0, k);
		form1[1].setPoint(0, -k);
		form1[2].setPoint(2 * k, -k);
		form1[3].setPoint(2 * k, k);
		form2[0].setPoint(0, 3 * k);
		form2[1].setPoint(-2 * k, 3 * k);
		form2[2].setPoint(-2 * k, k);
		form2[3].setPoint(0, k);
		form3[0].setPoint(-2 * k, k);
		form3[1].setPoint(0, k);
		form3[2].setPoint(0, -k);
		form3[3].setPoint(-2 * k, -k);
		form4[0].setPoint(-2 * k, -k);
		form4[1].setPoint(0, -k);
		form4[2].setPoint(0, -3 * k);
		form4[3].setPoint(-2 * k, -3 * k);
	}
	else if (number == 13)
	{
		form1[0].setPoint(k, 0);
		form1[1].setPoint(-k, 0);
		form1[2].setPoint(-k, -2 * k);
		form1[3].setPoint(k, -2 * k);
		form2[0].setPoint(-3 * k, 0);
		form2[1].setPoint(-3 * k, 2 * k);
		form2[2].setPoint(-k, 2 * k);
		form2[3].setPoint(-k, 0);
		form3[0].setPoint(-k, 2 * k);
		form3[1].setPoint(-k, 0);
		form3[2].setPoint(k, 0);
		form3[3].setPoint(k, 2 * k);
		form4[0].setPoint(k, 0);
		form4[1].setPoint(k, 2 * k);
		form4[2].setPoint(3 * k, 2 * k);
		form4[3].setPoint(3 * k, 0);
	}
	else if (number == 14)
	{
		form1[0].setPoint(-2 * k, k);
		form1[1].setPoint(0, k);
		form1[2].setPoint(0, -k);
		form1[3].setPoint(-2 * k, -k);
		form2[0].setPoint(0, 3 * k);
		form2[1].setPoint(2 * k, 3 * k);
		form2[2].setPoint(2 * k, k);
		form2[3].setPoint(0, k);
		form3[0].setPoint(2 * k, k);
		form3[1].setPoint(0, k);
		form3[2].setPoint(0, -k);
		form3[3].setPoint(2 * k, -k);
		form4[0].setPoint(2 * k, -k);
		form4[1].setPoint(0, -k);
		form4[2].setPoint(0, -3 * k);
		form4[3].setPoint(2 * k, -3 * k);
	}
	else if (number == 15)
	{
		form1[0].setPoint(-2 * k, 2 * k);
		form1[1].setPoint(0, 2 * k);
		form1[2].setPoint(0, 0);
		form1[3].setPoint(-2 * k, 0);
		form2[0].setPoint(2 * k, 2 * k);
		form2[1].setPoint(2 * k, 0);
		form2[2].setPoint(0, 0);
		form2[3].setPoint(0, 2 * k);
		form3[0].setPoint(0, -2 * k);
		form3[1].setPoint(-2 * k, -2 * k);
		form3[2].setPoint(-2 * k, 0);
		form3[3].setPoint(0, 0);
		form4[0].setPoint(2 * k, 0);
		form4[1].setPoint(2 * k, -2 * k);
		form4[2].setPoint(0, -2 * k);
		form4[3].setPoint(0, 0);
	}
	vec->push_back(form1);
	vec->push_back(form2);
	vec->push_back(form3);
	vec->push_back(form4);
	for (int i = 0; i < 4; i++)
		vecNumber->push_back(4);
	return fun(vec, vecNumber, 4, number, p);
}