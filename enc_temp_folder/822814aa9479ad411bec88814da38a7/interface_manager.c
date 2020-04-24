#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "tool.h"
#include "model.h"
#include "interface_card.h"
#include "card_manage.h"
#include "manager_manage.h"
#include "billing_manage.h"
#include "manager_manage.h"
#include "interface_manager.h"

char* id_of_manager;

void gotoMenu_manager(char* id, int level)
{
    id_of_manager = id;
    printf("你好，%s！你的权限为 %d\n", id, level);
    char inputnumber[5];				//接受用户数据并防溢出
    //循环打印屏幕
    do {
	  memset(inputnumber, 12, sizeof(inputnumber));
	  printf("——————管——理——员——菜——单——————\n");
	  printf("1、新建卡\n");
	  printf("2、查询卡及消费记录\n");
	  printf("3、充值\n");
	  printf("4、退费\n");
	  if (level < 2) {
		printf("5、卡一览\n");
		printf("6、修改卡状态\n");
		printf("7、修改卡密码\n");
		printf("8、营业数据统计\n");
	  }
	  if (level < 1) {
		printf("9、新建管理员\n");
		printf("10、管理员一览\n");
		printf("11、管理员删除\n");
		printf("12、计费标准修改\n");
	  }
	  printf("0、返回\n");
	  printf("———————————————————————————\n");
	  printf("输入选项前数字（0~%d）并按回车进行操作：", level < 2 ? (level < 1 ? 12 : 8) : 4);
	  scanf("%s", inputnumber);
	  system("cls");
	  int ans = -1;
	  if (inputnumber[2] == 0)ans = (inputnumber[0] - '0') * 10 + inputnumber[1] - '0';							//判断用户输入是不是单个字符
	  else if (inputnumber[1] == 0)ans = inputnumber[0] - '0';
	  if ((level == 2 && ans > 4) || (level == 1 && ans > 8))printf("输入不合法！请重新输入！\n");
	  else {
		switch (ans) {
		case 1: gotoCreateCard(); break;
		case 2: gotoCheckCard(); break;
		case 3: gotoRecharge(); break;
		case 4: gotoPayBack(); break;
		case 5:  gotoCheckAllCards(); break;
		case 6: gotoCreateCard(); break;
		case 7: gotoCreateCard(); break;
		case 8: gotoCreateCard(); break;
		case 9: gotoCreateCard(); break;
		case 10: gotoCreateCard(); break;
		case 11: gotoCreateCard(); break;
		case 12: gotoCreateCard(); break;
		case 0: system("cls"); break;
		default:
		    printf("输入不合法！请重新输入！\n");
		    system("pause");
		    system("cls");
		    break;
		}
	  }
    } while (inputnumber[0] != '0');
}

