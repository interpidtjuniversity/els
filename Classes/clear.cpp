#include "clear.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"


Scene* MainScene5::createScene()
{
	return MainScene5::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainScene5::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	_spriteSheet = SpriteBatchNode::create("sprites.png", 2);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites.plist", "sprites.png");
	this->addChild(_spriteSheet);
	this->spawnCar();
	this->schedule(schedule_selector(MainScene5::secondUpadte), 1.0f);
	this->scheduleUpdate();

	return true;
}


void MainScene5::menuCloseCallback(Ref* pSender)
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
void MainScene5::spawnCar()
{
	SpriteFrame* frame = SpriteFrameCache::getInstance()->spriteFrameByName("1.png");
	Sprite* car = Sprite::createWithSpriteFrame(frame);
	car->setPosition(Point(100, 100));
//	addBoxBodyForSprite(car);
	car->setTag(2);
	car->runAction(MoveTo::create(1.0f, Point(300, 300)));
	car->runAction(RepeatForever::create(Sequence::create(MoveTo::create(1.0, Point(300, 100)), MoveTo::create(1.0, Point(200, 200)), MoveTo::create(1.0, Point(100, 100)), NULL)));
	_spriteSheet->addChild(car);
}
void MainScene5::spawnCat()
{
	auto winSize = Director::getInstance()->getWinSize();

	auto cat = Sprite::createWithSpriteFrameName("19.png");

	int minY = cat->getContentSize().height / 2;
	int maxY = winSize.height - (cat->getContentSize().height / 2);
	int rangeY = maxY - minY;
	int actualY = CCRANDOM_0_1() * rangeY;

	int startX = winSize.width + (cat->getContentSize().width / 2);
	int endX = -(cat->getContentSize().width / 2);

	Point startPos = Point(startX, actualY);
	Point endPos = Point(endX, actualY);

	cat->setPosition(startPos);
//	addBoxBodyForSprite(cat);
	cat->setTag(1);
	cat->runAction(Sequence::create(MoveTo::create(1.0, endPos), CallFuncN::create(this, callfuncN_selector(MainScene5::spriteDone)), NULL));

	_spriteSheet->addChild(cat);

}
void MainScene5::secondUpadte(float dt)
{
	this->spawnCat();
}

void MainScene5::spriteDone(Node* sender)
{
	Sprite *sprite = (Sprite*)sender;
	_spriteSheet->removeChild(sprite, true);
}
void MainScene5::onEnter()
{
	Scene::onEnter();

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_2(MainScene5::onContactBegin, this);

	auto dispatcher = Director::getInstance()->getEventDispatcher();

	dispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}
bool MainScene5::onContactBegin(EventCustom* event, const PhysicsContact& contact)
{
	auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();

	if (spriteA->getTag() == 1)
	{
		spriteA->removeFromParentAndCleanup(true);
	}

	if (spriteB->getTag() == 1)
	{
		spriteB->removeFromParentAndCleanup(true);
	}

	return true;
}
