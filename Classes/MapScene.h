#pragma once
//���Ԥ������Ϊ�˷�ֹ�ظ����������޵ݹ�
//�������ifndef......endif.....

#include "cocos2d.h"
#include"Hero.h"
#include"Player.h"
#include "Battle.h"
#include "ShopLayer.h"
USING_NS_CC;
class MapScene :public Scene
{
protected:
	cocos2d::Vec2 lastHeroPosition;  // ��¼���һ��Ӣ�۵�λ��

	Player* player; // �洢�� Player ʵ�������û�ָ��
	ShopLayer* shopLayer;
	Battle* battlelayer;
	TeamManager* teamManager;
	Player* enPlayer;//�з����
	//showHPMP* myHP;  //Ѫ��  
	//showHPMP* enHP;
	bool isStartBattle;
public:
	//��ͼ
	TMXTiledMap* background;

	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MapScene);//���ڴ���Cocos2d-x��Ϸ�����еĽڵ������Զ������ʵ��

	//�����̵��ʵ��
	void createShopLayer(Player* player, TMXTiledMap* background);

	cocos2d::Vec2 getStartPosition();  // �·�������ȡ��ʼλ��

	void addHeroToMap(Hero* hero);

	void Playerinit();

	Player* getCurrentPlayer();

	void addBorder(TMXTiledMap* background);

	void CreateBattle(float t);
	virtual	void update(float dt);
};
