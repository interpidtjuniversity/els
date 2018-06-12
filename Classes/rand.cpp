#include "rand.h"
#include "SimpleAudioEngine.h"
#include"cocos2d.h"

USING_NS_CC;

Scene* MainScene4::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);


	// 'layer' is an autorelease object  
	auto layer = MainScene4::create();
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
bool MainScene4::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	auto edgeSp = Sprite::create();
	auto body1 = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	edgeSp->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	edgeSp->setPhysicsBody(body1);
	this->addChild(edgeSp); edgeSp->setTag(0);

	//初始化分数显示
	char buf[4] = { 0 };
	m_nCurScore = 0;
	sprintf(buf, "%d", m_nCurScore);
	m_pLabel = CCLabelTTF::create(buf, "Arial", 15);
	m_pLabel->setColor(ccc3(0, 0, 0));
	m_pLabel->setAnchorPoint(ccp(0, 0));
	m_pLabel->setPosition(ccp(0, 508));
	this->addChild(m_pLabel, 1);

	//初始化格子(10*18个)
	for (int i = 0; i < LINE; i++)
	{
		for (int j = 0; j <COLUME; j++)
		{
			m_pSquare[i][j] = Sprite::create("square.png");
			m_pSquare[i][j]->setPosition(Director::sharedDirector()->convertToGL(ccp(j * 20 + j * 2 + 10, i * 20 + i * 2 + 10)));
			m_pSquare[i][j]->setTag(0);
			m_pSquare[i][j]->setColor(ccc3(255, 255, 255));
			this->addChild(m_pSquare[i][j]);
		}
	}
	for (int i = 1; i < 20; i++)
	{
		addNewSpriteAtPosition(Point(50*i,900),i);
	}

//	this->schedule(schedule_selector(MainScene4::updateDown), 1.0);

	return true;
}


void MainScene4::menuCloseCallback(Ref* pSender)
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
void MainScene4::newSquareType()
{
	m_nCurSquareType = rand() % 19 + 1;
	switch (m_nCurSquareType)
	{
	case 1:
	case 3:
	case 4:
	case 9:
	case 10:
	case 11:
	case 12:
	case 15:
	case 16:
		m_nCurline = 0;
		m_nCurcolume = 3;
		break;
	case 2:
	case 5:
	case 6:
	case 7:
	case 8:
	case 13:
	case 14:
	case 17:
	case 18:
	case 19:
		m_nCurline = 0;
		m_nCurcolume = 4;
		break;
	}
}
void MainScene4::addNewSpriteAtPosition(Point p,int i)
{
	Point origin = Director::getInstance()->getVisibleOrigin();
	switch (i)
	{
	case 1:
		box[i] = Sprite::create("1.png");
		box[i]->setPosition(p);
		break;
	case 2:
		box[i] = Sprite::create("2.png");
		box[i]->setPosition(p);
		break;
	case 3:
		box[i] = Sprite::create("3.png");
		box[i]->setPosition(p);
		break;
	case 4:
		box[i] = Sprite::create("4.png");
		box[i]->setPosition(p);
		break;
	case 5:
		box[i] = Sprite::create("5.png");
		box[i]->setPosition(p);
		break;
	case 6:
		box[i] = Sprite::create("6.png");
		box[i]->setPosition(p);
		break;
	case 7:
		box[i] = Sprite::create("7.png");
		box[i]->setPosition(p);
		break;
	case 8:
		box[i] = Sprite::create("8.png");
		box[i]->setPosition(p);
		break;
	case 9:
		box[i] = Sprite::create("9.png");
		box[i]->setPosition(p);
		break;
	case 10:
		box[i] = Sprite::create("10.png");
		box[i]->setPosition(p);
		break;
	case 11:
		box[i] = Sprite::create("11.png");
		box[i]->setPosition(p);
			break;
	case 12:
		box[i] = Sprite::create("12.png");
		box[i]->setPosition(p);
		break;
	case 13:
		box[i] = Sprite::create("13.png");
		box[i]->setPosition(p);
		break;
	case 14:
		box[i] = Sprite::create("14.png");
		box[i]->setPosition(p);
		break;
	case 15:
		box[i] = Sprite::create("15.png");
		box[i]->setPosition(p);
		break;
	case 16:
		box[i] = Sprite::create("16.png");
		box[i]->setPosition(p);
		break;
	case 17:
		box[i] = Sprite::create("17.png");
		box[i]->setPosition(p);
		break;
	case 18:
		box[i] = Sprite::create("18.png");
		box[i]->setPosition(p);
		break;
	case 19:
		box[i] = Sprite::create("19.png");
		box[i]->setPosition(p);
	    break;
	}
	//创建物体，并且物体的形状为圆形，第一参数为半径，第二个参数为物体材质  
	//第三个参数为边的厚度,就是在Debug模式下看到的物体外面线条的厚度，默认为0  
	PhysicsBody* ballBodyOne = PhysicsBody::createCircle(box[i]->getContentSize().width / 2, PHYSICSBODY_MATERIAL_DEFAULT);
	//是否设置物体为静态  
	ballBodyOne->setDynamic(true);
	//设置物体的恢复力  
	ballBodyOne->getShape(0)->setRestitution(0);
	//设置物体的摩擦力  
	ballBodyOne->getShape(0)->setFriction(1.0f);
	//设置物体密度  
	ballBodyOne->getShape(0)->setDensity(1.0f);
	//设置质量  
	//ballBodyOne->getShape(0)->setMass(5000);  
	//设置物体是否受重力系数影响  
	ballBodyOne->setGravityEnable(true);

	//设置物体的冲力  
	Vect force = Vect(500000.0f, 500000.0f);
	ballBodyOne->applyImpulse(force);
	//把物体添加到精灵中  
	box[i]->setPhysicsBody(ballBodyOne);
	//设置标志  
	box[i]->setTag(1);
	this->addChild(box[i]);
}
