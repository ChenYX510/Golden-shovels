#pragma once
//���Ԥ������Ϊ�˷�ֹ�ظ����������޵ݹ�
//�������ifndef......endif.....

#include "cocos2d.h"
#include"Hero.h"
USING_NS_CC;
class MapScene :public Scene 
{
protected:
    cocos2d::Vec2 lastHeroPosition;  // ��¼���һ��Ӣ�۵�λ��
public:
	//��ͼ
	TMXTiledMap* background;

	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MapScene);//���ڴ���Cocos2d-x��Ϸ�����еĽڵ������Զ������ʵ��

	//�����̵��ʵ��
	void createShopLayer();

	cocos2d::Vec2 getStartPosition();  // �·�������ȡ��ʼλ��

	void addHeroToMap(Hero* hero);


};

