#define _CRT_SECURE_NO_WARNINGS 1
#include"stdio.h"
#include"string.h"
#include"stdlib.h"
#include"time.h"
#include"menu.h"
#include"card.h"
#include"add.h"
#include"card_file.h"
#include"recharge.h"
#include"refund.h"
#include"delete.h"

void Add() {
	card = ReadCard();
	char Name[50];
	char Pwd[50];
	float money;
	printf("请输入卡号<长度为1~18>: ");
	scanf("%s", Name);

	printf("请输入密码<长度为1~8>：");
	scanf("%s", Pwd);

	printf("请输入开卡金额(RMB)：");
	scanf("%f", &money);
	getchar();

	if (strlen(Name) > 18) {
		printf("卡号输入错误\n\n");
		return;
	}
	//卡号相同
	Card* t = card;
	while (t) {
		if (strcmp(t->aName, Name) == 0) {
			printf("该卡号已存在\n\n");
			return;
		}
		t = t->next;
	}

	if (strlen(Pwd) > 8) {
		printf("密码输入错误\n\n");
		return;
	}

	while (money < 0) {
		printf("请输入正常的开卡金额：");
		scanf("%f", &money);
	}
	printf("-----添加的卡信息如下-----\n");
	printf("卡号\t密码\t状态\t开卡金额\n");
	printf("%s\t%s\t0\t%.1f\n", Name, Pwd, money);

	if (card == NULL) card = Initial();
	AddCard(card, Name, Pwd, money);
}