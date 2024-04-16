#define _CRT_SECURE_NO_WARNINGS 1
#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#include"time.h"
#include"card.h"
#include"card_file.h"
#include"add.h"


void AddCard(Card* link, char* n, char* p, float t) {
	Card* card = (Card*)malloc(sizeof(Card));
	strcpy(card->aName, n);
	strcpy(card->aPwd, p);
	card->fTotalUse = 0;
	card->fBalance = t;
	card->nUseCount = 0;
	card->nStatus = 0;
	card->nDel = 0;

	// 将新节点插入链表的开头
	card->next = link->next;
	link->next = card;

	SaveCard(card); // 保存新添加的卡片信息
}


Card* Initial() {
	Card* card = (Card*)malloc(sizeof(Card));
	card->next = NULL;
	return card;
}

Card* QueryCard(Card *card, char name[]) {
	Card* t = card->next;
	int flag = 0;
	//模糊查询
	while (t) {
		if (strstr(t->aName, name)) {
			if (!flag) {
				printf("卡号\t状态\t余额\t累计使用\t使用次数\t上次使用时间\n");
				printf("%s\t%d\t%.1f\t%.1f\t\t%d\t\t", t->aName, t->nStatus, t->fBalance, t->fTotalUse, t->nUseCount);
			}
			else {
				printf("%s\t%d\t%.1f\t%.1f\t\t%d\t\t", t->aName, t->nStatus, t->fBalance, t->fTotalUse, t->nUseCount);
			}
			// 检查 t->tLastTime 是否为空
			if (t->tLastTime != 0) {
				// 获取上次使用时间的结构体指针
				struct tm* p = localtime(&t->tLastTime);
				printf("%4d-", p->tm_year + 1900);
				printf("%02d-", p->tm_mon + 1);
				printf("%02d ", p->tm_mday);
				printf("%02d:%02d:%02d\n", p->tm_hour, p->tm_min, p->tm_sec);
			}
			else {
				printf("无记录\n");
			}
			flag++;
		}
		t = t->next;
	}
	if (flag) return card;
	else return NULL;
}

