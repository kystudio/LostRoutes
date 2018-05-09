#include "HelpScene.h"

USING_NS_CC;

Scene * HelpLayer::createScene()
{
	auto scene = Scene::create();

	auto layer = HelpLayer::create();

	scene->addChild(layer);

	return scene;
}

bool HelpLayer::init()
{
	if (!BaseLayer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto top = Sprite::createWithSpriteFrameName("help-top.png");
	top->setPosition(origin + Vec2(visibleSize.width / 2, visibleSize.height - top->getContentSize().height / 2));
	addChild(top);

	// ���á����ԡ�����
	auto txtTest = Label::createWithTTF(MyUtility::getUTF8Char("test"), "fonts/hanyi.ttf", 18);
	txtTest->setColor(Color3B(14, 83, 204));
	txtTest->setPosition(95, top->getPositionY() - 70);
	txtTest->setAnchorPoint(Vec2::ZERO);
	addChild(txtTest, 1);

	// ���ò���������51work6
	auto test = Label::createWithTTF("51work6", "fonts/hanyi.ttf", 18);
	test->setAnchorPoint(Vec2::ZERO);
	Vec2 p1 = txtTest->convertToWorldSpace(Vec2(0, -20));
	test->setColor(Color3B(198, 12, 0));
	test->setPosition(p1);
	addChild(test, 1);

	// ���á����֡�����
	auto txtMusic = Label::createWithTTF(MyUtility::getUTF8Char("music"), "fonts/hanyi.ttf", 18);
	txtMusic->setColor(Color3B(14, 83, 204));
	Vec2 p2 = test->convertToWorldSpace(Vec2(0, -40));
	txtMusic->setPosition(p2);
	txtMusic->setAnchorPoint(Vec2::ZERO);
	addChild(txtMusic, 1);

	// �������������� Mr.Guan
	auto music1 = Label::createWithTTF("Mr.Guan", "fonts/hanyi.ttf", 18);
	music1->setAnchorPoint(Vec2::ZERO);
	Vec2 p3 = txtMusic->convertToWorldSpace(Vec2(0, -20));
	music1->setColor(Color3B(198, 12, 0));
	music1->setPosition(p3);
	addChild(music1, 1);

	// �������������� YunLong
	auto music2 = Label::createWithTTF("YunLong", "fonts/hanyi.ttf", 18);
	music2->setAnchorPoint(Vec2::ZERO);
	Vec2 p4 = music1->convertToWorldSpace(Vec2(0, -20));
	music2->setColor(Color3B(198, 12, 0));
	music2->setPosition(p4);
	addChild(music2, 1);
	
	// ���á���Ч������
	auto txtSound = Label::createWithTTF(MyUtility::getUTF8Char("sound"), "fonts/hanyi.ttf", 18);
	txtSound->setColor(Color3B(14, 83, 204));
	Vec2 p5 = music2->convertToWorldSpace(Vec2(0, -40));
	txtSound->setPosition(p5);
	txtSound->setAnchorPoint(Vec2::ZERO);
	addChild(txtSound, 1);

	// ������Ч������ Mr.Zhao
	auto sound1 = Label::createWithTTF("Mr.Zhao", "fonts/hanyi.ttf", 18);
	sound1->setAnchorPoint(Vec2::ZERO);
	Vec2 p6 = txtSound->convertToWorldSpace(Vec2(0, -20));
	sound1->setColor(Color3B(198, 12, 0));
	sound1->setPosition(p6);
	addChild(sound1, 1);

	// ������Ч������ YunLong
	auto sound2 = Label::createWithTTF("YunLong", "fonts/hanyi.ttf", 18);
	sound2->setAnchorPoint(Vec2::ZERO);
	Vec2 p7 = sound1->convertToWorldSpace(Vec2(0, -20));
	sound2->setColor(Color3B(198, 12, 0));
	sound2->setPosition(p7);
	addChild(sound2, 1);

	// ���á���Ϣ���������
	auto txtInfoService = Label::createWithTTF(MyUtility::getUTF8Char("info_service"), "fonts/hanyi.ttf", 18);
	txtInfoService->setColor(Color3B(14, 83, 204));
	Vec2 p8 = sound2->convertToWorldSpace(Vec2(0, -40));
	txtInfoService->setPosition(p8);
	txtInfoService->setAnchorPoint(Vec2::ZERO);
	addChild(txtInfoService, 1);

	// ������Ϣ����������� www.51work6.com
	auto infoService = Label::createWithTTF("www.51work6.com", "fonts/hanyi.ttf", 18);
	infoService->setAnchorPoint(Vec2::ZERO);
	Vec2 p9 = txtInfoService->convertToWorldSpace(Vec2(0, -20));
	infoService->setColor(Color3B(198, 12, 0));
	infoService->setPosition(p9);
	addChild(infoService, 1);

	return true;
}