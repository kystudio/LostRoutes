#include "GamePlayScene.h"

USING_NS_CC;

Scene * GamePlayLayer::createScene()
{
	auto scene = Scene::create();

	auto layer = GamePlayLayer::create();

	scene->addChild(layer);

	return scene;
}

bool GamePlayLayer::init()
{
	if (!BaseLayer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto lab = Label::createWithSystemFont("GamePlay", "", 24);
	lab->setTextColor(Color4B::BLACK);
	lab->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(lab);

	return true;
}