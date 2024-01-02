#include "Information.h"
#include<algorithm>

// �������ʼ����̬��Ա����
std::map<int, heroInformation> Information::info;

Information::Information() {
	////Ӣ����map
	//name[0] = "";
	////��ʦ
	//name[1] = "Taric";
	//name[2] = "Ali";
	//name[3] = "Anny";
	//name[4] = "Alice";
	////����
	//name[5] = "Nami";
	//name[6] = "Erlius";
	//name[7] = "Kasia";
	////������Զս��
	//name[8] = "Lilia";
	////��������ս��
	//name[9] = "Kuqi";
	////սʿ
	//name[10] = "Kennen";
	//name[11] = "Chuishi";
	//name[12] = "Serti";
	//name[13] = "Katerina";
	//name[14] = "Evelynn";

	//Ӣ����Ϣ����
	SetHeroInfo();
}
heroInformation* Information::getheroInformation(int heroTag, int level) {
	// ����Ƿ���ڸ�Ӣ�۵���Ϣ
	if (info.find(heroTag) != info.end()) {
		// ��ȡ������Ϣ
		heroInformation* baseInfo = &info[heroTag];

		// ����һ���µ� heroInformation �������洢�����������
	 heroInformation* upgradedInfo = new heroInformation(*baseInfo);

		// �������ԣ��������ÿ�����ӵ������ǹ̶���
		upgradedInfo->HP += level * 10; // ʾ����ÿ������10������ֵ
		upgradedInfo->attack += level * 5; // ʾ����ÿ������5�㹥����

		// ���ظ��º��Ӣ����Ϣ
		return upgradedInfo;
	}
	return nullptr; // ����Ҳ���Ӣ����Ϣ������ nullptr
}
void Information::SetHeroInfo() {
	for (int i = 1; i <= 14; i++) {
		HeroInfo[i] = { 500,60,70,1.2,35,200,80,160 };
	}
	//������...

	//��ʼ��Ӣ����Ϣ���ұ�
	for (int i = 1; i <= 14; i++) {
		info[i] = HeroInfo[i];
		//info[i].HP = 500;
	}
}
std::unordered_map<int, std::string> Information::name = {
	{0, ""},
	{1, "Taric"},
	{2, "Ali"},
	{3, "Anny"},
	{4, "Alice"},
	{5, "Nami"},
	{6, "Erlius"},
	{7, "Kasia"},
	{8, "Lilia"},
	{9, "Kuqi"},
	{10, "Kennen"},
	{11, "Chuishi"},
	{12, "Serti"},
	{13, "Katerina"},
	{14, "Evelynn"}
};


std::unordered_map<int, std::string> Information::imagePaths = {
    {1, "Taric.png"},
    {2, "Ali.png"},
   {3,"Anny.png" },
    {4,"Alice.png"},
	{5, "Nami.png"},
	{6, "Erlius.png"},
	{7, "Kasia.png"},
	{8, "Lilia.png"},
	{9, "Kuqi.png"},
	{10, "Kennen.png"},
	{11, "Chuishi.png"},
	{12, "Serti.png"},
	{13, "Katerina.png"},
	{14, "Evelynn.png"}
};

std::unordered_map<int, std::string> Information::warimagePaths = {
	{1, "Taric-action1.png"},
	{2, "Ali-action1.png"},
   {3,"Anny-action1.png" },
	{4,"Alice-action1.png"},
	{5, "Nami-action1.png"},
	{6, "Erlius-action1.png"},
	{7, "Kasia-action1.png"},
	{8, "Lilia-action1.png"},
	{9, "Kuqi-action1.png"},
	{10, "Kennen-action1.png"},
	{11, "Chuishi-action1.png"},
	{12, "Serti-action1.png"},
	{13, "Katerina-action1.png"},
	{14, "Evelynn-action1.png"}
};

std::string Information::getNameByTag(int tag) {
    return name[tag];
}

std::string Information::getHeroPathByTag(int tag) {
    return imagePaths[tag];
}

heroInformation* Information::GetInfoByTag(int tag) {
	heroInformation* testInfo4 = new heroInformation;
	testInfo4->HP = 700;
	testInfo4->MP = 60;
	testInfo4->attack = 60;
	testInfo4->atkspeed = 1.5;
	testInfo4->defence = 35;
	testInfo4->atkrange = 200;
	testInfo4->movespeed = 80;
	testInfo4->attackSpeed = 160;
	info[tag] = *testInfo4;
	return &info[tag];
}