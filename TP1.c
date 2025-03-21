#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const int ID =8;
const int full_name = 30;
const int date = 10;
const int history =5;

typedef struct Employerecords{
    char Employee_ID[ID];
    char Full_Name[full_name];
    char Last_consultation_Date[date];
    char Retrurn_to_wrok_Date[date];
    int Total_Number_of_consultations;
    char history[history][500];//we need a matrix that hold the 5 reasons of past consultation 
    struct Employerecords *p;
}Employerecords;//we need to define a records that holds employee informations




typedef struct Employerecords *ptr;

Employerecords* read_emprecord_file(const char *emprecord){
    FILE* file= fopen(emprecord,"r");//with this code we can open the file in read mode 
    if (file == NULL){
        printf("Error: could not open file\n");
        return NULL;
    }
    Employerecords* head=NULL;//the head pointer will point to the first emplyee 
    while(!feof(file)){//we need a loop to read employee record by using feof it loop until the end of the file and line by line 
        Employerecords* newemp = (Employerecords*)malloc(sizeof(Employerecords));
        if(newemp==NULL){
            printf("cannot allocate\n");
            return NULL;
        }
        //fcanf is the same as scanf but it read from a file *


        //%[^,] it let me read the fullname of the employee not just the   first name and it stops when , appears in the string not space , it is like a delimiter


        // i put comma after %d[^,] in order to seperate between the name of the employee and what comes after it , like i tell fscanf to read and discard the comma so i can read the next field correctly without crashing or errors
        
        //we need to read employee file and stores them in our struct 
        


        if(fscanf(file,"%[^;];%[^;];%d;%[^;];%[^;]",newemp->Employee_ID,newemp->Full_Name,newemp->Total_Number_of_consultations,newemp->Last_consultation_Date,newemp->Retrurn_to_wrok_Date)!=5){
            free(newemp);//if reading the file failed free the memory 
            break;//&
        }

        //now we need to read the history of the employee 

        char bufferforhistory[500];// we need a buffer to store the history of the employee , so we are going to read all the history line  then put it in this temporary buffer 

        if(fscanf(file,"%[^\]",bufferforhistory)==1){//%[^\"] it let me read the history of the employee not just the first reason and it stops when " appears in the string not space , it is very usefull and 1 it means that fscanf should read one string and put it in the buffer
            char* string = strtok(bufferforhistory,",");//the function strtok let me split the string into multiple strings , i need just to defint the delimiter which is the comma in this case ',' and the char* string will point to the first string in the buffer. 
            int i=0;
            while(string!=NULL && i<history){//if the string is not empty  and the index is less than the history of the employee
                strcpy(newemp->history[i],string);//we need to copy the string and put it in the right place in the histpry of the employee
                string = strtok(NULL,",");//we need to move to the next string in the buffer , and we need to put NULL in the strtok function in order to continue reading the buffer and strok will remember the last position it stopped at because it replace , with \0 so when we write strok(NULL,",")  and strtok works internally with the buffer because there is a static pointer that stores the last position in the string    
                i++;
            }
            while(i<history){//if the history of the employee is less than 5 we need to put empty strings in the rest of the history because we need to have 5 reasons of consultation for each employee
                strcpy(newemp->history[i],"");
                i++;
            }  
        }
        newemp->p=head;//we need to put the head pointer in the next pointer of the new employee
        head=newemp;//we need to put the new employee in the head pointer
 
        }

    fclose(file);//close the file
    return head;//return the head of the list
}



void add(ptr *h,Employerecords newemp){
    Employerecords* newcell = (Employerecords*)malloc(sizeof(Employerecords));//we need to allocate memory for the new employee
    *newcell = newemp;//we need to copy the new employee to the new cell
    newcell->p=*h;//we need to put the head pointer in the next pointer of the new employee
    *h=newcell;//we need to put the new employee in the head pointer
}
