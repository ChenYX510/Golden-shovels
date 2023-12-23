#pragma once
#include"card.h"
#include"cocos2d.h"
using namespace cocos2d;
#include<vector>

class ShopLayer : public cocos2d::Layer {
public:
    static ShopLayer* createLayer();
    virtual bool init()override;
    CREATE_FUNC(ShopLayer);

    static Sprite* shopBackground;

    void createShopBackground();

    void createItemPlace();
    void displayCards();//չʾ����
    void createRefreshButton();//ˢ�°�ť
    void refreshShop(Ref* pSender);//�ص�����
    void createMoneyButton();//������
    void addCardTouchListener(Card* card);

private:
    Vector<Card*> currentCards; // �洢���Ƶ�����
   
};