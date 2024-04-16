#pragma once
#include"time.h"
//����Ϣ�ṹ��
typedef struct Card {
	char aName[50];                //����
	char aPwd[50];                  //����
	int nStatus;				   //��״̬��0-δ�ϻ��� 1-�����ϻ��� 2-��ע����3-ʧЧ��
	time_t tStart;                 //����ʱ��
	time_t tEnd;                   //���Ľ���ʱ��
	float fTotalUse;               //�ۼƽ��
	time_t tLastTime;              //���ʹ��ʱ��
	int nUseCount;                 //ʹ�ô���
	float fBalance;                //���
	int nDel;                      //ɾ����ʶ��0-δɾ���� 1-ɾ����
	struct Card* next;
}Card;

void AddCard(Card* link, char* n, char* p, float t);
Card* Initial();
Card* QueryCard(Card* card, char name[]);
int DelCard(Card* card, char name[]);