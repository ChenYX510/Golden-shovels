#include "Hero.h"
USING_NS_CC;

bool Hero::init()
{
    if (!Sprite::init())//����ʼ��ʧ�ܣ�����0
    {
        return false;
    }
    heroAttack = Attack::create();
    this->getParent()->addChild(heroAttack);//�൱�ڰѹ������ΪӢ�۵��ֵ�
    heroHP = showHPMP::create();
    this->getParent()->addChild(heroHP);
    heroMP = showHPMP::create();
    this->getParent()->addChild(heroMP);
}

Hero* Hero::create()
{
    Hero* sprite = new (std::nothrow) Hero();
    if (sprite)
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void Hero::SetBaseInfo(heroInformation* info, std::string name,Vec2 pos) {
    baseInfo = info;
    heroName = name;
    heroPos = pos;
    this->setTexture(heroName + "action1.png");
    this->setVisible(0);
}

void Hero::SetHeroOn() {
    if (ison) {
        this->setPosition(heroPos);
        //Ѫ����ʼ��
        Vec2 posBlood;
        posBlood.x = heroPos.x;
        posBlood.y = heroPos.y + this->getContentSize().height / 2 + 8;
        heroHP->setPosition(posBlood);
        heroHP->setScale(2.2f);
        heroHP->setBackgroundTexture("Blood-back.png");
        heroHP->setForegroundTexture("Blood-front.png");
        heroHP->setTotalProgress(baseInfo->HP);
        heroHP->setCurrentProgress(baseInfo->HP);
        heroHP->setScale(0.8);
        //������ʼ��
        Vec2 posMP;
        posMP.x = heroPos.x;
        posMP.y = posBlood.y - 14;
        heroMP->setPosition(posMP);
        heroMP->setScale(2.2f);
        heroMP->setBackgroundTexture("MP-back.png");
        heroMP->setForegroundTexture("MP-front.png");
        heroMP->setTotalProgress(baseInfo->MP);
        heroMP->setCurrentProgress(0.0f);
        heroMP->setScale(0.8);
        //Ӣ����Ϊ�ɼ�
        this->setVisible(1);
    }
}

//��ʼ���ƶ��͹�������
void Hero::SetAciton() {
    //���ù�������
    Vector<SpriteFrame*>spriteFrameVec;
    for (int i = 1; i <= 2; i++) {
        char imageName[20];
        sprintf(imageName, "-attack%d.png", i);
        SpriteFrame* spriteFrame = SpriteFrame::create(heroName+imageName, Rect(0, 0, this->getContentSize().width, this->getContentSize().height));
        spriteFrameVec.pushBack(spriteFrame);
    }
    Animation* ani = Animation::createWithSpriteFrames(spriteFrameVec, 0.5);
    attackAction = Animate::create(ani);
    //�����ƶ�����
    Vector<SpriteFrame*>spriteFrameVec2;
    for (int i = 1; i <= 2; i++) {
        char imageName[20];
        sprintf(imageName, "-move%d.png", i);
        SpriteFrame* spriteFrame = SpriteFrame::create(heroName + imageName, Rect(0, 0, this->getContentSize().width, this->getContentSize().height));
        spriteFrameVec2.pushBack(spriteFrame);
    }
    Animation* ani2 = Animation::createWithSpriteFrames(spriteFrameVec2, 0.5);
    moveAction = Animate::create(ani2);
}

//�õ���Ӧ����ս����ĳ�����ӵ�����λ��
Vec2 Hero::GetTargetPos() {
    Vec2 enemyPos = atkTarget->getPosition();
    double distance = CountDistance();
    Vec2 direction = Vec2(enemyPos.x - heroPos.x, enemyPos.y - heroPos.y) / distance;
    Vec2 tarPos;
    if (distance - baseInfo->atkrange > 0)
        tarPos = direction * (distance - baseInfo->atkrange) + heroPos;
    return tarPos;
}

//�ƶ���ָ��λ��
void Hero::HeroMoveTo() {
    Vec2 pos = GetTargetPos();
    double time = CountDistance() / baseInfo->movespeed;
    this->runAction(moveAction);//��ʼ�ƶ�����
    MoveTo* moveTo = MoveTo::create(time,pos);
    Sequence* seq = Sequence::create(moveTo, CallFuncN::create(CC_CALLBACK_1(Hero::StopMove, this)), NULL);
    this->runAction(seq);
}

//ֹͣ����
void Hero::StopMove(Ref* obj) {
    this->stopAllActions();
    this->setTexture(heroName +"-action1.png");
    ismove = 0;
}

void Hero::StopAttack(Ref* obj) {
    this->stopAllActions();
    this->setTexture(heroName + "-action1.png");
    isatk = 0;
}

//����Ӣ��λ�õ�����Ŀ���λ��
double Hero::CountDistance() {
    Vec2 pos1 = heroPos;
    Vec2 pos2 = atkTarget->getPosition();
    return sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
}

void Hero::HeroAttack(float t) {
    this->runAction(attackAction);//��ʼ��������
    heroAttack->SetPosition(heroPos,this->getContentSize());
    heroAttack->setVisible(1);
    float flyTime = CountDistance() / attackSpeed;

    //�������ʱ��
    heroAttack->SetTarget(atkTarget);//���߹����﹥��Ŀ��
    heroAttack->scheduleUpdate();//����attack�ڲ���update�����¹������״̬

    //�����￪ʼ����
    MoveTo* attackMoveTo = MoveTo::create(flyTime,atkTarget->getPosition());
    heroAttack->runAction(attackMoveTo);
}

void Hero::ChangeHP(float data) {
    heroHP->setCurrentProgress(heroHP->getCurrentProgress() - data + baseInfo->defence);
    baseInfo->HP = heroHP->getCurrentProgress();
}

void Hero::ChangeMP(float data) {
    if(!isFull)
    heroMP->setCurrentProgress(heroMP->getCurrentProgress() + 10);
}

void Hero::update(float dt)
{
    if (baseInfo->HP <= 0)
    {
        this->isdead = 1;//����
        this->setVisible(0);//�������Ϊ��������ã��Ӻ���Ч������
    }

    if (isdead)//������˾�ֹͣ����
    {
        isatk = 0;
        heroAttack->setVisible(0);
        this->unscheduleUpdate();//ֹͣ��Ӣ�۵����ж�ʱ��
    }
    //���Ӳ����ƶ�
    if (!ismove)
    {
        //������Ŀ���ڹ�����Χ���򷢶�����
        if (CountDistance() <= baseInfo->atkrange )//������Ҫ��һ������������ֵ���Ƚ�����Ӣ��ͼƬ��СŪ��һ���Ŀ����ܲ��ܱ������
        {
            if (!isatk) {
                isatk = 1;//���ù���״̬Ϊ���ڹ���//isatk��ʱ���㣿
                this->schedule(schedule_selector(Hero::HeroAttack), baseInfo->atkspeed);//ÿ����Ӧ������������
            }
            //////////////////////////////
        }

        //Ŀ�겻�ڹ�����Χ�ڣ����Ӳ��ƶ�
        else
        {
            if (!isatk) {
                ismove = 1;//��������ƶ�
                heroAttack->setVisible(0);//�ƶ�״̬�����ع�����
                HeroMoveTo();//�ƶ����ܹ�����������λ��
            }
            else {//������ڹ�����Χ�����ڹ���
                isatk = 0;
            }
        }
    }
    isupdate = 1;
}

bool Hero::IsDead() {
    return isdead;
}