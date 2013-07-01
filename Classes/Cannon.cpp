#include "Cannon.h"
using namespace cocos2d;

Cannon::Cannon(float _ratio)
{
	//cannonLevel = level;
	ratio = _ratio;
	CCLog("ratio is %f", ratio);
}


Cannon::~Cannon(void)
{

}

void Cannon::onEnter(void)
{
	//this->setTouchEnabled(true);
	cannon = CCSprite::createWithSpriteFrameName("actor_cannon1_11.png");
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	if(cannon){
		cannon->setPosition(ccp(size.width/2 + 8,20));
		cannon->setScale(ratio);
		this->addChild(cannon,10);
		//CCLog("okkkkkkkk");
	}else{
		//CCLog("nooooooo");
	}

}

void Cannon::setConnonLevel(int level)
{
	cannonLevel = level;
	if(cannonLevel < 1){
		cannonLevel = 1;
	}

	if(cannonLevel > 6){
		cannonLevel = 6;
	}
}

void Cannon::setRotation(float rotation)
{
	cannon->setRotation(rotation);
}

void Cannon::rotateToPoint(cocos2d::CCPoint ptTo)
{
    CCPoint ptFrom = cannon->getPosition();
    float angle = atan2f(ptTo.y - ptFrom.y, ptTo.x - ptFrom.x) / M_PI * 180.0f;
    cannon->setRotation(90.0f - angle);
    //this->setDirection(ptTo);
}

CCPoint Cannon::getCannonPosition(void)
{
	return cannon->getPosition();
}

void Cannon::addLevel(int level)
{
	//CCLog("addLevel");
	cannonLevel = level;

	CCString *frameName = CCString::createWithFormat("actor_cannon1_%d1.png", cannonLevel);
	CCSpriteFrame *frame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString());
	
	

	CCScaleTo  *scaleto = CCScaleTo ::create(0.5f, 0.06f);
	CCBlink *blink =  CCBlink::create(1.0f, 5);
	CCFiniteTimeAction *sequence = CCSequence::create(scaleto, blink, NULL);
	cannon->runAction(sequence);

	//this->setVisible(false);
	//CCLog("scaleto is %f", this->getScale());
	if(frame){
		cannon->setDisplayFrame(frame);
		
		//cannon->setScale(0.02);
		//cannon->setScale(ratio);
		//CCLog("ok");
	}else{
		//CCLog("no");
	}
}

void Cannon::reduceLevel(int level)
{
	//CCLog("reduceLevel");
	cannonLevel = level;
	CCString *frameName = CCString::createWithFormat("actor_cannon1_%d1.png", cannonLevel);
	CCSpriteFrame *frame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString());
	//CCScaleBy *scaleTo = CCScaleBy::create(0.5, 0.2, 0.2);
	//CCScaleTo *scaleBack = scaleTo->reverse();
	if(frame){
		cannon->setDisplayFrame(frame);
		//cannon->runAction(CCSequence::create(scaleTo, NULL));
		CCLog("ok");
	}else{
		CCLog("no");
	}
}