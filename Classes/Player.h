#pragma once
#include "cocos2d.h"
#include <vector>
#include "Hero.h"
#include "SmallHero.h"

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

class Player :public Sprite
{
public:
    //static Player* getInstance();  // ��ȡ���ʵ���ķ���

    Player(int initialGold);

    ~Player();

    bool hasEnoughGold(int amount);

    void spendGold(int amount);
    int  getGold();

    //Ѫ������
    void changeplayerBlood(int hurt);

    void SetSmallHero(Vec2 pos, bool enabled);//ԭSetHP

    int GetLv();

    void SetHero(Hero* hero);//(�з���)�����ϳ�Ӣ�ۣ������ǲ���������

    void HeroInit();//Ӣ�۳�ʼ��

    Hero* GetWarHero();//�����ϳ�Ӣ��

    bool IsDead() {
        return playerIsDead;
    }

    int GetHeroNum();

    bool addHeroToWar(Hero& hero,int num);

    int GetplayerExperience();

    void SetplayerExperience(int x);

    int GetplayerNeedExperience();

    void SetplayerNeedExperience(int x);

    int GetplayerLevel();

    void SetplayerLevel(int x);

    SmallHero* getSmallHero();

    void Restart();

private:
    //static Player* _instance; // ��̬ʵ��ָ��
    int gold;  // ��ҵĽ������
    // ... ����������� ...

    //��������
    bool playerIsDead;

    //���Ѫ��
    int playerBlood;


    //��ҵȼ�
    int playerLevel;

    //��������һ����Ҫ���پ���
    int playerNeedExperience;
    //��Ҿ���
    int playerExperience;

    SmallHero* smallHero;//ССӢ�۵�Ѫ��ת�Ƶ�����

    //showHPMP* myHP;//ССӢ�۵�Ѫ��

    Hero chessWarPlayer[MaxHero];//�����Ӣ��

    int heroNum = 0;//����Ӣ������


};