#include "GameOverScene.h"

GameOverLayer::GameOverLayer(int score)
{
	this->_score = score;
}

bool GameOverLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	_defaults = UserDefault::getInstance();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//添加背景地图.
	auto bg = TMXTiledMap::create("hd/map/blue_bg.tmx");
	this->addChild(bg);

	//放置发光粒子背景
	ParticleSystem *ps = ParticleSystemQuad::create("particle/light.plist");
	ps->setPosition(Vec2(visibleSize.width, visibleSize.height - 200) / 2);
	this->addChild(ps);

	auto top = Sprite::createWithSpriteFrameName("gameover.top.png");
	//锚点在左下角
	top->setAnchorPoint(Vec2(0, 0));
	top->setPosition(Vec2(0, visibleSize.height - top->getContentSize().height));
	this->addChild(top);

	int highScore = _defaults->getIntegerForKey(HIGHSCORE_KEY);
	if (highScore < _score) {
		highScore = _score;
		_defaults->setIntegerForKey(HIGHSCORE_KEY, highScore);
	}
	__String *text = __String::createWithFormat("%i points", highScore);
	auto lblHighScore = Label::createWithTTF(MyUtility::getUTF8Char("lblHighScore"), "fonts/hanyi.ttf", 25);
	lblHighScore->setAnchorPoint(Vec2(0, 0));
	lblHighScore->setPosition(Vec2(60, top->getPosition().y - 30));
	addChild(lblHighScore);

	auto lblScore = Label::createWithTTF(text->getCString(), "fonts/hanyi.ttf", 24);
	lblScore->setColor(Color3B(75, 255, 255));
	lblScore->setAnchorPoint(Vec2(0, 0));
	lblScore->setPosition(lblHighScore->getPosition() - Vec2(0, 40));
	addChild(lblScore);

	auto text2 = Label::createWithTTF("Tap the Screen to Play", "fonts/hanyi.ttf", 24);
	text2->setAnchorPoint(Vec2(0, 0));
	text2->setPosition(lblScore->getPosition() - Vec2(10, 45));
	addChild(text2);

	//注册 触摸事件监听器
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [](Touch* touch, Event* event) {
		Director::getInstance()->popScene();
		if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
			SimpleAudioEngine::getInstance()->playEffect(sound_1);
		}
		return false;
	};

	// 添加 触摸事件监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void GameOverLayer::onExit()
{
	Layer::onExit();
	_eventDispatcher->removeEventListenersForTarget(this);
}

GameOverLayer * GameOverLayer::createWithScore(int score)
{
	GameOverLayer * gameOver = new GameOverLayer(score);

	if (gameOver && gameOver->init())
	{
		gameOver->autorelease();
		return gameOver;
	}

	CC_SAFE_DELETE(gameOver);

	return nullptr;
}
