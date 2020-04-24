#ifndef _MODEL_
#define _MODEL_
#include <time.h>


#define cardpath "data\\card.txt"
#define billingpath "data\\billing.txt"
#define managerpath "data\\manager.txt"

double moneypersec;
char statustostring[][7];
char biilingmodeltostring[][7];

typedef struct _manager {
    char managerID[19];
    char password[19];
    int  level;           // 权限，0最高
    time_t timeToCreate;
    time_t lastTimeOfUse;
} manager;

typedef struct _managers_line {
    manager a_manager;
    struct  _managers_line* next;
}managers_line;

typedef struct _card {
	char cardID[19];
	char password[19];
	double moneyleft;
	int  nStatus;           // 卡状态(0-未上机；1-正在上机；2-已注销；3-失效)
	double TotalUse;        // 累计花费金额
	int nUseCount;          // 使用次数
	int nDel;               // 删除标识 0-未删除,1-删除
	time_t timeToCreate;
	time_t lastTimeOfUse;
	time_t TimeToEnd;            // 卡的截止时间 
	
} card;


typedef struct _cards_line {
    card a_card;
    struct _cards_line* next;
}cards_line;


typedef struct _billing {
    int model;		//0-消费 1-充值 2-退费
    char cardID[19];
    time_t begin;
    time_t end;
    int cost;
    int moneyleft;
    char managerID[20];
}billing;

typedef struct _billing_line {
    billing a_record;
    struct _billing_line* next;
}billings_line;
#endif