#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

/** relation for Course-Day-Hour */
typedef struct CDH *CDH_LIST;
struct CDH{
	char* course;
	char day;
	char* hour;
	LinkedList collisions;
};

CDH_LIST CDH_HASHTABLE[1009];

CDH_LIST new_CDH(char* course, char day, char* hour){
	CDH_LIST this = (CDH_LIST)malloc(sizeof(CDH_LIST));
	this->course = course;
	this->day = day;
	this->hour = hour;
	this->collisions = new_LinkedList();
	return this;
}

int CDH_hash(char* course, char day, char* hour){
	int sum = 0;
	char* c;
	for(c = course; *c != '\0'; c++){
		sum += (int) *c;
	}
	for(c = hour; *c != '\0'; c++){
		sum += (int) *c;
	}
	sum += (int) day;
	return sum % 1009;
}


void CDH_insert(char* course, char day, char* hour){
	CDH_LIST this = new_CDH(course,day,hour);
	int index = CDH_hash(course,day,hour);
	if(CDH_HASHTABLE[index] == NULL){
		CDH_HASHTABLE[index] = this;
	}else{
		CDH_LIST node = CDH_HASHTABLE[index];
		if(strcmp(node->course,course) == 0 && strcmp(node->hour, hour) == 0 && node->day == day){
			printf("Tuple already in relation.\n");
		}else{LinkedList_add_at_end(node->collisions, this);}
	}
}

/** specific lookup when using a key. */
LinkedList CDH_keyLookup(char* course, char day, char* hour){
	LinkedList result = new_LinkedList();
	int index = CDH_hash(course, day,hour);
	LinkedList_add_at_end(result, CDH_HASHTABLE[index]);
	return result;
}

LinkedList CDH_lookup(char* course, char day , char* hour){
	printf("looking up for this course, day and hour: %s, %c, %s \n", course,day,hour);
	LinkedList result = new_LinkedList();
	if(course != NULL && day != '*' && hour != NULL){ //key is not empty, lookup(course, day, hour)
		return CDH_keyLookup(course,day,hour);
	}
	if(course == NULL && day != '*' && hour == NULL){//lookup(*, day, *)
		for(int i = 0; i < 1009; i++){
			if(CDH_HASHTABLE[i] != NULL){
				if(CDH_HASHTABLE[i]->day == day){LinkedList_add_at_end(result, CDH_HASHTABLE[i]);}
				LinkedList list = CDH_HASHTABLE[i]->collisions;
				LinkedListIterator iterator = LinkedList_iterator(list);
				while (LinkedListIterator_hasNext(iterator)) {
					CDH_LIST node = LinkedListIterator_next(iterator);
					if(node->day ==  day){
						LinkedList_add_at_end(result, node);
					}
				}
				free(iterator);
			}
		}
	}
	if(course == NULL && day != '*' && hour != NULL){//lookup(*, day, hour)
		for(int i = 0; i < 1009; i++){
			if(CDH_HASHTABLE[i] != NULL){
				if(CDH_HASHTABLE[i]->day == day && strcmp(CDH_HASHTABLE[i]->hour,hour) == 0){LinkedList_add_at_end(result, CDH_HASHTABLE[i]);}
				LinkedList list = CDH_HASHTABLE[i]->collisions;
				LinkedListIterator iterator = LinkedList_iterator(list);
				while (LinkedListIterator_hasNext(iterator)) {
					CDH_LIST node = LinkedListIterator_next(iterator);
					if(node->day ==  day && strcmp(CDH_HASHTABLE[i]->hour,hour) == 0){
						LinkedList_add_at_end(result, node);
					}
				}
				free(iterator);
			}
		}
	}
	if(course != NULL && day != '*' && hour == NULL){//lookup(course, day, *)
		for(int i = 0; i < 1009; i++){
			if(CDH_HASHTABLE[i] != NULL){
				if(CDH_HASHTABLE[i]->day == day && strcmp(CDH_HASHTABLE[i]->course,course) == 0){LinkedList_add_at_end(result, CDH_HASHTABLE[i]);}
				LinkedList list = CDH_HASHTABLE[i]->collisions;
				LinkedListIterator iterator = LinkedList_iterator(list);
				while (LinkedListIterator_hasNext(iterator)) {
					CDH_LIST node = LinkedListIterator_next(iterator);
					if(node->day ==  day && strcmp(CDH_HASHTABLE[i]->course,course) == 0){
						LinkedList_add_at_end(result, node);
					}
				}
				free(iterator);
			}
		}
	}
	if(course == NULL && day == '*' && hour != NULL){//lookup(*, *, hour)
		for(int i = 0; i < 1009; i++){
			if(CDH_HASHTABLE[i] != NULL){
				if(strcmp(CDH_HASHTABLE[i]->hour,hour) == 0){LinkedList_add_at_end(result, CDH_HASHTABLE[i]);}
				LinkedList list = CDH_HASHTABLE[i]->collisions;
				LinkedListIterator iterator = LinkedList_iterator(list);
				while (LinkedListIterator_hasNext(iterator)) {
					CDH_LIST node = LinkedListIterator_next(iterator);
					if(strcmp(CDH_HASHTABLE[i]->hour,hour) == 0){
						LinkedList_add_at_end(result, node);
					}
				}
				free(iterator);
			}
		}
	}
	if(course != NULL && day == '*' && hour != NULL){//lookup(course, *, hour)
		for(int i = 0; i < 1009; i++){
			if(CDH_HASHTABLE[i] != NULL){
				if(strcmp(CDH_HASHTABLE[i]->course,course) == 0 && strcmp(CDH_HASHTABLE[i]->hour,hour) == 0){LinkedList_add_at_end(result, CDH_HASHTABLE[i]);}
				LinkedList list = CDH_HASHTABLE[i]->collisions;
				LinkedListIterator iterator = LinkedList_iterator(list);
				while (LinkedListIterator_hasNext(iterator)) {
					CDH_LIST node = LinkedListIterator_next(iterator);
					if(strcmp(CDH_HASHTABLE[i]->course,course) == 0 && strcmp(CDH_HASHTABLE[i]->hour,hour) == 0){
						LinkedList_add_at_end(result, node);
					}
				}
				free(iterator);
			}
		}
	}
	if(course != NULL && day == '*' && hour == NULL){//lookup(course, *, *)
		for(int i = 0; i < 1009; i++){
			if(CDH_HASHTABLE[i] != NULL){
				if(strcmp(CDH_HASHTABLE[i]->course,course) == 0){LinkedList_add_at_end(result, CDH_HASHTABLE[i]);}
				LinkedList list = CDH_HASHTABLE[i]->collisions;
				LinkedListIterator iterator = LinkedList_iterator(list);
				while (LinkedListIterator_hasNext(iterator)) {
					CDH_LIST node = LinkedListIterator_next(iterator);
					if(strcmp(CDH_HASHTABLE[i]->course,course) == 0){
						LinkedList_add_at_end(result, node);
					}
				}
				free(iterator);
			}
		}
	}
	return result; // will return null or a linked list of nodes that match criteria.
}

