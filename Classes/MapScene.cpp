#include<iostream>
#include"MapScene.h"
#include"ShopLayer.h"
#include"Hero.h"
#include"Player.h"
#include"TeamManager.h"
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
    //��ɫ�߿�
    this->addBorder(background);
    /*---------����-----------*/

    lastHeroPosition = getStartPosition();

    auto spriteFrameCache = cocos2d::SpriteFrameCache::getInstance();
    for (int i = 1; i < 5; ++i) {
        std::string frameName = "star" + std::to_string(i) + ".png";
        spriteFrameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0, 0, 50, 50)), frameName);
    }
    //������
    //player = new Player(100);
    //this->addChild(player->getSmallHero(), 10);
    Playerinit();//��ʼ����Ҽ�Ѫ��
    isStartBattle = 0;
    //����̵�
    this->createShopLayer(this->player, this->background);

    ////----��ʼս����ť-----
    ////������ť
    //auto startBattleButton = cocos2d::ui::Button::create("play.png", "play1.png", "play2.png");

    //// ���ð�ť��λ�á���С������
    //startBattleButton->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    //startBattleButton->setPosition(cocos2d::Vec2(origin.x, visibleSize.height));

    //// ��Ӱ�ť���������
    //this->addChild(startBattleButton);

    //startBattleButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
    //    if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
    //        // ��ť����¼�
    //        TeamManager* teamManager = TeamManager::getInstance();
    //        teamManager->addHeroToPlayer(this->player);
    //        isStartBattle = 1;

    //    }
    //    });
    this->CreateBattle(0);//����ս����
    teamManager = TeamManager::getInstance();
    this->scheduleUpdate();

    return true;
}

void MapScene::createShopLayer(Player*player, TMXTiledMap* background)
{
	shopLayer = ShopLayer::createWithPlayer(player,background);
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
	const float offset = 150.0f;  // Ӣ�ۼ��ˮƽ���
	cocos2d::Vec2 newPosition = lastHeroPosition + cocos2d::Vec2(offset, 0);
	hero->setPosition(newPosition);

	// �������һ��Ӣ�۵�λ��
	lastHeroPosition = newPosition;

}

void MapScene::addBorder(TMXTiledMap* background)
{
	auto movableLayer = background->getLayer("move");
	movableLayer->setVisible(1);
	if (!movableLayer)//�ж��Ƿ���ڸ�ͼ��
		return;
	Size mapSize = background->getMapSize();
	Size tileSize = background->getTileSize();

	// ����һ���µ�ͼ��������Ӻ�ɫ�߿�
	auto borderLayer = Layer::create();
	this->addChild(borderLayer);

	for (int x = 0; x < mapSize.width; x++) {
		for (int y = 0; y < mapSize.height; y++) {
			int tileGid = movableLayer->getTileGIDAt(Vec2(x, y));
			if (tileGid > 0) {
				// ��ȡͼ���λ��
					Vec2 tilePos = movableLayer->getPositionAt(Vec2(x, y));
				// ����һ����ɫ�߿�ľ���
				Sprite* redBorder = Sprite::create("border.png");
				redBorder->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
				redBorder->setScale(0.12);
				// ���ú�ɫ�߿��λ��Ϊͼ�������
				redBorder->setPosition(tilePos);
				// ����ɫ�߿���ӵ�ͼ����
				borderLayer->addChild(redBorder,1);
			}
		}
	}
}

void MapScene::Playerinit()
{
	player = new Player(100);
	this->addChild(player);
	player->SetSmallHero(Vec2(400, 400),true);
    //player->changeplayerBlood(50);
	enPlayer = new Player(100);
	this->addChild(enPlayer);
	enPlayer->SetSmallHero(Vec2(1200, 700),false);
}

Player* MapScene::getCurrentPlayer() {
	return  player;
}

