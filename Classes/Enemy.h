#pragma once
#include "cocos2d.h"

// �����������Ҳ�ǵ��˾���֡������
#define Enemy_Stone "gameplay.stone1.png"
#define Enemy_1 "gameplay.enemy-1.png"
#define Enemy_2 "gameplay.enemy-2.png"
#define Enemy_Planet "gameplay.enemy.planet.png"

// �����������
typedef enum
{
	EnemyTypeStone = 0, // ��ʯ
	EnemyTypeEnemy1, // �л�1
	EnemyTypeEnemy2, // �л�2
	EnemyTypePlanet // ����
} EnemyTypes;

class Enemy : public cocos2d::Sprite
{
	CC_SYNTHESIZE(EnemyTypes, enemyType, EnemyType); // ��������
	CC_SYNTHESIZE(int, initialHitPoints, InitialHitPoints); // ��ʼ������ֵ
	CC_SYNTHESIZE(int, hitPoints, HitPoints); // ��ǰ������ֵ
	CC_SYNTHESIZE(cocos2d::Vec2, velocity, Velocity); // �ٶ�
public:
	Enemy(EnemyTypes enemyType); // ���캯��
	void spawn(); // �������˺���
	virtual void update(float dt); // ��Ϸѭ�����õ�Ĭ�Ϻ���
	static Enemy * createWithEnemyTypes(EnemyTypes enemyType); // ��̬�������˺���
};