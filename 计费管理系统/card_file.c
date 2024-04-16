#define _CRT_SECURE_NO_WARNINGS 1
#include"stdio.h"
#include"card.h"
#include"time.h"
#include"stdlib.h"
#include"string.h"
#include"tool.h"
#include <io.h>
#include"card_file.h"
#include"add.h"

void SaveCard(Card* card) {
	FILE* fp;
	time_t t = time(NULL);
	struct tm* p = localtime(&t);
	if ((fp = fopen("D:card.txt", "a")) != NULL) {
		fprintf(fp, "%s##%s##%d##%4d-%02d-%02d %02d:%02d:%02d##%4d-%02d-%02d %02d:%02d:%02d##%.1f##%4d-%02d-%02d %02d:%02d:%02d##%d##%.1f##%d\n",
			card->aName, card->aPwd, card->nStatus, p->tm_year + 1900, p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec,
			p->tm_year + 1901, p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec, card->fTotalUse,
			p->tm_year + 1900, p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec, card->nUseCount, card->fBalance, card->nDel);

	}
	else printf("文件打开失败\n");
	fclose(fp);

}

//开卡时间和开卡金额缺了，多了使用金额
Card* ReadCard() {
	Card* card = Initial();
	FILE* file;
	file = fopen("D:card.txt", "r");
	if (file == NULL) {
		printf("文件不存在，创建一个新文件\n");
		return card; // 直接返回空链表
	}

	// 文件存在，继续读取卡片信息
	char time_start[50], time_end[50], time_last[50];
	while (!feof(file)) {
		Card* t;
		t = (Card*)malloc(sizeof(Card));

		// 使用 %[^#] 格式指示符读取除 # 之外的所有字符
		if (fscanf(file, "%[^#]##%[^#]##%d##%[^#]##%[^#]##%f##%[^#]##%d##%f##%d\n",
			t->aName, t->aPwd, &t->nStatus, time_start, time_end,
			&t->fTotalUse, time_last, &t->nUseCount, &t->fBalance, &t->nDel) == EOF) break;


		// 转换时间字符串为时间格式
		t->tStart = StringToTime(time_start);
		t->tEnd = StringToTime(time_end);
		t->tLastTime = StringToTime(time_last);


		// 将新节点插入到链表中
		t->next = card->next;
		card->next = t;
	}


	fclose(file);

	return card;
}


