#include "Hero.h"
USING_NS_CC;
//
//bool Hero::init()
//{
//    if (!Sprite::init())//����ʼ��ʧ�ܣ�����0
//    {
//        return false;
//    }
//}

Hero::Hero(){
   
    atkTarget=NULL;//�����ĵз�Ŀ��Ӣ��
    ison=0;//�Ƿ��ϳ�
    isdead=0;//�Ƿ�����
    isatk=0;//�Ƿ����ڹ���
    ismove=0;//�Ƿ������ƶ�
    isFull=0;//�����Ƿ��������Ƿ��ͷŴ��У�
    isupdate=0;//�Ƿ���update
    moveAction=NULL;//�ƶ���������
    attackAction=NULL;//������������
}

Hero* Hero::create(const std::string& filename)
{
    Hero* sprite = new (std::nothrow) Hero();
    if (sprite && sprite->initWithFile(filename + ".png"))
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
    this->setTexture(heroName + "-action1.png");
    this->setVisible(0);
}

void Hero::SetHeroOn() {
    //heroAttack = Attack::create(heroName);
    //this->getParent()->addChild(heroAttack);//�൱�ڰѹ������ΪӢ�۵��ֵ�
    //heroAttack->GetAttack(baseInfo->attack);
    //heroAttack->setVisible(0);

    heroHP = showHPMP::create();
    this->getParent()->addChild(heroHP,2);
    heroMP = showHPMP::create();
    this->getParent()->addChild(heroMP,2);

    this->setPosition(heroPos);
    //Ѫ����ʼ��
    Vec2 posBlood;
    posBlood.x = heroPos.x;
    posBlood.y = heroPos.y + this->getContentSize().height / 2 +30;
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
    SetAction();
    ison = 1;
}

