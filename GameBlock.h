#pragma once
#include <iostream>
#include <cocos2d.h>
USING_NS_CC; 
class GameBlock:public Sprite
{
public:
	static Vector<GameBlock*>* getBlocks();
	static GameBlock* CreateWithArgs(Color3B color, Size size, std::string label, float fontsize, Color3B textcolor);
	virtual bool initWithArgs(Color3B color, Size size, std::string label, float fontsize, Color3B textcolor);
	void removeblock();
	int getlineindex();
	void setlineindex(int);
	void moveon();
private:
	static Vector<GameBlock*> *blocks;
	int lineindex;
};



