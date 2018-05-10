﻿#pragma once
#include "cocos2d.h"
#include "SystemHeader.h"
#include "MyUtility.h"

#include "BaseLayer.h"

class HelpLayer : public BaseLayer
{
public:
	static cocos2d::Scene * createScene();
	virtual bool init();

	CREATE_FUNC(HelpLayer);
};