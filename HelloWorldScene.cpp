#include "HelloWorldScene.h"
#include "GameBlock.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}
	srand(time(NULL));
	visibleSize = Director::getInstance()->getVisibleSize();
	gamelayer = Node::create();
	addChild(gamelayer);
	timelabel = Label::create();
	timelabel->setColor(Color3B::RED);
	timelabel->setSystemFontSize(38);
	timelabel->setPosition(visibleSize.width/2, visibleSize.height-50);
	timelabel->setString("0.000\"");
	addChild(timelabel);

	StartGame();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch *t, Event *e){
		//log("xuran is winner");
		GameBlock *b;
		auto bs = GameBlock::getBlocks();
		for(auto it = bs->begin(); it != bs->end(); it++)
		{
			b = *it;
			if(b->getlineindex() == 1 && b->getBoundingBox().containsPoint(t->getLocation()))
			{
				if(b->getColor() == Color3B::BLACK)
				{
					if(!timerrunning)
					{
						this->starttime();
					}
					b->setColor(Color3B::GRAY);
					this->movedown();
				}
				else if (b->getColor() == Color3B::GREEN)
				{
					this->movedown();
					this->endtime();
				}
				else
				{
					MessageBox("游戏失败", "GameOver");
				}
				break;
			}
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this); //对当前场景进行监听
	return true;
}

void HelloWorld::movedown()
{
	if(linecount < 50)
	{
		AddNormal(4); //在屏幕最上面添加一行，因为设置了屏幕内一次最多存在四行的块
	}
	else if(!showend)
	{
		showend = true;
		AddEndLine();
	}
	auto bs = GameBlock::getBlocks();
	for(auto it = bs->begin(); it != bs->end(); it++)
	{
		(*it)->moveon();	
	}
}
void HelloWorld::StartGame()
{
	linecount = 0;           //开始时要初始化行数
	timerrunning = false;    //计时器默认不运行
	showend = false;		//只添加一次结束快
	AddStartLine();
	AddNormal(1);
	AddNormal(2);
	AddNormal(3);
}

void HelloWorld::AddStartLine()
{
	auto b = GameBlock::CreateWithArgs(Color3B::YELLOW, Size(visibleSize.width, visibleSize.height/4), "Start", 20, Color3B::BLACK);
	gamelayer->addChild(b);
	b->setlineindex(0);
}

void HelloWorld::AddEndLine()
{
	auto b = GameBlock::CreateWithArgs(Color3B::GREEN, visibleSize, "GOD LIKE", 32, Color3B::BLACK);
	gamelayer->addChild(b);
	b->setlineindex(4);
}

void HelloWorld::AddNormal(int lineindex)
{
	int blackindex = rand()%4;
	GameBlock *b;

	for(int i = 0; i < 4; i++)
	{
		auto b = GameBlock::CreateWithArgs(blackindex == i?Color3B::BLACK:Color3B::WHITE, Size(visibleSize.width/4-1, visibleSize.height/4-1), "", 20, Color3B::BLACK);
		gamelayer->addChild(b);
		b->setPosition(i*visibleSize.width/4, lineindex*visibleSize.height/4);
		b->setlineindex(lineindex);
	}
	linecount++;
}

void HelloWorld::update(float dt)
{
	long offet = clock()-gametime;
	timelabel->setString(StringUtils::format("%g", ((double)offet)/1000));
}
void HelloWorld::starttime()
{
	if(!timerrunning)
	{
		gametime = clock();
		scheduleUpdate();   //开始执行计时器
		timerrunning = true;
	}
}
void HelloWorld::endtime()
{
	if(timerrunning)
	{
		unscheduleUpdate();  //停止执行计时器
		timerrunning = false;
	}

}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
