#pragma once
#ifndef __BATTLE_H__
#define __BATTLE_H__

#include "cocos2d.h"
#include "Hero.h"
#include "Player.h"
#define MaxRow 3
#define MaxCol 6
#define MaxHero 9
#define MaxDis 1000000
USING_NS_CC;

class Battle :public Layer {
public:
	CREATE_FUNC(Battle);
	virtual bool init();
	static Battle* createLayer();
	void Start();//ս����ʽ��ʼ
	void SetPlayer(Player* my, Player* en);//����˫�����
	void SetHeroPos();
	void SetHeroData();//���ó������ӵ���Ϣ��Ӧ���Ǳ�սʱ���
	double CountDistance(Vec2 pos1, Vec2 pos2);//����ĳ����Ӣ��֮��ľ���
	void SetAtkTarget(std::vector <Hero*>& atk, std::vector <Hero*>& tar, int atkNum, int tarNum);
	void UpdateTarget(std::vector <Hero*>& atk, std::vector <Hero*>& tar, int atkNum, int tarNum);//�������ӵĹ���Ŀ��
	void ResetHero();//��������״̬
	int IsEnd();//�жϱ��غ��Ƿ���������Ƿ�ֳ�ʤ��
	void End();//��ս��������Ĵ�������ССӢ�۵Ŀ�Ѫ
	virtual	void update(float dt);
	void Destory();//ע�����ж�ʱ��
private:
	std::vector <Hero*> self;
	std::vector <Hero*> enemy;
	//Hero* self[MaxHero];//�ҷ������Ӣ��
	//Hero* enemy[MaxHero];//�з������Ӣ��

	Vec2 myField[MaxRow][MaxCol] =
	{{ Vec2(665, 455), Vec2(770, 455), Vec2(875, 455), Vec2(980, 455), Vec2(1085, 455), Vec2(1190, 455)},
	 {Vec2(665, 525), Vec2(770, 525), Vec2(875, 525), Vec2(980, 525), Vec2(1085, 525), Vec2(1190, 525)},
	 {Vec2(665, 597), Vec2(770, 597), Vec2(875, 597), Vec2(980, 597), Vec2(1085, 597), Vec2(1190, 597)}};
	Vec2 enemyField[MaxRow][MaxCol] =
	{{Vec2(665, 385), Vec2(770, 385), Vec2(875, 385), Vec2(980, 385), Vec2(1085, 385), Vec2(1190, 385)},
	 {Vec2(665, 315), Vec2(770, 315), Vec2(875, 315), Vec2(980, 315), Vec2(1085, 315), Vec2(1190, 315)},
	 {Vec2(665, 245), Vec2(770, 245), Vec2(875, 245), Vec2(980, 245), Vec2(1085, 245), Vec2(1190, 245)}};
	site* myPos;//��¼�ҷ��ϳ�Ӣ�۵�λ��
	site* enPos;//��¼�з��ϳ�Ӣ�۵�λ��
	Player* myPlayer;//�ҷ�ССӢ��
	Player* enPlayer;//�з�ССӢ��
	int myHeroNum;
	int enHeroNum;
	int myLive;
	int enLive;
};

#endif
