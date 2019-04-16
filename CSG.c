
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

/** relation for Course-StudentID-Grade */
typedef struct CSG *CSG_LIST;
struct CSG{
	char* course;
	int studentID;
	char* grade;
	LinkedList collisions;
};

CSG_LIST CSG_HASHTABLE[1009];

CSG_LIST new_CSG(char* course, int id, char* grade){
	CSG_LIST this = (CSG_LIST)malloc(sizeof(CSG_LIST));
	if(this == NULL){
		return NULL; //out of memory
	}
	this->course = course;
	this->studentID = id;
	this->grade = grade;
	this->collisions = new_LinkedList();
	return this;
}

void free_CSG(CSG_LIST this){
	if(this == NULL){
		return;
	}
	free(this->collisions);
	free(this); 
}

char* CSG_getGrade(CSG_LIST node){
	return node->grade;
}

char* CSG_getCourse(CSG_LIST node){
	return node->course;
}
/** key is {course, student} */
int CSG_hash(char* course, int id){
	int sum = 0;
	char* c;
	for(c = course; *c != '\0'; c++){
		sum += (int) *c;
	}
	sum += id;
	return sum % 1009;
}

/** if hashed index is empty, simply insert there. If there is value, add to then end of the linked list.
If already in the list, dont add
 */
void CSG_insert(char* course, int id, char* grade){
	CSG_LIST this = new_CSG(course, id, grade);
	int index = CSG_hash(course, id);
	if(CSG_HASHTABLE[index] == NULL){
		CSG_HASHTABLE[index] = this;
	}else{
		CSG_LIST node = CSG_HASHTABLE[index];
		if(strcmp(node->course,course) == 0 && strcmp(node->grade, grade) == 0 && node->studentID == id){
			printf("Tuple already in relation.\n");
		}else{LinkedList_add_at_end(node->collisions, this);}
	}
}

/** specific lookup when using a key. */
LinkedList CSG_keyLookup(char* course, int id){
	LinkedList result = new_LinkedList();
	int index = CSG_hash(course, id);
	LinkedList_add_at_end(result, CSG_HASHTABLE[index]);
	return result;
}

