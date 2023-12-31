#pragma once
#include"card.h"
#include"cocos2d.h"
using namespace cocos2d;
#include<vector>

class ShopLayer : public cocos2d::Layer {
public:
    //����
    vector<Chess*> chessPool;

    //����
        //��ʼ������
    void InitChessPool();

    //�Ƴ�����
    Chess* DrawChess();

    //���뿨��
    void AddChess(Chess* chess);

    // ���ҿ���˳��
    void ShufflePool();
    static ShopLayer* createLayer();

    //������������
    vector<Chess*> displayFiveChess;
    //�����̵���
    void getFiveChess();

    //�������ӣ��������ý��ֵ
    int SellChess(Chess* chess);

    //������,��Ҽ���
    bool BuyChess(Chess* chess, int& money, int maxChess, int nowChess);

    virtual bool init()override;
    CREATE_FUNC(ShopLayer);

    static Sprite* shopBackground;

    void createShopBackground();

    void createItemPlace();
    void displayCards();//չʾ����
    void createRefreshButton();//ˢ�°�ť
    void refreshShop(Ref* pSender);
    void displayMoney();
    //�ص�����
    void createMoneyButton();//������
    void addCardTouchListener(Card* card);

    void createUpgradeButton();
    void upgradeButtonClickCallback(cocos2d::Ref* sender);
    void onUpgrade();
    void changeMoney(int addmoney);
    void displayLevelLabel();
    // ��ӻص��ӿ�
    class UpgradeCallback {
    public:
        virtual void onUpgrade() = 0;
    };

    // �����ĺ����������������ص�
    void setUpgradeCallback(UpgradeCallback* callback);

private:
    int moneyCoin = 50;
    int playerLevel;  // ģ����ҵȼ�
    //��������һ����Ҫ���پ���
    int playerNeedExperience;
    //��Ҿ���
    int playerExperience;
    cocos2d::Label* levelLabel;  // ��ʾ��ǰ�ȼ��ı�ǩ
    Vector<Card*> currentCards; // �洢���Ƶ�����
   
};