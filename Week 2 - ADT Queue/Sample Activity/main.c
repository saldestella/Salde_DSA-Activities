#include <stdio.h>
#include <stdbool.h>
#include "classWithdraw.h"
// #include "classWithdraw.c"

/*
    Program Description:  
	
	Case 1: When a student enrolls, the student gets inserted in the Class.
			// insert Stack
	
	Case 2:If the class is already full, the student gets waitlisted 
			and is queued for enrollment. 
			// insert Queue
	
	Case 3: If a student withdraws in the class, the first student 
			from the queue gets inserted in the class.
			// search in Stack then pop, push from Queue
*/

#define MAX 5

int main(){
    classStack list;
    ReservedQ reserveList;
    studentInfo newStud;
    studentInfo stud1 = {{"Zenno", "Abellana"}, {5, 2001}, 23, 1000, 'M', 3};
    studentInfo stud2 = {{"Jethro", "Engutan"}, {5, 2001}, 23, 1001, 'M', 3};
    studentInfo stud3 = {{"Mallen", "Jugalbot"}, {5, 2001}, 23, 1002, 'M', 3};
    studentInfo stud4 = {{"Kaelle", "Gravador"}, {5, 2001}, 23, 1003, 'F', 3};
    studentInfo stud5 = {{"Stella", "Salde"}, {5, 2001}, 23, 1004, 'F', 3};
    studentInfo stud6 = {{"Belle", "Lastimosa"}, {5, 2001}, 23, 1005, 'F', 3};
    studentInfo stud7 = {{"Erwin", "Nazareno"}, {5, 2001}, 23, 1006, 'M', 3};
    studentInfo stud8 = {{"Ethan", "Montera"}, {5, 2001}, 23, 1007, 'M', 3};

    initStack(&list);
    initQueue(&reserveList);
    int input, select, id;

    do{
		printf("0. EXIT\n");
		printf("1. Enroll\n");
		printf("2. Withdraw\n");
		printf("3. Display Class List\n");
        printf("4. Display Waitlist\n");
		printf("Input: ");
		scanf("%d", &input);
		
		switch(input){
			case 1:
				// printf("Enter Student First Name: ");
				// scanf("%s", &newStud.name.firstName);
				// printf("Enter Student Last Name: ");
				// scanf("%s", &newStud.name.lastName);
				// printf("Enter Student BirthMonth: ");
				// scanf("%d", &newStud.bdate.month);
				// printf("Enter Student BirthYear: ");
				// scanf("%d", &newStud.bdate.year);
				// printf("Enter Student Age: ");
				// scanf("%d", &newStud.age);
				// printf("Enter Student ID Number: ");
				// scanf("%d", &newStud.idNum);

                printf("Select a number from 1-8: ");
                scanf("%d", &select);

                switch (select)
                {
                case 1:
                    newStud = stud1;
                    break;

                case 2:
                    newStud = stud2;
                    break;

                case 3:
                    newStud = stud3;
                    break;

                case 4:
                    newStud = stud4;
                    break;

                case 5:
                    newStud = stud5;
                    break;

                case 6:
                    newStud = stud6;
                    break;

                case 7:
                    newStud = stud7;
                    break;

                case 8:
                    newStud = stud8;
                    break;
                
                default:
                    break;
                }

                enroll(newStud, &list, &reserveList);
				
				break;
				
			case 2:
				printf("Enter Student ID Number to withdraw: ");
				scanf("%d", &id);
				withdraw(id, &list, &reserveList);
				break;
				
			case 3:
                displayStack(list);
				break;

            case 4:
                displayQueue(reserveList);
				break;
				
			default:
                break;
		}
		
		system("pause");
		system("cls");
	}
	while(input!=0);
}