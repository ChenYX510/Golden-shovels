#include "Attack.h"

bool Attack::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	isHit = 0;
	return true;
}

//�����������ʼ��������ͼƬ
Attack* Attack::create(const std::string& filename)
{
	Attack* sprite = new (std::nothrow) Attack();
	if (sprite && sprite->initWithFile(filename + "attack.png"))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void Attack::SetPosition(Vec2 pos,Size heroSize) {//Ӧ��Ҫ����Ӣ�����ƽ��з�������
	this->setPosition(pos.x + heroSize.width / 2, pos.y + heroSize.height / 2 - 10);//10�ǵ���ֵ
}

void Attack::SetTarget(Hero* atktarget)
{
	target = atktarget;
}
void Attack::GetAttack(double atk)
{
	attack = atk;
}

void Attack::GetDistance() {
	Vec2 currentPos = this->getPosition();
	Vec2 targetPos = target->getPosition();
	//��ǰλ����Ŀ�깥��λ�õľ���
	distance = sqrt(pow(targetPos.x - currentPos.x, 2) + pow(targetPos.y - currentPos.y, 2));
}

void Attack::update(float dt)//���¹�����״̬
{
	GetDistance();
	//if (present_position == target_position)
	if (distance <= 1)
	{
		isHit = 0;
		target->ReduceHp(attack);//target����Ŀ����һ��Hero��
		this->unscheduleUpdate();
		this->setVisible(false);//�ù�������ʧ
	}
}
