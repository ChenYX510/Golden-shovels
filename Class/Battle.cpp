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
	return true;
}

Battle* Battle::createLayer() {
	return Battle::create();
}

void Battle::SetPlayer(Player* my, Player* en) {
	myPlayer = my;
	enPlayer = en;
}

//ս����ʼ
void Battle::Start() {
	//ResetHero();//�غ�ת��ʱʹ�����ϳ�Ӣ�۸���
	SetHeroData();
	//SetHeroPos();
	if (!IsEnd()) {
		SetAtkTarget(self, enemy, myHeroNum, enHeroNum);
		SetAtkTarget(enemy, self, enHeroNum, myHeroNum);
		this->scheduleUpdate();
		//�ɼ�һ��ս����ʱ
	}
}

void Battle::SetHeroData() {
	//�����������ȡ�ϳ�Ӣ����Ϣ
	self = myPlayer->GetWarHero();
	enemy = enPlayer->GetWarHero();
	myHeroNum = self.size();
	enHeroNum = enemy.size();
	for (int i = 0; i < myHeroNum; i++) {//Ӣ�ۺ�Ѫ����ʾ��ս������
		this->addChild(self[i], 2);
		self[i]->SetHeroOn();
	}
	for (int i = 0; i < enHeroNum; i++) {//Ӣ�ۺ�Ѫ����ʾ��ս������
		this->addChild(enemy[i], 1);
		enemy[i]->SetHeroOn();
	}
}

void Battle::update(float dt) {
	End();
	if (!IsEnd()) {
		UpdateTarget(self, enemy, myHeroNum, enHeroNum);
		UpdateTarget(enemy, self, enHeroNum, myHeroNum);
	}
}

//��������л�ȡ�ϳ�Ӣ�۵�λ����Ϣ
void Battle::SetHeroPos() {
	myPos = myPlayer->GetHeroPos();
	enPos = enPlayer->GetHeroPos();
	/*int my = 0;
	int en = 0;
	for (int i = 0; i < MaxRow; i++) {
		for (int j = 0; j < MaxCol; j++) {
			if (self[i][j]->IsOn()) {
				myPos[my].x = i;
				myPos[my].y = j;
				my++;
			}
			if (enemy[i][j]->IsOn()) {
				enPos[en].x = i;
				enPos[en].y = j;
				en++;
			}
		}
	}*/
}

double Battle::CountDistance(Vec2 pos1, Vec2 pos2) {
	return sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
}

void Battle::SetAtkTarget(std::vector <Hero*>& atk, std::vector <Hero*>& tar,int atkNum,int tarNum) {
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

void Battle::UpdateTarget(std::vector <Hero*>& atk, std::vector <Hero*>& tar, int atkNum, int tarNum) {
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
	for (int i = 0; i < myHeroNum; i++) {
		if (self[i]->IsOn())
			self[i]->SetDead(0);
	}
	for (int i = 0; i < enHeroNum; i++) {
		if (enemy[i]->IsOn())
			enemy[i]->SetDead(0);
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
			//myPlayer->changeplayerBlood(hurt);
		}
		else {
			int hurt = enLive * 2 + 8;//8Ϊ�׶��˺�������д�غ��ٸ�
			//enPlayer->changeplayerBlood(hurt);
		}
		//this->Destory();//�ѳ���Ӣ��ȫ����Ϊ���ɼ�����ֹͣ����Ӣ�۵�update
		//this->setVisible(0);
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