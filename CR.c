#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"


typedef struct CR *CR_LIST;

/** relation for Course-Room */
struct CR{
	char* course;
	char* room;
	LinkedList collisions;
};

CR_LIST CR_HASHTABLE[1009];

CR_LIST new_CR(char* course, char* room){
	CR_LIST this = (CR_LIST)malloc(sizeof(CR_LIST));
	this->course = course;
	this->room = room;
	this->collisions = new_LinkedList();
	return this;
}

int CR_hash(char* course){
	int sum = 0;
	char* c;
	for(c = course; *c != '\0'; c++){
		sum += (int) *c;
	}
	return sum % 1009;
}

char* CR_getRoom(CR_LIST node){
	return node->room;
}

char* CR_getCourse(CR_LIST node){
	return node->course;
}
void CR_insert(char* course, char* room){
	CR_LIST this = new_CR(course,room);
	int index = CR_hash(course);
	if(CR_HASHTABLE[index] == NULL){
		CR_HASHTABLE[index] = this;
	} else{
		CR_LIST node = CR_HASHTABLE[index];
		if(strcmp(node->course,course) == 0 && strcmp(node->room, room) == 0){
			printf("Tuple already in relation.\n");
		}else{LinkedList_add_at_end(node->collisions, this);}
	}
}

LinkedList CR_keyLookup(char* course){
	LinkedList result = new_LinkedList();
	int index = CR_hash(course);
	LinkedList_add_at_end(result, CR_HASHTABLE[index]);
	return result;
}

LinkedList CR_lookup(char* course, char* room){
	LinkedList result = new_LinkedList();
	if(course != NULL && room != NULL){
		LinkedList list = CR_keyLookup(course);
		LinkedListIterator iterator = LinkedList_iterator(list);
			while (LinkedListIterator_hasNext(iterator)) {
				CR_LIST node = LinkedListIterator_next(iterator);
				if(strcmp(node->room,room) == 0){
					LinkedList_add_at_end(result, node);
				}
			}
		}
	if(course == NULL && room != NULL){
		for(int i = 0; i < 1009; i++){
			if(CR_HASHTABLE[i] != NULL){
				if(CR_HASHTABLE[i]->room == room){LinkedList_add_at_end(result, CR_HASHTABLE[i]);}
				LinkedList list = CR_HASHTABLE[i]->collisions;
				LinkedListIterator iterator = LinkedList_iterator(list);
				while (LinkedListIterator_hasNext(iterator)) {
					CR_LIST node = LinkedListIterator_next(iterator);
					if(strcmp(node->room,room) == 0){
						LinkedList_add_at_end(result, node);
					}
				}
				free(iterator);
			}
		}
	}
	if(course != NULL && room == NULL){
		return CR_keyLookup(course);
	}
	return result;
}

void CR_delete(char* course, char* room){
	LinkedList result = new_LinkedList();
	if(course != NULL && room != NULL){
		int index = CR_hash(course);
		if(strcmp(CR_HASHTABLE[index]->room,room) == 0){
			free(CR_HASHTABLE[index]);
			CR_HASHTABLE[index] = NULL;
		}
	}
	if(course == NULL && room != NULL){
		for(int i = 0; i < 1009; i++){
			if(CR_HASHTABLE[i] != NULL){
				LinkedList list = CR_HASHTABLE[i]->collisions;
				LinkedListIterator iterator = LinkedList_iterator(list);
				while (LinkedListIterator_hasNext(iterator)) {
					CR_LIST node = LinkedListIterator_next(iterator);
					if(strcmp(node->room,room) == 0){
						LinkedList_remove(result, node);
					}
				}
				free(iterator);
				if(strcmp(CR_HASHTABLE[i]->room,room) == 0){
					free(CR_HASHTABLE[i]);
					CR_HASHTABLE[i] = NULL;
				}
			}
		}
	}
	if(course != NULL && room == NULL){
		int index = CR_hash(course);
		free(CR_HASHTABLE[index]);
		CR_HASHTABLE[index] = NULL;
	}
}

CR_LIST* CR_getAll()
{
    return CR_HASHTABLE;
}



void CR_printSingle(CR_LIST node){
	printf("%s \t %s\n", node->course, node->room);
}

void CR_printList(LinkedList list){
	printf("Course \t Room\n");
	LinkedListIterator iterator1 =  LinkedList_iterator(list);
	while (LinkedListIterator_hasNext(iterator1)) {
		CR_LIST node = LinkedListIterator_next(iterator1);
		CR_printSingle(node);
	}
	free(iterator1);

}

void CR_print(){
	printf("Course \t Room\n");
	for(int i = 0; i < 1009; i++){
		if(CR_HASHTABLE[i] != NULL){
			CR_LIST row = CR_HASHTABLE[i];
			printf("%s \t %s\n", row->course, row->room);
			if(row->collisions != NULL){
				LinkedList list = CR_HASHTABLE[i]->collisions;
				LinkedListIterator iterator =  LinkedList_iterator(list);
				while (LinkedListIterator_hasNext(iterator)) {
					CR_LIST node = LinkedListIterator_next(iterator);
					printf("%s \t %s\n", node->course, node->room);
				}
				free(iterator);
			}
		}
	}
}



/*
int main(){
	CR_insert("CS101", "Turing Aud.");
	CR_insert("EE200", "25 Ohm Hall" );
	CR_insert("PH100", "Newton Lab.");
	CR_print();

	printf("----Lookup Test----\n");
	LinkedList cs101 = CR_lookup("CS101", NULL); //lookup(CS101, *)
	CR_printList(cs101);
	printf("----Delete Test---\n");
	CR_delete(NULL, "Turing Aud.");
	CR_print();
}
*/