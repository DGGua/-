#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include "model.h"
#include <string.h>
#include "tool.h"
#include <malloc.h>



void time_ttostring(char* str, time_t time) {
    struct tm p;
    localtime_s(&p, &time);
    strftime(str, 20, "%Y-%m-%d %H:%M:%S", &p);
}
void cardcopy(card* toward, card* source) {
	strcpy(toward->cardID, source->cardID);
	strcpy(toward->password, source->password);
	toward->moneyleft = source->moneyleft;
	toward->nStatus = source->nStatus;
	toward->TotalUse = source->TotalUse;
	toward->nUseCount = source->nUseCount;
	toward->nDel = source->nDel;
	toward->timeToCreate = source->timeToCreate;
	toward->lastTimeOfUse = source->lastTimeOfUse;
	toward->TimeToEnd = source->TimeToEnd;

}

void managercopy(manager* toward, manager* source)
{
    strcpy(toward->managerID, source->managerID);
    strcpy(toward->password, source->password);
    toward->level = source->level;
    toward->lastTimeOfUse = source->lastTimeOfUse;
    toward->timeToCreate = source->timeToCreate;
}

void billingcopy(billing* toward, billing* source)
{
    strcpy(toward->cardID, source->cardID);
    toward->begin= source->begin;
    toward->cost = source->cost;
    toward->end = source->end;
    toward->model = source->model;
    toward->moneyleft = source->moneyleft;
    strcpy(toward->managerID, source->managerID);
}

int stringtoint(char* numbers) {
	int res = 0;
	for (int i = 0; numbers[i] != 0; i++) {
		res = res * 10 + numbers[i]-'0';
	}
	return res;
}


double moneytopay(time_t timebegin, time_t end) {
    struct tm a;
    long long between = end-timebegin;
    return between*moneypersec;
}
