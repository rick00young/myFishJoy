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

	static Fish* initFish(int level, GameScene *gameScene, cocos2d::CCSpriteBatchNode *pBatchNodeFish, cocos2d::CCArray *Fishes);
	bool createFish(int level, GameScene *gameScene, cocos2d::CCSpriteBatchNode *pBatchNodeFish, cocos2d::CCArray *Fishes);
	CC_SYNTHESIZE(cocos2d::CCParticleSystem *, m_pBubble, Bubble);
	CC_SYNTHESIZE(bool, isCaught, Caught);//��Ĳ�׽״̬
    CC_SYNTHESIZE(cocos2d::CCSprite *, _spriteFish, SpriteFish);//��ľ��� getter and setter
	void runWithPath();
	void runWithLine();
	void runFromLeftToRight();
    void showCaught();
    void changeFish(int level);
private:
	float ratio;
	int levelFish;//�������
	//cocos2d::CCSprite * _spriteFish;
	bool m_bBubble;
	
	
	void showBubble(cocos2d::CCPoint start, cocos2d::CCPoint end, float angle, float duation);
	void removeSelf();
};
#endif

