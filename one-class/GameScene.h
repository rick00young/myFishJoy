#ifndef __GameScene_SCENE_H__
#define __GameScene_SCENE_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"

class GameScene : public cocos2d::CCScene
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    //static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);
};

#endif  // __HELLOWORLD_SCENE_H__