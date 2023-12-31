#include "TeamManager.h"
#include"MapScene.h"
#include"ShopLayer.h"

// ��ʼ����̬��Ա����
TeamManager* TeamManager::_instance = nullptr;

void TeamManager::addOrUpdateHeroToTeam(Hero* hero)
{
	if (hero) {
		bool heroFound = false;
		std::string* newHeroName = static_cast<std::string*>(hero->getUserData());

		for (auto& teamHero : teamHeroes) {
			std::string* teamHeroName = static_cast<std::string*>(teamHero->getUserData());
			if (teamHeroName && newHeroName && *teamHeroName == *newHeroName) {
				// Ӣ�����ڶ����У�ִ����������
				teamHero->upgrade();
				heroFound = true;
				break;
			}
		}

		if (!heroFound) {
			// Ӣ�۲��ڶ����У���ӵ�����
			teamHeroes.push_back(hero);
			hero->setLevel(1);
			hero->updateStarLevel();
			// ��ȡ��ͼ����������
			auto mapScene = dynamic_cast<MapScene*>(Director::getInstance()->getRunningScene());
			if (mapScene) {
				mapScene->addHeroToMap(hero);
				// ��Ӣ����ӵ���ͼ��
				//mapScene->addHeroToMap(selectedHero);
			}
		}
	}
}

TeamManager* TeamManager::getInstance()
{
	if (_instance == nullptr) {
		_instance = new TeamManager();
		// ������Գ�ʼ���������ԣ�������
	}
	return _instance;
}
