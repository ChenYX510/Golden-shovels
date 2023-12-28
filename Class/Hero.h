#pragma once
#ifndef __HERO_H__  
#define __HERO_H__  
#include "showHPMP.h"
#include "Attack.h"
#include "cocos2d.h"  
using namespace cocos2d;

//Ӣ�ۣ����ƣ�������Ϣ
class showHPMP;
class Attack;
struct heroInformation {
	
	float HP;                 //����ֵ
	float MP;                 //����ֵ
	float attack;            //������
	float atkspeed;          //�����ٶ�(ÿ���빥��һ��)
	float defence;           //������
	float atkrange;          //��������
	float movespeed;         //�ƶ��ٶ�
	double attackSpeed;//����������ٶ�
};

class Hero :public cocos2d::Sprite
{
public:
	Hero();
	static Hero* create(const std::string& filename);
	void SetBaseInfo(heroInformation* info, std::string name,Vec2 pos);//����Ӣ�۳�ʼ��Ϣ
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
	virtual	void update(float dt);//ÿһ֡����һ��Ӣ��״̬
	void Destory();

	heroInformation* GetBaseInfo();
	std::string GetName();
	Vec2 GetHeroPos();
private:
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

//
//class Chess : public cocos2d::Sprite
//{
//public:
//	CREATE_FUNC(Chess);
//	virtual bool init();
//	static Chess* create(const std::string& filename);
//	double ShowHp();
//	double ShowAtk();
//	double ShowAtkSpeed();
//	double ShowMoveSpeed();
//	double ShowDef();
//	double ShowAtkRange();
//	double ShowFlySpeed();
//	int IsDead();
//	int IsOn();
//	std::string ShowName();
//	void SetHp(double data);
//	void SetAtk(double data);
//	void SetAtkSpeed(double data);
//	void SetMoveSpeed(double data);
//	void SetDef(double data);
//	void SetAtkRange(double data);
//	void SetName(std::string data);
//	void SetFlySpeed(double data);
//	double SetAtkTimer(double data);
//	double SetMoveTimer();
//	void SetAtkMark();
//	void SetMovemark();
//	void SetMoveTime();
//	void AtkTargetInit(Chess* data);
//	double CountTheDistance(Vec2 position1, Vec2 position2);//������������֮��ľ���
//	void SetDead(int);
//	void SetOn(int);
//	void PointInit();
//	void AttackTo(Vec2 position);//���ɹ������ƶ���Ŀ��λ�ã���������дһ���������࣬���ձ���д������������Ӧ�й�����ķ����ٶ�
//	void AttackTarget();//��������������һ��Ŀ�����ӵ�ָ�룬��ȡĿ�����ӵ�λ�ã���������ĺ�������һ���������ƶ���Ŀ������λ�ã������Ŀ�����ӿ�Ѫ
//	void ReduceHp(double atk);
//	void Reverse(int);
//	void MoveTo(Vec2 position);//�����ƶ���Ŀ��λ��
//	void MoveTarget(Chess* target);//����Ŀ������λ�þ���Ҫ�ƶ�����λ��
//	void Test(cocos2d::Ref* pSender);//���ڵ��ԵĻص�����
//	virtual	void update(float dt);
//	Chess* ShowTarget();
//	void destroy();//����update�İ�װ����
//	void setdatafromcard();
//	void setatkptrimage();
//private:
//	double healthpoint;       //HP
//	double attack;            //������
//	double atkspeed;          //�����ٶ�
//	double movespeed;         //�ƶ��ٶ�
//	double defence;           //������
//	double atkrange;          //��������
//	double flyspeed;          //������ķ����ٶ�
//	std::string name;         //������
//	Attack* p_attack;         //������ָ��
//	double standard_atktimer;    //��������׼//atktimer=atkspeed*60;
//	double standard_movetimer;   //������//
//	double atktimer;             //����ʵ�ּ�ʱ������
//	double movetimer;
//	int atkmark;              //��¼�Ƿ��ڹ���//0����δ���� 1��������
//	int movemark;             //��¼�Ƿ����ƶ�//0����δ�ƶ� 1�����ƶ���
//	double move_time;        //�ƶ���Ҫ���ѵ�ʱ��//�ǵó�ʼ��
//	Chess* atktarget;         //���Ŀ������
//	/// /////////////////////////////////////////////////////////////////////
//	int isdead;               //��¼�Ƿ�����
//	int ison;                 //��¼�Ƿ��ϳ�
//	int isupdate = 0;       //��¼�Ƿ���ִ��update
//};



#endif  