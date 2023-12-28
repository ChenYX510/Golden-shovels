#ifndef  _PLAYER_H_
#define  _PLAYER_H_

//#include "ChessShop.h"
#include "cocos2d.h"
#include <vector>
#include "Hero.h"
#define MaxHero 9

USING_NS_CC;

//��ʼѪ��
constexpr int initplayerBlood = 100;
//ÿ�������� 4 ����
constexpr int addExperience = 4;
//���������ֵ�� 4
constexpr int addMaxExperience = 4;

struct site {
	int x;
	int y;
};


class Hero;
class Player : public cocos2d::Sprite
{
private:
	//��������
	bool playerIsDead;

	//���Ѫ��
	int playerBlood;

	////���
	//int playerMoney;

	//��ҵȼ�
	int playerLevel;

	////��������һ����Ҫ���پ���
	//int playerNeedExperience;

	////�����ϳ�����������
	//int playerMaxNumChess;

	////��Ҿ���
	//int playerExperience;

	////�������
	//std::vector<Hero*> chessPlayer;

	////��ұ�ս������
	//std::vector<Hero*> chessPreparePlayer;

	showHPMP* myHP;//ССӢ�۵�Ѫ��

	Hero chessWarPlayer[MaxHero];//�����Ӣ��

	int heroNum = 0;//����Ӣ������

	site HeroPos[MaxHero];//Ӧ��û��
public:
	//ChessShop* chessShop;
    //Player(ChessShop* shop);

	//Ѫ������
	void changeplayerBlood(int hurt);

	////��ȡ�������
	//int getplayerMoney() const;

	////�ı�������
	//void changeplayerMoney(int num);

	////������
	//bool buyplayerExperience();

	////�ж������ȼ�
	//bool changeplayerLevel(int exp=0);

	////������ֻ�ܴӱ�ս������
	//void sellMyChess(Hero* chess);

	////����
	//bool buyMyChess(Hero* chess);

	////�����̵�
	//bool Update();
	Player();

	static Player* create();

	void SetHP(Vec2 pos);

	int GetLv();

	void SetHero(Hero* hero);//�����ϳ�Ӣ�ۣ������ǲ���������

	void HeroInit();//Ӣ�۳�ʼ��

	Hero* GetWarHero();//�����ϳ�Ӣ��

	bool IsDead() {
		return playerIsDead;
	}

	int GetHeroNum();
};


#endif

