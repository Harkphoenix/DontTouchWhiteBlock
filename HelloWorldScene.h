#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "GameBlock.h"
class HelloWorld : public cocos2d::Layer
{
private:
	 Size visibleSize;
	 int linecount;         //定义整个游戏的总行数
	 bool showend;
	 Label *timelabel;
	 Node *gamelayer;
	 long gametime;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	void AddStartLine();
    void AddEndLine();
	void AddNormal(int);
	void StartGame();
	void movedown();
	virtual void update(float dt);
	void starttime();
	void endtime();
	bool timerrunning;
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
