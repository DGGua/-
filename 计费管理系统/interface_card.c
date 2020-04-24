//计费也有问题
//billing的输出
//mallocdewenti
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "model.h"
#include "interface_card.h"
#include "tool.h"
#include "card_manage.h"
#include "billing_manage.h"
#include "manager_manage.h"
#include "interface_manager.h"

char* id_of_card;

//主菜单界面
void gotoMenu_card(char* id){
    id_of_card = id;
	printf("你好，%s！\n",id);
	char inputnumber[5];				//接受用户数据并防溢出
	//循环打印屏幕
	do {
		printf("——————主——菜——单——————\n");
		printf("1、上机\n");
		printf("2、下机\n");
		printf("3、查询当前卡信息\n");
		printf("4、查询消费记录\n");
		printf("5、注销卡\n");
		printf("0、退出登录\n");
		printf("———————————————————\n");
		printf("输入选项前数字（0~5）并按回车进行操作："); 
		scanf("%s", inputnumber);
		system("cls");
		if (inputnumber[1] != 0)inputnumber[0] = 0;							//判断用户输入是不是单个字符
		switch (inputnumber[0]-'0') {
		case 1:system("cls"); gotoGetUp(); break;
		case 2:system("cls"); gotoGetDown(); break;
		case 3:system("cls"); gotoGetInfo(); break;
		case 4:system("cls"); gotoCheckLog(); break;
		case 5:system("cls"); gotoDelete(); break;
		case 0: system("cls");gotoExit(); break;
		default:
			printf("输入不合法！请重新输入！\n"); 
			system("pause");
			system("cls");
			break;
		}
	} while (inputnumber[0] != '0');
}

//上机操作							    有问题
void gotoGetUp() {
    char cardid[20] = { 0 }, password[20] = { 0 };
    int iflegal = 1, ifhasone = 1;
    switch (check_card(id_of_card)->nStatus) {
    case 1:printf("当前账户已经上机！请先下机\n"); break;
    case 2:printf("当前账户已被注销！\n"); break;
    case 3:printf("当前账户已经过期！\n"); break;
    default: {
	  printf("——————上—————机——————\n");
	  printf("上机须知：\n");
	  printf("4、计费以秒计，不足一秒的按一秒处理\n");
	  printf("1、当前计费标准：%.2f元/秒\n",moneypersec);
	  printf("6、若下机时余额不足将无法下机，充值后才能下机\n");
	  printf("7、若有相关活动或是计费问题，请咨询管理员\n");
	  printf("8、若取消上机并返回，请输入“\\”\n");
	  printf("———————————————————\n");
	  printf("是否确定上机？（1/0）：");
	  char ans[5];
	  scanf("%s", ans);
	  while (ans[1] != 0 || (ans[0] != '1' && ans[0] != '0')) {
		printf("输入有误！请重新输入（1/0）：\n");
		scanf("%s", ans);
	  }
	  if (ans[0] =='0') {
		printf("已取消上机，现返回目录\n");
	  }
	  else {
		time_t getuptime = time(NULL);
		char str[20];
		time_ttostring(str, getuptime);
		card* c = check_card_without_free(id_of_card);
		c->lastTimeOfUse = getuptime;
		c->nStatus = 1;
		cards_override();
		printf("%s 于 %s 上机成功！\n", cardid, str);
		printf("下机时请选择“下机”选项并结算\n");
		
	  }
    }
    }
    system("pause");
    system("cls");
}

//下机操作                        
void gotoGetDown() {
	if (check_card(id_of_card)->nStatus!=1) {
		printf("当前账户未在上机！无法下机！\n");
		system("pause");
		system("cls");
	}
	else {
		time_t nowtime=time(NULL);
		time_t getuptime = check_card(id_of_card)->lastTimeOfUse;
		double money_to_pay = moneytopay(getuptime,nowtime);
		if (check_card(id_of_card)->moneyleft < money_to_pay) {
			printf("卡中余额不足！请联系管理员充值后下机！\n");
			system("pause");
			system("cls");
		}
		else {
			card* cardnow = check_card_without_free(id_of_card);
			time_t getdowntime = time(NULL);
			cardnow->moneyleft -= money_to_pay;
			create_a_billing_record(0,id_of_card, money_to_pay, cardnow->lastTimeOfUse, getdowntime,cardnow->moneyleft,NULL);
			cardnow->nStatus = 0;
			cardnow->TotalUse += money_to_pay;
			cardnow->lastTimeOfUse = getdowntime;
			cardnow->nUseCount++;
			cards_override();
			printf(" 下机成功！\n");
			printf("%-15s%-10s\n————————————————\n%-15.2f%-10.2f\n","本次花费","卡中剩余", money_to_pay, check_card(id_of_card)->moneyleft);
			system("pause");
			system("cls");
		}
	}
}

