#ifndef __SMALL_HERO_H__  
#define __SMALL_HERO_H__ 

#include "cocos2d.h" 
#include "showHPMP.h"
#include "ui/CocosGUI.h"

#include <string>  

using namespace cocos2d;
using std::string;
USING_NS_CC;

class Click;

//ÿ�������� 4 ����
const int addExperience = 4;
//���������ֵ�� 4
const int addMaxExperience = 4;

class SmallHero : public Sprite
{
public:
	virtual bool init();
	static SmallHero* create();//����Ӣ��
	void SetBaseInfo(string name, Vec2 pos);//����Ӣ�۳�ʼ��Ϣ
	Vec2 onMouseUp(Event* event);//�õ�Ӣ�۵�Ŀ��λ��
	void handleMouseClick(const Vec2& clickPos);
	void smallHeroMoveTo(const Vec2& clickPos);//Ӣ���ƶ���ָ��λ��
	void StopMove(Ref* obj);//�ص�������ֹͣ���ж���
	void ChangeHP(float data);//�ܵ���������Ѫ����õ����ƻָ�Ѫ��
	bool IsDead();

	//CREATE_FUNC(SmallHero);

	virtual	void update(float dt);//ÿһ֡����һ��Ӣ��״̬
private:
	string smallHeroName;//��������ͼƬ����
	Vec2 smallHeroPos;//Ӣ��λ��
	showHPMP* heroHP;//��ʾӢ�۵�Ѫ��
	bool isdead;//�Ƿ�����
	bool ismove;//�Ƿ������ƶ�
	bool isupdate;//�Ƿ���update
	int HP;//���Ѫ��
	int money;//���
	int Level;//��ҵȼ�
	int needExperience;//��������һ����Ҫ���پ���
};

#endif  