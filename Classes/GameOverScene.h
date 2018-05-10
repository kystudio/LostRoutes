#pragma once
#include "cocos2d.h"
#include "MyUtility.h"

#include "SystemHeader.h"

class GameOverLayer : public cocos2d::Layer 
{
public:
	GameOverLayer(int score);

	virtual bool init();
	virtual void onExit();

	static GameOverLayer * createWithScore(int score);
private:
	int _score; // 当前玩家获得的分数
	UserDefault * _defaults;
};