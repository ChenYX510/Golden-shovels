#pragma once
#include "cocos2d.h"
class Player {
public:
    

    

    static Player* getInstance();  // ��ȡ���ʵ���ķ���

    Player();

    ~Player();

    bool hasEnoughGold(int amount);

    void spendGold(int amount);
    int  getGold();
private:
    static Player* _instance; // ��̬ʵ��ָ��
    int gold;  // ��ҵĽ������
    // ... ����������� ...
};