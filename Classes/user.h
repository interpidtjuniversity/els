#include <stdio.h>
#include "cocos2d.h"
#include"Box2D.h"
USING_NS_CC;
using namespace cocos2d;

struct MyContact
{
	b2Fixture *fixtureA;
	b2Fixture *fixtureB;

	bool operator==(const MyContact &other) const
	{
		return (fixtureA == other.fixtureA) && (fixtureB == other.fixtureB);
	}
};

class MyContactListener : public b2ContactListener
{
public:
	MyContactListener();

	~MyContactListener();

	virtual void BeginContact(b2Contact* contact);

	virtual void EndContact(b2Contact* contact);

	std::vector<MyContact> _contacts;

};