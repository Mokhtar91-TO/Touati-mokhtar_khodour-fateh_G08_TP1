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

typedef struct Employerecords *ptr;//we need to define a pointer to the records 

Employerecords* filel_loading(const char *emprecord){
    FILE* file= fopen(emprecord,"r");//with this code we can open the file in read mode 
    if (file == NULL){
        printf("Error: could not open file\n");
        return NULL;
    }
    Employerecords* head=NULL;//the head pointer will point to the first emplyee 
    while(!feof(file)){//we need a loop to read employee record by using feof it loop until the end of the file 
        Employerecords* newemp = (Employerecords*)malloc(sizeof(Employerecords));
        if(newemp==NULL){
            printf("cannot allocate\n");
            return NULL;
        }
        //fcanf is the same as scanf but it read from a file *


        //%[^,] it let me read the fullname of the employee not just the   first name and it stops when , appears in the string not space


        // i put comma after %d[^,] in order to seperate between the name of the employee and what comes after it , like i tell fscanf to read and discard the comma so i can read the next field correctly without crashing or errors
        
        //we need to read employee file and stores them in our struct 
        


        if(fscanf(file,"%s %[^,], %d %s %s ",newemp->Employee_ID,newemp->Full_Name,newemp,newemp->Total_Number_of_consultations,newemp->Last_consultation_Date,newemp->Retrurn_to_wrok_Date)!=5){
            free(newemp);//if raiding the file failed free the memory 
            break;
        }
        //we need this loop in order to read the consultation history
        for(int i=0;i<history;i++){//%[^\"] it let me read the history of the employee not just the first reason and it stops when " appears in the string not space and if reason not available it stores an empty string , it is very usefull
            if(fscanf(file," %[^\"]",newemp->history[i])!= 1){
                strcpy(newemp->history[i],"")//if there is no reason set an empty string in the corresponds history
                //i use strcpy because it allows me to copy the string 

            }

    }





}




void add(ptr *h,Employerecords 
