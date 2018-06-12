#define RATIO 5
#include "min.h"
#include "SimpleAudioEngine.h"
#include  "math\Vec2.h"

b2World HelloWorld::createWorld(){
	world = new b2World(b2Vec2(0, -8));//��ʼ����������  
	return *world;
}

// Print useful error message instead of segfaulting when files are not there.
void HelloWorld::initSprite(){
	//�ȴ���һ�����飺  
	auto ss = Sprite::create("CloseNormal.png");
	this->addChild(ss);
	ss->setScale(3, 3);


	//����ȷ�������λ�ã����ͣ���̬����̬��;  
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(5, 6);
	b2Body *body = world->CreateBody(&bodyDef);

	//ָ���������״��������費��ʡ�ԣ�  
	b2PolygonShape shape;
	shape.SetAsBox(ss->getContentSize().width / RATIO, ss->getContentSize().height / RATIO);//��λ��m  

	//���ϣ�����������������ԣ��������ܶȣ�Ħ��������״����  
	b2FixtureDef fixtureDef;
	fixtureDef.density = 1;
	fixtureDef.friction = 0.3;
	fixtureDef.shape = &shape; //�����״Ϊ0�Ļ�����������Ǳ���ġ�  
	body->CreateFixture(&fixtureDef);

	body->SetUserData(ss);//���������������룺  
}
// on "init" you need to initialize your instance
void HelloWorld::myupdata(float dt){
	world->Step(dt, 8, 3);
	Sprite * bird;
	//���ڶ�̬�����壬����Ҫʵʱ�ĸ�������λ�ú�״̬����̬�ľͲ����ж��ˡ�  
	for (b2Body *body = world->GetBodyList(); body; body = body->GetNext()) {
		if (body->GetType() == b2_dynamicBody) {
			bird = (Sprite*)body->GetUserData();
			bird->setPosition(Vec2(body->GetPosition().x*RATIO, body->GetPosition().y*RATIO));//���ö�̬�����λ��  


		}
	}
}

void HelloWorld::initGround(){

	//�ذ��λ�ú����ͣ�����̬)  
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position = b2Vec2(0, 0.1);  
	b2Body *body = world->CreateBody(&bodyDef);  


	//ָ����״����һ���������  
	b2PolygonShape groundShape;
	groundShape.SetAsBox(960 / RATIO, 0.5);
	b2FixtureDef fixture;
	fixture.density = 1;//�ܶ�  
	fixture.friction = 0.3;//Ħ����  
	fixture.restitution = 0.8;
	fixture.shape = &groundShape;

	body->CreateFixture(&fixture);

	//���õذ壬�����õ��Ǿ��飬ͼƬ�����Լ��趨��Ҳ������UI ���л�ͼ��  
	Sprite *sp = Sprite::create("HelloWorld.png");
	sp->setAnchorPoint(Vec2(0, 0));
	sp->setPosition(Vec2(0, 0));
	sp->setScale(3, 0.1);
	this->addChild(sp);
	body->SetUserData(sp);
}




