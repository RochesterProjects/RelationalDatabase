#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"


typedef struct CR *CR_LIST;

extern CR_LIST new_CR(char* course, char* room);

extern int CR_hash(char* course);

extern char* CR_getRoom(CR_LIST node);

extern char* CR_getCourse(CR_LIST node);

extern CR_LIST* CR_getAll();

extern void CR_insert(char* course, char* room);

extern LinkedList CR_keyLookup(char* course);

extern LinkedList CR_lookup(char* course, char* room);

extern void CR_delete(char* course, char* room);

extern void CR_printSingle(CR_LIST node);

extern void CR_print();

extern void CR_printList(LinkedList list);