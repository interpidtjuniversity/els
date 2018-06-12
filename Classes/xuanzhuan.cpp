#include "xuanzhuan.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include<vector>
int rad = 90;
using namespace std;


Scene* MainScene3::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setAutoStep(false);          //
	// 'layer' is an autorelease object  
	auto layer = MainScene3::create();
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
bool MainScene3::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto body = PhysicsBody::create();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto edgeSp = Sprite::create();
	auto body1 = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT);
	edgeSp->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	edgeSp->setPhysicsBody(body1);
	this->addChild(edgeSp); edgeSp->setTag(0);


	tower = Sprite::create("1.png");
	tower->setPosition(Vec2(visibleSize.width / 6, visibleSize.height / 6));
	auto body2 = PhysicsBody::createBox(Size(tower->getContentSize().width, tower->getContentSize().height));
	body2->setGravityEnable(false);
	body2->getShape(0)->setRestitution(0.0f);
	tower->setPhysicsBody(body2);
	this->addChild(tower);

	//
	tower10 = Sprite::create("1.png");
	tower10->setPosition(Vec2(visibleSize.width / 6, visibleSize.height / 6));
	auto body10 = PhysicsBody::createBox(Size(tower10->getContentSize().width, tower10->getContentSize().height));
	body10->setGravityEnable(false);
	body10->getShape(0)->setRestitution(0.0f);
	tower10->setPhysicsBody(body10);
	this->addChild(tower10);
//
	auto world1 = this->getScene()->getPhysicsWorld();
	PhysicsJointLimit* joint = PhysicsJointLimit::construct(tower->getPhysicsBody(), tower10->getPhysicsBody(), Vec2(0, 0), Vec2(0, 0));
	world1->addJoint(joint);

//
	addBlock(1, Point(600, 800));
	addBlock(2, Point(500, 900));
	addBlock(3, Point(400, 400));
	addBlock(4, Point(500, 500));
	addBlock(5, Point(600, 600));
	addBlock(6, Point(700, 700));
	addBlock(7, Point(800, 800));
	addBlock(8, Point(900, 900));
	addBlock(9, Point(1000, 1000));
	addBlock(10, Point(400, 500));
	addBlock(11, Point(500, 600));
	addBlock(12, Point(600, 700));
	addBlock(13, Point(700, 800));
	addBlock(14, Point(800, 900));
	mama = addBlock(15, Point(900, 500));

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
		this->scheduleUpdate();
		return true;
}


void MainScene3::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}
void MainScene3::onKeyPressed(EventKeyboard::KeyCode keycode, Event *event) {
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
void MainScene3::update(float delta)
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
	for (int i = 0; i < 20; ++i)
	{
		getScene()->getPhysicsWorld()->step(1 / 1200.0f);
	}
}

bool MainScene3::isKeyPressed(EventKeyboard::KeyCode keyCode) {
	if (keys[keyCode]) {
		return true;
	}
	else {
		return false;
	}
}
void MainScene3::keyPressedDuration(EventKeyboard::KeyCode code) {
	int offsetX = 0, offsetY = 0;
	Sprite *sss = Sprite::create("square.png");
	switch (code) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		//offsetX = -tower->getContentSize().width;
		offsetX = -sss->getContentSize().width/5;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		//offsetX = tower->getContentSize().width;
		offsetX = sss->getContentSize().width/5;
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		offsetY = sss->getContentSize().height/5;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		offsetY = -sss->getContentSize().height/5;
		break;
	case EventKeyboard::KeyCode::KEY_Q:
		mama->runAction(RotateTo::create(0.0f, rad)), rad = rad + 90;
	default:
		offsetY = offsetX = 0;
		break;
	}
	// 0.0s耗时
	auto moveTo = MoveTo::create(0.5, Vec2( mama->getPositionX() + offsetX, mama->getPositionY() + offsetY));
	mama->runAction(moveTo);
}