//新建卡
void gotoCreateCard() {
    char cardid[20] = { 0 }, password[20] = { 0 };
    double money;
    int iflegal = 1;
    printf("——————新——建——卡——————\n");
    printf("开卡须知：\n");
    printf("1、用户名（卡号）和密码长度须小于18\n");
    printf("2、开卡费用为10元，开卡时可充值最低10元（余额0元），必须充值整元\n");
    printf("3、若取消开卡，请在用户名或者密码输入界面输入“\\”或充值金额处填“0”\n");
    printf("———————————————————\n");
    do {
	  iflegal = 1;																		//判断此次输入是否合法的变量
	  memset(cardid, 0, sizeof(cardid));				//每次输入前格式化id缓存
	  printf("请输入用户名（卡号）：");
	  scanf("%s", cardid);
	  if (cardid[0] == 92 && cardid[1] == 0) {				//判断是否是退出操作
		system("cls");
		return;
	  }
	  if (cardid[18])iflegal = 0;																				//判断是否超过长度限制
	  if (iflegal) {
		card* checkname = check_card(cardid);
		if (checkname != NULL) {
		    printf("用户名已被使用！");
		    iflegal = 0;
		}
	  }
	  if (!iflegal)printf("输入有误！请重新输入\n");
    } while (!iflegal);
    do {
	  iflegal = 1;																					//判断是否是合法变量
	  memset(password, 0, sizeof(password));										//初始化id缓存
	  printf("请输入密码：");
	  scanf("%s", password);
	  if (password[0] == 92 && password[1] == 0) {									    //判断是否要退出
		system("cls");
		return;
	  }
	  if (password[18])iflegal = 0;														    //判断是否超过长度限制
	  if (!iflegal)printf("输入有误！请重新输入\n");
    } while (!iflegal);
    do {
	  iflegal = 1;
	  money = -1;
	  printf("请输入充值金额：");
	  scanf("%lf", &money);
	  if (money == 0) {																    //判断是否要退出
		system("cls");
		return;
	  }
	  if (money < 10)iflegal = 0;
	  if (!iflegal)printf("输入有误！请重新输入\n");
    } while (!iflegal);
    if (money != 0) {
	  card newone;
	  strcpy(newone.cardID, cardid);
	  strcpy(newone.password, password);
	  newone.moneyleft = money - 10;
	  newone.nStatus = 0;
	  newone.TotalUse = 0;
	  newone.nUseCount = 0;
	  newone.nDel = 0;
	  newone.timeToCreate = time(NULL);
	  newone.lastTimeOfUse = time(NULL);
	  create_a_billing_record(1, newone.cardID, money - 10, time(NULL), time(NULL), newone.moneyleft,id_of_manager);
	  char str[20];
	  time_ttostring(str, newone.timeToCreate);
	  printf("开卡成功！\n\n");
	  printf("%-18s%-18s%-10s%-20s\n", "卡号", "密码", "余额", "开卡时间");
	  printf("————————————————————————————————————\n");
	  printf("%-18s%-18s%-10.2lf%-20s\n", newone.cardID, password, money - 10, str);
	  printf("————————————————————————————————————\n");
	  create_a_card(&newone);
	  system("pause");
    }
    system("cls");
    return;
}

//查询卡
void gotoCheckCard() {
    printf("——————查——询——卡——————\n");
    printf("查询须知：\n");
    printf("1、选择精确查找或模糊查找后，精确或模糊输入卡号\n");
    printf("2、精确查询卡信息会显示该卡的资金变动记录，模糊查找不会显示\n");
    printf("3、若取消查询，请在用户名输入界面输入“\\”或查询选项处填“0”\n");
    printf("———————————————————\n");
    int iflegal;
    int ans = -1;
    do {
	  iflegal = 1;
	  ans = -1;
	  printf("请输入选项（1:精确查找/2:模糊查找）：");
	  scanf("%d", &ans);
	  if (ans == 0) {
		printf("已取消查找\n");
		break;
	  }
	  else if (ans == 1) {
		char id[20];
		printf("请精确输入查询卡号：");
		scanf("%s", id);
		if (check_card(id) != NULL) {
		    char time[20], timeofcreate[20];
		    time_ttostring(time, check_card(id)->lastTimeOfUse);
		    time_ttostring(timeofcreate, check_card(id)->timeToCreate);
		    printf("查询到如下信息：\n\n%-18s%-18s%-8s%-10s%-10s%-15s%-25s%-30s\n",
			  "卡号", "密码", "余额", "当前状态", "使用次数", "总使用金额", "新建卡时间", "最后一次下机时间");
		    printf("———————————————————————————————————————————————————————————————————————\n");
		    printf("%-18s%-18s%-8.2f%-10s%-10d%-15.2f%-25s%-30s\n",
			  check_card(id)->cardID, check_card(id)->password, check_card(id)->moneyleft, statustostring[check_card(id)->nStatus],
			  check_card(id)->nUseCount, check_card(id)->TotalUse, timeofcreate, time);
		    printf("———————————————————————————————————————————————————————————————————————\n");
		}
		else {
		    printf("查无此卡！现即将返回上一级菜单\n");
		}
	  }
	  else if (ans == 2) {
		char id[20];
		printf("请输入查询的卡号片段：");
		scanf("%s", id);
		cards_line* head = check_card_mohu(id);
		if (head != NULL) {
		    printf("查询到如下信息：\n\n%-18s%-18s%-8s%-10s%-10s%-15s%-25s%-30s\n",
			  "卡号", "密码", "余额", "当前状态", "使用次数", "总使用金额", "新建卡时间", "最后一次下机时间");
		    printf("———————————————————————————————————————————————————————————————————————\n");
		    while (head != NULL) {
			  char time[20], timeofcreate[20];
			  time_ttostring(time,head->a_card.lastTimeOfUse);
			  time_ttostring(timeofcreate, head->a_card.timeToCreate);
			  printf("%-18s%-18s%-8.2f%-10s%-10d%-15.2f%-25s%-30s\n",
				head->a_card.cardID, head->a_card.password, head->a_card.moneyleft, statustostring[head->a_card.nStatus],
				head->a_card.nUseCount, head->a_card.TotalUse, timeofcreate, time);
			  head = head->next;
		    }
		    printf("———————————————————————————————————————————————————————————————————————\n");
		}
		else {
		    printf("查询不到相关信息！现即将返回上一级菜单\n");
		}
	  }
    } while (ans != 0 && ans != 1 && ans != 2);
    system("pause");
    system("cls");
    return;
}