void CDH_delete(char* course, char day , char* hour){
	if(course != NULL && day != '*' && hour != NULL){ //key is not empty, lookup(course, day, hour)
		int index = CDH_hash(course,day,hour);
		free(CDH_HASHTABLE[index]);
		CDH_HASHTABLE[index] = NULL;
	}
	if(course == NULL && day != '*' && hour == NULL){//lookup(*, day, *)
		for(int i = 0; i < 1009; i++){
			if(CDH_HASHTABLE[i] != NULL){
				
				LinkedList list = CDH_HASHTABLE[i]->collisions;
				LinkedListIterator iterator = LinkedList_iterator(list);
				while (LinkedListIterator_hasNext(iterator)) {
					CDH_LIST node = LinkedListIterator_next(iterator);
					if(node->day ==  day){
						LinkedList_remove(list, node);
					}
				}
				free(iterator);
				if(CDH_HASHTABLE[i]->day == day){
					free(CDH_HASHTABLE[i]);
					CDH_HASHTABLE[i] = NULL;
				}
				
			}
		}
	}
	if(course == NULL && day != '*' && hour != NULL){//lookup(*, day, hour)
		for(int i = 0; i < 1009; i++){
			if(CDH_HASHTABLE[i] != NULL){
				LinkedList list = CDH_HASHTABLE[i]->collisions;
				LinkedListIterator iterator = LinkedList_iterator(list);
				while (LinkedListIterator_hasNext(iterator)) {
					CDH_LIST node = LinkedListIterator_next(iterator);
					if(node->day ==  day && strcmp(CDH_HASHTABLE[i]->hour,hour) == 0){
						LinkedList_remove(list, node);
					}
				}
				free(iterator);
				if(CDH_HASHTABLE[i]->day == day && strcmp(CDH_HASHTABLE[i]->hour,hour) == 0){
					free(CDH_HASHTABLE[i]);
					CDH_HASHTABLE[i] = NULL;
				}
			}
		}
	}
	if(course != NULL && day != '*' && hour == NULL){//lookup(course, day, *)
		for(int i = 0; i < 1009; i++){
			if(CDH_HASHTABLE[i] != NULL){
				
				LinkedList list = CDH_HASHTABLE[i]->collisions;
				LinkedListIterator iterator = LinkedList_iterator(list);
				while (LinkedListIterator_hasNext(iterator)) {
					CDH_LIST node = LinkedListIterator_next(iterator);
					if(node->day ==  day && strcmp(CDH_HASHTABLE[i]->course,course) == 0){
						LinkedList_remove(list, node);
					}
				}
				free(iterator);
				if(CDH_HASHTABLE[i]->day == day && strcmp(CDH_HASHTABLE[i]->course,course) == 0){
					free(CDH_HASHTABLE[i]);
					CDH_HASHTABLE[i] = NULL;
				}
			}
		}
	}
	if(course == NULL && day == '*' && hour != NULL){//lookup(*, *, hour)
		for(int i = 0; i < 1009; i++){
			if(CDH_HASHTABLE[i] != NULL){
				LinkedList list = CDH_HASHTABLE[i]->collisions;
				LinkedListIterator iterator = LinkedList_iterator(list);
				while (LinkedListIterator_hasNext(iterator)) {
					CDH_LIST node = LinkedListIterator_next(iterator);
					if(strcmp(CDH_HASHTABLE[i]->hour,hour) == 0){
						LinkedList_remove(list, node);
					}
				}
				free(iterator);
				if(strcmp(CDH_HASHTABLE[i]->hour,hour) == 0){
					free(CDH_HASHTABLE[i]);
					CDH_HASHTABLE[i] = NULL;
				}
			}
		}
	}
	if(course != NULL && day == '*' && hour != NULL){//lookup(course, *, hour)
		for(int i = 0; i < 1009; i++){
			if(CDH_HASHTABLE[i] != NULL){
				
				LinkedList list = CDH_HASHTABLE[i]->collisions;
				LinkedListIterator iterator = LinkedList_iterator(list);
				while (LinkedListIterator_hasNext(iterator)) {
					CDH_LIST node = LinkedListIterator_next(iterator);
					if(strcmp(CDH_HASHTABLE[i]->course,course) == 0 && strcmp(CDH_HASHTABLE[i]->hour,hour) == 0){
						LinkedList_remove(list, node);
					}
				}
				free(iterator);
				if(strcmp(CDH_HASHTABLE[i]->course,course) == 0 && strcmp(CDH_HASHTABLE[i]->hour,hour) == 0){
					free(CDH_HASHTABLE[i]);
					CDH_HASHTABLE[i] = NULL;
				}
			}
		}
	}
	if(course != NULL && day == '*' && hour == NULL){//lookup(course, *, *)
		for(int i = 0; i < 1009; i++){
			if(CDH_HASHTABLE[i] != NULL){

				LinkedList list = CDH_HASHTABLE[i]->collisions;
				LinkedListIterator iterator = LinkedList_iterator(list);
				while (LinkedListIterator_hasNext(iterator)) {
					CDH_LIST node = LinkedListIterator_next(iterator);
					if(strcmp(CDH_HASHTABLE[i]->course,course) == 0){
						LinkedList_remove(list, node);
					}
				}
				free(iterator);
				if(strcmp(CDH_HASHTABLE[i]->course,course) == 0){
					CDH_HASHTABLE[i] = NULL;
					free(CDH_HASHTABLE[i]);
					
				}
			}
		}
	}
}

