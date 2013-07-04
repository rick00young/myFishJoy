#ifndef __Bullet_H__
#define __Bullet_H__

#include "cocos2d.h"

//#include "Box2D/Box2D.h"
#define CANNON_PADDING 20.0f
class Bullet : public cocos2d::CCSprite
{
public:
	~Bullet();
	Bullet();
	static Bullet* initBullet();
	bool createBullet();
	cocos2d::CCSprite * _spriteBullet;
	float ratio;
	int levelCannon;
	//void addCannon(cocos2d::CCObject *sender);
	//void reduceCannon(cocos2d::CCObject *sender);
	//void rotateToPoint(cocos2d::CCPoint ptTo);
};

#endif  // __Bullet_SCENE_H__