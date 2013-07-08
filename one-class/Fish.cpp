#include "Fish.h"

#include "GameScene.h"


using namespace cocos2d;
Fish::Fish(void)
{
}


Fish::~Fish(void)
{
	CCLog("release fish *****************************************");
}

Fish* Fish::initFish(int level, GameScene *gameScene, cocos2d::CCSpriteBatchNode *pBatchNodeFish)
{
	Fish* _fish = new Fish();
	if(_fish && _fish->createFish(level, gameScene, pBatchNodeFish)){
		return _fish;
	}else{
		delete _fish;
		return NULL;
	}
}

bool Fish::createFish(int level, GameScene *gameScene, cocos2d::CCSpriteBatchNode *pBatchNodeFish)
{
	levelFish = level;
	m_bBubble = false;
	this->setCaught(false);
	CCLog("create fish! levelFish is %d", levelFish);

	if(levelFish == 11 || levelFish == 12){//美人鱼要气泡
		m_bBubble = true;
	}
	
	this->setgameScene(gameScene);
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	ratio = size.width  / 960; 
	CCString *originalFrameName = CCString::createWithFormat("fish%02d_01.png", levelFish);
	CCLog("fish name is %s", originalFrameName->getCString());
	//_spriteFish = CCSprite::createWithSpriteFrameName("fish01_01.png");
	_spriteFish = CCSprite::createWithSpriteFrameName(originalFrameName->getCString());
	
	//动画创建
	CCArray *frames = CCArray::create();
    for(int i = 1; i <= 16; i++)
    {
        CCString *frameName = CCString::createWithFormat("fish%02d_%02d.png", levelFish, i);
        CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString());
        if(pFrame)
            frames->addObject(pFrame);
    }
	//执行动画
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.2f);
    animation->setRestoreOriginalFrame(false);
    CCAnimate *animate = CCAnimate::create(animation);
    CCAction *swing = CCRepeatForever::create(animate);

	if(_spriteFish){//规避指针错误
		_spriteFish->setScale(ratio);
		_spriteFish->runAction(swing);
		gameScene->getFishes()->addObject(this);
		pBatchNodeFish->addChild(_spriteFish);
		this->runWithPath();
	}
		
	return true;
}


void Fish::runWithPath()
{
	//this->runWithLine();
	this->runFromLeftToRight(_spriteFish);
}

void Fish::runWithLine()
{
	CCMoveTo *moveto = NULL;
    CCSize fishSize = _spriteFish->getContentSize();
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
    _spriteFish->setPosition(ptStart);
    _spriteFish->setRotation(rotation);
    moveto = CCMoveTo::create(duration, ptEnd);

    CCFiniteTimeAction *releaseFunc = CCCallFunc::create(this, callfunc_selector(Fish::removeSelf));
    CCFiniteTimeAction *sequence = CCSequence::create(moveto, releaseFunc, NULL);
    _spriteFish->runAction(sequence);

    if(m_bBubble)
    {	
		this->showBubble(ptStart, ptEnd, angle, moveto->getDuration());
    }
}

void Fish::showBubble(CCPoint start, CCPoint end, float angle, float duation){

	this->setBubble(CCParticleSystemQuad::create("bubble.plist"));
	this->getgameScene()->addChild(m_pBubble);
    float w = _spriteFish->getContentSize().width / 2.0f * ratio;
    //offsetPoint(ptStart, cosf(angle) * w, sinf(angle) * w);
	start.x += cosf(angle) * w;
	start.y += sinf(angle) * w;
    m_pBubble->setPosition(start);
    //offsetPoint(ptEnd, cosf(angle) * w, sinf(angle) * w);
	end.x += cosf(angle) * w;
	end.y += sinf(angle) * w;
    CCAction *act = CCMoveTo::create(duation, end);
    m_pBubble->setAutoRemoveOnFinish(false);
    m_pBubble->setPositionType(kCCPositionTypeFree);
	m_pBubble->setScale(ratio);
    m_pBubble->runAction(act);
}

void Fish::runFromLeftToRight(CCSprite *sprite)
{
	CCMoveTo *moveto = NULL;
    CCSize fishSize = sprite->getContentSize();
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint ptStart, ptEnd;
    //float radius = fmaxf(fishSize.width, fishSize.height) / 2;

	float radius = (fishSize.width > fishSize.height ? fishSize.width : fishSize.height) / 2;
	ptStart.x = - radius;
	ptStart.y = rand() % (int)winSize.height;
	ptEnd.x = winSize.width + radius;
	ptEnd.y = ptStart.y ;

	float angle = atan2f(ptEnd.y - ptStart.y, ptEnd.x - ptStart.x);
    float rotation = 180.0f - angle * 180.0f / M_PI;
    
    float duration = rand() % 10 + 4.0f;
    sprite->setPosition(ptStart);
    sprite->setRotation(rotation);
    moveto = CCMoveTo::create(duration, ptEnd);

    CCFiniteTimeAction *releaseFunc = CCCallFunc::create(this, callfunc_selector(Fish::removeSelf));
    CCFiniteTimeAction *sequence = CCSequence::create(moveto, releaseFunc, NULL);
    sprite->runAction(sequence);
}

void Fish::showCaught()
{
	this->setCaught(true);
    _spriteFish->stopAllActions();
    
    CCArray *frames = CCArray::createWithCapacity(11);
    for(int i = 1; i <= 4; i++)
    {
        CCString *frameName = CCString::createWithFormat("fish%02d_catch_%02d.png", levelFish ,i);
        CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString());
        if(pFrame)
            frames->addObject(pFrame);
    }
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.3f);
    CCAnimate *animate = CCAnimate::create(animation);
    CCFiniteTimeAction *callFunc = CCCallFunc::create(this, callfunc_selector(Fish::removeSelf));
    CCFiniteTimeAction *sequence = CCSequence::create(animate, callFunc, NULL);

    _spriteFish->runAction(sequence);
}

void Fish::removeSelf()
{
	CCLog("callback fish remveself");
	_spriteFish->removeFromParentAndCleanup(true);
	this->getgameScene()->getFishes()->removeObject(this);
	
	this->autorelease();
}