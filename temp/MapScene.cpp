#include<iostream>
#include"MapScene.h"
#include"ShopLayer.h"
#include"Hero.h"
#include "ui/CocosGUI.h"
using namespace ui;

using namespace std;

Scene* MapScene::createScene()
{
	return MapScene::create();
}

bool MapScene::init()
{
	//�����ʼ��ʧ��
	if (!Scene::init())
		return false;

	//��ȡ��Ļ��ʾ��С
	auto visibleSize = Director::getInstance()->getVisibleSize();

	/*---------����-----------*/
	// ��ȡ��Ļ�ߴ�
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	// ������Ƭ��ͼ��Ϊ����
	this->background = TMXTiledMap::create("warmap.tmx");
	if (!this->background) {
		return false; // �������ʧ�ܣ��򷵻� false
	}

	// ����ͼ��ӵ�����
	this->addChild(background);

	/*---------����-----------*/
	lastHeroPosition= getStartPosition();

	auto spriteFrameCache = cocos2d::SpriteFrameCache::getInstance();
	for (int i = 1; i < 5; ++i) {
		std::string frameName = "star" + std::to_string(i) + ".png";
		spriteFrameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0, 0, 50, 50)), frameName);
	}

	//����̵�
	this->createShopLayer();

	//----��ʼս����ť-----
	//������ť
	auto startBattleButton = cocos2d::ui::Button::create("play.png", "play1.png", "play2.png");

	// ���ð�ť��λ�á���С������
	startBattleButton->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	startBattleButton->setPosition(cocos2d::Vec2(origin.x, visibleSize.height));

	// ��Ӱ�ť���������
	this->addChild(startBattleButton);

	startBattleButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
			// ��ť����¼�
			//this->startBattle();
		}
		});



	return true;
}

void MapScene::createShopLayer()
{
	auto shopLayer = ShopLayer::create();
	this->addChild(shopLayer);
}

cocos2d::Vec2 MapScene::getStartPosition()
{

	auto objectGroup = background->getObjectGroup("startpoint");  // ��ȡ��Ϊ "start" �Ķ����
	if (objectGroup) {
		auto startObject = objectGroup->getObject("startpoint");  // ��ȡ��Ϊ "start" �Ķ���
		if (!startObject.empty()) {
			float x = startObject["x"].asFloat();
			float y = startObject["y"].asFloat();
			return cocos2d::Vec2(x, y);
		}
	}
	return cocos2d::Vec2::ZERO;  // ����Ҳ������󣬷���������
}

void MapScene::addHeroToMap(Hero* hero)
{
	// ������Ӣ�۵�λ��
	const float offset = 200.0f;  // ����Ӣ�ۼ��ˮƽ���Ϊ50
	cocos2d::Vec2 newPosition = lastHeroPosition + cocos2d::Vec2(offset, 0);
	hero->setPosition(newPosition);

	// �������һ��Ӣ�۵�λ��
	lastHeroPosition = newPosition;

}
