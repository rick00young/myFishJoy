#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "Fish.h"
#include "Cannon.h"
//#include "Bullet.h"
//#include "RollNum.h"

using namespace cocos2d;
using namespace CocosDenshion;

const int FishInBatchNode1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 13, 14};
const int FishInBatchNode2[] = {10, 18};
const int FishInBatchNode3[] = {16,17};//{16, 17};
const int FishInBatchNode4[] = {11, 12};

CCScene* GameLayer::scene()
{
    CCScene *scene = CCScene::create();
    GameLayer *layer = GameLayer::create();
    scene->addChild(layer);
    return scene;
}

GameLayer::GameLayer():m_pFishes(NULL)//, m_pBullets(NULL), m_pRollNumGroup(NULL), m_pCannon(NULL), m_nScore(0)
{
    
}

GameLayer::~GameLayer()
{
	/*
    CC_SAFE_RELEASE(m_pFishes);
    CC_SAFE_RELEASE(m_pBullets);
    CC_SAFE_RELEASE(m_pCannon);
    CC_SAFE_RELEASE(m_pRollNumGroup);
	*/
}

bool GameLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
	levelCannon = 1;//大炮的等级
    //srand(time(NULL));
    this->setTouchEnabled(true);
    this->initFrames();
    this->initBackground();
    this->initFishes();
    this->initCannon();
    //this->schedule(schedule_selector(GameLayer::updateGame), 0.05f);
    this->schedule(schedule_selector(GameLayer::updateFish), 1.0f);
    //this->setBullets(CCArray::create());
	////
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(GameLayer::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
	//
    return true;
}

void::GameLayer::initFrames()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("fish.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("fish2.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("fish3.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("fish4.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("cannon.plist");
}

void GameLayer::initBackground()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	ratio = winSize.width / 1024;//大小比例

    CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("bj01.jpg");
    CCSprite *pBackground = CCSprite::createWithTexture(texture);
	pBackground->setScale(ratio);
    pBackground->setAnchorPoint(ccp(0.5f, 0.5f));
    
    pBackground->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(pBackground);
 
    texture = CCTextureCache::sharedTextureCache()->addImage("ui_box_01.png");
    CCSprite *pTopBar = CCSprite::createWithTexture(texture);
	pTopBar->setScale(ratio);
    //pTopBar->setPosition(ccp(500, 700));
	//pTopBar->setAnchorPoint(CCPointZero);
	pTopBar->setPosition(ccp((winSize.width/2), (winSize.height - pTopBar->getContentSize().height/2*ratio)));
    this->addChild(pTopBar, 100);
    
    texture = CCTextureCache::sharedTextureCache()->addImage("ui_box_02.png");
    CCSprite *pBottomBar = CCSprite::createWithTexture(texture);
	pBottomBar->setScale(ratio);
    //pBottomBar->setPosition(ccp(440, 90));
	pBottomBar->setPosition(ccp(pBottomBar->getContentSize().width/2*ratio, pBottomBar->getContentSize().height/2*ratio));
    this->addChild(pBottomBar, 100);
    
    //this->setRollNumGroup(RollNumGroup::createWithGameLayer(this, 6));
    //m_pRollNumGroup->setPosition(ccp(353, 21));
}

