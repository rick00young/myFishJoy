#include "Bullet.h"
using namespace cocos2d;

Bullet::Bullet(void)
{
	CCLog("delete bullt");
}


Bullet::~Bullet(void)
{

}

Bullet* Bullet::initBullet()
{
	Bullet* _bullet = new Bullet();
	if(_bullet && _bullet->createBullet()){
		return _bullet;
	}else{
		delete _bullet;
		return NULL;
	}
	
}

bool Bullet::createBullet()
{
	_spriteBullet = CCSprite::createWithSpriteFrameName("bullet01.png");
	//this->addChild(_spriteBullet);
	return true;
}