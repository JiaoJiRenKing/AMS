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

void Query() {
	printf("-----查询卡-----\n");
	card = ReadCard();
	char sc[50];
	printf("请输入查询卡号<1~18>： ");
	scanf("%s", sc);
	if (strlen(sc) > 18) {
		printf("卡号过长\n");
		return;
	}

	Card* t = QueryCard(card, sc);
	if (t == NULL) {
		printf("无法查询到该卡信息\n");
		return;
	}

}