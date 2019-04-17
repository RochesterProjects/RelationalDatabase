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
	char* result = NULL;
	LinkedList getName = SNAP_lookup(0, name, NULL, NULL);
	if(!(LinkedList_isEmpty(getName))){
		SNAP_LIST snapNode = LinkedList_pop(getName);	
		int id = SNAP_getID(snapNode);
		LinkedList grades = CSG_lookup(NULL, id, NULL);
		if(!(LinkedList_isEmpty(grades))){
			LinkedListIterator iterator = LinkedList_iterator(grades);
			CSG_LIST csgNode;
			while(LinkedListIterator_hasNext(iterator)){
				CSG_LIST node = LinkedListIterator_next(iterator);
				if(strcmp(CSG_getCourse(node),course) == 0){
					csgNode = node;
					result = CSG_getGrade(csgNode);
				}
			}
			}
		}
		if(result != NULL){
			printf("%s got a %s in the course %s.\n", name, result,course);
		}else{printf("No grade. \n");}
	}
		
	


/** Where is STUDENTNAME at TIME on DAY?*/
void query2(char* name, char* time, char day){
	char* resultRoom = NULL;
	char* currentCourse = NULL;
	LinkedList getName = SNAP_lookup(0, name, NULL, NULL);
	if(!(LinkedList_isEmpty(getName))){
		SNAP_LIST snapNode = LinkedList_pop(getName);
		int id = SNAP_getID(snapNode);
		LinkedList grades = CSG_lookup(NULL, id, NULL);
		LinkedListIterator iterator = LinkedList_iterator(grades);
		CSG_LIST csgNode;
		while(LinkedListIterator_hasNext(iterator)){
			CSG_LIST node = LinkedListIterator_next(iterator);
			currentCourse = CSG_getCourse(node);
			LinkedList cdhList = CDH_lookup(currentCourse, '*',NULL);
			LinkedListIterator cdh_iterator = LinkedList_iterator(cdhList);
			while(LinkedListIterator_hasNext(cdh_iterator)){
				CDH_LIST cdhNode = LinkedListIterator_next(cdh_iterator);
				char* cdhTime = CDH_getHour(cdhNode);
				char cdhDay = CDH_getDay(cdhNode);
				if(strcmp(cdhTime, time) == 0 && cdhDay == day){
					LinkedList cr_list = CR_lookup(currentCourse, NULL);
					LinkedListIterator cr_iterator = LinkedList_iterator(cr_list);
					while(LinkedListIterator_hasNext(cr_iterator)){
						CR_LIST crNode = LinkedListIterator_next(cr_iterator);
						resultRoom = CR_getRoom(crNode);
						printf("%s is in room %s on %s on day %c.\n ", name, resultRoom, time,day);
						return;
					}
				}
			}
			
		}	

	}
	printf("No such name,hour, or day combination.\n");
}

int main(){
	printf("These are the full tables:\n");
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

	printf("Showing Functionality of Example 8.2:\n");
	LinkedList lookup1 = CSG_lookup("CS101", 12345, NULL);
	printf("lookup((\"CS101\", 12345, \"*\"), Course-Student-Grade)\nResult:\n");
	CSG_printList(lookup1);

	LinkedList lookup2 = CP_lookup("CS205", "CS120");
	printf("lookup((\"CS205\",\"CS120\"), Course-Prerequiste)\nResult:\n");
	CP_printList(lookup2);

	printf("delete((\"CS101\",\"*\"), Course-Room)\n");
	CR_delete("CS101", NULL);
	printf("Updated CR table:\n");
	CR_print();

	printf("insert((\"CS205\",\"CS120\"), Course-Prerequiste)\nResult:\n");
	CP_insert("CS205", "CS120");
	CP_print();

	printf("insert((\"CS205\",\"CS101\"), Course-Prerequiste)\nResult(should have no effect on relation):\n");
	CP_insert("CS205", "CS101");
	CP_print();


	printf("\n\nTesting part two\n");
	//get user input 
	printf("QUERY1: What grade did STUDENTNAME get in COURSENAME?\nPlease enter a name:");
	char* nameInput = (char*)malloc(20 * sizeof(char));
	fgets(nameInput,20,stdin);
	strtok(nameInput, "\n");
	printf("Please enter a course: ");
	char* courseInput = (char*)malloc(5 * sizeof(char));
	fgets(courseInput,6,stdin);
	strtok(courseInput, "\n");
	query1(nameInput, courseInput);

	
	printf("QUERY2: What room is STUDENTNAME at HOUR on DAY?\nPlease enter a name:");
	char* nameInput2 = (char*)malloc(20 * sizeof(char));
	fgets(nameInput2,20,stdin);
	strtok(nameInput2, "\n");
	printf("\nPlease enter an hour: ");
	char* hourInput = (char*)malloc(5 * sizeof(char));
	fgets(hourInput,5,stdin);
	strtok(hourInput, "\n");
	printf("\nPlease enter a day: ");
	char dayInput;
	scanf(" %c", &dayInput);
	query2(nameInput2,hourInput, dayInput);


	

}