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