#pragma once
#include "cocos2d.h"
#include "SystemHeader.h"
#include "MyUtility.h"

#include "BaseLayer.h"

#include "Enemy.h"
#include "Fighter.h"
#include "Bullet.h"

#define GameSceneNodeTagStatusBarFighterNode	301
#define GameSceneNodeTagStatusBarLifeNode		302
#define GameSceneNodeTagStatusBarScore			303

#define GameSceneNodeBatchTagBackground			800
#define GameSceneNodeTagFighter					900
#define GameSceneNodeTagExplosionParticleSystem 901
#define GameSceneNodeBatchTagBullet				902
#define GameSceneNodeBatchTagEnemy				903
// 发射炮弹的速度
#define GameSceneBulletVelocity					300

//typedef enum
//{
//	EnemyStone_Score = 5,
//	Enemy1_Score = 10,
//	Enemy2_Score = 15,
//	EnemyPlanet_Score = 20
//} EnemyScores;

enum EnemyScores
{
	EnemyStone_Score = 5,
	Enemy1_Score = 10,
	Enemy2_Score = 15,
	EnemyPlanet_Score = 20
};

class GamePlayLayer : public BaseLayer
{
private:
	Fighter * _fighter;
	cocos2d::Menu * _menu;
	// 分数
	int _score;
	// 记录0~999分数
	int _scorePlaceholder;

	cocos2d::EventListenerTouchOneByOne * _touchFighterListener;
	cocos2d::EventListenerPhysicsContact * _contactListener;
	Size _visibleSize;
	UserDefault * _defaults;
public:
	static cocos2d::Scene * createScene();
	virtual bool init();

	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	
	// 发射炮弹
	void shootBullet(float dt);

	// 初始化背景
	void initBG();

	// 在状态栏中设置和更新玩家的生命值
	void updateStatusBarFighter();
	// 在状态栏中更新得分
	void updateStatusBarScore();

	void menuPauseCallback(cocos2d::Ref * pSender);
	void menuBackCallback(cocos2d::Ref * pSender);
	void menuResumeCallback(cocos2d::Ref * pSender);

	// 处理玩家与敌人的碰撞检测
	void handleFighterCollidingWithEnemy(Enemy * enemy);
	// 处理子弹与敌人的碰撞检测
	void handleBulletCollidingWithEnemy(Enemy * enemy);

	CREATE_FUNC(GamePlayLayer);
};