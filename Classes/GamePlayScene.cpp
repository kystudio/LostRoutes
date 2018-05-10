#include "GamePlayScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene * GamePlayLayer::createScene()
{
	auto scene = Scene::createWithPhysics();

	PhysicsWorld * phyWorld = scene->getPhysicsWorld();

	phyWorld->setGravity(Vect(0, 0));

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

	_defaults = UserDefault::getInstance();
	_visibleSize = Director::getInstance()->getVisibleSize();

	this->initBG();
	
	return true;
}

void GamePlayLayer::onEnter()
{
	Layer::onEnter();
	// 初始化暂停按钮
	auto pauseSp = Sprite::createWithSpriteFrameName("gameplay.button.pause.png");
	auto pauseItem = MenuItemSprite::create(pauseSp, pauseSp, CC_CALLBACK_1(GamePlayLayer::menuPauseCallback, this));
	auto pauseMenu = Menu::create(pauseItem, NULL);
	pauseMenu->setPosition(Vec2(30, _visibleSize.height - 28));
	this->addChild(pauseMenu, 20, 999);

	// 添加陨石1
	auto stone1 = Enemy::createWithEnemyTypes(EnemyTypeStone);
	stone1->setVelocity(Vec2(0, -100));
	this->addChild(stone1, 10, GameSceneNodeBatchTagEnemy);

	// 添加行星
	auto planet = Enemy::createWithEnemyTypes(EnemyTypePlanet);
	planet->setVelocity(Vec2(0, -50));
	this->addChild(planet, 10, GameSceneNodeBatchTagEnemy);

	// 添加敌机1
	auto enemyFighter1 = Enemy::createWithEnemyTypes(EnemyTypeEnemy1);
	enemyFighter1->setVelocity(Vec2(0, -80));
	this->addChild(enemyFighter1, 10, GameSceneNodeBatchTagEnemy);

	// 添加敌机2
	auto enemyFighter2 = Enemy::createWithEnemyTypes(EnemyTypeEnemy2);
	enemyFighter2->setVelocity(Vec2(0, -100));
	this->addChild(enemyFighter2, 10, GameSceneNodeBatchTagEnemy);

	// 玩家的飞机
	this->_fighter = Fighter::createWithSpriteFrameName("gameplay.fighter.png");
	this->_fighter->setHitPoints(5);
	this->_fighter->setPosition(Vec2(_visibleSize.width / 2, 70));
	this->addChild(this->_fighter, 10, GameSceneNodeTagFighter);

	// 注册触摸飞机事件监听器
	_touchFighterListener = EventListenerTouchOneByOne::create();
	_touchFighterListener->setSwallowTouches(true);

	_touchFighterListener->onTouchBegan = [](Touch * touch, Event * event) {
		return true;
	};

	_touchFighterListener->onTouchMoved = [](Touch * touch, Event * event) {
		auto target = event->getCurrentTarget();
		target->setPosition(target->getPosition() + touch->getDelta());
	};

	// 添加触摸飞机事件监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_touchFighterListener, this->_fighter);

	_contactListener = EventListenerPhysicsContact::create();
	_contactListener->onContactBegin = [this](PhysicsContact& contact)
	{
		auto spriteA = contact.getShapeA()->getBody()->getNode();
		auto spriteB = contact.getShapeA()->getBody()->getNode();

		// 检测飞机与敌人的碰撞
		log("A = %d  ------------ B = %d", spriteA->getTag(), spriteB->getTag());
		Node * enemy1 = nullptr;
		if (spriteA->getTag() == GameSceneNodeTagFighter && spriteB->getTag() == GameSceneNodeBatchTagEnemy)
		{
			enemy1 = spriteB;
		}

		if (spriteA->getTag() == GameSceneNodeBatchTagEnemy && spriteB->getTag() == GameSceneNodeTagFighter)
		{
			enemy1 = spriteA;
		}

		if (enemy1 != nullptr)
		{
			this->handleFighterCollidingWithEnemy((Enemy *)enemy1);
			return false;
		}

		// 检测炮弹与敌人的碰撞
		Node * enemy2 = nullptr;

		if (spriteA->getTag() == GameSceneNodeBatchTagBullet && spriteB->getTag() == GameSceneNodeBatchTagEnemy)
		{
			if (!spriteA->isVisible())
			{
				return false;
			}
			spriteA->setVisible(false);
			enemy2 = spriteB;
		}

		if (spriteA->getTag() == GameSceneNodeBatchTagEnemy && spriteB->getTag() == GameSceneNodeBatchTagBullet)
		{
			if (!spriteB->isVisible())
			{
				return false;
			}
			spriteB->setVisible(false);
			enemy2 = spriteA;
		}

		if (enemy2 != nullptr)
		{
			this->handleBulletCollidingWithEnemy((Enemy *)enemy2);
			return false;
		}

		return false;
	};

	_eventDispatcher->addEventListenerWithFixedPriority(_contactListener, 2);

	// 每0.2s调用shootBullet函数发射1发炮弹
	this->schedule(schedule_selector(GamePlayLayer::shootBullet), 0.2f);

	this->_score = 0;
	this->_scorePlaceholder = 0;

	this->updateStatusBarFighter();

	this->updateStatusBarScore();
}

