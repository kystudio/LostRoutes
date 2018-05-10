﻿#pragma once
typedef enum
{
	MenuItemStart,
	MenuItemSetting,
	MenuItemHelp
} ActionType;

#include "cocos2d.h"

#include "SystemHeader.h"

#include "GamePlayScene.h"
#include "SettingScene.h"
#include "HelpScene.h"

class HomeMenuLayer : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene();

	virtual bool init();

	virtual void onEnterTransitionDidFinish();

	void menuItemCallback(cocos2d::Ref * sender);

	CREATE_FUNC(HomeMenuLayer);
private:
};