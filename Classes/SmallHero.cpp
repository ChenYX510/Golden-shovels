#include "SmallHero.h"

bool SmallHero::init()
{
	if (!Sprite::init())//����ʼ��ʧ�ܣ�����0
	{
		return false;
	}
    heroHP = showHPMP::create();
    this->addChild(heroHP);
    // ����һ��������
    auto _mouseListener = EventListenerMouse::create();

    // ���� onMouseUp �¼��ص�
    _mouseListener->onMouseUp = CC_CALLBACK_1(SmallHero::onMouseUp, this);

    // ����������ӵ��¼��ַ�����
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
}

SmallHero* SmallHero::create()
{
    SmallHero* sprite = new (std::nothrow) SmallHero();
    if (sprite && sprite->init())
    {
        sprite->autorelease();
        sprite->SetBaseInfo("SmallHero.png", Vec2(0, 0));  // ����Ĭ�ϳ�ʼλ�ú�ͼƬ
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void SmallHero::SetBaseInfo(string name, Vec2 pos) 
{
	smallHeroName = name;
	smallHeroPos = pos;
    HP = 100;
    isdead = 0;
    ismove = 0;
    isupdate = 0;
    money = 10;
    Level = 1;
    needExperience = 4;
	this->setTexture(smallHeroName);
    this->setPosition(smallHeroPos);
    //Ѫ����ʼ��
    Vec2 posBlood;
    posBlood.x = smallHeroPos.x;
    posBlood.y = smallHeroPos.y + this->getContentSize().height / 2 + 8;
    heroHP->setPosition(posBlood);
    heroHP->setScale(2.2f);
    heroHP->setBackgroundTexture("Blood-back.png");
    heroHP->setForegroundTexture("Blood-front.png");
    heroHP->setTotalProgress(HP);
    heroHP->setCurrentProgress(HP);
    heroHP->setScale(0.8);
    this->setVisible(1);
}

Vec2 SmallHero::onMouseUp(Event* event)
{
    EventMouse* e = dynamic_cast<EventMouse*>(event);
    if (e)
    {
        // ��ȡ�����λ��
        Vec2 mouseClickPos = Vec2(e->getCursorX(), e->getCursorY());

        // ��������ô�����λ�õĺ���
        handleMouseClick(mouseClickPos);

        return mouseClickPos;
    }
    return nullptr;
}

void SmallHero::handleMouseClick(const Vec2& clickPos)
{
    // ��������Խ��н�һ���Ĵ��������ƶ�Ӣ�۵����λ��
    smallHeroMoveTo(clickPos);
}

//�ƶ���ָ��λ��
void SmallHero::smallHeroMoveTo(const Vec2& clickPos)
{
    Vec2 pos1 = smallHeroPos;
    Vec2 pos2 = clickPos;
    double distance = sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
    double time = distance / 500;
    MoveTo* moveTo = MoveTo::create(time, pos2);
    Sequence* seq = Sequence::create(moveTo, CallFuncN::create(CC_CALLBACK_1(SmallHero::StopMove, this)), NULL);
    this->runAction(seq);
}

//ֹͣ����
void SmallHero::StopMove(Ref* obj) 
{
    this->stopAllActions();
    this->setTexture(smallHeroName);
    ismove = 0;
}

void SmallHero::ChangeHP(float data) 
{
    heroHP->setCurrentProgress(heroHP->getCurrentProgress() - data);
    HP = heroHP->getCurrentProgress();
}

void SmallHero::update(float dt)
{
    if (HP <= 0){
        this->isdead = 1;//����
        this->setVisible(0);
    }
    if (isdead){
        this->unscheduleUpdate();//ֹͣ��Ӣ�۵����ж�ʱ��
    }
}

bool SmallHero::IsDead() 
{
    return isdead;
}


