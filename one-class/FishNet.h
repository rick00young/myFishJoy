#ifndef __FishNet_H__
#define __FishNet_H__

#include "cocos2d.h"

class GameScene;
class FishNet : public cocos2d::CCSprite
{
public:
	FishNet(void);
	~FishNet(void);
	static FishNet* initFishNet(int level, GameScene *gameScene, cocos2d::CCSpriteBatchNode *m_pBatchNode3);
	bool createFishNet(int level, GameScene *gameScene, cocos2d::CCSpriteBatchNode *m_pBatchNode3);
	CC_SYNTHESIZE(GameScene *, m_pgameScene, gameScene);

	cocos2d::CCSprite* _netSprite;
	void showFishNet(cocos2d::CCPoint point);
	void removeSelf();
	int levelNet;

};
#endif