//充值
void gotoRecharge() {
    char cardid[20],pas[20];
    int iflegal = 0;
    double  val;
    printf("——————充——值——————\n");
    printf("充值须知：\n");
    printf("1、精确输入充值卡号\n");
    printf("2、搜索到充值卡后，输入充值金额，输入管理员密码完成充值\n");
    printf("3、若取消充值，请在卡号或者管理员密码输入界面输入“\\”或充值金额处填“0”\n");
    printf("———————————————————\n");
    printf("请精确输入充值卡号：");
    do {
	  iflegal = 0;
	  scanf("%s", cardid);
	  if (cardid[1] == 0 && cardid[0] == 92) {
		printf("已取消充值\n");
		system("pause");
		system("cls");
		return;
	  }
	  if (check_card(cardid) == NULL) {
		printf("查无此卡！请重新输入：");
		iflegal = 0;
	  }
	  else {
		iflegal = 1;
	  }
    } while (!iflegal);
    printf("请输入充值金额：");
    do {
	  iflegal = 0;
	  scanf("%lf", &val);
	  if (val == 0) {
		printf("已取消充值\n");
		system("pause");
		system("cls");
		return;
	  }
	  else if(val<0){
		printf("输入有误！请重新输入：");
	  }
	  else {
		iflegal = 1;
	  }
    } while (!iflegal);
    printf("请输入管理员账户密码：");
    do {
	  iflegal = 0;
	  scanf("%s", pas);
	  if (pas[1] == 0 && pas[0] == 92) {
		printf("已取消充值\n");
		system("pause");
		system("cls");
		return;
	  }
	  else if (check_manager_with_pas(id_of_manager, pas) == NULL) {
		printf("密码错误！请重新输入：");
	  }
	  else {
		iflegal = 1;
	  }
    } while (!iflegal);
    card* c = check_card_without_free(cardid);
    c->moneyleft += val;
    create_a_billing_record(1, cardid, val, time(NULL), time(NULL), c->moneyleft,id_of_manager);
    printf("充值成功！%s现有余额%.2f元\n", cardid, c->moneyleft);
    cards_override();
    system("pause");
    system("cls");
}

