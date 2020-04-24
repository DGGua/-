#ifndef _BILLING_MANAGE_
#define _BILLING_MANAGE_
#include "model.h"
#include <time.h>
void create_a_billing_record(int model, char* id, double money, time_t from, time_t to, double moneyleft, char* managerID);
billings_line* check_billing_record_with_id(char* id);
#endif
