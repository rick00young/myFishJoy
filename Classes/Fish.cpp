//
//  Fish.cpp
//  FishingJoy
//
//  Created by jie ding on 11/28/12.
//
//

#include "Fish.h"
#include "GameLayer.h"
//#include "math.h"

using namespace cocos2d;

//CCSize size = CCDirector::

const int pathArray[][8] = {
	{-200, 100, 200, 100, 300, -50, 200, 300},//0�����ң�ƫ��
	{-200, -100, 200, 200, 300, 300, 680, 300},//1�����ң�ƫ��
	{-100, -50, 240, 320, 560, -100, 110, 240},//2���µ�����
	{-100, 330, -20, -100, 550, 380, 270, 130},//3���ϵ�����
	{  50,-100,  30, 350,  500,  350, 70, 180},//4���µ�����
	{ 600, 100, 300, 100, -100, 300, -20,  40},//5�ҵ���ƫ��
	{ 550, 300, 300, -50, -150, 160, -60,  25},//6���ϵ���
	{ 600, 240, -20, 350, -150, -100, 10, -30},//7�ҵ���ƫ��
	{ 550, -100, 450,350, -100,  350, 70,  20},//8���µ�����
	{ 400, 400, 150, 420, 100, -100, -20, -80},//9�ϵ���ƫ��1
	{ 300, 400, 600, 100, 50, -100, -130, -35},//10�ϵ���ƫ��2
	{  50, 400, 600, 150, 250, -100, -160,-60},//11�ϵ���ƫ��1
	{ 300, 550,-100, 100, 100, -100, -50,-105},//12�ϵ���ƫ��2
	{ 25, -100, 350, 200, 100,  400, 150,  60},//13�µ���
	{ 200, -100, -100, 240, 350, 400, 10, 160},//14�µ���
	{ 400, -100,  500, 200, 200, 400, 120, 40},//15�µ���
	{ 450, -100, -100, 200, 260, 400, 0, 110}//16�µ���
};

Fish::~Fish()
{
    CCLOG("destruct fish %d", m_nFishType);
}


Fish *Fish::createWithFishType(int fishType, GameLayer *gameLayer, CCSpriteBatchNode *pBatchNode, float ratio)
{
    Fish *fish = new Fish();
	
    if(fish && fish->initWithFishType(fishType, gameLayer, pBatchNode, ratio))
    {
        fish->autorelease();
        return fish;
    }
    else
    {
        delete fish;
        return NULL;
    }
}


bool Fish::initWithFishType(int fishType, GameLayer *gameLayer, CCSpriteBatchNode *pBatchNode, float ratio)
{
	fishRatio = ratio;
	//////
    m_bCaught = false;
    this->setFishType(fishType);
    this->setGameLayer(gameLayer);
    this->setBatchNode(pBatchNode);
    m_bParticleBubble = false;
    
    if(m_nFishType == 11 || m_nFishType == 12)  //mermaid
        m_bParticleBubble = true;
    
    CCArray *frames = CCArray::create();
    for(int i = 1; i <= 16; i++)
    {
        CCString *frameName = CCString::createWithFormat("fish%02d_%02d.png", fishType, i);
        CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString());
        if(pFrame)
            frames->addObject(pFrame);
    }
    
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.2f);
    animation->setRestoreOriginalFrame(false);
    CCAnimate *animate = CCAnimate::create(animation);
    CCAction *swing = CCRepeatForever::create(animate);
    
    CCString *originalFrameName = CCString::createWithFormat("fish%02d_01.png", fishType);
    
    m_pSprite = CCSprite::createWithSpriteFrameName(originalFrameName->getCString());
	m_pSprite->setScale(ratio);
    m_pSprite->runAction(swing);
    
    m_pSprite->setAnchorPoint(ccp(0.5f, 0.5f));
    
    CCMoveTo *moveto = NULL;
	CCFiniteTimeAction*  bezierForward = NULL;

    this->getPath(moveto);
	//this->getPath(bezierForward);

    CCFiniteTimeAction *releaseFunc = CCCallFunc::create(this, callfunc_selector(Fish::removeSelf));
    CCFiniteTimeAction *sequence = CCSequence::create(moveto, releaseFunc, NULL);
	//CCFiniteTimeAction *sequence = CCSequence::create(bezierForward, releaseFunc, NULL);
    m_pSprite->runAction(sequence);
    
    this->getGameLayer()->getFishes()->addObject(this);
    this->getBatchNode()->addChild(m_pSprite);

    return true;
}

