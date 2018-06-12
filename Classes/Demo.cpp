#include "Demo.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "Box2d.h"
#include<iostream>
#include "xuanzhuan.h"
using namespace std;
int rads = 90;
float Position[1000][99999] = {900};


Scene* MainScene1::createScene()
{
	auto scene = Scene::createWithPhysics();
	Vect gravity(0, -10.0f);
	scene->getPhysicsWorld()->setGravity(gravity);
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
//	scene->getPhysicsWorld()->setAutoStep(false);          //
//	scene->getPhysicsWorld()->setFixedUpdateRate(500);
	// 'layer' is an autorelease object  
	auto layer = MainScene1::create();
	layer->setPhyWorld(scene->getPhysicsWorld());
	// add layer as a child to scene  
	scene->addChild(layer);
	// return the scene  
	return scene;
}
/*
void MainScene1::onEnter()
{
	Layer::onEnter();
	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = [](PhysicsContact& contact)                           
	{
		auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();                //ballBody->setDynamic(false);  ballBodyOne->getShape(0)->setRestitution(1.0f);
		auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();                

		if (spriteA && spriteA->getTag() == 1&& spriteB && spriteB->getTag() == 1)                                
		{
			contact.getShapeA()->setRestitution(0);
			contact.getShapeB()->setRestitution(0);
			contact.getShapeA()->getBody()->setDynamic(false);
			contact.getShapeB()->getBody()->setDynamic(false);
			spriteA->setColor(Color3B::YELLOW);
			spriteB->setColor(Color3B::YELLOW);
			spriteA->getPhysicsBody()->setDynamic(false);
			spriteB->getPhysicsBody()->setDynamic(false);
		}

		log("onContactBegin");
		return true;
	};


	listener->onContactPreSolve = [](PhysicsContact& contact,PhysicsContactPreSolve& solve)
	{                


		log("onContactPreSolve");
	return true;
	};


	listener->onContactPostSolve = [](PhysicsContact& contact,const PhysicsContactPostSolve& solve)
	{


		log("onContactPostSolve");
    };
    listener->onContactSeparate = [](PhysicsContact& contact)
{                      
auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();

if (spriteA && spriteA->getTag() == 1&& spriteB && spriteB->getTag() == 1)
{
	spriteA->setColor(Color3B::WHITE);
	spriteB->setColor(Color3B::WHITE);
}
log("onContactSeperate");
};


Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);                  


}


	void MainScene1::onExit()
	{
		Layer::onExit();
		log("HelloWorld onExit");
		Director::getInstance()->getEventDispatcher()->removeAllEventListeners();             
	}
*/

	Sprite* MainScene1::addNewSpriteAtPosition(Vec2 p)
	{
		Point origin = Director::getInstance()->getVisibleOrigin();

		sp= Sprite::create("1.png");
		sp->setPosition(p);
		PhysicsBody* body = PhysicsBody::createBox(sp->getContentSize());
		Vect force = Vect(0.0f, 0.0f);
		body->applyImpulse(force);
		body->setContactTestBitmask(0xFFFFFFFF);   
//		body->getShape(1)->setRestitution(0);
		sp->setPhysicsBody(body);   
		sp->setTag(i);
		this->addChild(sp);
		return sp;
	}
	
	void MainScene1::onKeyPressed(EventKeyboard::KeyCode keycode, Event *event) {
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
		else if (keycode == EventKeyboard::KeyCode::KEY_Q){
			CCLOG("按下了：字母Q键");
		}
	}
	void MainScene1::update(float delta) 
	{
		Node::update(delta);
		auto leftArrow = EventKeyboard::KeyCode::KEY_LEFT_ARROW, rightArrow = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
		auto upArrow = EventKeyboard::KeyCode::KEY_UP_ARROW, downArrow = EventKeyboard::KeyCode::KEY_DOWN_ARROW;
		auto qArrow = EventKeyboard::KeyCode::KEY_Q;
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
		else if (isKeyPressed(qArrow)){
			keyPressedDuration(qArrow);
		}
		for (int i = 0; i < 3; ++i)
		{
			getScene()->getPhysicsWorld()->step(1 / 180.0f);                      //
		}
	}

	bool MainScene1::isKeyPressed(EventKeyboard::KeyCode keyCode) {
		if (keys[keyCode]) {
			return true;
		}
		else {
			return false;
		}
	}
	void MainScene1::keyPressedDuration(EventKeyboard::KeyCode code) 
	{
		int offsetX = 0, offsetY = 0;
		Sprite *sss = Sprite::create("square.png");
		switch (code) {
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			//offsetX = -tower->getContentSize().width;
			offsetX = -sss->getContentSize().width/10;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			//offsetX = tower->getContentSize().width;
			offsetX = sss->getContentSize().width/10;
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			offsetY = sss->getContentSize().height;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			offsetY = -sss->getContentSize().height;
			break;
		case EventKeyboard::KeyCode::KEY_Q:
			sprites[i]->runAction(RotateTo::create(0.0f, 180)), rads = rads + 90;
			if (rads > 360)
				rads = 0;
		default:
			offsetY = offsetX = 0;
			break;
		}
		// 0.0s耗时
		auto moveTo = MoveTo::create(0.0, Vec2(sprites[i]->getPositionX() + offsetX, sprites[i]->getPositionY() + offsetY));
		sprites[i]->runAction(moveTo);
	}

	bool MainScene1::init()
	{
		//////////////////////////////
		// 1. super init first
		if (!Layer::init())
		{
			return false;
		}
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		auto edgeSp = Sprite::create();
		auto body1 = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT);
		body1->getShape(0)->setRestitution(0);
		Vect force = Vect(0.0f, 0.0f);
		body1->applyImpulse(force);
		edgeSp->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
		edgeSp->setPhysicsBody(body1);
		this->addChild(edgeSp); edgeSp->setTag(0);
		//
		//
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
		//
		sprites[i]=addNewSpriteAtPosition(Point(600, 900));
		this->schedule(schedule_selector(MainScene1::updates));
		this->scheduleUpdate();
		return true;
	}
	void MainScene1::updates(float dt)
	{
		Position[i][0] = 1000;
		sss = Sprite::create("square.png");
		float k = sss->getContentSize().height / 2;
		Position[i][j+1] = sprites[i]->getPositionY();
		//
		//
		j++;
		//
		if (abs(Position[i][j]-Position[i][j-1])==0)
		{
			rands[i+1] = rand() % (15) + 1;
			sprites[i]->getPhysicsBody()->getShape(0)->setFriction(1000.0f);
			sprites[i]->getPhysicsBody()->setDynamic(false);
			//
			// 按照刚体的旋转角度添加新的刚体
			int finalrads = sprites[i]->getRotation();
			int fx = sprites[i]->getPositionX();
			int fy = sprites[i]->getPositionY();
			addbaseblock(sprites[0], finalrads, fx, fy, 1);
			removeChild(sprites[i], true);
			//
			//
			i++;
	//		addNewSpriteAtPosition(Point(600, 900));
			sprites[i] = addBlock(rands[i], Point(600, 900));
			j = 0;
			rads = 0;
		}
	}
	Sprite* MainScene1::fun(vector<Vec2*>*shapeVecs, vector<int>* shapeVecAmount, int shapeAmount, int number, Point p)
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
	Sprite* MainScene1::addBlock(int number, Point p)
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
	void MainScene1::addbaseblock(Sprite* mmm, int rotations, int X, int Y, int number)
	{
		Sprite*base[4];
		for (int i = 0; i < 4; i++)
		{
			base[i] = Sprite::create("square.png");
			PhysicsBody *itsbody = PhysicsBody::createBox(Size(base[i]->getContentSize().width, base[i]->getContentSize().height));
			base[i]->setPhysicsBody(itsbody);
			base[i]->getPhysicsBody()->setDynamic(false);
		}
		if (number == 1)
		{
			if (rotations == 0)
			{
				base[0]->setPosition(X - 40, Y);
				this->addChild(base[0]);
				base[1]->setPosition(X - 10, Y);
				this->addChild(base[1]);
				base[2]->setPosition(X + 10, Y);
				this->addChild(base[2]);
				base[3]->setPosition(X + 40, Y);
				this->addChild(base[3]);
			}
			/*	else if (rotations == 90)
				{

				}
				else if (rotations == 180)
				{

				}
				else if (rotations==270)*/
		}
	}