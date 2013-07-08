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

	CCString *frameName = CCString::createWithFormat("net0%d.png",level);
	_netSprite = CCSprite::createWithSpriteFrameName(frameName->getCString());
	gameScene->getFishNets()->addObject(this);
	m_pBatchNode3->addChild(_netSprite);
	return true;
}

void FishNet::showFishNet(CCPoint point)
{
	_netSprite->setPosition(point);

	CCFadeTo* fadeTo = CCFadeTo::create(1.0f, 0.0f);
	CCFiniteTimeAction *releaseFunc = CCCallFunc::create(this, callfunc_selector(FishNet::removeSelf));
	CCFiniteTimeAction *sequence = CCSequence::create(fadeTo,releaseFunc, NULL);
	//CCString *bulletName = CCString::createWithFormat("bullet0%d.png", levelBullet);
	//_spriteBullet->setRotation(angle);
	//_spriteBullet->runAction(sequence);
	_netSprite->runAction(sequence);
	
}


void FishNet::removeSelf()
{
	//CCLog("release fishnet");

	_netSprite->removeFromParentAndCleanup(true);
	this->getgameScene()->getFishNets()->removeObject(this);
	
	this->autorelease();
}