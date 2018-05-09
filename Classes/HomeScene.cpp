#include "HomeScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene * HomeMenuLayer::createScene()
{
	auto scene = Scene::create();

	auto layer = HomeMenuLayer::create();

	scene->addChild(layer);

	return scene;
}

bool HomeMenuLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto bg = TMXTiledMap::create("map/red_bg.tmx");
	addChild(bg);

	auto top = Sprite::createWithSpriteFrameName("home-top.png");
	top->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - top->getContentSize().height / 2));
	addChild(top);

	auto end = Sprite::createWithSpriteFrameName("home-end.png");
	end->setPosition(Vec2(visibleSize.width / 2, top->getContentSize().height / 2));
	addChild(end);

	// 添加菜单
	//1.开始菜单
	auto startNormal = Sprite::createWithSpriteFrameName("home.button.start.png");
	auto startSelected = Sprite::createWithSpriteFrameName("home.button.start-on.png");
	auto startMenuItem = MenuItemSprite::create(startNormal,startSelected,CC_CALLBACK_1(HomeMenuLayer::menuItemCallback, this));
	startMenuItem->setTag(ActionType::MenuItemStart);
	//2.设置菜单
	auto settingNormal = Sprite::createWithSpriteFrameName("home.button.setting.png");
	auto settingSelected = Sprite::createWithSpriteFrameName("home.button.setting-on.png");
	auto settingMenuItem = MenuItemSprite::create(settingNormal, settingSelected, CC_CALLBACK_1(HomeMenuLayer::menuItemCallback, this));
	settingMenuItem->setTag(ActionType::MenuItemSetting);
	//3.帮助菜单
	auto helpNormal = Sprite::createWithSpriteFrameName("home.button.help.png");
	auto helpSelected = Sprite::createWithSpriteFrameName("home.button.help-on.png");
	auto helpMenuItem = MenuItemSprite::create(helpNormal, helpSelected, CC_CALLBACK_1(HomeMenuLayer::menuItemCallback, this));
	helpMenuItem->setTag(ActionType::MenuItemHelp);

	auto menu = Menu::create(startMenuItem, settingMenuItem, helpMenuItem, NULL);
	menu->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	menu->alignItemsVerticallyWithPadding(12);
	addChild(menu);

	return true;
}

void HomeMenuLayer::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	//log("HomeMenuLayer::onEnterTransitionDidFinish");
	UserDefault * userdefault = UserDefault::getInstance();

	if (userdefault->getBoolForKey(MUSIC_KEY))
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic(bg_music_1, true);
	}
}

void HomeMenuLayer::menuItemCallback(Ref * sender)
{
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}

	Scene * tsc = nullptr;

	MenuItem *menuItem = (MenuItem*)sender;
	log("MenuItem Tag = %d", menuItem->getTag());
	switch (menuItem->getTag())
	{
	case ActionType::MenuItemStart:
		tsc = TransitionFade::create(1.0f, GamePlayLayer::createScene());
		break;
	case ActionType::MenuItemSetting:
		tsc = TransitionFade::create(1.0f, SettingLayer::createScene());
		break;
	case ActionType::MenuItemHelp:
		tsc = TransitionFade::create(1.0f, HelpLayer::createScene());
		break;
	default:
		break;
	}

	if (tsc)
	{
		Director::getInstance()->pushScene(tsc);
	}
}