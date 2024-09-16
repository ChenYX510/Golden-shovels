#include "Hero.h"
#include"Information.h"
#include<string>
using namespace std;
USING_NS_CC;

Hero::Hero() {

    atkTarget = NULL;//�����ĵз�Ŀ��Ӣ��
    ison = 0;//�Ƿ��ϳ�
    isdead = 0;//�Ƿ�����
    isatk = 0;//�Ƿ����ڹ���
    ismove = 0;//�Ƿ������ƶ�
    isrecover = 0;
    isFull = 0;//�����Ƿ��������Ƿ��ͷŴ��У�
    isupdate = 0;//�Ƿ���update
    moveAction = NULL;//�ƶ���������
    attackAction = NULL;//������������

}

void Hero::upgrade()
{
    if (level < 4) {
        level++;
        // �����Ǽ���ʾ
        updateStarLevel();

        heroInformation* attributes = Information::getheroInformation(this->getTag(), level);
        if (attributes) {
            // ʹ���µ����Ը���Ӣ��
            baseInfo->HP=attributes->HP;
            baseInfo->HP=attributes->attack;
            // ... ������������ ...

            // �ͷ� attributes �����Ա����ڴ�й©
            delete attributes;
        }

        
    }
}


int Hero::getLevel() const {
    return level;
}

void Hero::setLevel(int x)
{
    level = x;
}

void Hero::updateStarLevel()
{
    string StarList[4] = { "star1.png","star2.png","star3.png","star4.png" };
    // ����ɵ����Ǿ���
    this->removeAllChildren();
    string starFileName = StarList[this->level - 1];
    auto star = Sprite::create(starFileName);
    if (star) {
        float spacing = 15.0f;
        float CardWidth = this->getContentSize().width;
        float CardHeight = this->getContentSize().height;
        float posY =this->getPositionY() / 10;
        float posX = this->getPositionX() / 50;
        //��С
        if (level == 1)
            star->setScale(0.1, 0.1);
        else
            star->setScale(0.15, 0.15);
        //λ��
        star->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
        Vec2 StarPosition = this->getPosition();
        star->setPosition(posX, posY);
        this->addChild(star, 0);
    }
}



Hero* Hero::create(const std::string& filename)
{
    Hero* sprite = new (std::nothrow) Hero();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void Hero::SetBaseInfo(heroInformation* info, std::string name, Vec2 pos) {
    baseInfo = info;
    heroName = name;
    heroPos = pos;
    this->setTexture(heroName + "-action1.png");
    this->setVisible(0);
}

//void Hero::HPInit() {
//    heroHP = showHPMP::create();
//    this->getParent()->addChild(heroHP, 5);
//    heroMP = showHPMP::create();
//    this->getParent()->addChild(heroMP, 5);
//}

