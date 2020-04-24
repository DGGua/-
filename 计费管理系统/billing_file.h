#ifndef _BILLING_FILE_
#define _BILLING_FILE_
#include "model.h"
#include <time.h>
void add_a_billing_record(billing* p);
void add_records_from_file(billings_line** head);
#endif

