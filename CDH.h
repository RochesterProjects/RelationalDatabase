#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

typedef struct CDH *CDH_LIST;

extern CDH_LIST new_CDH(char* course, char day, char* hour);

extern int CDH_hash(char* course, char day, char* hour);

extern char CDH_getDay(CDH_LIST this);

extern char* CDH_getHour(CDH_LIST this);

extern char* CDH_getCourse(CDH_LIST this);

extern CDH_LIST* CDH_getAll();

extern void CDH_insert(char* course, char day, char* hour);

extern LinkedList CDH_keyLookup(char* course, char day, char* hour);

extern LinkedList CDH_lookup(char* course, char day , char* hour);

extern void CDH_delete(char* course, char day , char* hour);

extern void CDH_print();

extern void CDH_printSingle(CDH_LIST node);

extern void CDH_printList(LinkedList list);