void GamePlayLayer::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	if (_defaults->getBoolForKey(MUSIC_KEY))
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic(bg_music_2, true);
	}
}

void GamePlayLayer::onExit()
{
	Layer::onExit();

	this->unschedule(schedule_selector(GamePlayLayer::shootBullet));

	_eventDispatcher->removeEventListener(_touchFighterListener);
	_eventDispatcher->removeEventListener(_contactListener);

	auto nodes = this->getChildren();

	for (const auto& node : nodes)
	{
		if (node->getTag() != GameSceneNodeBatchTagBackground)
		{
			this->removeChild(node);
		}
	}
}

void GamePlayLayer::shootBullet(float dt)
{
	if (_fighter && _fighter->isVisible())
	{
		Bullet * bullet = Bullet::createWithSpriteFrameName("gameplay.bullet.png");
		bullet->setVelocity(Vec2(0, GameSceneBulletVelocity));
		this->addChild(bullet, 0, GameSceneNodeBatchTagBullet);
		bullet->shootBulletFromFighter(_fighter);
	}
}

void GamePlayLayer::initBG()
{
	// 添加背景地图
	auto bg = TMXTiledMap::create("map/blue_bg.tmx");
	this->addChild(bg, 0, GameSceneNodeBatchTagBackground);

	// 放置发光粒子背景
	ParticleSystem * ps = ParticleSystemQuad::create("particle/light.plist");
	ps->setPosition(Vec2(_visibleSize.width, _visibleSize.height / 2));
	this->addChild(ps, 0, GameSceneNodeBatchTagBackground);

	// 添加背景精灵1
	auto sprite1 = Sprite::createWithSpriteFrameName("gameplay.bg.sprite-1.png");
	sprite1->setPosition(Vec2(-50, -50));
	addChild(sprite1, 0, GameSceneNodeBatchTagBackground);

	FiniteTimeAction * ac1 = (FiniteTimeAction *)MoveBy::create(20, Vec2(500, 600));
	FiniteTimeAction * ac2 = ((FiniteTimeAction *)ac1)->reverse();
	ActionInterval * as1 = Sequence::create(ac1, ac2, NULL);
	sprite1->runAction(RepeatForever::create(EaseSineInOut::create(as1)));

	// 添加背景精灵2
	auto sprite2 = Sprite::createWithSpriteFrameName("gameplay.bg.sprite-2.png");
	sprite2->setPosition(Vec2(_visibleSize.width, 0));
	addChild(sprite2, 0, GameSceneNodeBatchTagBackground);

	FiniteTimeAction * ac3 = (FiniteTimeAction *)MoveBy::create(10, Vec2(-500, 600));
	FiniteTimeAction * ac4 = ((FiniteTimeAction *)ac3)->reverse();
	ActionInterval * as2 = Sequence::create(ac3, ac4, NULL);
	sprite2->runAction(RepeatForever::create(EaseExponentialInOut::create(as2)));
}

void GamePlayLayer::updateStatusBarFighter()
{
	Node * n1 = this->getChildByTag(GameSceneNodeTagStatusBarFighterNode);

	if (n1)
	{
		this->removeChildByTag(GameSceneNodeTagStatusBarFighterNode);
	}

	Sprite * fg = Sprite::createWithSpriteFrameName("gameplay.life.png");
	fg->setPosition(Vec2(_visibleSize.width - 60, _visibleSize.height - 28));
	this->addChild(fg, 20, GameSceneNodeTagStatusBarFighterNode);

	// 添加生命值 x5
	Node * n2 = this->getChildByTag(GameSceneNodeTagStatusBarLifeNode);

	if (n2)
	{
		this->removeChildByTag(GameSceneNodeTagStatusBarLifeNode);
	}

	if (this->_fighter->getHitPoints() < 0)
	{
		this->_fighter->setHitPoints(0);
	}

	__String * life = __String::createWithFormat("x %d", this->_fighter->getHitPoints());
	auto lblLife = Label::createWithTTF(life->getCString(), "fonts/hanyi.ttf", 18);
	lblLife->setPosition(fg->getPosition() + Vec2(30, 0));
	this->addChild(lblLife, 20, GameSceneNodeTagStatusBarLifeNode);
}

void GamePlayLayer::updateStatusBarScore()
{
	Node * n = this->getChildByTag(GameSceneNodeTagStatusBarScore);

	if (n)
	{
		this->removeChildByTag(GameSceneNodeTagStatusBarScore);
	}

	if (this->_score < 0)
	{
		this->_score = 0;
	}

	__String * score = __String::createWithFormat(" %d", this->_score);
	auto lblScore = Label::createWithTTF(score->getCString(), "fonts/hanyi.ttf", 18);
	lblScore->setPosition(Vec2(_visibleSize.width / 2, _visibleSize.height - 28));
	this->addChild(lblScore, 20, GameSceneNodeTagStatusBarScore);
}