void GameLayer::initFishes()
{
	
    //CCArray *temp = CCArray::createWithCapacity(MAX_FISH_COUNT);
	//this->setFishes(temp);
	this->setFishes(CCArray::createWithCapacity(MAX_FISH_COUNT));    
    
    CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("fish.png");
    this->setBatchNode1(CCSpriteBatchNode::createWithTexture(texture));
    this->addChild(m_pBatchNode1);
	
    
    texture = CCTextureCache::sharedTextureCache()->addImage("fish2.png");
    this->setBatchNode2(CCSpriteBatchNode::createWithTexture(texture));
    this->addChild(m_pBatchNode2);
    
    texture = CCTextureCache::sharedTextureCache()->addImage("fish3.png");
    this->setBatchNode3(CCSpriteBatchNode::createWithTexture(texture));
    this->addChild(m_pBatchNode3);
    
    texture = CCTextureCache::sharedTextureCache()->addImage("fish4.png");
    this->setBatchNode4(CCSpriteBatchNode::createWithTexture(texture));
    this->addChild(m_pBatchNode4);
	
	
    for(int i = 0; i < GET_ARRAY_LEN(FishInBatchNode1); i++)
    {
        fishInBatchNode1.insert(FishInBatchNode1[i]);
    }
    for(int i = 0; i < GET_ARRAY_LEN(FishInBatchNode2); i++)
    {
        fishInBatchNode2.insert(FishInBatchNode2[i]);
    }
    for(int i = 0; i < GET_ARRAY_LEN(FishInBatchNode3); i++)
    {
        fishInBatchNode3.insert(FishInBatchNode3[i]);
    }
    for(int i = 0; i < GET_ARRAY_LEN(FishInBatchNode4); i++)
    {
        fishInBatchNode4.insert(FishInBatchNode4[i]);
    }
    
    m_pFishes->removeAllObjects();
	m_pFishes->retain();
	//CCLog("test000000 %d",m_pFishes->count());
	//CCLog("test000000 %d",m_pFishes->count());
}

void GameLayer::initCannon()
{
    CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage("cannon.png");
	/*
    CCSpriteBatchNode *pBatchNode = CCSpriteBatchNode::createWithTexture(pTexture);
    this->addChild(pBatchNode, 101);
    this->setCannon(Cannon::createWithCannonType(7, this, pBatchNode));
    m_pCannon->setRotation(0.0f);
	*/
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	cannon = new Cannon(ratio);
	this->addChild(cannon,101,220);

	CCMenuItemImage *addLevel = CCMenuItemImage::create("addA.png", "addB.png", this, menu_selector(GameLayer::addCannon));
	
	addLevel->setPosition(ccp(size.width/2 + 35, 13));


	CCMenuItemImage *reduceLevel = CCMenuItemImage::create("reduceA.png", "reduceB.png", this, menu_selector(GameLayer::reduceCannon));
	//addLevel->setPosition(ccp(30, -size.height/2 + 20));
	reduceLevel->setPosition(ccp(size.width/2 - 20, 13));
	//CCLog("%f ** %f", cannon->getCannonPosition().x,cannon->getCannonPosition().y);
	//addLevel->setPosition(ccp(cannon->getCannonPosition().x + 20,cannon->getCannonPosition().y));
	CCMenu *menuAdd = CCMenu::create(addLevel,reduceLevel, NULL);
	//menuAdd->setPosition(ccp(size.width/2 + 20 + 8,20));
	menuAdd->setPosition(CCPointZero);
	this->addChild(menuAdd, 102);

}

void GameLayer::addFish()
{
    while(1)
    {
        int type = rand() % 18 + 1;
        std::set<int>::iterator it = fishInBatchNode1.find(type);
		//CCLog("it is %d",it);
        if(it != fishInBatchNode1.end())
        {
            Fish::createWithFishType(type, this, m_pBatchNode1, ratio);
            return;
        }
     
        it = fishInBatchNode2.find(type);
        if(it != fishInBatchNode2.end())
        {
            Fish::createWithFishType(type, this, m_pBatchNode2, ratio);
            return;
        }
        
        it = fishInBatchNode3.find(type);
        if(it != fishInBatchNode3.end())
        {
            Fish::createWithFishType(type, this, m_pBatchNode3, ratio);
            return;
        }
        
        it = fishInBatchNode4.find(type);
        if(it != fishInBatchNode4.end())
        {
            Fish::createWithFishType(type, this, m_pBatchNode4, ratio);
            return;
        }
    }
}

