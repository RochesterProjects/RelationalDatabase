#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"




/** relation for Course- Prerequiste */
typedef struct CP *CP_LIST;
struct CP{
	char* course;
	char* prereq;
	LinkedList collisions;
};

CP_LIST CP_HASHTABLE[1009];

CP_LIST new_CP(char* course, char* prereq){
	CP_LIST this = (CP_LIST)malloc(sizeof(CP_LIST));
	this->course = course;
	this->prereq = prereq;
	this->collisions = new_LinkedList();
	return this;
}

int CP_hash(char* course, char* prereq){
	int sum = 0;
	char* c;
	for(c = course; *c != '\0'; c++){
		sum += (int) *c;
	}
	for(c = prereq; *c != '\0'; c++){
		sum += (int) *c;
	}
	return sum % 1009;
}

void CP_insert(char* course, char* prereq){
	CP_LIST this = new_CP(course,prereq);
	int index = CP_hash(course,prereq);
	if(CP_HASHTABLE[index] == NULL){
		CP_HASHTABLE[index] = this;
	} else{
		CP_LIST node = CP_HASHTABLE[index];
		if(strcmp(node->course,course) == 0 && strcmp(node->prereq, prereq) == 0){
			printf("Tuple already in relation.\n");
		}else{LinkedList_add_at_end(node->collisions, this);}
	}
}

LinkedList CP_keyLookup(char* course, char* prereq){
	LinkedList result = new_LinkedList();
	int index = CP_hash(course, prereq);
	if(CP_HASHTABLE[index] == NULL){return result;}
	LinkedList_add_at_end(result, CP_HASHTABLE[index]);
	return result;
}

LinkedList CP_lookup(char* course, char* prereq){
	LinkedList result = new_LinkedList();
	if(course != NULL && prereq != NULL){
		return CP_keyLookup(course,prereq);
	}
	if(course == NULL && prereq != NULL){
		for(int i = 0; i < 1009; i++){
			if(CP_HASHTABLE[i] != NULL){
				if(CP_HASHTABLE[i]->prereq == prereq){LinkedList_add_at_end(result, CP_HASHTABLE[i]);}
				LinkedList list = CP_HASHTABLE[i]->collisions;
				LinkedListIterator iterator = LinkedList_iterator(list);
				while (LinkedListIterator_hasNext(iterator)) {
					CP_LIST node = LinkedListIterator_next(iterator);
					if(strcmp(node->prereq,prereq) == 0){
						LinkedList_add_at_end(result, node);
					}
				}
				free(iterator);
			}
		}
	}
	if(course != NULL && prereq == NULL){
		for(int i = 0; i < 1009; i++){
			if(CP_HASHTABLE[i] != NULL){
				if(CP_HASHTABLE[i]->course == course){LinkedList_add_at_end(result, CP_HASHTABLE[i]);}
				LinkedList list = CP_HASHTABLE[i]->collisions;
				LinkedListIterator iterator = LinkedList_iterator(list);
				while (LinkedListIterator_hasNext(iterator)) {
					CP_LIST node = LinkedListIterator_next(iterator);
					if(strcmp(node->course,course) == 0){
						LinkedList_add_at_end(result, node);
					}
				}
				free(iterator);
			}
		}
	}
	return result;

}

void CP_delete(char* course, char* prereq){
	LinkedList result = new_LinkedList();
	if(course != NULL && prereq != NULL){
		int index = CP_hash(course,prereq);
		free(CP_HASHTABLE[index]);
		CP_HASHTABLE[index] = NULL;
	}
	if(course == NULL && prereq != NULL){
		for(int i = 0; i < 1009; i++){
			if(CP_HASHTABLE[i] != NULL){
				
				LinkedList list = CP_HASHTABLE[i]->collisions;
				LinkedListIterator iterator = LinkedList_iterator(list);
				while (LinkedListIterator_hasNext(iterator)) {
					CP_LIST node = LinkedListIterator_next(iterator);
					if(strcmp(node->prereq,prereq) == 0){
						LinkedList_remove(result, node);
					}
				}
				free(iterator);
				if(strcmp(CP_HASHTABLE[i]->prereq,prereq) == 0){
					free(CP_HASHTABLE[i]);
					CP_HASHTABLE[i] = NULL;
				}
			}
		}
	}
	if(course != NULL && prereq == NULL){
		for(int i = 0; i < 1009; i++){
			if(CP_HASHTABLE[i] != NULL){
				LinkedList list = CP_HASHTABLE[i]->collisions;
				LinkedListIterator iterator = LinkedList_iterator(list);
				while (LinkedListIterator_hasNext(iterator)) {
					CP_LIST node = LinkedListIterator_next(iterator);
					if(strcmp(node->course,course) == 0){
						LinkedList_remove(result, node);
					}
				}
				free(iterator);
				if(strcmp(CP_HASHTABLE[i]->course,course) == 0){
					free(CP_HASHTABLE[i]);
					CP_HASHTABLE[i] = NULL;
				}
			}
		}
	}

}

void CP_print(){
	printf("Course \t Prerequiste\n");
	for(int i = 0; i < 1009; i++){
		if(CP_HASHTABLE[i] != NULL){
			CP_LIST row = CP_HASHTABLE[i];
			printf("%s \t %s\n", row->course, row->prereq);
			if(row->collisions != NULL){
				LinkedList list = CP_HASHTABLE[i]->collisions;
				LinkedListIterator iterator =  LinkedList_iterator(list);
				while (LinkedListIterator_hasNext(iterator)) {
					CP_LIST node = LinkedListIterator_next(iterator);
					printf("%s \t %s\n", node->course, node->prereq);
				}
				free(iterator);
			}
		}
	}
}

void CP_printSingle(CP_LIST node){
	printf("%s \t %s\n", node->course, node->prereq);

}

void CP_printList(LinkedList list){
	if(LinkedList_isEmpty(list)){
		printf("No such tuples\n");
		return;
	}
	printf("Course \t Prerequiste\n");
	LinkedListIterator iterator1 =  LinkedList_iterator(list);
	while (LinkedListIterator_hasNext(iterator1)) {
		CP_LIST node = LinkedListIterator_next(iterator1);
		CP_printSingle(node);
	}
	free(iterator1);

}

/*
int  main(){
	CP_insert("CS101", "CS100");
	CP_insert("EE200", "EE005");
	CP_insert("EE200", "CS100");
	CP_insert("CS120", "CS101");
	CP_insert("CS121", "CS120");
	CP_insert("CS205", "CS101");
	CP_insert("CS206", "CS121");
	CP_insert("CS206", "CS205");
	CP_print();

	printf("----Lookup Test----\n");
	LinkedList cs101 = CP_lookup("CS101", NULL); //lookup(CS101, *)
	CP_printList(cs101);
	printf("----Delete Test---\n");
	CP_delete("EE200", NULL);
	CP_print();
}*/
