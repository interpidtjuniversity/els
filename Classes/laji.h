#ifndef MainScene5_hpp
#define MainScene5_hpp

#include "cocos2d.h"

class MainScene5 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene5);
};

#endif // __HELLOWORLD_SCENE_H__