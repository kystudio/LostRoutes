#pragma once
#include "cocos2d.h"

class Fighter :public cocos2d::Sprite
{
	CC_SYNTHESIZE(int, hitPoints, HitPoints);
public:
	void setPosition(const cocos2d::Vec2& newPosition);
	static Fighter * createWithSpriteFrameName(const char * spriteFrameName);
};