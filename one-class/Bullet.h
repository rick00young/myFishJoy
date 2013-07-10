#ifndef __Bullet_H__
#define __Bullet_H__

#include "cocos2d.h"


//#include "Box2D/Box2D.h"
#define CANNON_PADDING 20.0f
class GameScene;

class Bullet : public cocos2d::CCSprite
{
public:
	~Bullet();
	Bullet();
	static Bullet* initBullet(int level, GameScene *gameScene, cocos2d::CCSpriteBatchNode *pBatchNodeBullet);
	bool createBullet(int level, GameScene *gameScene, cocos2d::CCSpriteBatchNode *pBatchNodeBullet);
	CC_SYNTHESIZE(GameScene *, m_pgameScene, gameScene);
    CC_SYNTHESIZE(cocos2d::CCSprite *, _spriteBullet, SpriteBullet);//子弹精灵
	 
	float ratio;
	//FishNet* fishNet;
	int levelBullet;
	CC_SYNTHESIZE(bool, isCaught, Caught);//子弹的触发状态
	void removeSelf();
	void shoot(int level, cocos2d::CCPoint startPosition, cocos2d::CCPoint endPosition, float angle);
	//void addCannon(cocos2d::CCObject *sender);
	//void reduceCannon(cocos2d::CCObject *sender);
	//void rotateToPoint(cocos2d::CCPoint ptTo);
};

#endif  // __Bullet_SCENE_H__