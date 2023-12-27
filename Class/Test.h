#pragma once
#ifndef __TEST_H__
#define __TEST_H__

#include "cocos2d.h"
#include "Hero.h"
#include "showHPMP.h"
#include "Battle.h"
USING_NS_CC;

class Test : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();//������Ϸ����

    virtual bool init();//���캯������ʼ��
    CC_CONSTRUCTOR_ACCESS:
    // implement the "static create()" method manually
    CREATE_FUNC(Test);
    Battle* battleLayer = Battle::create();
    void callback(Ref* data);

    Player* myPlayer = Player::create();
    Player* enPlayer = Player::create();

};

#endif // __HELLOWORLD_SCENE_H__
