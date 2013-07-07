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
	CCLog("create fish!");
	levelFish = level;
	this->setgameScene(gameScene);
	_spriteFish = CCSprite::createWithSpriteFrameName("fish01_01.png");
	
	//动画创建
	CCArray *frames = CCArray::create();
    for(int i = 1; i <= 16; i++)
    {
        CCString *frameName = CCString::createWithFormat("fish0%d_0%d.png", 1, i);
        CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString());
        if(pFrame)
            frames->addObject(pFrame);
    }
	//执行动画
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.2f);
    animation->setRestoreOriginalFrame(false);
    CCAnimate *animate = CCAnimate::create(animation);
    CCAction *swing = CCRepeatForever::create(animate);

	_spriteFish->runAction(swing);

	gameScene->getFishes()->addObject(this);
	pBatchNodeFish->addChild(_spriteFish);

	this->runWithPath();
	return true;
}


void Fish::runWithPath()
{

	//_spriteFish->setPosition(ccp(0,0));
	//CCMoveTo* moveTo = CCMoveTo::create(1.5f, ccp(200,200));
	//_spriteFish->runAction(moveTo);
	this->runWithLine();
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
}


void Fish::removeSelf()
{
	CCLog("callback fish remveself");
	_spriteFish->removeFromParentAndCleanup(true);
	this->getgameScene()->getFishes()->removeObject(this);
	
	this->autorelease();
}