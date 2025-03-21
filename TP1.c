#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const int ID =8;
const int full_name = 30;
const int date = 10;
const int history =5;

typedef struct Employerecords{
    char Employee_ID[ID];//we need to define the id of the employee
    char Full_Name[full_name];//we need to define the full name of the employee
    char Last_consultation_Date[date];//we need to define the last consultation date of the employee
    char Retrurn_to_wrok_Date[date];//we need to define the return to work date of the employee
    int Total_Number_of_consultations;//we need to define the total number of consultations of the employee
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


//now we need a function to add a new employee to the list

void add(ptr *h,Employerecords newemp){
    Employerecords* newcell = (Employerecords*)malloc(sizeof(Employerecords));//we need to allocate memory for the new employee
    *newcell = newemp;//we need to copy the new employee to the new cell
    newcell->p=*h;//we need to put the head pointer in the next pointer of the new employee
    *h=newcell;//we need to put the new employee in the head pointer
}

//now we need a function to update the employee information
//so we need the head of the list and the new employee information and we also need its id to confirm that this is the employee we want to update

void update(ptr h,Employerecords newemp,char id[ID]){
    Employerecords* temp = h;//we need a temporary pointer to point to the head of the list because we need to loop through the list to find the employee we want to update

    while(temp!=NULL){//we need a loop to loop through the list
        //now we are going to use a function called strcmp to compare between two strings and if they are equal it will return 0
        if(strcmp(temp->Employee_ID,id)==0){//if the id of the employee is equal to the id we want to update 
            *temp = newemp;
            printf("Employee information updated successfully\n");
            return;//in order to exit the function and stop the loop
        }
        temp=temp->p;//we need to move to the next employee in the list because we didn't find the employee we want to update yet
    }

    printf("Employee not found\n");//if we didn't find the employee we want to update  
}


//now we need a function to delete an employee from the list 
//it is the same as delete by position or value in linked list the difference is that we need to compare between the id of the employee and the id we want to delete

void delete(ptr *h,char id[ID]){
    Employerecords* temp=*h;//we need a temporary pointer to point to the head of the list because we need to loop through the list to find the employee we want to delete
    Employerecords* prev=NULL;//we need a pointer to the previous employee in the list because we need to link the previous employee with the next employee after we delete the employee we want to delete 
    while(temp!=NULL && strcmp(temp->Employee_ID,id)!=0){
        prev=temp;//we need to put the current employee in the previous pointer 
        temp=temp->p;//we need to move to the next employee in the list because we didnt find the employee we want to delete yet 

    }
    if(temp==NULL){
        printf("Employee not found\n");
        return;
    }
    if(prev==NULL){
        *h=temp->p;//if the employee we want to delete is the first employee in the list we need to put the next employee in the head pointer 
    }else{
        prev->p=temp->p;//if the employee we want to delete is not the first employee in the list we need to link the previous employee with the next employee after we delete the employee we want to delete 
    }

    free(temp);//we need to free the memory of the employee we want to delete 
    printf("Employee deleted successfully\n");


}
