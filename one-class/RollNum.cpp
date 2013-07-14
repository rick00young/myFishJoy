#include "RollNum.h"
using namespace cocos2d;

#define NUMBERHEIGHT    16
#define NUMBERWIDTH     12
#define TEXTUREHEIGHT   196

RollNum::RollNum(void):m_nNumber(0), CurRoll_h(0), EndRoll_h(0), m_bRolling(false), m_pTexture(NULL)
{
}


RollNum::~RollNum(void)
{
}


RollNum* RollNum::initRollNum(CCSpriteBatchNode *m_pBatchNode)
{
    RollNum* _rollNum = new RollNum();
    
    if(_rollNum && _rollNum->createRollNum(m_pBatchNode)){
        _rollNum->autorelease();
       
        return _rollNum;
    }else{
        CC_SAFE_DELETE(_rollNum);
        return NULL;
    }


}

bool RollNum::createRollNum(CCSpriteBatchNode *m_pBatchNode)
{
    ratio = CCDirector::sharedDirector()->getWinSize().width / 1024;
    m_pTexture = CCTextureCache::sharedTextureCache()->textureForKey("number.png");
    CCSpriteFrame *pFrame = CCSpriteFrame::createWithTexture(m_pTexture, CCRectMake(0, 0, NUMBERWIDTH, NUMBERHEIGHT));
    
    if(pFrame){
        this->setSpriteRollNum(CCSprite::createWithSpriteFrame(pFrame));
        //_spriteRollNum->setScale(ratio);
        m_pBatchNode->addChild(_spriteRollNum);
        return true;
    }else{
        return false;
    }


}

void RollNum::updateNumber(float dt){
    CCLog("update %%%%%%%%%%%%%%%%%%%%");
}

void RollNum::setNumber(int var)
{
    

    if(var == m_nNumber){
        return;
    }
  
    int h = var * (NUMBERHEIGHT + 4);
    if(h > TEXTUREHEIGHT || h < 0){
        return;
    }
    CCSpriteFrame *pFrame = CCSpriteFrame::createWithTexture(m_pTexture, CCRectMake(0, h, NUMBERWIDTH, NUMBERHEIGHT));
    if(pFrame){
        _spriteRollNum->setDisplayFrame(pFrame);
    }
        

    //m_bRolling = true;
}

int RollNum::getNumber()
{
    return m_nNumber;
}

//////////////////////////////////////////////////////////
RollNumGroup::RollNumGroup():m_pRollNumArray(NULL), m_nValue(0)
{
    
}

RollNumGroup::~RollNumGroup()
{
    CC_SAFE_RELEASE(m_pRollNumArray);
}


RollNumGroup *RollNumGroup::initRollGroup(cocos2d::CCSpriteBatchNode *m_pBatchNode, int nDigit)
{
    RollNumGroup *pRollNumGroup = new RollNumGroup();
    if(pRollNumGroup && pRollNumGroup->createRollGroup(m_pBatchNode, nDigit))
    {
        //pRollNumGroup->autorelease();
        return pRollNumGroup;
    }
    else
    {
        CC_SAFE_DELETE(pRollNumGroup);
        return NULL;
    }
}

bool RollNumGroup::createRollGroup(cocos2d::CCSpriteBatchNode *m_pBatchNode, int nDigit)
{
    //CCLog("crate rollgroup ++++++++++++++++++++++++++++++");
    
    //m_pGameScene->addChild(m_pBatchNode, 100);
    
    ratio = CCDirector::sharedDirector()->getWinSize().width / 1024;
    this->setRollNumArray(CCArray::createWithCapacity(nDigit));
    m_pRollNumArray->retain();
   
    
    
    for(int i = 0; i < nDigit; i++)
    {
        RollNum *pRollNum = RollNum::initRollNum(m_pBatchNode);
        m_pRollNumArray->addObject(pRollNum);
        
    }
    
    return true;
}