//查询当前卡信息
void gotoGetInfo(){
    char time[20],timeofcreate[20];
    time_ttostring(time, check_card(id_of_card)->lastTimeOfUse);
    time_ttostring(timeofcreate, check_card(id_of_card)->timeToCreate);
    printf("——————查—询—卡—信—息——————\n");
    printf("查询到如下信息：\n\n%-18s%-8s%-10s%-10s%-15s%-25s%-30s\n",
	  "卡号","余额","当前状态","使用次数", "总使用金额","新建卡时间","最后一次下机时间");
    printf("—————————————————————————————————————————————————————\n");
    printf("%-18s%-8.2f%-10s%-10d%-15.2f%-25s%-30s\n",
	  check_card(id_of_card)->cardID, check_card(id_of_card)->moneyleft, statustostring[check_card(id_of_card)->nStatus], 
	  check_card(id_of_card)->nUseCount, check_card(id_of_card)->TotalUse, timeofcreate, time);
    printf("—————————————————————————————————————————————————————\n");
    system("pause");
    system("cls");
    return;
}

//查询消费记录操作               有问题
void gotoCheckLog() {
    printf("——————查—询—消—费—记—录—————\n");
    printf("查询到%s以下金额记录：\n\n", id_of_card);
    printf("%-8s%-25s%-25s%-20s%-10s%-20s\n","","开始时间","结束时间","消费/充值金额","余额","操作管理员");
    printf("——————————————————————————————————————————————\n");
    billings_line *o = check_billing_record_with_id(id_of_card);
    
    while (o != NULL) {
	  char t1[20], t2[20];
	  time_ttostring(t1, o->a_record.begin);
	  time_ttostring(t2, o->a_record.end);
		printf("%-8s%-25s%-25s%-20d%-10d%-20s\n",
		biilingmodeltostring[o->a_record.model],t1,t2, o->a_record.cost, o->a_record.moneyleft,o->a_record.managerID);
	  o = o->next;
    }
    printf("——————————————————————————————————————————————\n");
    system("pause");
    system("cls");
}

//注销操作
void gotoDelete() {
    printf("——————注—————销——————\n");
    printf("注销须知：\n");
    printf("1、卡注销后仍可登录、查询，但不可上机\n");
    printf("2、注销后卡用户名会保留，该用户名不会被再次注册\n");
    printf("3、若卡中有余额将提示，注销过程无法退还，但可以取消注销先行联系管理员退费\n");
    printf("———————————————————\n");
    switch (check_card(id_of_card)->nStatus) {
    case 1:printf("当前卡正在上机！请先下机结算\n");
    case 2:printf("当前卡已注销！\n");
    case 3:printf("当前卡已过期！\n");
    default: {
	  char timea[20], timeofcreate[20];
	  time_ttostring(timea, check_card(id_of_card)->lastTimeOfUse);
	  time_ttostring(timeofcreate, check_card(id_of_card)->timeToCreate);
	  printf("查询到如下信息：\n\n%-18s%-8s%-10s%-10s%-15s%-25s%-30s\n",
		"卡号", "余额", "当前状态", "使用次数", "总使用金额", "新建卡时间", "最后一次下机时间");
	  printf("—————————————————————————————————————————————————————\n");
	  printf("%-18s%-8.2f%-10s%-10d%-15.2f%-25s%-30s\n",
		check_card(id_of_card)->cardID, check_card(id_of_card)->moneyleft, statustostring[check_card(id_of_card)->nStatus],
		check_card(id_of_card)->nUseCount, check_card(id_of_card)->TotalUse, timeofcreate, timea);
	  printf("—————————————————————————————————————————————————————\n");
	  if (check_card(id_of_card)->moneyleft > 0) {
		printf("当前卡中还有余额%.2f元，是否继续进行注销（1/0）：", check_card(id_of_card)->moneyleft);
		int ans;
		do {
		    scanf("%d", &ans);
		    if (ans == 0) {
			  printf("已取消注销\n");
			  system("pause");
			  system("cls");
			  return;
		    }
		    else if (ans != 1)printf("输入有误！请重新输入（1/0）：");
		} while (ans != 1 && ans != 0);
	  }
	  char password[20];
	  int  iflegal = 0;
	  do {
		iflegal = 1;
		memset(password, 0, sizeof(password));
		printf("请输入密码（输入：“\\”以终止注销）：");
		scanf("%s", password);
		if (password[0] == 92 && password[1] == 0) {
		    printf("已取消注销\n");
		    system("pause");
		    system("cls");
		    return;
		}
		if (password[18] != 0 || password[19] != 0)iflegal = 0;
		if (check_card_with_pas(id_of_card, password) == NULL)iflegal = 0;
		if (!iflegal) {
		    printf("输入有误！请重新输入\n");
		}
	  } while (!iflegal);
	  card* c = check_card_without_free(id_of_card);
	  c->nStatus = 2;
	  c->moneyleft = 0;
	  c->lastTimeOfUse = time(NULL);
	  cards_override();
	  printf("%s 已完成注销操作\n", id_of_card);
    }
    }
    system("pause");
    system("cls");
}

//退出程序
void gotoExit() {
	system("cls");
	return;
}