void GameLayer::updateFish(float dt)
{	
    if(m_pFishes->count() < MAX_FISH_COUNT)
    {
        int n = MAX_FISH_COUNT - m_pFishes->count();
        int nAdd = rand() % n + 1;
        for(int i = 0; i < nAdd; i++)
        {
            this->addFish();
			//CCLog("test000000 %d",nAdd);
        }
    }

	//CCLog("test000000 %d",m_pFishes->count());
}

void GameLayer::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	
 	CCSetIterator it = pTouches->begin();
	for(; it != pTouches->end(); it++)
    {
		CCTouch *pTouch = (CCTouch*)*it;
		CCPoint pt = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
		//CCLog("pt.y %f ** cannon.y %f", pt.y, cannon->getCannonPosition().y);
		if(pt.y < cannon->getCannonPosition().y + 50){
			return;
		}
		//CCLog("pt.y %f ** cannon.y %f", pt.y, cannon->getCannonPosition().y);
        cannon->rotateToPoint(pt);
        break;



	}
	CCLog("%f ** %f", cannon->getCannonPosition().x,cannon->getCannonPosition().y);
	/*
	CCTouch* touch = (CCTouch*)( pTouches->anyObject() );
	CCPoint location = touch->getLocation();
	location = CCDirector::sharedDirector()->convertToGL(location);

	CCPoint cannonPos = cannon->getPosition();

	//float angle = atan2f(location.y - cannonPos.y, location.x - cannonPos.x);
	float angle = (location.y - cannonPos.y)/( location.x - cannonPos.x);
    //float rotation = angle * 180.0f / M_PI;
	float rotation = atanf(angle) / M_PI * 180.0f;

	cannon->setRotation(rotation);

	CCLog("%f****%f******%f", location.x, location.y, angle);
	*/
}

void GameLayer::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{	/*
    CCSetIterator it = pTouches->begin();
    while(it != pTouches->end())
    {
        //CCTouch *pTouch = (CCTouch *)*it;
        //CCPoint pt = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
        m_pCannon->fire();
        break;
    }
	*/
}

/*
CCRect shrinkRect(CCRect rc, float xr, float yr)
{
    float w = rc.size.width * xr;
    float h = rc.size.height * yr;
    CCPoint pt = ccp(rc.origin.x + rc.size.width * (1.0f - xr) / 2, 
                     rc.origin.y + rc.size.height * (1.0f - yr) / 2);
    return CCRectMake(pt.x, pt.y, w, h);   
}

void GameLayer::updateGame(CCTime dt)
{
    CCObject *pFishObj = NULL;
    CCObject *pBulletObj = NULL;
    CCARRAY_FOREACH(m_pBullets, pBulletObj)
    {
        Bullet *pBullet = (Bullet *)pBulletObj;
        if(pBullet->getCaught())
            continue;
        bool caught = false;
        CCARRAY_FOREACH(m_pFishes, pFishObj)
        {
            Fish *pFish = (Fish *)pFishObj;
            if(pFish->getCaught())
                continue;
            
            CCRect hittestRect = shrinkRect(pFish->getSprite()->boundingBox(), 1.0f, 0.5f);
            
            if(hittestRect.containsPoint(pBullet->getSpriteBullet()->getPosition()))
            {
                caught = true;
                pFish->showCaught();
                m_nScore += 125;
                m_pRollNumGroup->setValue(m_nScore);
            }
        }
        
        if(caught)
        {
            pBullet->showNet();
        }
    }
}
*/

void GameLayer::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();
}

void GameLayer::addCannon(CCObject* pSender)
{
	CCLog("addCannon");
	
	levelCannon++;
	if(levelCannon > 7){
		levelCannon = 1;
	}

	cannon->addLevel(levelCannon);
}

void GameLayer::reduceCannon(CCObject* pSender)
{
	CCLog("reduceCannon");

	levelCannon--;
	if(levelCannon < 1){
		levelCannon = 7;
	}
	cannon->reduceLevel(levelCannon);
}