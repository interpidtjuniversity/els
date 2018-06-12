#define RATIO 5
#include "min.h"
#include "SimpleAudioEngine.h"
#include  "math\Vec2.h"

b2World HelloWorld::createWorld(){
	world = new b2World(b2Vec2(0, -8));//初始化重力环境  
	return *world;
}

// Print useful error message instead of segfaulting when files are not there.
void HelloWorld::initSprite(){
	//先创建一个精灵：  
	auto ss = Sprite::create("CloseNormal.png");
	this->addChild(ss);
	ss->setScale(3, 3);


	//用来确定物体的位置，类型（动态。静态）;  
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(5, 6);
	b2Body *body = world->CreateBody(&bodyDef);

	//指定精灵的形状，这个步骤不能省略，  
	b2PolygonShape shape;
	shape.SetAsBox(ss->getContentSize().width / RATIO, ss->getContentSize().height / RATIO);//单位是m  

	//材料，用来设置物体的属性（质量，密度，摩擦力，形状，）  
	b2FixtureDef fixtureDef;
	fixtureDef.density = 1;
	fixtureDef.friction = 0.3;
	fixtureDef.shape = &shape; //如果形状为0的话，这个属性是必须的。  
	body->CreateFixture(&fixtureDef);

	body->SetUserData(ss);//物体和世界关联代码：  
}
// on "init" you need to initialize your instance
void HelloWorld::myupdata(float dt){
	world->Step(dt, 8, 3);
	Sprite * bird;
	//对于动态的物体，我们要实时的更新它的位置和状态。静态的就不用判断了。  
	for (b2Body *body = world->GetBodyList(); body; body = body->GetNext()) {
		if (body->GetType() == b2_dynamicBody) {
			bird = (Sprite*)body->GetUserData();
			bird->setPosition(Vec2(body->GetPosition().x*RATIO, body->GetPosition().y*RATIO));//设置动态物体的位置  


		}
	}
}

void HelloWorld::initGround(){

	//地板的位置和类型，（静态)  
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position = b2Vec2(0, 0.1);  
	b2Body *body = world->CreateBody(&bodyDef);  


	//指定形状，这一步骤必须有  
	b2PolygonShape groundShape;
	groundShape.SetAsBox(960 / RATIO, 0.5);
	b2FixtureDef fixture;
	fixture.density = 1;//密度  
	fixture.friction = 0.3;//摩擦力  
	fixture.restitution = 0.8;
	fixture.shape = &groundShape;

	body->CreateFixture(&fixture);

	//设置地板，这里用的是精灵，图片可以自己设定，也可以用UI 进行绘图：  
	Sprite *sp = Sprite::create("HelloWorld.png");
	sp->setAnchorPoint(Vec2(0, 0));
	sp->setPosition(Vec2(0, 0));
	sp->setScale(3, 0.1);
	this->addChild(sp);
	body->SetUserData(sp);
}




