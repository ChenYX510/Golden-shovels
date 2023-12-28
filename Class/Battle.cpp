#include "Battle.h"

bool Battle::init() {
	if (!Layer::init())
		return false;
	//for (int i = 0; i < MaxHero; i++) {//����ÿ�������ڵ�Ӣ��
	//	self[i] = Hero::create();
	//	self[i]->setVisible(0);
	//	enemy[i] = Hero::create();
	//	enemy[i]->setVisible(0);

	//}
	for (int i = 0; i < MaxHero; i++) {//Ӣ�ۺ�Ѫ����ʾ��ս������
		self[i] = Hero::create();
		this->addChild(self[i], 2);
		self[i]->HPInit();
		//self[i]->SetHeroOn();
	}
	for (int i = 0; i < MaxHero; i++) {//Ӣ�ۺ�Ѫ����ʾ��ս������
		enemy[i] = Hero::create();
		this->addChild(enemy[i], 1);
		enemy[i]->HPInit();
		//enemy[i]->SetHeroOn();
	}
	return true;
}

Battle* Battle::createLayer() {
	return Battle::create();
}

void Battle::SetPlayer(Player* my, Player* en) {
	myPlayer = my;
	enPlayer = en;
	//myHeroNum=myPlayer->GetWarHero().size();
	//enHeroNum = enPlayer->GetWarHero().size();
	
}

//ս����ʼ
void Battle::Start() {
	//�غ�ת��ʱʹ�����ϳ�Ӣ�۸���
	this->SetHeroData();
	if (!this->IsEnd()) {
		this->setVisible(1);
		this->SetAtkTarget(self, enemy, myHeroNum, enHeroNum);
		this->SetAtkTarget(enemy, self, enHeroNum, myHeroNum);
		this->scheduleUpdate();
		//�ɼ�һ��ս����ʱ
	}
}

void Battle::CallBack(float t) {
	this->setVisible(1);
	heroInformation* testEnemyInfo2 = new heroInformation;
   testEnemyInfo2->HP = 550;
   testEnemyInfo2->MP = 60;
   testEnemyInfo2->attack = 70;
   testEnemyInfo2->atkspeed = 1.2;
   testEnemyInfo2->defence = 25;
   testEnemyInfo2->atkrange = 300;
   testEnemyInfo2->movespeed = 80;
   testEnemyInfo2->attackSpeed = 160;

   Hero* testEnemy2 = Hero::create();//����һ��Ӣ��
   this->addChild(testEnemy2);//�ӵ�����
   testEnemy2->HPInit();
   testEnemy2->SetBaseInfo(testEnemyInfo2, "En-Anny", Vec2(500,500));//����Ӣ����Ϣ
  
   testEnemy2->SetHeroOn();//��Ӣ���ϳ�
}

void Battle::SetHeroData() {
	////�����������ȡ�ϳ�Ӣ����Ϣ
	//self = myPlayer->GetWarHero();
	//enemy = enPlayer->GetWarHero();

	myHeroNum = myPlayer->GetHeroNum();
	enHeroNum = enPlayer->GetHeroNum();
	
	//this->ResetHero();
	for (int i = 0; i < myHeroNum; i++) {//Ӣ�ۺ�Ѫ����ʾ��ս������
		//this->addChild(self[i], 2);
		self[i]->SetBaseInfo(myPlayer->GetWarHero()[i].GetBaseInfo(), myPlayer->GetWarHero()[i].GetName(), myPlayer->GetWarHero()[i].GetHeroPos());
		//self[i] = myPlayer->GetWarHero()[i];
		self[i]->SetDead(0);
		self[i]->setVisible(1);
		self[i]->SetHeroOn();
	}
	for (int i = 0; i < enHeroNum; i++) {//Ӣ�ۺ�Ѫ����ʾ��ս������
		//this->addChild(enemy[i], 1);
		enemy[i]->SetBaseInfo(enPlayer->GetWarHero()[i].GetBaseInfo(), enPlayer->GetWarHero()[i].GetName(), enPlayer->GetWarHero()[i].GetHeroPos());
		//enemy[i] = enPlayer->GetWarHero()[i];
		enemy[i]->SetDead(0);
		enemy[i]->setVisible(1);
		enemy[i]->SetHeroOn();
	}
}

void Battle::update(float dt) {
	End();
	if (!IsEnd()) {
		for (int i = 0; i < myHeroNum; i++) {
			if (self[i]->IsOn() && self[i]->IsDead() == 0) {
				if (self[i]->IsRecover()) {
					Recover(self, myHeroNum, 100);
					self[i]->SetRecover();
				}
			}
		}
		for (int i = 0; i < enHeroNum; i++) {
			if (enemy[i]->IsOn() && enemy[i]->IsDead() == 0) {
				if (enemy[i]->IsRecover()) {
					Recover(enemy, enHeroNum, 100);
					enemy[i]->SetRecover();
				}
			}
		}
		UpdateTarget(self, enemy, myHeroNum, enHeroNum);
		UpdateTarget(enemy, self, enHeroNum, myHeroNum);
		
	}
}

