#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Maze.h"

using namespace std;
using namespace cocos2d;
class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	void createMap(vector<vector<int>> _map);
	void update(float delta) override;
	void menuResetCallBack(Ref* pSender);
	void menuAutoCallBack(Ref* pSender);

private:
	Sprite* map;
	Sprite* hero;
	Sprite* goal;
	vector<point> mazePath;
	int pathCount = 0;
};

#endif // __HELLOWORLD_SCENE_H__
