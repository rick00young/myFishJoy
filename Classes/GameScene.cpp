//#include "HelloWorldScene.h"
#include "GameScene.h"
using namespace cocos2d;
using namespace std;


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
		this->initBackground();
		this->initFishes();
        this->initCannon();
        this->initRollNum();

		this->schedule(schedule_selector(GameScene::updateFish), 1.0f);//更新鱼
        bRet = true;
		scheduleUpdate();//

       CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("audio/scg.wav",true);
       CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("audio/CoinFly.wav");
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
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("8goldItem.plist");
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
	CCLog("cannon ");
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

    for(int i = 0; i < 15; i++){
        bullet = Bullet::initBullet(1,this, m_pBatchNode2);
        CCLog("create bullet");
    }

    for(int i = 0; i < 15; i++){
        fishNet = FishNet::initFishNet(1, this, m_pBatchNode3);
        CCLog("create fishNet");
    }

    CCLog("the ccarray bullet count is %d", this->getBullets()->count());
    CCLog("the ccarray fishnet count is %d", this->getFishNets()->count());
}

void GameScene::initRollNum()
{
    CCTexture2D *pTex = CCTextureCache::sharedTextureCache()->addImage("number.png");
   
    //this->setBatchNode1(CCSpriteBatchNode::createWithTexture(texture));
    this->setBatchNode5(CCSpriteBatchNode::createWithTexture(pTex));
    this->addChild(m_pBatchNode5, 100);
    score = 3000;//默认是3000个金币
    rollNumGroup = RollNumGroup::initRollGroup(m_pBatchNode5, 6);
    rollNumGroup->setPosition(ccp(170, 10));
    rollNumGroup->setValue(score);
    //rollNumGroup->setValue(7);

    //coins
    CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("8goldItem.png");
    this->setBatchNode6(CCSpriteBatchNode::createWithTexture(texture));
    this->addChild(m_pBatchNode6);

    this->setCoins(CCArray::createWithCapacity(20));
    m_pCoins->retain();
    for(int i = 0;i < 20; i++){
        Coin* coin = Coin::initCoin(m_pBatchNode6);
        m_pCoins->addObject(coin);
    }

    //CCLog("Coins count is %d", m_pCoins->count());
}

void GameScene::initFishes(){

    this->setFishes(CCArray::createWithCapacity(MAX_FISH_COUNT));    
    m_pFishes->retain();

    this->setFishes2(CCArray::createWithCapacity(MAX_FISH_COUNT));    
	m_pFishes2->retain();

    this->setFishes3(CCArray::createWithCapacity(MAX_FISH_COUNT));    
	m_pFishes3->retain();

    this->setFishes4(CCArray::createWithCapacity(MAX_FISH_COUNT));    
	m_pFishes4->retain();

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
    FishCount = 0;
    for(int i = 0; i < 60; i++){
        if(i < 20){
            Fish::initFish(1, this, m_pBatchNode1, m_pFishes);
        }

        if(i >= 20 && i < 40){
            Fish::initFish(10, this, m_pBatchNode2, m_pFishes2);
        }

        if(i >= 40 && i < 50){
            Fish::initFish(16, this, m_pBatchNode3, m_pFishes3);
        }

        if(i >= 50){
            Fish::initFish(11, this, m_pBatchNode4, m_pFishes4);
        }
        
    }

    CCLog("the fish count is %d", this->getFishes2()->count());
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
    rollNumGroup->setValue(rollNumGroup->getValue() - 2);
	int level = cannon->getLevelCannon();
	
    CCSetIterator it = pTouches->begin();
    CCPoint temp_pt;
    while(it != pTouches->end() && isControl)
    {
        CCTouch *pTouch = (CCTouch *)*it;
        CCPoint pt = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
        temp_pt = pt;
        for(int j = 0;j < (int)(this->getBullets()->count()); j++){
             Bullet *_bullet = (Bullet *)this->getBullets()->objectAtIndex(j);
            //CCLog("shoot");
             if(!(_bullet->getSpriteBullet()->isVisible())){
                _bullet->getSpriteBullet()->setVisible(true);
                _bullet->shoot(level,cannon->getPosition(), pt, cannon->getAngle()); 
                //CCLog("shoot");
                break;
             }
                  
        }



        break;
    }

	isControl = false;
	
}

