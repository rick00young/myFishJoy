#ifndef __Fish_H__
#define __Fish_H__

#include "cocos2d.h"

class GameScene;
class Fish : public cocos2d::CCSprite
{
public:
	Fish(void);
	~Fish(void);
	CC_SYNTHESIZE(GameScene *, m_pgameScene, gameScene);

	static Fish* initFish(int level, GameScene *gameScene, cocos2d::CCSpriteBatchNode *pBatchNodeFish);
	bool createFish(int level, GameScene *gameScene, cocos2d::CCSpriteBatchNode *pBatchNodeFish);
	CC_SYNTHESIZE(cocos2d::CCParticleSystem *, m_pBubble, Bubble);
	CC_SYNTHESIZE(bool, isCaught, Caught);//鱼的捕捉状态

	void runWithPath();
	void runWithLine();
	void runFromLeftToRight(cocos2d::CCSprite *sprite);
private:
	float ratio;
	int levelFish;//鱼的种类
	cocos2d::CCSprite * _spriteFish;
	bool m_bBubble;
	void showCaught();
	
	void showBubble(cocos2d::CCPoint start, cocos2d::CCPoint end, float angle, float duation);
	void removeSelf();
};

#endif

