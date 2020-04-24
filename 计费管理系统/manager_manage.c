#define _CRT_SECURE_NO_WARNINGS
#include "model.h"
#include"tool.h"
#include <string.h>
#include <malloc.h>
#include "manager_file.h"
#include "manager_manage.h"

managers_line* head_manager = NULL, * last_manager = NULL, * mohuhead_manager = NULL;
manager buf;

void managers_override() {
    free_line_with_override_manager();
}

void free_line_with_override_manager() {
    managers_override_to_file(head_manager);
    managers_line* p = head_manager;
    while (head_manager != NULL) {
	  head_manager = head_manager->next;
	  free(p);
	  p = head_manager;
    }
}

void free_line_manager(managers_line** headl) {
    managers_line* p = *headl, * o = *headl;
    *headl = NULL;
    while (p != NULL) {
	  p = p->next;
	  free(o);
	  o = p;
    }
}

void add_managers() {
    add_managers_from_file(&head_manager);
}

void create_a_manager(manager* the_new_manager) {
    add_a_manager_to_file(the_new_manager);
}

manager* check_manager(char* id) {
    add_managers_from_file(&head_manager);
    managers_line* point = head_manager;
    while (point != NULL) {
	  if (strcmp(id, point->a_manager.managerID) == 0) {
		break;
	  }
	  point = point->next;
    }
    if (point == NULL) {
	  free_line_manager(&head_manager);
	  return NULL;
    }
    else {
	  managercopy(&buf, &(point->a_manager));
	  free_line_manager(&head_manager);
	  return &buf;
    }
}

manager* check_manager_with_pas(char* id, char* pas) {
    add_managers_from_file(&head_manager);
    managers_line* point = head_manager;
    while (point != NULL) {
	  if (strcmp(id, point->a_manager.managerID) == 0 && strcmp(pas, point->a_manager.password) == 0) {
		break;
	  }
	  point = point->next;
    }
    if (point == NULL) {
	  free_line_manager(&head_manager);
	  return NULL;
    }
    else {
	 
	  managercopy(&buf, &(point->a_manager));
	  free_line_manager(&head_manager);
	  return &buf;
    }
}

manager* check_manager_without_free(char* id) {
    add_managers_from_file(&head_manager);
    managers_line* point = head_manager;
    while (point != NULL) {
	  if (strcmp(id, point->a_manager.managerID) == 0) {
		break;
	  }
	  point = point->next;
    }
    if (point == NULL) {
	  return NULL;
    }
    else {
	  return &(point->a_manager);
    }
}

managers_line* check_manager_mohu(char* id) {
    if (mohuhead_manager != NULL) {
	  free_line_manager(&mohuhead_manager);
    }
    add_managers_from_file(&head_manager);
    managers_line* point = head_manager, * p = mohuhead_manager;
    char* ask;
    while (point != NULL) {
	  if ((ask = strstr(point->a_manager.managerID, id) != NULL)) {
		if (mohuhead_manager == NULL) {
		    mohuhead_manager = (managers_line*)malloc(sizeof(managers_line));
		    mohuhead_manager->next = NULL;
		    managercopy(&(mohuhead_manager->a_manager), &(point->a_manager));
		    p = mohuhead_manager;
		}
		else {
		    p->next = (managers_line*)malloc(sizeof(managers_line));
		    p = p->next;
		    p->next = NULL;
		    managercopy(&(p->a_manager), &(point->a_manager));
		}
	  }
	  point = point->next;
    }
    return mohuhead_manager;

}