void GameScene::showFishNet(CCPoint point)
{
	//CCLog("show fish net");
	int level = cannon->getLevelCannon();
	//fishNet = FishNet::initFishNet(level, this, m_pBatchNode3);
	//fishNet->showFishNet(point);

    for(int j = 0;j < (int)(this->getFishNets()->count()); j++){
            FishNet *_fishNet = (FishNet *)this->getFishNets()->objectAtIndex(j);
             //CCLog("net");
            if(!(_fishNet->getSpriteFishNet()->isVisible())){
                _fishNet->getSpriteFishNet()->setVisible(true);
                _fishNet->showFishNet(level, point);
                //CCLog("shoot");
                break;
             }
                  
    }
}

void GameScene::updateFish(float dt)
{
	//CCLog("update fish");
	if(FishCount < MAX_FISH_COUNT)
    {
        int n = MAX_FISH_COUNT - m_pFishes->count();
        int nAdd = rand() % n + 1;
        for(int i = 0; i < nAdd; i++)
        {
			//CCLog("add fish");
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
         for(int i = 0; i < (int)(this->getFishes()->count()); i++){
             Fish* _fish = (Fish *)this->getFishes()->objectAtIndex(i);
             if(!(_fish->getSpriteFish()->isVisible())){
                 //FishCount++;
                 //if(FishCount > 5) return;
                 _fish->getSpriteFish()->setVisible(true);
                 _fish->changeFish(type);
                 //CCLog("_fish->getSpriteFish()->isVisible() %d",FishCount);
                // FishCount--;
                 break;
             }
         }
		return;
	 }
     /*
	 ip = find(FishInBatchNode2, FishInBatchNode2 + LENGTH_ARRAY, type);
	 if(ip != FishInBatchNode2 + LENGTH_ARRAY){
         for(int i = 0; i < (int)(this->getFishes2()->count()); i++){
             Fish* _fish = (Fish *)this->getFishes2()->objectAtIndex(i);
             if(!(_fish->getSpriteFish()->isVisible())){
                 FishCount++;
                 if(FishCount > 5) return;
                 _fish->getSpriteFish()->setVisible(true);
                 _fish->changeFish(type);
                 CCLog("_fish->getSpriteFish()->isVisible() %d",FishCount);
                 break;
             }
         }
		return;
	 }
	 
     /*
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
     */

}

void GameScene::update(float time)
{
	//遍历子弹和鱼
	CCObject *FishObj = NULL;
	CCObject *BulletObj = NULL;
	CCARRAY_FOREACH(m_pBullets, BulletObj){
		
		Bullet *pBullet = (Bullet *)BulletObj;
        if(pBullet->getSpriteBullet()->isVisible()){
            
            CCPoint bulletPos = pBullet->getSpriteBullet()->getPosition();
		    CCARRAY_FOREACH(m_pFishes, FishObj){
			    
			    Fish *pFish = (Fish *)FishObj;
                if(pFish && pFish->getSpriteFish()->isVisible() && !(pFish->getCaught())){
                    
                    if(pFish->getSpriteFish()->boundingBox().containsPoint(bulletPos)){
                        
                        pBullet->getSpriteBullet()->setVisible(false);
                        this->showFishNet(bulletPos);
                    }
                }

                
		    }

        }
        
	}
    //遍历鱼网和鱼
    CCObject *FishNetObj = NULL;
	
    CCARRAY_FOREACH(m_pFishNets, FishNetObj){

        FishNet* _FishNet = (FishNet *)FishNetObj;
        CCRect rect = _FishNet->getSpriteFishNet()->boundingBox();

        if(_FishNet->getSpriteFishNet()->isVisible()){
  		    CCARRAY_FOREACH(m_pFishes, FishObj){
			    
			    Fish *pFish = (Fish *)FishObj;
                if(pFish && pFish->getSpriteFish()->isVisible()){
                    
                    if(!(pFish->getCaught()) && rect.intersectsRect(pFish->getSpriteFish()->boundingBox())){
                        
                        pFish->showCaught();
                        //pFish->set
                        this->showCoin(pFish->getSpriteFish()->getPosition());
                        //CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("audio/CoinFly.ogg");
                        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("audio/CoinFly.wav");
                    }
                }

                
		    }          
        }
    }

}

void GameScene::showCoin(CCPoint pt)
{
    //test
     for(int m = 0; m < (int)(m_pCoins->count()); m++){
            //CCLog("show coin_______________________");
            Coin* _coin = (Coin *)this->getCoins()->objectAtIndex(m);
            if(!(_coin->getSpriteCoin()->isVisible())){
                _coin->showCoin(pt, 1);
                //CCLog("show coin");
                break;
            }
     }
}

void GameScene::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

