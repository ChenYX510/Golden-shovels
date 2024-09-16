#include "ShopLayer.h"
#include"HeroData.h"
#include"Hero.h"
#include"Information.h"
#include"Player.h"
#include"TeamManager.h"
#include"MapScene.h"
#include<vector>
#include<algorithm>
#include "cocos/ui/UIButton.h"  // ����UIButtonͷ�ļ�
#include "cocos/ui/UIWidget.h"  // ����UIWidgetͷ�ļ�

const int DisplayedCardNum = 5;

bool ShopLayer::init()
{
    if (!Layer::init()) {
        return false;
    }

    /*--------------��ʼ���̵����----------------*/
        //�����̵걳��
    this->createShopBackground();

	//��ɫλ����
	this->createItemPlace();

	this->createRefreshButton();

	this->createGoldIcon();
    /*--------------��ʼ���̵����----------------*/
	this->displayCards();
	return true;
}

void ShopLayer::createShopBackground()
{
	//��ȡ��Ļ��ʾ��С
	auto visibleSize = Director::getInstance()->getVisibleSize();
	shopBackground = Sprite::create("shopbackground.png");
	// �����̵걳��������Ԫ��
	Size originalSize = shopBackground->getContentSize();//��ȡԭʼͼƬ��С
	// ����ê��Ϊ���е�
	shopBackground->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	// �����µĿ�Ⱥ͸߶�
	float newWidth = visibleSize.width; // ռ��������Ļ���
	float newHeight = visibleSize.height / 4; // ռ����Ļ�߶ȵ�1/4
	// Ӧ������
	shopBackground->setScale(0.9, 0.9);
	// ����λ�ã�ʹ�̵�λ����Ļ�ײ�
	shopBackground->setPosition(Vec2(newWidth / 2, originalSize.height / 8));
	this->addChild(shopBackground);
}

void ShopLayer::createItemPlace()
{
	//��ȡ��Ļ��ʾ��С
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// �����һ�ű���ͼ����ʼλ��
	float startX = 750.0f;
	float startY = 0;
	float itemWidth = 118.0f; // ����ÿ�ű���ͼ�Ŀ���� 100
	float itemHeight = 118.0f; // ����ÿ�ű���ͼ�ĸ߶��� 100
	float itemSpacing = 5.0f;//���
	// ѭ�������ͷ������ű���ͼ
	for (int i = 0; i < 4; ++i) {
		auto itemBackground = Sprite::create("position.png");
		itemBackground->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		//itemBackground->setScale(0.6, 0.6);
		itemBackground->setContentSize(Size(itemWidth, itemHeight)); // ���ñ���ͼ�ߴ�
		//startY = (shopBackground->getContentSize().height/2);
		//float itemWidth = itemBackground->getContentSize().width;
		itemBackground->setPosition(startX + i * (itemWidth + itemSpacing), startY);
		this->addChild(itemBackground);
	}
}

vector<int>  ShopLayer::selectRandomHeroes(int count)
{
	std::vector<int> tags = {1,2,3,4 };
	std::random_shuffle(tags.begin(), tags.end());
	if (count > tags.size()) 
		count = tags.size();
	return std::vector<int>(tags.begin(), tags.begin() + count);
}

void ShopLayer::displayCards()
{
	Vec2 shopbg = shopBackground->getPosition();
	float cardSpacing = 12.0f;//���
	float startX = 750.0f;//��ʼ����ֵ
	float itemWidth = 110.0f; // ����ÿ�ű���ͼ�Ŀ��
	float itemHeight = 110.0f; // ����ÿ�ű���ͼ�ĸ߶�
/*-----------------------Ԥ��ֵ------------------------*/

	int count = DisplayedCardNum - 1;
	std::vector<int> heroTags = selectRandomHeroes(DisplayedCardNum - 1);

	for (int i = 0; i < heroTags.size(); ++i) {
		int tag = heroTags[i];
		std::string heroName = Information::getNameByTag(tag);
		std::string heroImagePath = Information::getHeroPathByTag(tag);  

		Hero* heroCard = Hero::create(heroImagePath);  // ʹ����ȷ��ͼƬ·��
		if (!heroCard) {
			continue;
		}

		heroCard->setContentSize(Size(itemWidth, itemHeight));
		float posX = startX + i * (itemWidth + cardSpacing);
		float posY = 60;
		heroCard->setPosition(Vec2(posX, posY));
		heroCard->setUserData(new std::string(heroName));  // �洢Ӣ������

		this->addTouchListenerToCard(heroCard, tag);
		this->addChild(heroCard);
		heroesInShop.push_back(heroCard);
		
	}
	//this->createRefreshButton();  // ���ˢ�°�ť
}


void ShopLayer::addTouchListenerToCard(Hero* heroCard,int tag) {
	// Ϊ������Ӵ����¼����������߼�
	auto touchListener = EventListenerTouchOneByOne::create();

	touchListener->onTouchBegan = [heroCard, this, tag](Touch* touch, Event* event) -> bool {
		if (heroCard->getBoundingBox().containsPoint(touch->getLocation())) {
			this->onCardSelected(tag);
			return true;
		}
		return false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, heroCard);//Ϊ������Ӽ�����
}

