#pragma once
//���Ԥ������Ϊ�˷�ֹ�ظ����������޵ݹ�
//�������ifndef......endif.....

#include "cocos2d.h"
#include "Hero.h"  // ���� Hero �ඨ��
#include"HeroData.h"
#include <algorithm> 
#include <vector> 
#include"Information.h"
USING_NS_CC;


class ShopLayer:public Layer
{
protected:
	Sprite* shopBackground;
	std::vector<Hero*> heroesInShop;  // �̵��е�Ӣ���б�
   const  std::vector<HeroData> allHeroes = {
		{"hero1","hero1.png"},
		{"hero2","hero2.png"},
		{"hero3","hero3.png"},
		{"hero4","hero4.png"}
	};

   Label* goldLabel;
public:
	CREATE_FUNC(ShopLayer);

	virtual bool init() override;  // ��ʼ������
	void createShopBackground();//����
	void createItemPlace();//��ɫλ
	vector<int>  selectRandomHeroes(int count);//���ѡ�����
	void displayCards();
	void addTouchListenerToCard(Hero* heroCard,int tag);
	void onCardSelected(int heroTag);
	void removeHeroFromShop(Hero* hero);
	void createRefreshButton();
	void refreshShopCards();
	void createGoldIcon();
	void showMessage(const std::string& message);
	//չʾ���Ƶķ���
};