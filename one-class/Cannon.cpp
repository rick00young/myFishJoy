#include "Cannon.h"

using namespace cocos2d;

Cannon::~Cannon()
{
	CCLog("cannon quit");
}

Cannon::Cannon()
{
	//CCLog("cannon quit");
}

Cannon* Cannon::initCannon()
{
	Cannon* _cannon = new Cannon();
	if(_cannon && _cannon->createCannon()){
		
		//
		CCLog("canon is inited");
		return _cannon;
	}else{
		delete _cannon;
		return NULL;
	}
}

bool Cannon::createCannon()
{
	CCSize  size = CCDirector::sharedDirector()->getWinSize();

	ratio = size.width / 1024;//´óÐ¡±ÈÀý
	levelCannon = 1;
	_sprite = CCSprite::createWithSpriteFrameName("actor_cannon1_11.png");
	_sprite->setScale(ratio);
	this->addChild(_sprite);

	//CCMoveTo *moveto = CCMoveTo::create(1.0f, ccp(size.width, size.height));
	//_sprite->runAction(moveto);

	CCMenuItemImage *addLevel = CCMenuItemImage::create("addA.png", "addB.png", this, menu_selector(Cannon::addCannon));
	
	addLevel->setPosition(ccp(30, -10));
	CCMenuItemImage *reduceLevel = CCMenuItemImage::create("reduceA.png", "reduceB.png", this, menu_selector(Cannon::reduceCannon));
	reduceLevel->setPosition(ccp(-30, -10));

	CCMenu *menuLevel = CCMenu::create(addLevel,reduceLevel, NULL);
	
	menuLevel->setPosition(CCPointZero);
	this->addChild(menuLevel, 102);

	return true;
}

void Cannon::addCannon(CCObject* pSender)
{
	CCLog("addCannon");

	levelCannon++;
	if(levelCannon > 6){
		levelCannon = 1;
	}
	CCLog("levelCannon id %d", levelCannon);
	//CCSize  size = CCDirector::sharedDirector()->getWinSize();
	CCString *frameName = CCString::createWithFormat("actor_cannon1_%d1.png", levelCannon);
	CCSpriteFrame *frame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString());

	CCScaleTo *scaleto = CCScaleTo::create(0.2f, 0.4f);
	CCScaleTo *scaleto_back = CCScaleTo::create(0.2f, ratio);
	CCFiniteTimeAction *sequence = CCSequence::create(scaleto, scaleto_back, NULL);
	_sprite->runAction(sequence);

	if(frame){
		_sprite->setDisplayFrame(frame);
	}
}

void Cannon::reduceCannon(CCObject* pSender)
{
	CCLog("reduceCannon");

	levelCannon--;
	
	if(levelCannon < 1){
		levelCannon = 6;
	}
	//CCLog("levelCannon id %d", levelCannon);
	//CCSize  size = CCDirector::sharedDirector()->getWinSize();
	CCString *frameName = CCString::createWithFormat("actor_cannon1_%d1.png", levelCannon);
	CCSpriteFrame *frame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString());

	CCScaleTo *scaleto = CCScaleTo::create(0.2f, 0.4f);
	CCScaleTo *scaleto_back = CCScaleTo::create(0.2f, ratio);
	CCFiniteTimeAction *sequence = CCSequence::create(scaleto, scaleto_back, NULL);
	_sprite->runAction(sequence);

	if(frame){
		_sprite->setDisplayFrame(frame);
	}
}


void Cannon::rotateToPoint(cocos2d::CCPoint ptTo)
{
    CCPoint ptFrom = this->getPosition();
    float angle = atan2f(ptTo.y - ptFrom.y, ptTo.x - ptFrom.x) / M_PI * 180.0f;
    _sprite->setRotation(90.0f - angle);
    //this->setDirection(ptTo);
}

float Cannon::getAngle()
{
	return _sprite->getRotation();
}

void Cannon::shoot()
{
	//bullet = Bullet::initBullet();
	//if(bullet){
		//CCLog("shoot");
	//}
}

int Cannon::getLevelCannon()
{
	return levelCannon;
}