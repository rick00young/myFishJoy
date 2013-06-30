#ifndef FishingJoy_Cannon_h
#define FishingJoy_Cannon_h
#include "cocos2d.h"

class Cannon : public cocos2d::CCNode, public cocos2d::CCTargetedTouchDelegate
{
public:
	Cannon(void);
	Cannon(float);
	~Cannon(void);
	virtual void onEnter();
	int cannonLevel;
	float ratio;
	void setConnonLevel(int level);
	float rotation;
	cocos2d::CCSprite *cannon;
	void setRotation(float);
	void rotateToPoint(cocos2d::CCPoint pt);
	cocos2d::CCPoint getCannonPosition(void);
	CREATE_FUNC(Cannon);
};

#endif