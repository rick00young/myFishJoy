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

	void runWithPath();
	void runWithLine();
private:
	int levelFish;
	cocos2d::CCSprite * _spriteFish;
	void removeSelf();
};

#endif

