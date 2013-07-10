#include "Bullet.h"
#include "Math.h"


#include "GameScene.h"

using namespace cocos2d;

Bullet::Bullet(void)
{
	
}


Bullet::~Bullet(void)
{
	//CCLog("bullt is deleting....................................");
    /*
    if(_spriteBullet){
        delete _spriteBullet;
        _spriteBullet = NULL;
    }
    */
}

Bullet* Bullet::initBullet(int level, GameScene *gameScene, cocos2d::CCSpriteBatchNode *pBatchNodeBullet)
{
	Bullet* _bullet = new Bullet();
	if(_bullet && _bullet->createBullet(level, gameScene, pBatchNodeBullet)){
		return _bullet;
	}else{
		delete _bullet;
		return NULL;
	}
	
}

bool Bullet::createBullet(int level, GameScene *gameScene,cocos2d::CCSpriteBatchNode *pBatchNodeBullet)
{
	levelBullet = level;//子弹级别
	this->setgameScene(gameScene);
    this->setCaught(false);
	CCString *frameName = CCString::createWithFormat("bullet0%d.png",level);
	//_spriteBullet = CCSprite::createWithSpriteFrameName("bullet01.png");
    this->setSpriteBullet(CCSprite::createWithSpriteFrameName(frameName->getCString()));
    _spriteBullet->setVisible(false);//初始化时可见性为false
	gameScene->getBullets()->addObject(this);


	pBatchNodeBullet->addChild(_spriteBullet);
	
	return true;
}

void Bullet::shoot(int level,CCPoint startPosition, CCPoint endPosition, float angle)
{
	//CCLog("level is %d", levelBullet);
    levelBullet = level;
    CCString *frameName = CCString::createWithFormat("bullet0%d.png",level);

    CCSpriteFrame *frame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString()); 
    if(frame){
        _spriteBullet->setDisplayFrame(frame); 
    }

    _spriteBullet->setVisible(true);
	_spriteBullet->setPosition(startPosition);
	//计算子弹的最大射程

	float distance = ccpDistance(startPosition, endPosition);
	//CCLog("distance is %f", distance);

	CCPoint realEnd;
	float x = 0;
	float y = 0;
	float _angle = angle;
	int _level = levelBullet < 3 ? 3 : levelBullet; 
	float radius = (float)(_level * 55);
	//CCLog("levelBullet is %d", levelBullet);

	if( radius >= distance){
		realEnd = endPosition;
	}else{
		
		if(angle < 0){
			_angle = CC_DEGREES_TO_RADIANS(angle + 90.0f);
			x = startPosition.x - radius * cos(_angle);
		}else{
			_angle = CC_DEGREES_TO_RADIANS(90.0f - angle);
			x = startPosition.x + radius * cos(_angle);
		}
		y = radius * sin(_angle);
		//CCLog("y is %f", y);
		realEnd = ccp(x, y);
	}

	
	//CCLog("angle is %f", _angle);
	CCMoveTo* moveto = CCMoveTo::create(levelBullet * 0.2f, realEnd);
	CCFiniteTimeAction *releaseFunc = CCCallFunc::create(this, callfunc_selector(Bullet::removeSelf));
	CCFiniteTimeAction *sequence = CCSequence::create(moveto,releaseFunc, NULL);
	//CCString *bulletName = CCString::createWithFormat("bullet0%d.png", levelBullet);
	_spriteBullet->setRotation(angle);
	_spriteBullet->runAction(sequence);
	
}

void Bullet::removeSelf()
{
	//CCLog("moved....");
    _spriteBullet->setVisible(false);
	this->getgameScene()->showFishNet(_spriteBullet->getPosition());//展现鱼网

	//_spriteBullet->removeFromParentAndCleanup(true);
	//this->getgameScene()->getBullets()->removeObject(this);
	
	//this->autorelease();
}