Sprite* MainScene3::fun(vector<Vec2*>*shapeVecs, vector<int>* shapeVecAmount, int shapeAmount,int number,Point p)
{
	PhysicsBody* body = PhysicsBody::create();
	Vect force = Vect(0.0f, 0.0f);
	body->applyImpulse(force);
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
		else if (number ==11)
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
Sprite* MainScene3::addBlock(int number,Point p)
{
	Sprite *square = Sprite::create("square.png");
	float k = square->getContentSize().width/2;
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
		form1[0].setPoint(-2 * k, 3*k);
		form1[1].setPoint(0, 3 * k);
		form1[2].setPoint(0, k);
		form1[3].setPoint(-2 * k, k);
		form2[0].setPoint(0, 3*k);
		form2[1].setPoint(2*k, 3*k);
		form2[2].setPoint(2*k, k);
		form2[3].setPoint(0, k);
		form3[0].setPoint(0, -k);
		form3[1].setPoint(-2*k, -k);
		form3[2].setPoint(-2 * k, k);
		form3[3].setPoint(0, k);
		form4[0].setPoint(0, -k);
		form4[1].setPoint(0, -3*k);
		form4[2].setPoint(-2*k, -3*k);
		form4[3].setPoint(-2 * k, -k);
	}
	else if (number == 5)
	{
		form1[0].setPoint(-3 * k, 0);
		form1[1].setPoint(-3 * k, 2*k);
		form1[2].setPoint(- k, 2*k);
		form1[3].setPoint(-k, 0);
		form2[0].setPoint(-k, 2*k);
		form2[1].setPoint(-k, 0);
		form2[2].setPoint(k, 0);
		form2[3].setPoint(k, 2*k);
		form3[0].setPoint(k, 0);
		form3[1].setPoint(k, 2*k);
		form3[2].setPoint(3 * k,2*k);
		form3[3].setPoint(3 * k, 0);
		form4[0].setPoint(k, 0);
		form4[1].setPoint(3 * k, 0);
		form4[2].setPoint(3 * k, -2*k);
		form4[3].setPoint(k, -2*k);
	}
	else if (number == 6)
	{
		form1[0].setPoint(0, 3*k);
		form1[1].setPoint(2*k, 3*k);
		form1[2].setPoint(2*k, k);
		form1[3].setPoint(0, k);
		form2[0].setPoint(0, k);
		form2[1].setPoint(2*k, k);
		form2[2].setPoint(0, -k);
		form2[3].setPoint(2*k, -k);
		form3[0].setPoint(0, -k);
		form3[1].setPoint(2*k, -k);
		form3[2].setPoint(2 * k, -3*k);
		form3[3].setPoint(0, -3*k);
		form4[0].setPoint(0, -k);
		form4[1].setPoint(0, -3*k);
		form4[2].setPoint(-2*k, -3*k);
		form4[3].setPoint(-2*k, -k);
	}
	else if (number == 7)
	{
		form1[0].setPoint(-3* k, 0);
		form1[1].setPoint(-3 * k, -2*k);
		form1[2].setPoint(-k, -2*k);
		form1[3].setPoint(-k, 0);
		form2[0].setPoint(-k, 0);
		form2[1].setPoint(-k, -2*k);
		form2[2].setPoint(k, -2*k);
		form2[3].setPoint(k, 0);
		form3[0].setPoint(k, 0);
		form3[1].setPoint(k, 2*k);
		form3[2].setPoint(- k, 2*k);
		form3[3].setPoint(-k, 0);
		form4[0].setPoint(k, 0);
		form4[1].setPoint(3*k, 0);
		form4[2].setPoint(3*k, 2*k);
		form4[3].setPoint(k, 2*k);
	}
	else if (number == 8)
	{
		form1[0].setPoint(-2 * k, 3*k);
		form1[1].setPoint(0, 3*k);
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
		form4[2].setPoint(2 * k, -3*k);
		form4[3].setPoint(0, -3*k);
	}
	else if (number == 9)
	{
		form1[0].setPoint(- 3* k, 0);
		form1[1].setPoint(-3 * k, 2*k);
		form1[2].setPoint(- k, 2*k);
		form1[3].setPoint(-k, 2*k);
		form2[0].setPoint(-k, 0);
		form2[1].setPoint(-k, 2*k);
		form2[2].setPoint(k, 2*k);
		form2[3].setPoint(k, 0);
		form3[0].setPoint(-k, 0);
		form3[1].setPoint(k, 0);
		form3[2].setPoint( k, -2*k);
		form3[3].setPoint(-k, -2*k);
		form4[0].setPoint(k, 0);
		form4[1].setPoint(k, -2*k);
		form4[2].setPoint(3 * k, -2*k);
		form4[3].setPoint(3 * k, 0);
	}
	else if (number == 10)
	{
		form1[0].setPoint(0, 3*k);
		form1[1].setPoint(2 * k, 3*k);
		form1[2].setPoint(2 * k, k);
		form1[3].setPoint(0, k);
		form2[0].setPoint(0, k);
		form2[1].setPoint(2 * k, k);
		form2[2].setPoint(2*k, -k);
		form2[3].setPoint(0, -k);
		form3[0].setPoint(0, -k);
		form3[1].setPoint(0, k);
		form3[2].setPoint(-2 * k, k);
		form3[3].setPoint(-2 * k, -k);
		form4[0].setPoint(-2 * k, -k);
		form4[1].setPoint(-2 * k, -3*k);
		form4[2].setPoint(0, -3*k);
		form4[3].setPoint(0, -k);
	}
	else if (number == 11)
	{
		form1[0].setPoint(-k, 0);
		form1[1].setPoint(k, 0);
		form1[2].setPoint( k, 2*k);
		form1[3].setPoint(-k, 2*k);
		form2[0].setPoint(-k, 0);
		form2[1].setPoint(k, 0);
		form2[2].setPoint(k, -2*k);
		form2[3].setPoint(-k, -2*k);
		form3[0].setPoint(-k, 0);
		form3[1].setPoint(-k, -2*k);
		form3[2].setPoint(-3* k, -2*k);
		form3[3].setPoint(-3*k, 0);
		form4[0].setPoint(k, 0);
		form4[1].setPoint(k, -2*k);
		form4[2].setPoint(3 * k, -2*k);
		form4[3].setPoint(3 * k, 0);
	}
	else if (number == 12)
	{
		form1[0].setPoint(0, k);
		form1[1].setPoint(0, -k);
		form1[2].setPoint(2 * k, -k);
		form1[3].setPoint(2 * k, k);
		form2[0].setPoint(0, 3*k);
		form2[1].setPoint(-2 * k, 3*k);
		form2[2].setPoint(-2*k, k);
		form2[3].setPoint(0, k);
		form3[0].setPoint(-2*k, k);
		form3[1].setPoint(0, k);
		form3[2].setPoint(0, -k);
		form3[3].setPoint(-2 * k, -k);
		form4[0].setPoint(-2 * k, -k);
		form4[1].setPoint(0, -k);
		form4[2].setPoint(0, -3*k);
		form4[3].setPoint(-2*k, -3*k);
	}
	else if (number == 13)
	{
		form1[0].setPoint(k, 0);
		form1[1].setPoint(-k, 0);
		form1[2].setPoint(- k, -2*k);
		form1[3].setPoint(k, -2*k);
		form2[0].setPoint(-3 * k, 0);
		form2[1].setPoint(-3 * k, 2*k);
		form2[2].setPoint(-k, 2*k);
		form2[3].setPoint(-k, 0);
		form3[0].setPoint(-k, 2*k);
		form3[1].setPoint(-k, 0);
		form3[2].setPoint(k, 0);
		form3[3].setPoint(k, 2*k);
		form4[0].setPoint(k, 0);
		form4[1].setPoint(k, 2*k);
		form4[2].setPoint(3*k, 2*k);
		form4[3].setPoint(3*k, 0);
	}
	else if (number == 14)
	{
		form1[0].setPoint(-2*k, k);
		form1[1].setPoint(0, k);
		form1[2].setPoint(0, -k);
		form1[3].setPoint(-2 * k, -k);
		form2[0].setPoint(0, 3*k);
		form2[1].setPoint(2 * k, 3*k);
		form2[2].setPoint(2*k, k);
		form2[3].setPoint(0, k);
		form3[0].setPoint(2*k, k);
		form3[1].setPoint(0, k);
		form3[2].setPoint(0, -k);
		form3[3].setPoint(2 * k, -k);
		form4[0].setPoint(2 * k, -k);
		form4[1].setPoint(0, -k);
		form4[2].setPoint(0, -3*k);
		form4[3].setPoint(2 * k, -3*k);
	}
	else if (number == 15)
	{
		form1[0].setPoint(-2*k, 2*k);
		form1[1].setPoint(0, 2*k);
		form1[2].setPoint(0, 0);
		form1[3].setPoint(-2*k, 0);
		form2[0].setPoint(2*k, 2*k);
		form2[1].setPoint(2*k, 0);
		form2[2].setPoint(0, 0);
		form2[3].setPoint(0, 2*k);
		form3[0].setPoint(0, -2*k);
		form3[1].setPoint(-2*k, -2*k);
		form3[2].setPoint(-2*k, 0);
		form3[3].setPoint(0, 0);
		form4[0].setPoint(2*k, 0);
		form4[1].setPoint(2*k, -2*k);
		form4[2].setPoint(0, -2*k);
		form4[3].setPoint(0, 0);
	}
	vec->push_back(form1);
	vec->push_back(form2);
	vec->push_back(form3);
	vec->push_back(form4);
	for (int i = 0; i < 4; i++)
		vecNumber->push_back(4);
	return fun(vec, vecNumber, 4,number,p);
}