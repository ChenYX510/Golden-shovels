#pragma once
#include "cocos2d.h"
#include"Hero.h"
class TeamManager {
public:
    std::vector<Hero*>teamHeroes;//���Ӣ�۵Ķ��飬һ���ǽ��̵��е�Ӣ��ת�ƹ���
    void addOrUpdateHeroToTeam(Hero* hero);

    static TeamManager* getInstance();  // ��ȡ���������ʵ���ķ���

   // Hero* findHeroByTag(int heroTag);  // ���ݱ�ǩ����Ӣ��

    // ... ������������� ...
private:
    static TeamManager* _instance; // ��̬ʵ��ָ��

    
};