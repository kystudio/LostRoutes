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
// �����ڵ����ٶ�
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
	// ����
	int _score;
	// ��¼0~999����
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
	
	// �����ڵ�
	void shootBullet(float dt);

	// ��ʼ������
	void initBG();

	// ��״̬�������ú͸�����ҵ�����ֵ
	void updateStatusBarFighter();
	// ��״̬���и��µ÷�
	void updateStatusBarScore();

	void menuPauseCallback(cocos2d::Ref * pSender);
	void menuBackCallback(cocos2d::Ref * pSender);
	void menuResumeCallback(cocos2d::Ref * pSender);

	// �����������˵���ײ���
	void handleFighterCollidingWithEnemy(Enemy * enemy);
	// �����ӵ�����˵���ײ���
	void handleBulletCollidingWithEnemy(Enemy * enemy);

	CREATE_FUNC(GamePlayLayer);
};