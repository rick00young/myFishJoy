#ifndef __GameScene_SCENE_H__
#define __GameScene_SCENE_H__

#include "cocos2d.h"
#include "Cannon.h"
#include "Bullet.h"
//#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"

class GameScene : public cocos2d::CCLayer
{
public:
    
    virtual bool init();
	static cocos2d::CCScene* scene();
    void menuCloseCallback(CCObject* pSender);

	CC_SYNTHESIZE(cocos2d::CCSpriteBatchNode *, m_pBatchNode1, BatchNode1);
    CC_SYNTHESIZE(cocos2d::CCSpriteBatchNode *, m_pBatchNode2, BatchNode2);
    CC_SYNTHESIZE(cocos2d::CCSpriteBatchNode *, m_pBatchNode3, BatchNode3);
    CC_SYNTHESIZE(cocos2d::CCSpriteBatchNode *, m_pBatchNode4, BatchNode4);
	//CC_SYNTHESIZE_RETAIN(cocos2d::CCArray *, m_pFishes, Fishes);
    CC_SYNTHESIZE(cocos2d::CCArray *, m_pBullets, Bullets);

	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	//CC_SYNTHESIZE(cocos2d::CCArray *, BulletArray, Bullet);
    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);

private:
	float ratio;//´óÐ¡±ÈÀý
	bool isControl;
	Cannon* cannon;
	Bullet *bullet;
	void initFrames();
    void initBackground();
    void initCannon();
	void initFishes();
    
};

#endif  // __HELLOWORLD_SCENE_H__