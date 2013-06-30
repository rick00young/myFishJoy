//
//  Fish.h
//  FishingJoy
//
//  Created by jie ding on 11/28/12.
//
//

#ifndef __FishingJoy__Fish__
#define __FishingJoy__Fish__

#include <iostream>
#include "cocos2d.h"

class GameLayer;

class Fish : public cocos2d::CCObject
{
public:
    virtual ~Fish();
	//virtual Fish();
    static Fish *createWithFishType(int fishType, GameLayer *gameLayer, cocos2d::CCSpriteBatchNode *pBatchNode, float ratio);
    CC_SYNTHESIZE(GameLayer *, m_pGameLayer, GameLayer);
    CC_SYNTHESIZE(cocos2d::CCSpriteBatchNode *, m_pBatchNode, BatchNode);
    CC_SYNTHESIZE(int, m_nFishType, FishType);
    CC_SYNTHESIZE(cocos2d::CCSprite *, m_pSprite, Sprite);
    CC_SYNTHESIZE_READONLY(bool, m_bCaught, Caught);
    CC_SYNTHESIZE(cocos2d::CCParticleSystem *, m_pParticleBubble, ParticleBubble);
    void showCaught();
private:
	//int pathArray[][8];
	float fishRatio;
    bool initWithFishType(int fishType, GameLayer *gameLayer, cocos2d::CCSpriteBatchNode *pBatchNode, float ratio);
    void removeSelf();
    void getPath(cocos2d::CCMoveTo *&moveto);
    bool m_bParticleBubble;

};

#endif /* defined(__FishingJoy__Fish__) */
