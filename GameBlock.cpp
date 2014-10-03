#include "GameBlock.h"

Vector<GameBlock*> *GameBlock::blocks = new Vector<GameBlock*>();

GameBlock* GameBlock::CreateWithArgs(Color3B color, Size size, std::string label, float fontsize, Color3B textcolor)
{
	auto b = new GameBlock();
	b->initWithArgs(color, size, label, fontsize, textcolor);
	b->autorelease();
	blocks->pushBack(b);
	return b;
	
}

Vector<GameBlock*>* GameBlock::getBlocks()
{
	return GameBlock::blocks;
}


void GameBlock::removeblock()
{
	log("remove block, color is %d, %d, %d",getColor().r,getColor().g, getColor().b);
	removeFromParent();
	blocks->eraseObject(this);   //ɾ���������ض��Ķ���
}

bool GameBlock::initWithArgs(Color3B color, Size size, std::string label, float fontsize, Color3B textcolor)
{

	Sprite::init();
	setContentSize(size);
	setAnchorPoint(Point::ZERO);
	setTextureRect(Rect(0,0,size.width, size.height));
	setColor(color);
	lineindex = 0;
	auto l = Label::create();
	l->setString(label);
	l->setSystemFontSize(fontsize);
	l->setColor(textcolor);
	addChild(l);
	l->setPosition(size.width/2, size.height/2);
	return true;
}

void GameBlock::setlineindex(int v)
{
	this->lineindex = v;
}

int GameBlock::getlineindex()
{
	return this->lineindex;
}

void GameBlock::moveon()
{
	Size visable = Director::getInstance()->getVisibleSize();
	this->lineindex--; //���������ƶ����У��ƶ�֮�����ڵ��л��ȥ1
	runAction(Sequence::create(MoveTo::create(0.1f,Point(getPositionX(), lineindex*visable.height/4)),CallFunc::create([this]()
	{
		if(lineindex < 0)
		{
			this->removeblock();
		}
	}
	),NULL));  //ִ��һ���ƶ��Ķ�������һ�����ƶ�����Ӧ��λ���ϣ����0.1
}