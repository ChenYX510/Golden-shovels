#include "Player.h"

// ��ʼ����̬��Ա����
Player* Player::_instance = nullptr;

Player* Player::getInstance() {
	if (!_instance) {
		_instance = new Player();
		// ������Գ�ʼ���������ԣ�������
		_instance->gold = 100; // ʾ����ʼ�������
	}
	return _instance;
}

// ���캯��
Player::Player() : gold(0) {
	// ��ʼ��������Ա����
}

// �����Ҫ������������ʵ����������
Player::~Player() {
	// ������Դ������еĻ�
}

// �����ڴ�ʵ������ Player ��ķ���
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