LinkedList CSG_lookup(char* course, int id, char* grade){
	LinkedList result = new_LinkedList();
	if(grade == NULL && course != NULL && id != 0){ //key is not empty, lookup(course, id, *)
		return CSG_keyLookup(course,id);
	}
	if(grade == NULL && course == NULL && id != 0){//lookup(*, id, *)
		for(int i = 0; i < 1009; i++){
			if(CSG_HASHTABLE[i] != NULL){
				if(CSG_HASHTABLE[i]->studentID == id){LinkedList_add_at_end(result, CSG_HASHTABLE[i]);}
				LinkedList list = CSG_HASHTABLE[i]->collisions;
				LinkedListIterator iterator = LinkedList_iterator(list);
				while (LinkedListIterator_hasNext(iterator)) {
					CSG_LIST node = LinkedListIterator_next(iterator);
					if(node->studentID ==  id){
						LinkedList_add_at_end(result, node);
					}
				}
				free(iterator);
			}
		}
	}
	if(grade != NULL && course == NULL && id != 0){//lookup(*, id, grade)
		for(int i = 0; i < 1009; i++){
			if(CSG_HASHTABLE[i] != NULL){
				if(CSG_HASHTABLE[i]->studentID == id && strcmp(CSG_HASHTABLE[i]->grade,grade) == 0){LinkedList_add_at_end(result, CSG_HASHTABLE[i]);}
				LinkedList list = CSG_HASHTABLE[i]->collisions;
				LinkedListIterator iterator = LinkedList_iterator(list);
				while (LinkedListIterator_hasNext(iterator)) {
					CSG_LIST node = LinkedListIterator_next(iterator);
					if(node->studentID ==  id && strcmp(node->grade,grade) == 0){
						LinkedList_add_at_end(result, node);
					}
				}
				free(iterator);
			}
		}
	}
	if(grade == NULL && course != NULL && id == 0){//	lookup(course, *, *)
		for(int i = 0; i < 1009; i++){
			if(CSG_HASHTABLE[i] != NULL){
			if(strcmp(CSG_HASHTABLE[i]->course,course) == 0){LinkedList_add_at_end(result, CSG_HASHTABLE[i]);}
				LinkedList list = CSG_HASHTABLE[i]->collisions;
				LinkedListIterator iterator = LinkedList_iterator(list);
				while (LinkedListIterator_hasNext(iterator)) {
					CSG_LIST node = LinkedListIterator_next(iterator);
					if(strcmp(node->course, course) == 0){
						LinkedList_add_at_end(result, node);
					}
				}
				free(iterator);
			}
		}
	}
	if(grade != NULL && course == NULL && id == 0){//lookup(*, *, grade)
		for(int i = 0; i < 1009; i++){
			if(CSG_HASHTABLE[i] != NULL){
				if(strcmp(CSG_HASHTABLE[i]->grade, grade) == 0){LinkedList_add_at_end(result, CSG_HASHTABLE[i]);}
				LinkedList list = CSG_HASHTABLE[i]->collisions;
				LinkedListIterator iterator = LinkedList_iterator(list);
				while (LinkedListIterator_hasNext(iterator)) {
					CSG_LIST node = LinkedListIterator_next(iterator);
					if(strcmp(node->grade,grade) == 0){
						LinkedList_add_at_end(result, node);
					}
				}
				free(iterator);
			}
		}
	}
	if(grade != NULL && course != NULL && id == 0){//lookup(course, *, grade)
		for(int i = 0; i < 1009; i++){
			if(CSG_HASHTABLE[i] != NULL){
				if(strcmp(CSG_HASHTABLE[i]->course,course) == 0 && strcmp(CSG_HASHTABLE[i]->grade,grade) == 0){LinkedList_add_at_end(result, CSG_HASHTABLE[i]);}
				LinkedList list = CSG_HASHTABLE[i]->collisions;
				LinkedListIterator iterator =  LinkedList_iterator(list);
				while (LinkedListIterator_hasNext(iterator)) {
					CSG_LIST node = LinkedListIterator_next(iterator);
					if(strcmp(node->course,course) == 0 && strcmp(node->grade,grade) == 0){
						LinkedList_add_at_end(result, node);
					}
				}
				free(iterator);
			}
		}
	}
	if(grade != NULL && course != NULL && id != 0){//lookup(course, id, grade)
		for(int i = 0; i < 1009; i++){
			if(CSG_HASHTABLE[i] != NULL){
				if(CSG_HASHTABLE[i]->course == course && CSG_HASHTABLE[i]->studentID == id &&CSG_HASHTABLE[i]->grade == grade){LinkedList_add_at_end(result, CSG_HASHTABLE[i]);}
				LinkedList list = CSG_HASHTABLE[i]->collisions;
				LinkedListIterator iterator =  LinkedList_iterator(list);
				while (LinkedListIterator_hasNext(iterator)) {
					CSG_LIST node = LinkedListIterator_next(iterator);
					if(strcmp(node->course,course) == 0 && node->studentID == id && strcmp(node->grade,grade) == 0){
						LinkedList_add_at_end(result, node);
					}
				}
				free(iterator);
			}
		}
	}
	return result; // will return null or a linked list of nodes that match criteria.
}

