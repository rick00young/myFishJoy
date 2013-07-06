#ifndef __Cannon_H__
#define __Cannon_H__

#include "cocos2d.h"
#include "Bullet.h"
//#include "Box2D/Box2D.h"
#define CANNON_PADDING 20.0f
class Cannon : public cocos2d::CCNode
{
public:
	~Cannon();
	Cannon();
	static Cannon* initCannon();
	bool createCannon();
	cocos2d::CCSprite * _sprite;
	float ratio;
	int levelCannon;
	void addCannon(cocos2d::CCObject *sender);
	void reduceCannon(cocos2d::CCObject *sender);
	void rotateToPoint(cocos2d::CCPoint ptTo);
	float getAngle();
	int getLevelCannon();
	Bullet *bullet;
	void shoot();
};

#endif  // __HELLOWORLD_SCENE_H__