//退费
void gotoPayBack() {
    char cardid[20], pas[20];
    int iflegal = 0;
    double  val;
    printf("——————退——费——————\n");
    printf("退费须知：\n");
    printf("1、精确输入退费卡号\n");
    printf("2、搜索到退费卡后，输入退费金额，输入管理员密码完成退费\n");
    printf("3、若取消退费，请在卡号或者管理员密码输入界面输入“\\”或退费金额处填“0”\n");
    printf("4、若退还全部费用，退费金额处填“-1”\n");
    printf("———————————————————\n");
    printf("请精确输入退费卡号：");
    do {
	  iflegal = 0;
	  scanf("%s", cardid);
	  if (cardid[1] == 0 && cardid[0] == 92) {
		printf("已取消退费\n");
		system("pause");
		system("cls");
		return;
	  }
	  if (check_card(cardid) == NULL) {
		printf("查无此卡！请重新输入：");
		iflegal = 0;
	  }
	  else {
		printf("查询到如下信息：\n\n%-18s%-8s%-10s%-10s%-15s\n",
		    "卡号",  "余额", "当前状态", "使用次数", "总使用金额");
		printf("———————————————————————————————————————————————————\n");
		printf("%-18s%-8.2f%-10s%-10d%-15.2f\n",
		    check_card(cardid)->cardID, check_card(cardid)->moneyleft, statustostring[check_card(cardid)->nStatus],
		    check_card(cardid)->nUseCount, check_card(cardid)->TotalUse);
		printf("———————————————————————————————————————————————————\n");
		iflegal = 1;
	  }
    } while (!iflegal);
    printf("请输入退费金额：");
    do {
	  iflegal = 0;
	  scanf("%lf", &val);
	  if (val == 0) {
		printf("已取消退费\n");
		system("pause");
		system("cls");
		return;
	  }
	  else if (val < 0&&val!=-1) {
		printf("输入有误！请重新输入：");
	  }
	  else {
		iflegal = 1;
	  }
    } while (!iflegal);
    printf("请输入管理员账户密码：");
    do {
	  iflegal = 0;
	  scanf("%s", pas);
	  if (pas[1] == 0 && pas[0] == 92) {
		printf("已取消退费\n");
		system("pause");
		system("cls");
		return;
	  }
	  else if (check_manager_with_pas(id_of_manager, pas) == NULL) {
		printf("密码错误！请重新输入：");
	  }
	  else {
		iflegal = 1;
	  }
    } while (!iflegal);
    card* c = check_card_without_free(cardid);
    if (val == -1) {
	  val = c->moneyleft;
	  c->moneyleft = 0;
    } 
    else {
	  c->moneyleft -= val;
    }
    create_a_billing_record(2, cardid, val, time(NULL), time(NULL), c->moneyleft,id_of_manager);
    printf("退费成功！%s现有余额%.2f元\n", cardid, c->moneyleft);
    cards_override();
    system("pause");
    system("cls");
}

//卡一览
void gotoCheckAllCards() {
    printf("——————卡——一——览——————\n");
    printf("现有如下卡信息：\n\n%-18s%-18s%-8s%-10s%-10s%-15s%-25s%-30s\n",
	  "卡号", "密码", "余额", "当前状态", "使用次数", "总使用金额", "新建卡时间", "最后一次下机时间");
    printf("———————————————————————————————————————————————————————————————————————\n");
    cards_line* all = check_card_mohu("");
    while (all != NULL) {
	  char timeofcreate[20], timea[20];
	  time_ttostring(timeofcreate, all->a_card.timeToCreate);
	  time_ttostring(timea, all->a_card.lastTimeOfUse);
	  printf("%-18s%-18s%-8.2f%-10s%-10d%-15.2f%-25s%-30s\n",
		all->a_card.cardID, all->a_card.password, all->a_card.moneyleft, statustostring[all->a_card.nStatus],
		all->a_card.nUseCount, all->a_card.TotalUse, timeofcreate, timea);
	  all = all->next;
    }
    system("pause");
    system("cls");
}

//修改卡状态
void gotoChangeStatus() {
    
}