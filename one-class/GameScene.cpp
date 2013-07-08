//#include "HelloWorldScene.h"
#include "GameScene.h"
using namespace cocos2d;
using namespace std;
/*
const int FishInBatchNode1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 13, 14};
const int FishInBatchNode2[] = {10, 18};
const int FishInBatchNode3[] = {16, 17};
const int FishInBatchNode4[] = {11, 12};
*/

int FishInBatchNode1[LENGTH_ARRAY] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 13, 14};
int FishInBatchNode2[LENGTH_ARRAY] = {10, 18};
int FishInBatchNode3[LENGTH_ARRAY] = {16, 17};
int FishInBatchNode4[LENGTH_ARRAY] = {11, 12};


CCScene* GameScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        GameScene *layer = GameScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////

        // 1. Add a menu item with "X" image, which is clicked to quit the program.

        // Create a "close" menu item with close icon, it's an auto release object.
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(GameScene::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);

        // Place the menu item bottom-right conner.
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu, 1);



        // Get window size and place the label upper. 
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		ratio = winSize.width / 1024;//大小比例

		this->setTouchEnabled(true);
		this->initFrames();
		this->initCannon();
		this->initBackground();
		this->initFishes();

		this->schedule(schedule_selector(GameScene::updateFish), 1.0f);//更新鱼
        bRet = true;
		scheduleUpdate();//
    } while (0);

    return bRet;
}

void::GameScene::initFrames()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("fish.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("fish2.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("fish3.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("fish4.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("cannon.plist");
}

void GameScene::initBackground()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

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

void GameScene::initCannon()
{
	CCLog("gae00000000 ");
	this->setBullets(CCArray::createWithCapacity(100));
	m_pBullets->retain();

	this->setFishNets(CCArray::createWithCapacity(100));
	m_pFishNets->retain();

	//this->setFishes(CCArray::createWithCapacity(MAX_FISH_COUNT));  
	CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage("cannon.png");
	CCSize size = CCDirector::sharedDirector()->getWinSize();


	cannon = Cannon::initCannon();
	cannon->setPosition(ccp(size.width/2 + 10, 20));
	//CCMoveTo *moveto = CCMoveTo::create(1.0f, ccp(size.width, size.height));
	//cannon->runAction(moveto);

	this->addChild(cannon,101,220);

	
}

void GameScene::initFishes(){

	this->setFishes(CCArray::createWithCapacity(MAX_FISH_COUNT));    
	m_pFishes->retain();

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

	m_pFishes->removeAllObjects();

	this->addFish();
}
void GameScene::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	//CCLog("touch begin");
	
 	CCSetIterator it = pTouches->begin();
	for(; it != pTouches->end(); it++)
    {
		CCTouch *pTouch = (CCTouch*)*it;
		CCPoint pt = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
		//CCLog("pt.y %f ** cannon.y %f", pt.y, cannon->getCannonPosition().y);
		if(pt.y < cannon->getPosition().y + 25){
			return;
		}
		//CCLog("pt.y %f ** cannon.y %f", pt.y, cannon->getPosition().y);
        cannon->rotateToPoint(pt);
		isControl = true;
        break;
		


	}

}

void GameScene::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{	
	//CCLog("touch end");
	//cannon->shoot();
	int level = cannon->getLevelCannon();
	bullet = Bullet::initBullet(level,this, m_pBatchNode2);
	
	//CCLog("bullets count is %d", this->getBullets()->count());
	
    CCSetIterator it = pTouches->begin();
    while(it != pTouches->end() && isControl)
    {
        CCTouch *pTouch = (CCTouch *)*it;
        CCPoint pt = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
        
		if(bullet){
			bullet->shoot(cannon->getPosition(), pt, cannon->getAngle());
		}
        break;
    }

	isControl = false;
	
}

void GameScene::showFishNet(CCPoint point)
{
	//CCLog("show fish net");
	int level = cannon->getLevelCannon();
	fishNet = FishNet::initFishNet(level, this, m_pBatchNode3);
	fishNet->showFishNet(point);
}

void GameScene::updateFish(float dt)
{
	//CCLog("update fish");
	if(m_pFishes->count() < MAX_FISH_COUNT)
    {
        int n = MAX_FISH_COUNT - m_pFishes->count();
        int nAdd = rand() % n + 1;
        for(int i = 0; i < nAdd; i++)
        {
            //this->addFish();
			//CCLog("add fish");
			//fish = Fish::initFish(2, this, m_pBatchNode1);
			this->addFish();
        }
    }
}

void GameScene::addFish()
{
	 int type = rand() % 18 + 1;
	 int* ip = find(FishInBatchNode1, FishInBatchNode1 + LENGTH_ARRAY, type);
	 
	 if(ip != FishInBatchNode1 + LENGTH_ARRAY){
		//CCLog("find in FishInBatchNode1 *ip is %d", *ip);
		Fish::initFish(type, this, m_pBatchNode1);
		return;
	 }

	 ip = find(FishInBatchNode2, FishInBatchNode2 + LENGTH_ARRAY, type);
	 if(ip != FishInBatchNode2 + LENGTH_ARRAY){
		//CCLog("find in FishInBatchNode2 *ip is %d", *ip);
		Fish::initFish(type, this, m_pBatchNode2);
		return;
	 }
	 
	 ip = find(FishInBatchNode3, FishInBatchNode3 + LENGTH_ARRAY, type);
	 if(ip != FishInBatchNode3 + LENGTH_ARRAY){
		//CCLog("find in FishInBatchNode3 *ip is %d", *ip);
		Fish::initFish(type, this, m_pBatchNode3);
		return;
	 }

	 ip = find(FishInBatchNode4, FishInBatchNode4 + LENGTH_ARRAY, type);
	 if(ip != FishInBatchNode4 + LENGTH_ARRAY){
		//CCLog("find in FishInBatchNode4 *ip is %d", *ip);
		Fish::initFish(type, this, m_pBatchNode4);
		return;
	 }

}

void GameScene::update(float time)
{
	//CCLog("update");
	CCObject *FishObj = NULL;
	CCObject *BulletObj = NULL;
	CCARRAY_FOREACH(m_pBullets, BulletObj){
		//CCLog("Bullet");
		Bullet *pBullet = (Bullet *)BulletObj;

		if(!pBullet && pBullet->getCaught()){
			continue;
		}

		bool caught = false;
		CCARRAY_FOREACH(m_pFishes, FishObj){
			//CCLog("Fish");
			Fish *pFish = (Fish *)FishObj;
            if(!pFish && pFish->getCaught()){
                continue;
            }

            if(pFish && pBullet && pFish->getSpriteFish()->boundingBox().containsPoint(pBullet->getSpriteBullet()->getPosition())){
                CCLog("hit the fish");
                pFish->setCaught(true);
                pBullet->setCaught(true);
                pFish->showCaught();
            }
                
		}
	}
}

void GameScene::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

