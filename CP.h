#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"


typedef struct CP *CP_LIST;

extern CP_LIST new_CP(char* course, char* prereq);

extern int CP_hash(char* course);


extern void CP_insert(char* course, char* prereq);

extern LinkedList CP_keyLookup(char* prereq);

extern LinkedList CP_lookup(char* course, char* prereq);

extern void CP_delete(char* course, char* prereq);

extern void CP_printSingle(CP_LIST node);

extern void CP_print();

extern void CP_printList(LinkedList list);