void MapScene::CreateBattle(float t) {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    heroInformation* testEnemyInfo = new heroInformation;
    testEnemyInfo->HP = 550;
    testEnemyInfo->MP = 60;
    testEnemyInfo->attack = 60;
    testEnemyInfo->atkspeed = 3;
    testEnemyInfo->defence = 45;
    testEnemyInfo->atkrange = 300;
    testEnemyInfo->movespeed = 80;
    testEnemyInfo->attackSpeed = 160;

    Hero *testEnemy = Hero::create();//����һ��Ӣ��
    testEnemy->SetBaseInfo(testEnemyInfo, "En-Taric", Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 300));//����Ӣ����Ϣ
    //this->addChild(testEnemy);//�ӵ�����
    //testEnemy->SetHeroOn();//��Ӣ���ϳ�
    enPlayer->SetHero(testEnemy);

    heroInformation* testEnemyInfo2 = new heroInformation;
    testEnemyInfo2->HP = 550;
    testEnemyInfo2->MP = 60;
    testEnemyInfo2->attack = 70;
    testEnemyInfo2->atkspeed = 1.2;
    testEnemyInfo2->defence = 25;
    testEnemyInfo2->atkrange = 300;
    testEnemyInfo2->movespeed = 80;
    testEnemyInfo2->attackSpeed = 160;

    Hero* testEnemy2 = Hero::create();//����һ��Ӣ��
    testEnemy2->SetBaseInfo(testEnemyInfo2, "En-Anny", Vec2(visibleSize.width / 2 + origin.x - 200, visibleSize.height / 2 + origin.y + 300));//����Ӣ����Ϣ
    //this->addChild(testEnemy2);//�ӵ�����
    //testEnemy2->SetHeroOn();//��Ӣ���ϳ�
    enPlayer->SetHero(testEnemy2);

    heroInformation* testEnemyInfo3 = new heroInformation;
    testEnemyInfo3->HP = 550;
    testEnemyInfo3->MP = 60;
    testEnemyInfo3->attack = 70;
    testEnemyInfo3->atkspeed = 1.2;
    testEnemyInfo3->defence = 25;
    testEnemyInfo3->atkrange = 300;
    testEnemyInfo3->movespeed = 80;
    testEnemyInfo3->attackSpeed = 160;

    Hero* testEnemy3 = Hero::create();//����һ��Ӣ��
    testEnemy3->SetBaseInfo(testEnemyInfo3, "En-Alice", Vec2(visibleSize.width / 2 + origin.x + 200, visibleSize.height / 2 + origin.y + 180));//����Ӣ����Ϣ
    enPlayer->SetHero(testEnemy3);

    heroInformation* testEnemyInfo4 = new heroInformation;
    testEnemyInfo4->HP = 850;
    testEnemyInfo4->MP = 60;
    testEnemyInfo4->attack = 70;
    testEnemyInfo4->atkspeed = 1.2;
    testEnemyInfo4->defence = 25;
    testEnemyInfo4->atkrange = 80;
    testEnemyInfo4->movespeed = 80;
    testEnemyInfo4->attackSpeed = 160;

    Hero* testEnemy4 = Hero::create();//����һ��Ӣ��
    testEnemy4->SetBaseInfo(testEnemyInfo4, "En-Kennen", Vec2(visibleSize.width / 2 + origin.x + 100, visibleSize.height / 2 + origin.y + 80));//����Ӣ����Ϣ
    enPlayer->SetHero(testEnemy4);

    heroInformation* testEnemyInfo5 = new heroInformation;
    testEnemyInfo5->HP = 850;
    testEnemyInfo5->MP = 60;
    testEnemyInfo5->attack = 70;
    testEnemyInfo5->atkspeed = 1.2;
    testEnemyInfo5->defence = 25;
    testEnemyInfo5->atkrange = 80;
    testEnemyInfo5->movespeed = 80;
    testEnemyInfo5->attackSpeed = 160;

    Hero* testEnemy5 = Hero::create();//����һ��Ӣ��
    testEnemy5->SetBaseInfo(testEnemyInfo5, "En-Ali", Vec2(visibleSize.width / 2 + origin.x - 100, visibleSize.height / 2 + origin.y + 80));//����Ӣ����Ϣ
    enPlayer->SetHero(testEnemy5);

    heroInformation* testEnemyInfo6 = new heroInformation;
    testEnemyInfo6->HP = 850;
    testEnemyInfo6->MP = 60;
    testEnemyInfo6->attack = 70;
    testEnemyInfo6->atkspeed = 1.2;
    testEnemyInfo6->defence = 25;
    testEnemyInfo6->atkrange = 80;
    testEnemyInfo6->movespeed = 80;
    testEnemyInfo6->attackSpeed = 160;

    Hero* testEnemy6 = Hero::create();//����һ��Ӣ��
    testEnemy6->SetBaseInfo(testEnemyInfo6, "En-Chuishi", Vec2(visibleSize.width / 2 + origin.x + 50, visibleSize.height / 2 + origin.y +60));//����Ӣ����Ϣ
    enPlayer->SetHero(testEnemy6);



    //heroInformation* testInfo = new heroInformation;
    //testInfo->HP = 400;
    //testInfo->MP = 60;
    //testInfo->attack = 65;
    //testInfo->atkspeed = 0.9;
    //testInfo->defence = 25;
    //testInfo->atkrange = 350;
    //testInfo->movespeed = 80;
    //testInfo->attackSpeed = 160;

    //Hero* testHero = Hero::create();//����һ��Ӣ��
    //testHero->SetBaseInfo(testInfo, "Erlius", Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 300));//����Ӣ����Ϣ
    ////this->addChild(testHero);//�ӵ�����
    ////testHero->SetHeroOn();//��Ӣ���ϳ�
    //Player->SetHero(testHero);

    //heroInformation* testInfo2 = new heroInformation;
    //testInfo2->HP = 850;
    //testInfo2->MP = 60;
    //testInfo2->attack = 50;
    //testInfo2->atkspeed = 2;
    //testInfo2->defence = 35;
    //testInfo2->atkrange = 80;
    //testInfo2->movespeed = 80;
    //testInfo2->attackSpeed = 160;

    //Hero* testHero2 = Hero::create();//����һ��Ӣ��
    //testHero2->SetBaseInfo(testInfo2, "Kuqi", Vec2(visibleSize.width / 2 + origin.x - 100, visibleSize.height / 2 + origin.y - 100));//����Ӣ����Ϣ
    //myPlayer->SetHero(testHero2);

    //heroInformation* testInfo3 = new heroInformation;
    //testInfo3->HP = 400;
    //testInfo3->MP = 60;
    //testInfo3->attack = 80;
    //testInfo3->atkspeed = 0.8;
    //testInfo3->defence = 35;
    //testInfo3->atkrange = 280;
    //testInfo3->movespeed = 80;
    //testInfo3->attackSpeed = 160;

    //Hero* testHero3 = Hero::create();//����һ��Ӣ��
    //testHero3->SetBaseInfo(testInfo3, "Kasia", Vec2(visibleSize.width / 2 + origin.x - 200, visibleSize.height / 2 + origin.y - 300));//����Ӣ����Ϣ
    //myPlayer->SetHero(testHero3);

    //heroInformation* testInfo4 = new heroInformation;
    //testInfo4->HP = 700;
    //testInfo4->MP = 60;
    //testInfo4->attack = 60;
    //testInfo4->atkspeed = 1.5;
    //testInfo4->defence = 35;
    //testInfo4->atkrange = 200;
    //testInfo4->movespeed = 80;
    //testInfo4->attackSpeed = 160;

    //Hero* testHero4 = Hero::create();//����һ��Ӣ��
    //testHero4->SetBaseInfo(testInfo4, "Lilia", Vec2(visibleSize.width / 2 + origin.x + 100, visibleSize.height / 2 + origin.y - 200));//����Ӣ����Ϣ
    //myPlayer->SetHero(testHero4);


    /////////////
    // �����ǲ���Ӣ�۵�����
    ////////////

    battlelayer = Battle::create();
    this->addChild(battlelayer);
    battlelayer->SetPlayer(player, enPlayer);//����˫�����

    /*auto startItem = MenuItemImage::create("start.png",
        "start2.png", CC_CALLBACK_0(Battle::Start, battlelayer));
    startItem->setScale(0.8);
    auto menu = Menu::create(startItem, NULL);
    menu->setPosition(Vec2(visibleSize.width / 2 + origin.x, 80));
    this->addChild(menu, 5);*/

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
            teamManager->addHeroToPlayer(this->player);
            isStartBattle = 1;
            battlelayer->Start();
        }
        });

    //this->scheduleOnce(schedule_selector(Round::callback), 3);
  //this->addChild(battlelayer, 3);
  //battlelayer->Start();
}

void MapScene::update(float dt) {
    if (battlelayer->IsEnd()) {
        //this->unscheduleUpdate();
        shopLayer->showAllHero(1);
        //player->Restart();
    }
    else {
        if(isStartBattle)
        shopLayer->showAllHero(0);
    }
    if (player->IsDead()) {
        auto lose = Scene::create();
        auto label1 = Label::createWithTTF("LOSE", "fonts/Marker Felt.ttf", 140);
        label1->setPosition(Vec2(960, 540));
        lose->addChild(label1);
        Director::getInstance()->pushScene(lose);

        this->unscheduleUpdate();
    }
    else if (enPlayer->IsDead()) {
        auto win = Scene::create();
        auto label1 = Label::createWithTTF("WIN", "fonts/Marker Felt.ttf", 140);
        label1->setPosition(Vec2(960, 540));
        win->addChild(label1);
        Director::getInstance()->pushScene(win);

        this->unscheduleUpdate();
    }

}


