#include "Fighter.h"

USING_NS_CC;

Fighter * Fighter::createWithSpriteFrameName(const char * spriteFrameName)
{
	Fighter * fighter = new Fighter();

	if (fighter && fighter->initWithSpriteFrameName(spriteFrameName))
	{
		fighter->autorelease();

		ParticleSystem * ps = ParticleSystemQuad::create("particle/fire.plist");

		// 在飞机下面
		ps->setPosition(Vec2(fighter->getContentSize().width / 2, 0));
		ps->setRotation(180.0f);
		ps->setScale(0.5f);
		fighter->addChild(ps);

		Vec2 verts[] = {
			Vec2(-43.5, 15.5),
			Vec2(-23.5, 33),
			Vec2(28.5, 34),
			Vec2(48, 17.5),
			Vec2(0, -39.5)};

		auto body = PhysicsBody::createPolygon(verts, 5);

		body->setCategoryBitmask(0x01);
		body->setCollisionBitmask(0x02);
		body->setContactTestBitmask(0x01);

		fighter->setPhysicsBody(body);

		return fighter;
	}

	CC_SAFE_DELETE(fighter);
	return nullptr;
}

void Fighter::setPosition(const cocos2d::Vec2 & newPosition)
{
	Size screenSize = Director::getInstance()->getVisibleSize();

	float halfWidth = this->getContentSize().width / 2;
	float halfHeight = this->getContentSize().height / 2;
	float xPos = newPosition.x;
	float yPos = newPosition.y;

	if (xPos < halfWidth)
	{
		xPos = halfWidth;
	}
	else if (xPos > (screenSize.width - halfWidth))
	{
		xPos = screenSize.width - halfWidth;
	}

	if (yPos < halfHeight)
	{
		yPos = halfHeight;
	}
	else if (yPos > (screenSize.height - halfHeight))
	{
		yPos = screenSize.height - halfHeight;
	}

	Sprite::setPosition(Vec2(xPos, yPos));
	Sprite::setAnchorPoint(Vec2(0.5f, 0.5f));
}
