#ifndef __GameScene_SCENE_H__
#define __GameScene_SCENE_H__

#include "cocos2d.h"
//#include "iostream"
#include <algorithm>
#include "Cannon.h"
#include "Fish.h"
#include "Bullet.h"
#include "FishNet.h"
#include "RollNum.h"
//#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"
#define MAX_FISH_COUNT 5
#define LENGTH_ARRAY 12

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

    CC_SYNTHESIZE(cocos2d::CCSpriteBatchNode *, m_pBatchNode5, BatchNode5);//计分器

	CC_SYNTHESIZE(cocos2d::CCArray *, m_pFishes, Fishes);
    CC_SYNTHESIZE(cocos2d::CCArray *, m_pFishes2, Fishes2);
    CC_SYNTHESIZE(cocos2d::CCArray *, m_pFishes3, Fishes3);
    CC_SYNTHESIZE(cocos2d::CCArray *, m_pFishes4, Fishes4);

    CC_SYNTHESIZE(cocos2d::CCArray *, m_pBullets, Bullets);
	CC_SYNTHESIZE(cocos2d::CCArray *, m_pFishNets, FishNets);

	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	//CC_SYNTHESIZE(cocos2d::CCArray *, BulletArray, Bullet);
    // implement the "static node()" method manually
    int FishCount;//
	void showFishNet(cocos2d::CCPoint point);//展现鱼网
    CREATE_FUNC(GameScene);

private:
	float ratio;//大小比例
	bool isControl;
    
	Cannon* cannon;
	Bullet *bullet;
	FishNet *fishNet;
	Fish *fish;
    RollNumGroup* rollNumGroup;
	void initFrames();
    void initBackground();
    void initCannon();
    void initRollNum();
	void initFishes();
	void addFish();
	void updateFish(float dt);
	
    virtual void update(float time);
};

#endif  // __HELLOWORLD_SCENE_H__