//��ʼ���ƶ��͹�������
void Hero::SetAction() {
    //���ù�������
    Vector<SpriteFrame*>spriteFrameVec;
    for (int i = 1; i <= 2; i++) {
        char imageName[20];
        sprintf(imageName, "-action%d.png", i);
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


void Hero::StartBattle(Hero* target) {
    atkTarget = target;
    //if (CountDistance() > baseInfo->atkrange) {
    //    ismove = 1;//��������ƶ�
    //    ////            heroAttack->setVisible(0);//�ƶ�״̬�����ع�����
    //    HeroMoveTo();//�ƶ����ܹ�����������λ��
    //}
    auto attackcopy = attackAction;
    MoveBy* stop = MoveBy::create(baseInfo->atkspeed - 1, Vec2(0, 0));//������ͣ��
    Sequence* Atk = Sequence::create(attackAction, stop, NULL);
    this->runAction(RepeatForever::create(Atk));

    atktimer = baseInfo->atkspeed * 60;//60��֡��
    curAtkTimer = 0;
    this->scheduleUpdate();//���ö�ʱ������ʼִ��update����
}

//�õ���Ӧ����ս����ĳ�����ӵ�����λ��
Vec2 Hero::GetTargetPos() {
    Vec2 enemyPos = atkTarget->getPosition();
    double distance = CountDistance();
    Vec2 direction = Vec2(enemyPos.x - heroPos.x, enemyPos.y - this->getPosition().y) / distance;
    Vec2 tarPos;
    if (distance - baseInfo->atkrange > 0)
        tarPos = direction * (distance - baseInfo->atkrange) + this->getPosition();
    else
        tarPos = (0, 0);
    return tarPos;
}

//�ƶ���ָ��λ��
void Hero::HeroMoveTo() {
    Vec2 pos = GetTargetPos();
    double distance = CountDistance();
    movetime = distance/ baseInfo->movespeed;

    Vector<SpriteFrame*>spriteFrameVec2;
    for (int i = 1; i <= 2; i++) {
        char imageName[20];
        sprintf(imageName, "-move%d.png", i);
        SpriteFrame* spriteFrame = SpriteFrame::create(heroName + imageName, Rect(0, 0, this->getContentSize().width, this->getContentSize().height));
        spriteFrameVec2.pushBack(spriteFrame);
    }
    Animation* ani2 = Animation::createWithSpriteFrames(spriteFrameVec2, 0.5);
    auto ani = Animate::create(ani2);
    auto movecopy = moveAction;
    Repeat* rep = Repeat::create(ani,movetime);
    this->runAction(RepeatForever::create(ani));//��ʼ�ƶ�����
    //this->runAction(rep);
    MoveTo* heroMoveTo = MoveTo::create(4,pos);
    //
    Sequence* seq = Sequence::create(heroMoveTo, CallFuncN::create(CC_CALLBACK_1(Hero::StopMove, this)), NULL);
    auto spa = Spawn::createWithTwoActions(rep, heroMoveTo);
    this->runAction(seq);

    Vec2 posBlood;
    posBlood.x = pos.x;
    posBlood.y = pos.y + this->getContentSize().height / 2 + 30;
    Vec2 posMP;
    MoveTo* HPMoveTo = MoveTo::create(4, posBlood);
    heroHP->runAction(HPMoveTo);
    posMP.x = pos.x;
    posMP.y = posBlood.y - 14;
    MoveTo* MPMoveTo = MoveTo::create(4, posMP);
    heroMP->runAction(MPMoveTo);
}

//ֹͣ����
void Hero::StopMove(Ref* obj) {
    this->stopAllActions();
    this->setTexture(heroName +"-action1.png");
}

void Hero::StopAttack(Ref* obj) {
    this->stopAllActions();
    this->setTexture(heroName + "-action1.png");
    isatk = 0;
}

//����Ӣ��λ�õ�����Ŀ���λ��
double Hero::CountDistance() {
    Vec2 pos1 = this->getPosition();//ʵʱ����Ӣ��λ��
    Vec2 pos2 = atkTarget->getPosition();
    return sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
}

void Hero::HeroAttack() {

    Vector<SpriteFrame*>spriteFrameVec;
    for (int i = 1; i <= 2; i++) {
        char imageName[20];
        sprintf(imageName, "-action%d.png", i);
        SpriteFrame* spriteFrame = SpriteFrame::create(heroName + imageName, Rect(0, 0, this->getContentSize().width, this->getContentSize().height));
        spriteFrameVec.pushBack(spriteFrame);
    }
    Animation* ani = Animation::createWithSpriteFrames(spriteFrameVec, 0.5);
    auto atk = Animate::create(ani);
    MoveBy* stop = MoveBy::create(baseInfo->atkspeed - 1, Vec2(0, 0));//������ͣ��
    Sequence* Atk = Sequence::create(atk, stop, NULL);
    this->runAction(Atk);
    //this->runAction(attackAction);//��ʼ��������
    heroAttack = Attack::create(heroName);
    heroAttack->setScale(2);
    this->getParent()->addChild(heroAttack);//�൱�ڰѹ������ΪӢ�۵��ֵ�
    heroAttack->GetAttack(baseInfo->attack);
    heroAttack->SetPosition(this->getPosition(), this->getContentSize());
    heroAttack->setVisible(1);
    float flyTime = CountDistance() / baseInfo->attackSpeed;

    //�������ʱ��
    heroAttack->SetTarget(atkTarget);//���߹����﹥��Ŀ�꣬Attack�ڲ����ö�ʱ����ʵ�ַ����빥��
    //heroAttack->scheduleUpdate();//����attack�ڲ���update�����¹������״̬

    ////�����￪ʼ����
    //MoveTo* attackMoveTo = MoveTo::create(flyTime,atkTarget->getPosition());
    //heroAttack->runAction(attackMoveTo);
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
    //if (curAtkTimer == atktimer) {//���˷���������ʱ��
    //    isatk = 1;//���ù���״̬Ϊ���ڹ���//isatk��ʱ���㣿
    //    //this->runAction(attackAction);//��ʼ��������
    //    //this->schedule(schedule_selector(Hero::HeroAttack), baseInfo->atkspeed);//ÿ����Ӧ������������
    //    HeroAttack();
    //}
    //curAtkTimer++;//��ǰʱ���һ
    //if (curAtkTimer > atktimer)
    //    curAtkTimer = 0;
    //���Ӳ����ƶ�
    if (!ismove)
    {
        //������Ŀ���ڹ�����Χ���򷢶�����
        if (CountDistance() <= baseInfo->atkrange)//������Ҫ��һ������������ֵ���Ƚ�����Ӣ��ͼƬ��СŪ��һ���Ŀ����ܲ��ܱ������
        {

            //Vector<SpriteFrame*>spriteFrameVec;
            //for (int i = 1; i <= 2; i++) {
            //    char imageName[20];
            //    sprintf(imageName, "-action%d.png", i);
            //    SpriteFrame* spriteFrame = SpriteFrame::create(heroName + imageName, Rect(0, 0, this->getContentSize().width, this->getContentSize().height));
            //    spriteFrameVec.pushBack(spriteFrame);
            //}
            //Animation* ani = Animation::createWithSpriteFrames(spriteFrameVec, 0.5);
            //auto atk = Animate::create(ani);
            //MoveBy* stop = MoveBy::create(baseInfo->atkspeed - 1, Vec2(0, 0));//������ͣ��
            //Sequence* Atk = Sequence::create(atk, stop, NULL);
            //this->runAction(Atk);
            //this->runAction(RepeatForever::create(Atk));
            if (curAtkTimer == atktimer) {//���˷���������ʱ��
                isatk = 1;//���ù���״̬Ϊ���ڹ���//isatk��ʱ���㣿
                //this->runAction(attackAction);//��ʼ��������
                //this->schedule(schedule_selector(Hero::HeroAttack), baseInfo->atkspeed);//ÿ����Ӧ������������
                HeroAttack();
            }
            curAtkTimer++;//��ǰʱ���һ
            if (curAtkTimer > atktimer)
                curAtkTimer = 0;
        }

        //Ŀ�겻�ڹ�����Χ��
        else
        {
            this->stopAllActions();
            ismove = 1;//��������ƶ�
            //            heroAttack->setVisible(0);//�ƶ�״̬�����ع�����
            //CallFuncN::create(CC_CALLBACK_1(Hero::StopAttack, this));
            HeroMoveTo();//�ƶ����ܹ�����������λ��
            movetimer = movetime * 60;
            curMoveTimer = 0;
            //        
            //        else {//������ڹ�����Χ�����ڹ���
            //            isatk = 0;
            //            this->runAction(CallFuncN::create(CC_CALLBACK_1(Hero::StopAttack, this)));
            //        }
        }
    }
    if (ismove) {
        curMoveTimer++;
        if (curMoveTimer >= movetimer|| CountDistance() <= baseInfo->atkrange) {
            ismove = 0;
            atktimer = baseInfo->atkspeed * 60;
            curAtkTimer = atktimer;
        }
        
    }
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
    isupdate = 1;
}


bool Hero::IsDead() {
    return isdead;
}