#pragma once
#include "cocos2d.h"

#include "Fighter.h"

class Bullet : public cocos2d::Sprite
{
	CC_SYNTHESIZE(cocos2d::Vec2, velocity, Velocity); // 速度
public:
	void shootBulletFromFighter(Fighter * fighter); // 发射炮弹
	virtual void update(float dt);
	static Bullet * createWithSpriteFrameName(const char * spriteFrameName);
};