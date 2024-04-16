#define _CRT_SECURE_NO_WARNINGS 1
#include"stdio.h"
#include"string.h"
#include"stdlib.h"
#include"time.h"
#include"menu.h"
#include"card.h"
#include"card.h"
#include"card_file.h"
#include"add.h"
#include"recharge.h"
#include"refund.h"
#include"delete.h"

//注销卡
void Delete() {
	printf("------注销卡--------\n");
	card = ReadCard();

	printf("请输入注销卡号<1~18>：");
	char myName[50];
	scanf("%s", myName);

	printf("请输入密码<1~8>：");
	char myPwd[50];
	scanf("%s", myPwd);

	Card* t = card->next;
	if (!t) {
		printf("未添加卡\n");
		return;
	}

	while (t) {
		if (strcmp(t->aName, myName) == 0 && strcmp(t->aPwd, myPwd) == 0) {
			if (t->nStatus == 3) {
				printf("卡号已失效，注销卡失败\n");
				return;
			}
			else if (t->nStatus == 2) {
				printf("卡号已注销\n");
				return;
			}
			else if (t->nStatus == 1) {
				printf("卡号正在上机，注销卡失败\n");
				return;
			}
			else {
				float money = t->fBalance;
				t->fBalance = 0;
				t->nStatus = 2;
				updateCard(t, t->nStatus);
				printf("------注销卡信息如下--------\n");
				printf("卡号\t退款金额\n");
				printf("%s\t%.1f\n", t->aName, money);
				return;
			}
		}
		t = t->next;
	}
	if (!t) {
		printf("账号或密码错误\n");
		return;
	}
}