void GamePlayLayer::menuPauseCallback(cocos2d::Ref * pSender)
{
	if (_defaults->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}

	// 暂停当前层中的node
	this->pause();

	for (const auto& node : this->getChildren())
	{
		node->pause();
	}
	// 返回主菜单
	auto backNormal = Sprite::createWithSpriteFrameName("gameplay.button.back.png");
	auto backSelected = Sprite::createWithSpriteFrameName("gameplay.button.back-on.png");

	auto backItem = MenuItemSprite::create(backNormal, backSelected, CC_CALLBACK_1(GamePlayLayer::menuBackCallback, this));

	// 继续游戏菜单
	auto resumeNoraml = Sprite::createWithSpriteFrameName("gameplay.button.resume.png");
	auto resumeSelected = Sprite::createWithSpriteFrameName("gameplay.button.resume-on.png");

	auto resumeItem = MenuItemSprite::create(resumeNoraml, resumeSelected, CC_CALLBACK_1(GamePlayLayer::menuResumeCallback, this));

	_menu = Menu::create(backItem, resumeItem, NULL);
	_menu->alignItemsVertically();
	_menu->setPosition(Vec2(_visibleSize.width / 2, _visibleSize.height / 2));

	addChild(_menu, 20, 1000);
}

void GamePlayLayer::menuBackCallback(cocos2d::Ref * pSender)
{
	if (_defaults->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
	Director::getInstance()->popScene();
}

void GamePlayLayer::menuResumeCallback(cocos2d::Ref * pSender)
{
	if (_defaults->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}

	this->resume();

	for (const auto& node : this->getChildren())
	{
		node->resume();
	}

	removeChild(_menu);
}

void GamePlayLayer::handleFighterCollidingWithEnemy(Enemy * enemy)
{
	Node * node = this->getChildByTag(GameSceneNodeTagExplosionParticleSystem);
	if (node)
	{
		this->removeChild(node);
	}

	ParticleSystem * explosion = ParticleSystemQuad::create("particle/explosion.plist");
	explosion->setPosition(enemy->getPosition());
	this->addChild(explosion, 2, GameSceneNodeTagExplosionParticleSystem);
	if (_defaults->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect(sound_2);
	}

	enemy->setVisible(false);

	enemy->spawn();

	_fighter->setHitPoints(_fighter->getHitPoints() - 1);
	this->updateStatusBarFighter();
	// 游戏结束
	if (_fighter->getHitPoints() <= 0)
	{
		log("GameOver");
	} 
	else
	{
		_fighter->setPosition(Vec2(_visibleSize.width / 2, 70));
		auto ac1 = Show::create();
		auto ac2 = FadeIn::create(1.0f);
		auto seq = Sequence::create(ac1, ac2, NULL);

		_fighter->runAction(seq);
	}
}

void GamePlayLayer::handleBulletCollidingWithEnemy(Enemy * enemy)
{
	enemy->setHitPoints(enemy->getHitPoints() - 1);

	if (enemy->getHitPoints() <= 0)
	{
		Node * node = this->getChildByTag(GameSceneNodeTagExplosionParticleSystem);
		if (node)
		{
			this->removeChild(node);
		}

		ParticleSystem * explosion = ParticleSystemQuad::create("particle/explosion.plist");
		explosion->setPosition(enemy->getPosition());
		this->addChild(explosion, 2, GameSceneNodeTagExplosionParticleSystem);
		if (_defaults->getBoolForKey(SOUND_KEY))
		{
			SimpleAudioEngine::getInstance()->playEffect(sound_2);
		}

		switch (enemy->getEnemyType())
		{
		case EnemyTypeStone:
			_score += EnemyStone_Score;
			_scorePlaceholder += EnemyStone_Score;
			break;
		case EnemyTypeEnemy1:
			_score += Enemy1_Score;
			_scorePlaceholder += Enemy1_Score;
			break;
		case EnemyTypeEnemy2:
			_score += Enemy2_Score;
			_scorePlaceholder += Enemy2_Score;
			break;
		case EnemyTypePlanet:
			_score += EnemyPlanet_Score;
			_scorePlaceholder += EnemyPlanet_Score;
			break;
		}

		// 每次获得1000分值，生命值+1，_scorePlaceholder恢复为0
		if (_scorePlaceholder >= 1000)
		{
			_fighter->setHitPoints(_fighter->getHitPoints() + 1);
			this->updateStatusBarFighter();
			_scorePlaceholder -= 1000;
		}

		this->updateStatusBarScore();

		enemy->setVisible(false);

		enemy->spawn();
	}
}