void ShopLayer::onCardSelected(int heroTag) {
	//��ȡ��Ļ��ʾ��С
	auto visibleSize = Director::getInstance()->getVisibleSize();

	Player* player = Player::getInstance();
	TeamManager* teamManager = TeamManager::getInstance();
	const int HeroCost = 10;  // ����ÿ��Ӣ�۵ĳɱ���10���

	if (player->hasEnoughGold(HeroCost)) {
		player->spendGold(HeroCost);  // ������ҵĽ��

		// ���½��������ǩ����ʾ����
		int currentGold = player->getGold();
		goldLabel->setString(StringUtils::format("%d", currentGold));

		// ���Ѵ�����Ӣ�����ҵ���Ӧ��Ӣ��ʵ��
		Hero* selectedHero = nullptr;
		for (auto& hero : heroesInShop) {
			std::string* heroName = static_cast<std::string*>(hero->getUserData());
			if (heroName && *heroName == Information::getNameByTag(heroTag)) {
				selectedHero = hero;
				break;
			}
		}//�����̵��е�Ӣ�ۣ��ҵ���tag��Ӧ��Ӣ�ۼ������

		if (selectedHero) {
			teamManager->addOrUpdateHeroToTeam(selectedHero);  // ��Ӣ����ӵ�����
			
			removeHeroFromShop(selectedHero);
			
			
		}

	}
	else {
		// ��ʾһ����ʾ��Ϣ
		auto label = Label::createWithSystemFont("No enough money!", "arial", 50);
		label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		this->addChild(label);
		label->setColor(Color3B::RED);
		label->runAction(Sequence::create(
			DelayTime::create(2),  // �ӳ�2��
			RemoveSelf::create(),   // �Ƴ�����
			nullptr
		));
	}
	 
}

void ShopLayer::removeHeroFromShop(Hero* hero) {
	if (hero) {
		//hero->removeFromParent();  // �Ӳ����Ƴ�Ӣ�ۿ��ƣ��Ῠ��
		heroesInShop.erase(std::remove(heroesInShop.begin(), heroesInShop.end(), hero), heroesInShop.end());  // ���������Ƴ�
	}
}

void ShopLayer::createRefreshButton() {
	//��ȡ��Ļ��ʾ��С
	auto visibleSize = Director::getInstance()->getVisibleSize();

	Size shopbgSize = shopBackground->getContentSize();
	float startX = visibleSize.width / 2 - shopbgSize.width / 2;

	auto refreshButton = cocos2d::ui::Button::create("refresh.png", "refresh.png");

	float scale = 0.18f; // ��С��ԭʼ��С��
	refreshButton->setScale(scale);

	Size buttonSize = refreshButton->getContentSize();//ע�⣺�õ��Ĵ�С��û������ǰ�Ĵ�С��

	// ���ð�ť��λ��Ϊ�̵����½�
	float posX = (visibleSize.width / 2 - shopbgSize.width / 2) + 30.0f;
	float posY = buttonSize.height * scale / 2-10;
	refreshButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	refreshButton->setPosition(Vec2(posX, posY));

	refreshButton->addTouchEventListener([this](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
			this->refreshShopCards();  // ����ˢ���̵꿨�Ƶķ���
		}
		});
	this->addChild(refreshButton);
}

void ShopLayer::refreshShopCards() {
	//��ȡ��Ļ��ʾ��С
	auto visibleSize = Director::getInstance()->getVisibleSize();

	Player* player = Player::getInstance();
	TeamManager* teamManager = TeamManager::getInstance();
	for (auto& hero : heroesInShop) {
		hero->removeFromParent();  // �Ӳ����Ƴ�Ӣ�ۿ���
	}
	
	const int Cost = 20;
	if (player->hasEnoughGold(Cost)) {
		player->spendGold(Cost);  // ������ҵĽ��

		// ���½��������ǩ����ʾ����
		int currentGold = player->getGold();
		goldLabel->setString(StringUtils::format("%d", currentGold));
		heroesInShop.clear();  // �������
		displayCards();  // ����չʾ�����ȡ�Ľ�ɫ
	}
	else {
		// ��ʾһ����ʾ��Ϣ
		auto label = Label::createWithSystemFont("No enough money!", "arial", 50);
		label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		this->addChild(label);
		label->setColor(Color3B::RED);
		label->runAction(Sequence::create(
			DelayTime::create(2),  // �ӳ�2��
			RemoveSelf::create(),   // �Ƴ�����
			nullptr
		));
	}
}

void ShopLayer::createGoldIcon() {

	/*------------------���ͼ-------------------------------------------------*/

	//��ȡ��Ļ��ʾ��С
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Size shopbgSize = shopBackground->getContentSize();
	float startX = visibleSize.width / 2 - shopbgSize.width / 2;
	auto gold = Sprite::create("money.png");
	float scale = 0.3f; // ��С��ԭʼ��С��
	gold->setScale(scale);
	gold->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	gold->setPosition(Vec2(startX + gold->getContentSize().width / 2 - 10.0f, 100.0f));
	this->addChild(gold);
	/*------------------���ͼ-------------------------------------------------*/

	/*-----------Ǯ��-------------------------------*/
	 // ��ȡPlayerʵ��
	auto player = Player::getInstance();

	int currentGold = player->getGold();
	// ������ǩ������ʾǮ��
	goldLabel = Label::createWithSystemFont(StringUtils::format("%d", currentGold), "MarkerFelt.ttf", 40);
	goldLabel->setColor(Color3B::RED);
	// ���ñ�ǩλ�ã��������ǽ������ͼ����Ҳࣩ
	goldLabel->setPosition(Vec2(startX + gold->getContentSize().width/1.5, 100.0f));

	// ����ǩ��Ϊ�ӽڵ���ӵ�����
	this->addChild(goldLabel);
	/*-----------Ǯ��-------------------------------*/

}