void CSG_delete(char* course, int id, char* grade){
	if(grade == NULL && course != NULL && id != 0){ //key is not empty, delete(course, id, *)
		int index = CSG_hash(course, id);
		free(CSG_HASHTABLE[index]);
		CSG_HASHTABLE[index] = NULL;
	}
	if(grade == NULL && course == NULL && id != 0){//delete(*, id, *)
		for(int i = 0; i < 1009; i++){
			if(CSG_HASHTABLE[i] != NULL){
				LinkedList list = CSG_HASHTABLE[i]->collisions;
				LinkedListIterator iterator =  LinkedList_iterator(list);
				while (LinkedListIterator_hasNext(iterator)) {
					CSG_LIST node = LinkedListIterator_next(iterator);
					if(node->studentID ==  id){
						LinkedList_remove(list, node);
					}
				}
				free(iterator);
				if(CSG_HASHTABLE[i]->studentID == id){
					free(CSG_HASHTABLE[i]);
					CSG_HASHTABLE[i] = NULL;
				}
			}
		}
	}
	if(grade != NULL && course == NULL && id != 0){//delete(*, id, grade)
		for(int i = 0; i < 1009; i++){
			if(CSG_HASHTABLE[i] != NULL){
				LinkedList list = CSG_HASHTABLE[i]->collisions;
				LinkedListIterator iterator =  LinkedList_iterator(list);
				while (LinkedListIterator_hasNext(iterator)) {
					CSG_LIST node = LinkedListIterator_next(iterator);
					if(CSG_HASHTABLE[i]->studentID == id && strcmp(node->grade,grade) == 0){
						LinkedList_remove(list, node);
						free(node);
					}
				}
				free(iterator);
				if(CSG_HASHTABLE[i]->studentID == id && strcmp(CSG_HASHTABLE[i]->grade,grade) == 0){
					free(CSG_HASHTABLE[i]);
					CSG_HASHTABLE[i] = NULL;}
			}
		}
	}
	if(grade == NULL && course != NULL && id == 0){//delete(course, *, *)
		for(int i = 0; i < 1009; i++){
			if(CSG_HASHTABLE[i] != NULL){
				LinkedList list = CSG_HASHTABLE[i]->collisions;
				if(!(LinkedList_isEmpty(list))){
					LinkedListIterator iterator =  LinkedList_iterator(list);
					while (LinkedListIterator_hasNext(iterator)) {
						CSG_LIST node = LinkedListIterator_next(iterator);
						if(strcmp(node->course,course) == 0){
							LinkedList_remove(list, node);
						}
					}

					free(iterator);
				}
				if(strcmp(CSG_HASHTABLE[i]->course,course) == 0){
					free(CSG_HASHTABLE[i]);
					CSG_HASHTABLE[i] = NULL;
				}
			}
			
		}
	}
	if(grade != NULL && course == NULL && id == 0){//delete(*, *, grade)
		for(int i = 0; i < 1009; i++){
			if(CSG_HASHTABLE[i] != NULL){
				LinkedList list = CSG_HASHTABLE[i]->collisions;
				LinkedListIterator iterator =  LinkedList_iterator(list);
				while (LinkedListIterator_hasNext(iterator)) {
					CSG_LIST node = LinkedListIterator_next(iterator);
					if(strcmp(node->grade, grade) == 0){
						LinkedList_remove(list, node);
					}
				}
				free(iterator);
				if(strcmp(CSG_HASHTABLE[i]->grade,grade) == 0){
					free(CSG_HASHTABLE[i]);
					CSG_HASHTABLE[i] = NULL;
				}
			}
		}
	}
	if(grade != NULL && course != NULL && id == 0){//delete(course, *, grade)
		for(int i = 0; i < 1009; i++){
			if(CSG_HASHTABLE[i] != NULL){
				LinkedList list = CSG_HASHTABLE[i]->collisions;
				LinkedListIterator iterator =  LinkedList_iterator(list);
				while (LinkedListIterator_hasNext(iterator)) {
					CSG_LIST node = LinkedListIterator_next(iterator);
					if(strcmp(node->course,course) == 0 && strcmp(node->grade,grade) == 0){
						LinkedList_remove(list, node);
					}
				}
				free(iterator);
				if(strcmp(CSG_HASHTABLE[i]->course,course) == 0 && strcmp(CSG_HASHTABLE[i]->grade,grade) == 0){
					free(CSG_HASHTABLE[i]);
					CSG_HASHTABLE[i] = NULL;
				}
			}
		}
	}
	if(grade != NULL && course != NULL && id != 0){ //delete(course, id, grade)
		int index = CSG_hash(course, id);
		if(strcmp(CSG_HASHTABLE[index]->grade,grade) == 0){
			free(CSG_HASHTABLE[index]);
			CSG_HASHTABLE[index] = NULL;
		}
	}
}

void CSG_print(){
	printf("Course \t Student-ID \t Grade\n");
	for(int i = 0; i < 1009; i++){
		if(CSG_HASHTABLE[i] != NULL){
			CSG_LIST row = CSG_HASHTABLE[i];
			printf("%s \t %d \t %s\n", row->course, row->studentID, row->grade);
			if(row->collisions != NULL){
				LinkedList list = CSG_HASHTABLE[i]->collisions;
				LinkedListIterator iterator =  LinkedList_iterator(list);
				while (LinkedListIterator_hasNext(iterator)) {
					CSG_LIST node = LinkedListIterator_next(iterator);
					printf("%s \t %d \t %s\n", node->course, node->studentID, node->grade);
				}
				free(iterator);
			}
		}
	}
}

void CSG_printSingle(CSG_LIST this){
	printf("%s \t %d \t %s\n", this->course, this->studentID, this->grade);
}


void CSG_printList(LinkedList list){
	printf("Course \t Student-ID \t Grade\n");
	LinkedListIterator iterator1 =  LinkedList_iterator(list);
	while (LinkedListIterator_hasNext(iterator1)) {
		CSG_LIST node = LinkedListIterator_next(iterator1);
		CSG_printSingle(node);
	}
	free(iterator1);
}

/*
int main(){
	CSG_insert("CS101", 12345, "A");
	CSG_insert("CS101", 67890, "B");
	CSG_insert("EE200", 12345, "C");
	CSG_insert("EE200", 22222, "B+");
	CSG_insert("CS101", 33333, "A-");
	CSG_insert("PH100", 67890, "C+");
	CSG_print();
	//int id = 12345;
	printf("LOOKUP Test\n\n");
	LinkedList cs101_12345 = CSG_lookup("CS101", 12345, NULL); //lookup(CS101, 12345, *)
	CSG_printList(cs101_12345);
	
	printf("\nDELete TEST\n\n");
	CSG_delete(NULL, 12345,NULL);
	CSG_print();
}*/