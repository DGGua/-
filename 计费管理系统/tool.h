#ifndef _TOOL_
#define _TOOL_
#include "model.h"
#include <time.h>

void time_ttostring(char* str, time_t time);
void cardcopy(card* toward, card* source);
void managercopy(manager* toward, manager* source);
int daybetween(int year_start, int month_start, int day_start, int year_end, int month_end, int day_end);
int stringtoint(char* numbers);
double moneytopay(time_t timebegin, time_t end);
void billingcopy(billing* toward, billing* source);
#endif