void Fish::showCaught()
{
    m_bCaught = true;
    m_pSprite->stopAllActions();
    
    CCArray *frames = CCArray::createWithCapacity(11);
    for(int i = 1; i <= 4; i++)
    {
        CCString *frameName = CCString::createWithFormat("fish%02d_catch_%02d.png", m_nFishType ,i);
        CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString());
        if(pFrame)
            frames->addObject(pFrame);
    }
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.3f);
    CCAnimate *animate = CCAnimate::create(animation);
    CCFiniteTimeAction *callFunc = CCCallFunc::create(this, callfunc_selector(Fish::removeSelf));
    CCFiniteTimeAction *sequence = CCSequence::create(animate, callFunc, NULL);
    m_pSprite->runAction(sequence);
    
}

void offsetPoint(CCPoint& pt, float offsetX, float offsetY)
{
    pt.x += offsetX;
    pt.y += offsetY;
}

//void Fish::getPath(cocos2d::CCMoveTo *&moveto)
void Fish::getPath(cocos2d::CCMoveTo *&moveto)
{
    CCSize fishSize = m_pSprite->getContentSize();
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint ptStart, ptEnd;
    //float radius = fmaxf(fishSize.width, fishSize.height) / 2;
	float radius = (fishSize.width > fishSize.height ? fishSize.width : fishSize.height) / 2;
    switch (rand() % 4) {
        case 0:
            ptStart.x = - radius;
            ptStart.y = rand() % (int)winSize.height;
            ptEnd.x = winSize.width + radius;
            ptEnd.y = rand() % (int)winSize.height;
            break;
        case 1:
            ptStart.x = winSize.width + radius;
            ptStart.y = rand() % (int)winSize.height;
            ptEnd.x = - radius;
            ptEnd.y = rand() % (int)winSize.height;
            break;
        case 2:
            ptStart.x = rand() % (int)winSize.width;
            ptStart.y = - radius;
            ptEnd.x = rand() % (int)winSize.width;
            ptEnd.y = winSize.height + radius;
            break;
        case 3:
            ptStart.x = rand() % (int)winSize.width;
            ptStart.y = winSize.height + radius;
            ptEnd.x = rand() % (int)winSize.width;
            ptEnd.y = - radius;
            break;
        default:
            break;
    }

    float angle = atan2f(ptEnd.y - ptStart.y, ptEnd.x - ptStart.x);
    float rotation = 180.0f - angle * 180.0f / M_PI;
    
    float duration = rand() % 10 + 4.0f;
    m_pSprite->setPosition(ptStart);
    m_pSprite->setRotation(rotation);
    moveto = CCMoveTo::create(duration, ptEnd);
	/*
	int index = rand() % 16;
	if(index > 15) index = 15;
	CCLog("index is %d", index);
	index = 0;
	m_pSprite->setPosition(ccp(pathArray[index][0],pathArray[index][1]));
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	ccBezierConfig bezier;
	bezier.controlPoint_1 = ccp(pathArray[index][2], pathArray[index][3]);
	bezier.controlPoint_2 = ccp(pathArray[index][4], pathArray[index][5]);
	bezier.endPosition = ccp(pathArray[index][6],pathArray[index][7]);

	float angle = atan2f(pathArray[index][7] - pathArray[index][1], pathArray[index][6] - pathArray[index][0]);
    float rotation = 180.0f - angle * 180.0f / M_PI;

    m_pSprite->setRotation(rotation);
	bezierForward = CCBezierBy::create(duration, bezier);
	/////
	*/

    
    if(m_bParticleBubble)
    {
        this->setParticleBubble(CCParticleSystemQuad::create("bubble.plist"));
        m_pGameLayer->addChild(m_pParticleBubble);
        float w = m_pSprite->getContentSize().width / 2.0f;
        offsetPoint(ptStart, cosf(angle) * w, sinf(angle) * w);

        m_pParticleBubble->setPosition(ptStart);
		m_pParticleBubble->setScale(fishRatio);
		m_pParticleBubble->setPosition(m_pSprite->getPosition());
        offsetPoint(ptEnd, cosf(angle) * w, sinf(angle) * w);
        CCAction *act = CCMoveTo::create(moveto->getDuration(), ptEnd);

		//CCAction *act = CCMoveTo::create(bezierForward->getDuration(), m_pSprite->getPosition());
        m_pParticleBubble->setAutoRemoveOnFinish(false);
		m_pParticleBubble->setPositionType(kCCPositionTypeFree);
		m_pParticleBubble->runAction(act);
		//CCFiniteTimeAction *m_sequence = CCSequence::create(bezierForward, NULL);

		//m_pParticleBubble->runAction(CCFollow::create(m_pSprite));
		
    }
    
}

void Fish::removeSelf()
{
    this->getGameLayer()->getFishes()->removeObject(this);
    m_pSprite->removeFromParentAndCleanup(true);
    if(m_bParticleBubble && m_pParticleBubble)
        m_pParticleBubble->removeFromParentAndCleanup(true);
}
