#pragma once
#include "cocos2d.h"

#include "Fighter.h"

class Bullet : public cocos2d::Sprite
{
	CC_SYNTHESIZE(cocos2d::Vec2, velocity, Velocity); // ÀŸ∂»
public:
	void shootBulletFromFighter(Fighter * fighter); // ∑¢…‰≈⁄µØ
	virtual void update(float dt);
	static Bullet * createWithSpriteFrameName(const char * spriteFrameName);
};