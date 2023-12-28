#include "Round.h"

Scene* Round::createScene()
{
	return Round::create();
}

bool Round::init() {
	if (!Scene::init())
		return false;
	Sprite* battleScene = Sprite::create("battleScene.png");
	battleScene->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));//���м�
	this->addChild(battleScene);
	this->PlayerInit();//��ʼ�����
	this->CreateBattle(0);//����ս����
	this->scheduleUpdate();
	return true;
}

void Round::PlayerInit() {
	myPlayer = Player::create();
	this->addChild(myPlayer);
	myPlayer->SetHP(Vec2(200, 200));
	enPlayer = Player::create();
	this->addChild(enPlayer);
	enPlayer->SetHP(Vec2(1600, 800));
}

void Round::CreateBattle(float t) {
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

    heroInformation* testInfo = new heroInformation;
    testInfo->HP = 400;
    testInfo->MP = 60;
    testInfo->attack = 65;
    testInfo->atkspeed = 0.9;
    testInfo->defence = 25;
    testInfo->atkrange = 350;
    testInfo->movespeed = 80;
    testInfo->attackSpeed = 160;

    Hero* testHero = Hero::create();//����һ��Ӣ��
    testHero->SetBaseInfo(testInfo, "Erlius", Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 300));//����Ӣ����Ϣ
    //this->addChild(testHero);//�ӵ�����
    //testHero->SetHeroOn();//��Ӣ���ϳ�
    myPlayer->SetHero(testHero);

    heroInformation* testInfo2 = new heroInformation;
    testInfo2->HP = 850;
    testInfo2->MP = 60;
    testInfo2->attack = 50;
    testInfo2->atkspeed = 2;
    testInfo2->defence = 35;
    testInfo2->atkrange = 80;
    testInfo2->movespeed = 80;
    testInfo2->attackSpeed = 160;

    Hero* testHero2 = Hero::create();//����һ��Ӣ��
    testHero2->SetBaseInfo(testInfo2, "Kuqi", Vec2(visibleSize.width / 2 + origin.x - 100, visibleSize.height / 2 + origin.y - 100));//����Ӣ����Ϣ
    myPlayer->SetHero(testHero2);

    heroInformation* testInfo3 = new heroInformation;
    testInfo3->HP = 400;
    testInfo3->MP = 60;
    testInfo3->attack = 80;
    testInfo3->atkspeed = 0.8;
    testInfo3->defence = 35;
    testInfo3->atkrange = 280;
    testInfo3->movespeed = 80;
    testInfo3->attackSpeed = 160;

    Hero* testHero3 = Hero::create();//����һ��Ӣ��
    testHero3->SetBaseInfo(testInfo3, "Kasia", Vec2(visibleSize.width / 2 + origin.x - 200, visibleSize.height / 2 + origin.y - 300));//����Ӣ����Ϣ
    myPlayer->SetHero(testHero3);

    heroInformation* testInfo4 = new heroInformation;
    testInfo4->HP = 700;
    testInfo4->MP = 60;
    testInfo4->attack = 60;
    testInfo4->atkspeed = 1.5;
    testInfo4->defence = 35;
    testInfo4->atkrange = 200;
    testInfo4->movespeed = 80;
    testInfo4->attackSpeed = 160;

    Hero* testHero4 = Hero::create();//����һ��Ӣ��
    testHero4->SetBaseInfo(testInfo4, "Lilia", Vec2(visibleSize.width / 2 + origin.x + 100, visibleSize.height / 2 + origin.y - 200));//����Ӣ����Ϣ
    myPlayer->SetHero(testHero4);


    /////////////
    // �����ǲ���Ӣ�۵�����
    ////////////

    battlelayer = Battle::create();
	this->addChild(battlelayer);
	  battlelayer->SetPlayer(myPlayer, enPlayer);//����˫�����
   
	auto startItem = MenuItemImage::create("start.png",
		"start2.png",CC_CALLBACK_0(Battle::Start, battlelayer));
	startItem->setScale(0.8);
	auto menu = Menu::create(startItem, NULL);
	menu->setPosition(Vec2(visibleSize.width / 2 + origin.x, 80));
	this->addChild(menu, 5);

      //this->scheduleOnce(schedule_selector(Round::callback), 3);
    //this->addChild(battlelayer, 3);
    //battlelayer->Start();
}

void Round::callback(float t) {
    battlelayer = Battle::create();
    battlelayer->SetPlayer(myPlayer, enPlayer);
    this->addChild(battlelayer,5);
    //battlelayer->Start();
    auto startItem = MenuItemImage::create("start.png",
        "start2.png", CC_CALLBACK_0(Battle::Start, battlelayer));
    startItem->setScale(0.25);
    auto menu = Menu::create(startItem, NULL);
    menu->setPosition(Vec2(500, 170));
    this->addChild(menu, 5);
}

void Round::update(float dt) {
    /*if (battlelayer->IsEnd()) {
        this->unscheduleUpdate();
    }*/
    if (myPlayer->IsDead()) {
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