void CDH_print(){
	printf("Course \t Day \t Hour\n");
	for(int i = 0; i < 1009; i++){
		if(CDH_HASHTABLE[i] != NULL){
			CDH_LIST row = CDH_HASHTABLE[i];
			printf("%s \t %c \t %s\n", row->course, row->day, row->hour);
			if(row->collisions != NULL){
				LinkedList list = CDH_HASHTABLE[i]->collisions;
				LinkedListIterator iterator =  LinkedList_iterator(list);
				while (LinkedListIterator_hasNext(iterator)) {
					CDH_LIST node = LinkedListIterator_next(iterator);
					printf("%s \t %c \t %s\n", node->course, node->day, node->hour);
				}
				free(iterator);
			}
		}
	}
}

void CDH_printSingle(CDH_LIST node){
	if(node == NULL){
		printf("u fuckwad\n");
	}
	printf("node->course: %s", node->course);
	printf("%s \t %c \t %s\n", node->course, node->day, node->hour);
}


void CDH_printList(LinkedList list){
	printf("Course \t Day \t Hour\n");
	LinkedListIterator iterator1 =  LinkedList_iterator(list);
	while (LinkedListIterator_hasNext(iterator1)) {

		CDH_LIST node = LinkedListIterator_next(iterator1);
		printf("got here\n");
		CDH_printSingle(node);
	}
	//sfree(iterator1);

}

/*
int main(){
	CDH_insert("CS101", 'M', "9AM");
	CDH_insert("CS101", 'W', "9AM");
	CDH_insert("CS101", 'F', "9AM");
	CDH_insert("EE200", 'T', "10AM");
	CDH_insert("EE200", 'W', "1PM");
	CDH_insert("EE200", 'R', "10AM");
	CDH_print();

	printf("----Lookup Test----\n");
	LinkedList cs101 = CDH_lookup("CS101", 'M', "9AM"); //lookup(CS101, *, *)

	CDH_printList(cs101);


	printf("---Delete Test---\n");
	CDH_delete("CS101", '*', NULL);
	CDH_print();

}
*/
