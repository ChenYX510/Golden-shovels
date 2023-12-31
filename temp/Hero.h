#pragma once
 
//#include "showHPMP.h"
//#include "Attack.h"
#include "cocos2d.h"  
#include"Information.h"
using namespace cocos2d;

//Ӣ�ۣ����ƣ�������Ϣ
class showHPMP;
class Attack;

class Hero :public cocos2d::Sprite
{
public:
	Hero();

	void Hero::upgrade();

	int getLevel() const;
	void setLevel(int x);

	void updateStarLevel();  // �����Ǽ���ʾ�ķ���

	static Hero* create(const std::string& filename);
	void SetBaseInfo(heroInformation* info, std::string name, Vec2 pos);//����Ӣ�۳�ʼ��Ϣ
	void HPInit();
	void SetHeroOn();//����Ӣ���ϳ�������Ѫ����ʼ��������heroPos����λ��
	void SetAction();//��ʼ���ƶ��͹�����������
	Vec2 GetTargetPos();//���ݹ���Ŀ��õ�Ӣ�۵�ս��λ��
	void Movetimer(float delta);
	void HeroMoveTo();//Ӣ���ƶ���ָ��λ�ã������ƶ�������ʵ�֣��ṩ�ƶ�ʱ�䣬Ŀ��λ�ã�
	void StopMove(Ref* obj);//�ص�������ֹͣ���ж���
	void StopAttack(Ref* obj);//�ص�������ֹͣ���ж���
	void StartBattle(Hero* target);
	void HeroAttack();//��ʼ��������
	void ChangeHP(float data);//�ܵ���������Ѫ����õ����ƻָ�Ѫ��
	void ChangeMP();//��������ʱдһ���չ������ļ򵥻���
	void ChangeHPColor();
	double GetAtk();
	bool IsDead();
	bool IsOn();
	bool IsRecover();
	void SetRecover();
	void SetOn(int data);
	void SetDead(int data);
	Hero* ShowTarget();
	double CountDistance();
	CREATE_FUNC(Hero);
	//virtual	void update(float dt);//ÿһ֡����һ��Ӣ��״̬
	void Destory();

	heroInformation* GetBaseInfo();
	std::string GetName();
	Vec2 GetHeroPos();
private:
	int level;  // Ӣ�۵ĵȼ�
	cocos2d::Sprite* starSprite;  // �Ǽ���ʾ�ľ���

	std::string heroName;         //��������ͼƬ����
	heroInformation* baseInfo;
	Vec2 heroPos;//Ӣ��λ��
	showHPMP* heroHP;//��ʾӢ�۵�Ѫ��
	showHPMP* heroMP;//��ʾӢ�۵�����
	Attack* heroAttack;//��Ӣ�۵Ĺ�����ָ��
	Hero* atkTarget;//�����ĵз�Ŀ��Ӣ��
	bool ison;//�Ƿ��ϳ�
	bool isdead;//�Ƿ�����
	bool isatk;//�Ƿ����ڹ���
	bool ismove;//�Ƿ������ƶ�
	bool isFull;//�����Ƿ��������Ƿ��ͷŴ��У�
	bool isupdate;//�Ƿ���update
	bool isrecover;//�Ƿ�Ϊ���ѻָ�Ѫ��
	Animate* moveAction;//�ƶ���������
	Animate* attackAction;//������������
	float atktimer;//������ʱ��
	float curAtkTimer;//��¼��ǰʱ��ļ�ʱ��
	float movetime;//�ƶ���Ҫ��ʱ��
	float movetimer;//�ƶ���ʱ��
	float curMoveTimer;//��¼��ǰʱ��ļ�ʱ��
	float moveActTimer;
	float curMoveActTimer;
	Vec2 direction;
};
