#ifndef __GameScene_SCENE_H__
#define __GameScene_SCENE_H__

#include "cocos2d.h"
#include "Cannon.h"
//#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"

class GameScene : public cocos2d::CCScene
{
public:
    
    virtual bool init();

    void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);

private:
	float ratio;//��С����
	Cannon* cannon;
	void initFrames();
    void initBackground();
    void initCannon();
	//void initFishes();
    
};

#endif  // __HELLOWORLD_SCENE_H__