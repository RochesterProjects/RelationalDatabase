#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "SNAP.h"
#include "CSG.h"
#include "CDH.h"
#include "CR.h"
#include "CP.h"


/**What grade did STUDENTNAME get in COURSENAME? */
void query1(char* name, char* course){
	char* result;
	LinkedList getName = SNAP_lookup(0, name, NULL, NULL);
	SNAP_LIST snapNode = LinkedList_pop(getName);
	int id = SNAP_getID(node);
	printf("This is the ID found: %d\n", id);
	LinkedList grades = CSG_lookup(NULL, id, NULL);
	CSG_LIST csgNode = LinkedList_pop(grades);
		if(csgNode == NULL){
			printf("Parameters incorrect. (No course for this name)\n");
			return;
		}else{
			result = CSG_getGrade(csgNode);
			return;
		}
	free(iterator1);
	printf("%s got a %s in the course %s.\n", name, result,course);	
	}
	


/** Where is STUDENTNAME at TIME on DAY?*/
void query2(char* name, char* time, char day){
	char* resultRoom;
	char* course;
	LinkedList getNames = SNAP_lookup(0, name, NULL, NULL);;
	LinkedListIterator iterator1 = LinkedList_iterator(getNames);
	while (LinkedListIterator_hasNext(iterator1)){
		SNAP_LIST node = LinkedListIterator_next(iterator1);
		int id = SNAP_getID(node);
		LinkedList csgNodes = CSG_lookup(NULL, id,NULL);
		CSG_LIST csgNode = LinkedList_pop(csgNodes);
		course = CSG_getCourse(csgNode);
	}
	LinkedList tester = CDH_lookup(course,day,time);
	CDH_LIST cdhNode = LinkedList_pop(tester);
	//CDH_printList(tester);
	if(cdhNode == NULL){
		printf("No classes at given time and day and for given student.\n");
	} else{
		printf("here\n");
		LinkedList crList = CR_lookup(course,NULL);
		CR_LIST node = LinkedList_pop(crList);
		//printf("fucko ducko, %s\n", CR_getRoom(node));
		resultRoom = CR_getRoom(node);  //we need to check if a class is actually taking place during the given time and day.

		printf("%s is at %s room at %s time on %c day.\n", name,resultRoom,time,day);
	}
	

}

int main(){
	SNAP_insert(12345,"C.Brown", "12 Apple St.", "555-1234");
	SNAP_insert(67890,"L.Van Pelt", "34 Pear Ave.", "555-5678");
	SNAP_insert(22222,"P. Patty", "56 Grape Blvd.", "555-9999");
	SNAP_print();

	CSG_insert("CS101", 12345, "A");
	CSG_insert("CS101", 67890, "B");
	CSG_insert("EE200", 12345, "C");
	CSG_insert("EE200", 22222, "B+");
	CSG_insert("CS101", 33333, "A-");
	CSG_insert("PH100", 67890, "C+");
	CSG_print();

	CR_insert("CS101", "Turing Aud.");
	CR_insert("EE200", "25 Ohm Hall" );
	CR_insert("PH100", "Newton Lab.");
	CR_print();

	CP_insert("CS101", "CS100");
	CP_insert("EE200", "EE005");
	CP_insert("EE200", "CS100");
	CP_insert("CS120", "CS101");
	CP_insert("CS121", "CS120");
	CP_insert("CS205", "CS101");
	CP_insert("CS206", "CS121");
	CP_insert("CS206", "CS205");
	CP_print();

	CDH_insert("CS101", 'M', "9AM");
	CDH_insert("CS101", 'W', "9AM");
	CDH_insert("CS101", 'F', "9AM");
	CDH_insert("EE200", 'T', "10AM");
	CDH_insert("EE200", 'W', "1PM");
	CDH_insert("EE200", 'R', "10AM");
	CDH_print();

	printf("\n\nTesting part two\n");
	query1("C.Brown", "CS101");
	query2("L. Van Pelt","9AM", 'M');


	

}