int updateCard(Card* card, int nStatus) {
	//read
	struct temp_card {
		char aName[50];                //卡号
		char aPwd[50];                  //密码
		int nStatus;				   //卡状态（0-未上机； 1-正在上机； 2-已注销；3-失效）
		char start[50];                 //开卡时间
		char end[50];                   //卡的截至时间
		float fTotalUse;               //累计金额
		char lasttime[50];              //最后使用时间
		int nUseCount;                 //使用次数
		float fBalance;                //余额
		int nDel;                      //删除标识（0-未删除， 1-删除）
		struct temp_card* next;
	};
	struct temp_card *t;
	t= (struct temp_card*)malloc(sizeof(struct temp_card));
	t->next = NULL;
	struct temp_card* head= t;
	int flag = 0;
	//Card* t = (Card*)malloc(sizeof(Card));
	//t = Initial();
	//Card* head = t;
	FILE* file;
	file = fopen("D:card.txt", "r");
	if (file == NULL) {
		printf("文件不存在，创建一个新文件\n");
		return 0;
	}
	char time_start[50], time_end[50], time_last[50];
	while (!feof(file)) {
		//Card* temp;
		//temp = (Card*)malloc(sizeof(Card));
		struct temp_card* Temp;
		Temp= (struct temp_card*)malloc(sizeof(struct temp_card));

		// 使用 %[^#] 格式指示符读取除 # 之外的所有字符
		if (fscanf(file, "%[^#]##%[^#]##%d##%[^#]##%[^#]##%f##%[^#]##%d##%f##%d\n",
			Temp->aName, Temp->aPwd, &Temp->nStatus, Temp->start, Temp->end,
			&Temp->fTotalUse, Temp->lasttime, &Temp->nUseCount, &Temp->fBalance, &Temp->nDel) == EOF) break;

		/*temp->tStart = StringToTime(time_start);
		temp->tEnd = StringToTime(time_end);
		temp->tLastTime = StringToTime(time_last);*/

		Temp->next = t->next;
		t->next = Temp;
		flag = 1;
	}


	fclose(file);
	if (flag == 0) return 0;

	//modify
	while (t) {
		if (strcmp(t->aName, card->aName) == 0) {
			t->nStatus = nStatus;
			t->nUseCount++;
			t->fBalance = card->fBalance;
			t->fTotalUse = card->fTotalUse;
			if (t->nStatus == 2) t->nDel = 1;
			else t->nDel = 0;

			time_t nowtime = time(NULL);
			struct tm* p = localtime(&nowtime);
			//t->lasttime = StringToTime(nowtime);
			//sscanf(t->lasttime, "%4d%2d%2d-%2d:%2d:%2d", &p->tm_year, &p->tm_mon, &p->tm_mday, &p->tm_hour, &p->tm_min, &p->tm_sec);
			strftime(t->lasttime, sizeof(t->lasttime), "%Y-%m-%d %H:%M:%S", p);
			break;
		}
		t = t->next;
	}
	t = head->next;

	//clear
	// 以写入模式打开文件，如果文件不存在则创建，如果文件存在则清空文件
	file = fopen("D:card.txt", "w");
	if (file == NULL) {
		printf("文件不存在，创建一个新文件\n");
		return 0;
	}
	fclose(file);

	//write
	time_t now_time = time(NULL); // 获取当前时间
	struct tm* local_time = localtime(&now_time); // 将当前时间转换为本地时间
	file = fopen("D:card.txt", "a");
	if (file == NULL) {
		printf("文件打开失败\n");
		return 0;
	}
	while (t) {
		if (nStatus != 2) {
			// 将更新后的卡片信息写入文件
			if (strcmp(t->aName, card->aName)==0) {
				/*fprintf(file, "%s##%s##%d##%s##%s##%.1f##%4d%02d%02d-%02d:%02d:%02d##%d##%.1f##%d\n",
					t->aName, t->aPwd, t->nStatus, time_start, time_end, t->fTotalUse,
					local_time->tm_year + 1900, local_time->tm_mon + 1, local_time->tm_mday, local_time->tm_hour, local_time->tm_min, local_time->tm_sec, t->nUseCount, t->fBalance, 0);*/
				fprintf(file, "%s##%s##%d##%s##%s##%.1f##%4d-%02d-%02d %02d:%02d:%02d##%d##%.1f##%d\n",
						t->aName, t->aPwd, t->nStatus, t->start, t->end, t->fTotalUse,
						local_time->tm_year + 1900, local_time->tm_mon + 1, local_time->tm_mday, local_time->tm_hour, local_time->tm_min, local_time->tm_sec, t->nUseCount, t->fBalance, 0);
			}
			else {
				fprintf(file, "%s##%s##%d##%s##%s##%.1f##%s##%d##%.1f##%d\n",
					t->aName, t->aPwd, t->nStatus, t->start, t->end, t->fTotalUse,
					t->lasttime, t->nUseCount, t->fBalance, 0);
			}
		}
		else {
			// 将更新后的卡片信息写入文件
			if (strcmp(t->aName, card->aName)==0) {
				/*fprintf(file, "%s##%s##%d##%s##%s##%.1f##%4d%02d%02d-%02d:%02d:%02d##%d##%.1f##%d\n",
					t->aName, t->aPwd, t->nStatus, time_start, time_end, t->fTotalUse,
					local_time->tm_year + 1900, local_time->tm_mon + 1, local_time->tm_mday, local_time->tm_hour, local_time->tm_min, local_time->tm_sec, t->nUseCount, t->fBalance, 0);*/
				fprintf(file, "%s##%s##%d##%s##%s##%.1f##%4d-%02d-%02d %02d:%02d:%02d##%d##%.1f##%d\n",
					t->aName, t->aPwd, t->nStatus, t->start, t->end, t->fTotalUse,
					local_time->tm_year + 1900, local_time->tm_mon + 1, local_time->tm_mday, local_time->tm_hour, local_time->tm_min, local_time->tm_sec, t->nUseCount, t->fBalance, 1);
			}
			else {
				fprintf(file, "%s##%s##%d##%s##%s##%.1f##%s##%d##%.1f##%d\n",
					t->aName, t->aPwd, t->nStatus, t->start, t->end, t->fTotalUse,
					t->lasttime, t->nUseCount, t->fBalance, 1);
			}
		}
		t = t->next;
	}
	fclose(file);

	return flag;
}