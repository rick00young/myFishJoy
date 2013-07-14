#include "FishNet.h"

#include "GameScene.h"

using namespace cocos2d;

FishNet::FishNet(void)
{
}


FishNet::~FishNet(void)
{
	//CCLog("release FishNet ++++++++++++++++++++++++++++++++++++++++++++++++++++");
}

FishNet* FishNet::initFishNet(int level, GameScene *gameScene, CCSpriteBatchNode *m_pBatchNode3)
{
	//CCLog("init fishnet");
	FishNet* _fishNet = new FishNet();
	if(_fishNet && _fishNet->createFishNet(level, gameScene, m_pBatchNode3)){
		return _fishNet;
	}else{
		delete _fishNet;
		return NULL;
	}
}

bool FishNet::createFishNet(int level, GameScene *gameScene, CCSpriteBatchNode *m_pBatchNode3)
{
	//CCLog("fishnet is created");
	levelNet = level;
	this->setgameScene(gameScene);

	CCString *frameName = CCString::createWithFormat("net0%d.png",levelNet);
	_netSprite = CCSprite::createWithSpriteFrameName(frameName->getCString());
    _netSprite->setVisible(false);
    
	gameScene->getFishNets()->addObject(this);
	m_pBatchNode3->addChild(_netSprite);
	return true;
}

void FishNet::showFishNet(int level, CCPoint point)
{
    _netSprite->stopAllActions();
    levelNet = level;
    CCString *frameName = CCString::createWithFormat("net0%d.png",levelNet);

    CCSpriteFrame *frame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString()); 
    if(frame){
        _netSprite->setDisplayFrame(frame); 
        //CCLog("levelNet is %d", levelNet);
    }

	_netSprite->setPosition(point);

	CCFadeOut* fadeOut = CCFadeOut::create(1.0f);//FadeTo与setVisibel不能配合使用
	CCFiniteTimeAction *releaseFunc = CCCallFunc::create(this, callfunc_selector(FishNet::removeSelf));
	CCFiniteTimeAction *sequence = CCSequence::create(fadeOut,releaseFunc, NULL);
	_netSprite->runAction(sequence);
	
}


void FishNet::removeSelf()
{
	//CCLog("release fishnet");
    _netSprite->setVisible(false);
    //CCLog("visible is %d", _netSprite->isVisible());
    //_netSprite->runAction(CCFadeTo::create(0.0f, 1.0f));
	//_netSprite->removeFromParentAndCleanup(true);
	//this->getgameScene()->getFishNets()->removeObject(this);
	
	//this->autorelease();
}