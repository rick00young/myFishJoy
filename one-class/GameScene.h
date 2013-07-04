#ifndef __GameScene_SCENE_H__
#define __GameScene_SCENE_H__

#include "cocos2d.h"
#include "Cannon.h"
//#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"

class GameScene : public cocos2d::CCLayer
{
public:
    
    virtual bool init();
	static cocos2d::CCScene* scene();
    void menuCloseCallback(CCObject* pSender);

	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	CC_SYNTHESIZE(cocos2d::CCArray *, BulletArray, Bullet);
    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);

private:
	float ratio;//´óÐ¡±ÈÀý
	Cannon* cannon;
	void initFrames();
    void initBackground();
    void initCannon();
	//void initFishes();
    
};

#endif  // __HELLOWORLD_SCENE_H__