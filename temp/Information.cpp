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
	}
}
std::unordered_map<int, std::string> Information::name = {
    {1, "Hero1"},
    {2, "Hero2"},
    {3,"Hero3" },
    {4,"Hero4"}
};

std::unordered_map<int, std::string> Information::imagePaths = {
    {1, "hero1.png"},
    {2, "hero2.png"},
   {3,"hero3.png" },
    {4,"hero4.png"}
};

//std::unordered_map<int, std::string> Information::alternateImagePaths = {
//    {1, "hero1_alt.png"},
//    {2, "hero2_alt.png"},
//    {3, "hero3_alt.png"},
//    {4, "hero4_alt.png"}
//};
std::string Information::getNameByTag(int tag) {
    return name[tag];
}

std::string Information::getHeroPathByTag(int tag) {
    return imagePaths[tag];
}

heroInformation* Information::GetInfoByTag(int tag) {
	return &info[tag];
}