#ifndef __RollNum__
#define __RollNum__

#include "cocos2d.h"


class GameScene;

class RollNum : public cocos2d::CCSprite
{
public:
    RollNum(void);
    ~RollNum(void);
    //CREATE_FUNC(RollNum);
    static RollNum* initRollNum(cocos2d::CCSpriteBatchNode *m_pBatchNode);

    CC_SYNTHESIZE(cocos2d::CCSpriteBatchNode *, m_pBatchNode, BatchNode);

    CC_SYNTHESIZE(cocos2d::CCSprite *, _spriteRollNum, SpriteRollNum);

    void setNumber(int var);
    void updateNumber(float dt);
    int getNumber();
private:
    float ratio;
    //bool init();
    int CurRoll_h;
    int EndRoll_h;
    int m_nNumber;
    bool m_bRolling;
    bool createRollNum(cocos2d::CCSpriteBatchNode *m_pBatchNode);
    cocos2d::CCTexture2D *m_pTexture;
    
};


class RollNumGroup : public cocos2d::CCObject
{
public:
    RollNumGroup();
    virtual ~RollNumGroup();

    //static RollNumGroup *initRollGroup(GameScene *m_pGameScene, int nDigit);
    static RollNumGroup *initRollGroup(cocos2d::CCSpriteBatchNode *m_pBatchNode, int nDigit);

    //CC_SYNTHESIZE(cocos2d::CCSpriteBatchNode *, m_pBatchNode, BatchNode);

    CC_SYNTHESIZE(GameScene *, m_pGameScene, GameScene);

    CC_SYNTHESIZE(cocos2d::CCArray *, m_pRollNumArray, RollNumArray);

    void setValue(int nValue);
    int getValue();
    void test();
    void setPosition(cocos2d::CCPoint pt);
private:
    cocos2d::CCPoint m_ptPosition;
    int m_nDigit;
    int m_nValue;
    float ratio;
    bool createRollGroup(cocos2d::CCSpriteBatchNode *m_pBatchNode, int nDigit);
};

class Coin : public cocos2d::CCSprite
{
public:
    Coin(void);
    ~Coin(void);
    //CREATE_FUNC(RollNum);
    static Coin* initCoin(cocos2d::CCSpriteBatchNode *m_pBatchNode);

    CC_SYNTHESIZE(cocos2d::CCSpriteBatchNode *, m_pBatchNode, BatchNode);

    CC_SYNTHESIZE(cocos2d::CCSprite *, _spriteCoin, SpriteCoin);

    void showCoin(cocos2d::CCPoint pt, int level);
    void runWithPath();
    int getNumber();
private:
    float ratio;
    int levelCoin;
    void removeSelf();
    bool createCoin(cocos2d::CCSpriteBatchNode *m_pBatchNode);
    cocos2d::CCTexture2D *m_pTexture;
    
};

#endif //_Roll_Num__H