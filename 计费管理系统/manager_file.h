#ifndef _MANAGER_FILE_
#define _MANAGER_FILE_
#include "model.h"
#include <time.h>
void add_managers_from_file(managers_line** head);
void add_a_manager_to_file(manager* p);
void managers_override_to_file(managers_line* head);
#endif

