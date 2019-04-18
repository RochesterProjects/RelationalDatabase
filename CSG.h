
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

typedef struct CSG *CSG_LIST;

extern CSG_LIST new_CSG(char* course, int id, char* grade);

extern char* CSG_getGrade(CSG_LIST node);

extern char* CSG_getCourse(CSG_LIST node);

extern int CSG_getStudentID(CSG_LIST node);

extern int CSG_hash(char* course, int id);

extern void CSG_insert(char* course, int id, char* grade);

extern LinkedList CSG_keyLookup(char* course, int id);

extern LinkedList CSG_lookup(char* course, int id, char* grade);

extern void CSG_delete(char* course, int id, char* grade);

extern void CSG_print();

extern void CSG_printSingle(CSG_LIST this);

extern void CSG_printList(LinkedList list);