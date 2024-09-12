#pragma once
#ifndef __SHOWHPMP_H__
#define __SHOWHPMP_H__

#include "cocos2d.h"  
using namespace cocos2d;

class showHPMP : public cocos2d::Sprite
{
public:
    virtual bool init();
    static showHPMP* showHPMP::create();
public:
    //����Ѫ������  
    void setBackgroundTexture(const char* pName);
    //����Ѫ��ǰ��  
    void setForegroundTexture(const char* pName);
    //������Ѫ��  
    void setTotalProgress(float total);
    //���õ�ǰѪ��  
    void setCurrentProgress(float progress);
    //�õ���ǰѪ��  
    float getCurrentProgress() const;
    //�õ���Ѫ��  
    float getTotalProgress() const;

private:
    //����ǰ��Ѫ����ʾ�ĳ���  
    void setForegroundTextureRect(const CCRect& rect);

private:
    Sprite* P_back;//����Ѫ��  
    Sprite* P_front;//ǰ��Ѫ��  
    float total;//��Ѫ��  
    float P_current;//��ǰѪ��  
    float P_scale;//�Ŵ���  
};

#endif
