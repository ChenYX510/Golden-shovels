#include "Player.h"

// ��ʼ����̬��Ա����
//Player* Player::_instance = nullptr;


// ���캯��
Player::Player(int initialGold) : gold(initialGold) {
	// ��ʼ��������Ա����
	playerLevel = 1;
	playerNeedExperience = 4;
	playerExperience = 0;
	playerIsDead = 0;
	playerBlood = 20;
	//smallHero = SmallHero::create();
	//smallHero->SetBaseInfo("SmallHero.png", Vec2(400, 400));
}

void Player::SetSmallHero(Vec2 pos,bool enabled) {
	//ССӢ�۵Ĵ���ת������
	smallHero = SmallHero::create();
	smallHero->SetBaseInfo("SmallHero.png", pos, enabled);
	this->getParent()->addChild(smallHero, 2);
	
}

Player::~Player() {
	smallHero->removeFromParentAndCleanup(true);
	// ������Դ������еĻ�
}

bool Player:: hasEnoughGold(int amount) {
	return gold >= amount;  // ������Ƿ��㹻
}


void Player::spendGold(int amount) {
	if (gold >= amount) {
		gold -= amount;  // ���ٽ��
	}
}

int Player::getGold()
{
	return gold;
}

int Player::GetHeroNum()
{
	return heroNum;
}

bool Player::addHeroToWar(Hero& hero,int num)
{
	if (num > playerLevel)
		return 0;
	else {
		chessWarPlayer[heroNum].SetHeroDataByTag(hero.getTag(), hero.GetHeroPos());
		chessWarPlayer[heroNum].SetOn(1);
		heroNum++;
		return true;
	}
	//for (int i = 0; i < MaxHero; i++) {
	//	//chessWarPlayer[i] = *Hero::create();
	//	//CC_SAFE_DELETE(chessWarPlayer);
	//}
	//for (int i = 0; i < num; ++i) {
	//	
	//	//if (chessWarPlayer[i].isEmpty()) { // ʹ�� isEmpty �����ж�
	//		//chessWarPlayer[i] = hero; // ���λ�ÿ��У�����Ӣ��
	//		//chessWarPlayer[i].setId(3);
	//		chessWarPlayer[i].SetHeroDataByTag(hero.getTag(), hero.GetHeroPos());
	//		chessWarPlayer[i].SetOn(1);
	//		heroNum++;
	//		return true;
	//	//}
	//}
	//return false; // û�п�λ
}

int Player::GetplayerExperience()
{
	return playerExperience;
}

void Player::SetplayerExperience(int x)
{
	playerExperience = x;
}

int Player::GetplayerNeedExperience()
{
	return playerNeedExperience;
}

void Player::SetplayerNeedExperience(int x)
{
	playerNeedExperience = x;
}

int Player::GetplayerLevel()
{
	return playerLevel;
}

void Player::SetplayerLevel(int x)
{
	playerLevel = x;
}

SmallHero* Player::getSmallHero()
{
	return smallHero;
}

class Hero* Player::GetWarHero() {
	return chessWarPlayer;
}

void Player::changeplayerBlood(int hurt)
{
	playerBlood -= hurt;
	smallHero->ChangeHP(hurt);

	if (smallHero->IsDead())
	{
		playerIsDead = true;//�������
	}
}

void Player::SetHero(Hero* hero) {
	chessWarPlayer[heroNum].SetBaseInfo(hero->GetBaseInfo(), hero->GetName(), hero->GetHeroPos());
	//chessWarPlayer.onBattle[chessWarPlayer.heroNum].SetHeroOn();
	chessWarPlayer[heroNum].SetOn(1);
	heroNum++;
}

void Player::Restart() {
	heroNum = 0;
}

