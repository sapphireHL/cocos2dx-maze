#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto closemenu = Menu::create(closeItem, NULL);
	closemenu->setPosition(Vec2::ZERO);
    this->addChild(closemenu, 1);

	//reset
	auto resetLabel = Label::createWithTTF("reset", "fonts/Marker Felt.ttf", 60);
	auto resetItem = MenuItemLabel::create(resetLabel, CC_CALLBACK_1(HelloWorld::menuResetCallBack, this));
	//auto find
	auto autoLabel = Label::createWithTTF("auto", "fonts/Marker Felt.ttf", 60);
	auto autoItem = MenuItemLabel::create(autoLabel, CC_CALLBACK_1(HelloWorld::menuAutoCallBack, this));
	//create menu
	auto menu = Menu::create(autoItem, resetItem, nullptr);
	menu->setPosition(800, visibleSize.height / 2);
	menu->alignItemsVerticallyWithPadding(20);
	this->addChild(menu);

    /////////////////////////////
    // 3. add your codes below...
	Maze maze(10, 10);
	maze.generateMaze();
	auto mazeMapData = maze.getMazeMap();
	createMap(mazeMapData);
	
	maze.solveMaze();
	mazePath = maze.getPath();
    
	//this->scheduleUpdate();
	//this->schedule(schedule_selector(HelloWorld::update), 0.1f);
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}

void HelloWorld::createMap(vector<vector<int>> _map)
{
	map = Sprite::create("none.png");
	map->setAnchorPoint(Vec2(0.5, 0.5));
	auto size = map->getContentSize();
	for (int i = 0; i < (int)_map.size(); i++) {
		for (int j = 0; j < (int)_map[0].size(); j++) {
			Sprite* wall;
			if (_map[i][j])
				wall = Sprite::create("none.png");
			else
				wall = Sprite::create("wall.png");
			wall->setAnchorPoint(Vec2(0.5, 0.5));
			wall->setPosition(size.width*j, size.height*i);
			map->addChild(wall);
		}
	}
	//add goal
	goal = Sprite::create("goal.png");
	goal->setPosition((_map[0].size() - 2)*size.width, (_map.size() - 2)*size.height);
	map->addChild(goal);
	//add hero
	hero = Sprite::create("hero.png");
	hero->setPosition(1 * size.width, 1 * size.height);
	map->addChild(hero);
	//auto winSize = Director::getInstance()->getVisibleSize();
	map->setPosition(100, 150);
	this->addChild(map);
}

void HelloWorld::update(float delta)
{
	if (++pathCount >= (int)mazePath.size())
		return;
	auto size = hero->getContentSize();
	auto newPos = Vec2(mazePath[pathCount].y * size.width, mazePath[pathCount].x * size.height);
	auto moveto = MoveTo::create(delta, newPos);
	hero->runAction(moveto);
}

void HelloWorld::menuResetCallBack(Ref * pSender)
{
	auto newScene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, newScene));
}

void HelloWorld::menuAutoCallBack(Ref * pSender)
{
	this->schedule(schedule_selector(HelloWorld::update), 0.1f);
}
