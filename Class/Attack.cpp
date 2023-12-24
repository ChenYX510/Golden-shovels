#include "Attack.h"

bool Attack::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	isHit = 0;
	attack = 100;
	return true;
}

//�����������ʼ��������ͼƬ
Attack* Attack::create(const std::string& filename)
{
	Attack* sprite = new (std::nothrow) Attack();
	if (sprite && sprite->initWithFile(filename + "-attack.png"))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void Attack::SetPosition(Vec2 pos,Size heroSize) {//Ӧ��Ҫ����Ӣ�����ƽ��з�������
	this->setPosition(pos.x + heroSize.width / 2-23, pos.y + heroSize.height / 2 - 10);//10�ǵ���ֵ
}

void Attack::SetTarget(Hero* atktarget)
{
	target = atktarget;
	targetPos.x = target->getPosition().x;
	targetPos.y = target->getPosition().y;
	MoveTo* attackMoveTo = MoveTo::create(1.3, targetPos);
	this->runAction(attackMoveTo);
	//this->scheduleUpdate();
	if (isHit == 0)
		this->schedule(schedule_selector(Attack::timer), 0.01f);
}


void Attack::timer(float delta) {//��δ���ÿ0.05sִ��һ��
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();//��ȡ��Ļ�ĳߴ硢λ����Ϣ��
	//this->setPositionY(this->getPositionY() + 2);//��ť���������ƶ�2����
	GetDistance();
	//if (present_position == target_position)
	if (distance <= 1){//�����ť���鳬����Ļ��1/4
		if (!isHit) {
			isHit = 1;//��Ϊ������
			target->ChangeHP(attack);//target����Ŀ����һ��Hero��
			this->setVisible(false);//�ù�������ʧ
			this->unschedule(schedule_selector(Attack::timer));
		}
	}
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
		isHit = 1;//��Ϊ������
		target->ChangeHP(attack);//target����Ŀ����һ��Hero��
		this->unscheduleUpdate();
		this->setVisible(false);//�ù�������ʧ
	}
}
void Attack::destroy()
{
	if (isHit)
	{
		this->unscheduleUpdate();
		isHit = 0;
	}
}