void RollNumGroup::setPosition(cocos2d::CCPoint pt)
{
    m_ptPosition = pt;
    for(int i = 0; i < (int)(m_pRollNumArray->count()); i++)
    {
        RollNum *pRollNum = (RollNum *)m_pRollNumArray->objectAtIndex(i);
        pRollNum->getSpriteRollNum()->setPosition(pt);
        pt.x -= (20.7f * ratio);
    }
}

void RollNumGroup::setValue(int nValue)
{
    if(m_nValue == nValue){
        return;
    }
       
    //CCLog("hit **********************************");
    //return;
    m_nValue = nValue;
    unsigned int count = m_pRollNumArray->count();

    for(unsigned int i = 0; i < count; i++)
    {
        
        RollNum *pRollNum = (RollNum *)m_pRollNumArray->objectAtIndex(i);
        int num = nValue % 10;
        if(pRollNum->getNumber() != num){
            pRollNum->setNumber(num);
            
        }
        
        nValue = nValue / 10;
    }
}

int RollNumGroup::getValue(){
    return m_nValue;
}

void RollNumGroup::test()
{
    CCLog("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
    
    CCLog("count is %d", (CCArray *)m_pRollNumArray->count());
}

///////////////////////////////////////////////////////////////

Coin::Coin(void)
{
}


Coin::~Coin(void)
{

}

Coin* Coin::initCoin(cocos2d::CCSpriteBatchNode *m_pBatchNode)
{
    Coin* _coin = new Coin();
    if(_coin && _coin->createCoin(m_pBatchNode)){
        return _coin;
    }else{
        CC_SAFE_DELETE(_coin);
        return NULL;
    }
}

bool Coin::createCoin(cocos2d::CCSpriteBatchNode *m_pBatchNode){

    levelCoin = 0;
    ratio = CCDirector::sharedDirector()->getWinSize().width / 1024;
    this->setSpriteCoin(CCSprite::createWithSpriteFrameName("gold01.png"));//´´½¨coin¾«Áé
    m_pBatchNode->addChild(_spriteCoin);
    if(_spriteCoin){
        _spriteCoin->setScale(ratio);
        _spriteCoin->setVisible(false);    
    }


    return true;
}

void Coin::showCoin(CCPoint pt, int level)
{
    
    levelCoin = level;
    _spriteCoin->setPosition(pt);
    _spriteCoin->setVisible(true);
    _spriteCoin->stopAllActions();

    CCArray *frames = CCArray::createWithCapacity(10);
    for(int i = 1; i <= 9; i++)
    {
        CCString *frameName = CCString::createWithFormat("gold0%d.png",i);
        //CCLog("string is %s", frameName->getCString());
        CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString());
        if(pFrame)
            frames->addObject(pFrame);
    }
    
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.2f);
    animation->setRestoreOriginalFrame(true);
    CCAnimate *animate = CCAnimate::create(animation);
    CCAction *swing = CCRepeatForever::create(animate);

    _spriteCoin->runAction(swing);
    this->runWithPath();
}

void Coin::runWithPath()
{
    CCMoveTo* moveTo = CCMoveTo::create(2.0f, ccp(170, 10));
    CCFadeOut *fadeOut = CCFadeOut::create(2.0f);
    //mouse_panel->runAction(CCSequence::create(CCSpawn::create(actionTo, fadeOut, NULL),actionMoveDone, NULL));
    CCFiniteTimeAction *callFunc = CCCallFunc::create(this, callfunc_selector(Coin::removeSelf));
    _spriteCoin->runAction(CCSequence::create(CCSpawn::create(moveTo, fadeOut, NULL), callFunc, NULL));
    //_spriteCoin->runAction(CCSequence::create(CCDelayTime::create(1.0f), CCSpawn::create(moveTo, fadeOut, NULL), callFunc, NULL));
}

void Coin::removeSelf()
{
    _spriteCoin->setVisible(false);
}