double Battle::CountDistance(Vec2 pos1, Vec2 pos2) {
	return sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
}

void Battle::SetAtkTarget(Hero** atk, Hero** tar,int atkNum,int tarNum) {
	double minDistance = CountDistance(atk[0]->getPosition(), tar[0]->getPosition());
	Hero* atkTarget=Hero::create();
	for (int i = 0; i < atkNum; i++) {
		/*int x = atkPos[i].x;
		int y = atkPos[i].y;*/
		if (!atk[i]->IsDead()) {//�������������Ӣ��û��
			for (int j = 0; j < tarNum; j++) {
				/*int m = tarPos[j].x;
				int n = tarPos[j].y;*/
				if (!tar[j]->IsDead()) {//����з�Ӣ��û��
					double temp = CountDistance(atk[i]->getPosition(), tar[j]->getPosition());
					if (temp <= minDistance) {
						minDistance = temp;
						atkTarget = tar[j];
					}
				}
			}
			atk[i]->StartBattle(atkTarget);
		}
	}
}

void Battle::UpdateTarget(Hero** atk, Hero** tar, int atkNum, int tarNum) {
	Hero* atkTarget = Hero::create();
	for (int i = 0; i < atkNum; i++) {
		/*int x = atkPos[i].x;
		int y = atkPos[i].y;*/
		if (!atk[i]->IsDead()) {
			if (atk[i]->ShowTarget()->IsDead()) {
				double minDistance = MaxDis;
				for (int j = 0; j < tarNum; j++) {
				    //int m = tarPos[j].x;
					//int n = tarPos[j].y;
					if (tar[j]->IsOn()&&tar[j]->IsDead() == 0) {
						double temp = CountDistance(atk[i]->getPosition(), tar[j]->getPosition());
						if (temp <= minDistance) {
							minDistance = temp;
							atkTarget = tar[j];
						}
					}
				}
				atk[i]->Destory();
				atk[i]->StartBattle(atkTarget);
			}
		}
	}
}

void Battle::ResetHero() {
	isNext = 0;
	for (int i = 0; i < myHeroNum; i++) {
		self[i]->SetDead(0);
		self[i]->SetOn(1);
	}
	for (int i = 0; i < enHeroNum; i++) {
		enemy[i]->SetDead(0);
		enemy[i]->SetOn(1);
	}
}

int Battle::IsEnd() {
	int myon = 0;
	int enon = 0;//�ҷ��͵з�����Ӣ������
	for (int i = 0; i < myHeroNum; i++) {
		if (self[i]->IsOn() && self[i]->IsDead() == 0)
			myon++;
	}
	for (int i = 0; i < enHeroNum; i++) {
		if (enemy[i]->IsOn() && enemy[i]->IsDead() == 0)
			enon++;
	}
	myLive = myon;
	enLive = enon;
	if (myon && !enon)//�ҷ�ʤ��
		return 1;
	if (!myon && enon)//�з�ʤ��
		return 2;
	else
		return 0;//��û����
}

void Battle::End() {
	if (IsEnd()) {
		this->unscheduleUpdate();
		if (IsEnd() == 1) {//�ҷ�ʤ��
			int hurt = myLive * 2 + 8;//8Ϊ�׶��˺�������д�غ��ٸ�
			enPlayer->changeplayerBlood(10);
		}
		else {
			int hurt = enLive * 2 + 8;//8Ϊ�׶��˺�������д�غ��ٸ�
			myPlayer->changeplayerBlood(hurt);
		}
		this->Destory();//�ѳ���Ӣ��ȫ����Ϊ���ɼ�����ֹͣ����Ӣ�۵�update
		this->setVisible(0);
		isNext = 1;

	}
}

void Battle::Destory() {
	for (int i = 0; i < myHeroNum; i++) {
		self[i]->setVisible(0);
		self[i]->Destory();
	}
	for (int i = 0; i < enHeroNum; i++) {
		enemy[i]->setVisible(0);
		enemy[i]->Destory();
	}
}

void Battle::Recover(Hero** hero,int num,double data) {
	for (int i = 0; i < num; i++) {
		if (hero[i]->IsOn() && hero[i]->IsDead() == 0) {
			hero[i]->ChangeHP(-data);
		}
	}
}

bool Battle::IsNext() {
	return isNext;
}