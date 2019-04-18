#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

typedef struct SNAP *SNAP_LIST;

extern SNAP_LIST new_SNAP(int id,char* name, char* address, char* phone);

extern int SNAP_hash(int id);

extern void SNAP_write();

extern void SNAP_read();

extern int SNAP_getID(SNAP_LIST list);

extern void SNAP_insert(int id, char* name, char* address, char* phone);

extern LinkedList SNAP_keyLookup(int id);

extern LinkedList SNAP_lookup(int id, char* name, char* address, char* phone);

extern LinkedList SNAP_delete(int id, char* name, char* address, char* phone);

extern void SNAP_print();

extern void SNAP_printSingle(SNAP_LIST this);

extern void SNAP_printList(LinkedList list);