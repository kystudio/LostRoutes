#include "SettingScene.h"

USING_NS_CC;

Scene * SettingLayer::createScene()
{
	auto scene = Scene::create();

	auto layer = SettingLayer::create();

	scene->addChild(layer);

	return scene;
}

bool SettingLayer::init()
{
	if (!BaseLayer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto top = Sprite::createWithSpriteFrameName("setting-top.png");
	top->setPosition(origin + Vec2(visibleSize.width / 2, visibleSize.height - top->getContentSize().height / 2));
	addChild(top);

	//音效菜单项
	auto soundOnSp = Sprite::createWithSpriteFrameName("setting.check-on.png");
	auto soundOffSp = Sprite::createWithSpriteFrameName("setting.check-off.png");
	auto soundOnItem = MenuItemSprite::create(soundOnSp, NULL);
	auto soundOffItem = MenuItemSprite::create(soundOffSp, NULL);
	auto soundToggleItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingLayer::menuSoundToggleCallback, this), soundOnItem, soundOffItem, NULL);
	//音乐菜单项
	auto musicOnSp = Sprite::createWithSpriteFrameName("setting.check-on.png");
	auto musicOffSp = Sprite::createWithSpriteFrameName("setting.check-off.png");
	auto musicOnItem = MenuItemSprite::create(musicOnSp, NULL);
	auto musicOffItem = MenuItemSprite::create(musicOffSp, NULL);
	auto musicToggleItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingLayer::menuMusicToggleCallback, this), musicOnItem, musicOffItem, NULL);

	auto menu = Menu::create(soundToggleItem, musicToggleItem, NULL);
	menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2) + Vec2(70, 40));
	menu->alignItemsVerticallyWithPadding(50.0f);
	addChild(menu, 1);

	auto lblSound = Label::createWithTTF(MyUtility::getUTF8Char("lblSound"), "fonts/hanyi.ttf", 36);
	lblSound->setColor(Color3B(14, 83, 204));
	lblSound->setPosition(menu->getPosition() - Vec2(100, -50));
	addChild(lblSound, 1);

	auto lblMusic = Label::createWithTTF(MyUtility::getUTF8Char("lblMusic"), "fonts/hanyi.ttf", 36);
	lblMusic->setColor(Color3B(14, 83, 204));
	lblMusic->setPosition(menu->getPosition() - Vec2(100, 45));
	addChild(lblMusic, 1);

	// 设置音效和音乐选中状态
	_defaults = UserDefault::getInstance();

	if (_defaults->getBoolForKey(MUSIC_KEY))
	{
		musicToggleItem->setSelectedIndex(0);
	} 
	else
	{
		musicToggleItem->setSelectedIndex(1);
	}

	if (_defaults->getBoolForKey(SOUND_KEY))
	{
		soundToggleItem->setSelectedIndex(0);
	}
	else
	{
		soundToggleItem->setSelectedIndex(1);
	}

	return true;
}

void SettingLayer::menuSoundToggleCallback(Ref * pSender)
{
	if (_defaults->getBoolForKey(SOUND_KEY))
	{
		_defaults->setBoolForKey(SOUND_KEY, false);
	}
	else
	{
		_defaults->setBoolForKey(SOUND_KEY, true);
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
}

void SettingLayer::menuMusicToggleCallback(Ref * pSender)
{
	if (_defaults->getBoolForKey(MUSIC_KEY))
	{
		_defaults->setBoolForKey(MUSIC_KEY, false);
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
	else
	{
		_defaults->setBoolForKey(MUSIC_KEY, true);
		SimpleAudioEngine::getInstance()->playBackgroundMusic(bg_music_2, true);
	}
}