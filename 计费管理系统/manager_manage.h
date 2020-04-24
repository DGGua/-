#ifndef _MANAGER_MANAGE_
#define _MANAGER_MANAGE_
#include "model.h"
#include <time.h>
void create_a_manager(manager* the_new_manager);
manager* check_manager(char* id);
manager* check_manager_with_pas(char* id, char* pas);
void add_managers();
manager* check_manager_without_free(char* id); 
void free_line_manager(managers_line** headl);
void managers_override();
void free_line_with_override_manager();
managers_line* check_manager_mohu(char* id);
#endif
