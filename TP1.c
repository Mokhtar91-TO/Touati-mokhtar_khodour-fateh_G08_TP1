#include <stdio.h>
#include <stdlib.h>
#include <string.h>





const int ID =8;
const int full_name = 30;
const int date = 10;//XX/XX/XXXX
const int history =5;
const int date2 = 5;//XX:XX
const int max_appointments = 10;



//TASK 1 : Managing employee's records 



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

Employerecords* read_emprecord_file(const char *emprecordfile){
    FILE* file= fopen(emprecordfile,"r");//with this code we can open the file in read mode 
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
    newcell->p=*h;//we need to put the head pointer in the next pointer of the new employee so it will point to the next employee in the list
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





//TASK 2 : Managing appointments using priority appointment queue



typedef struct consultation{
    char Employee_ID[ID];//we need to define the id of the employee 
    char Employee_Name[full_name];//we need to define the name of the employee 
    char Consultation_Time[date2];//we need to define the consultation time of the employee 
    char Consultation_Reason[500];//we need to define the consultation reason of the employee 
    struct consultation *p; 
    int priority;//we need to define the priority of the appointment

}consultation;//we need to define a struct that holds the consultation information 

typedef struct Queue{
    consultation* head;
    consultation* tail;
    int size;//we need to define the size of the queue to know how many appointments in the queue so we dont exceed the maximum number of appointments in the queue  which is 10
}Queue;//we need to define a struct that holds the head and the tail of the queue

Queue* create_Queue(){
    Queue* q = (Queue*)malloc(sizeof(Queue));//we need to allocate memory for the queue
    q->head=NULL;
    q->tail=NULL;
    q->size=0;//we need to put the size of the queue to 0 because the queue is empty at first 
    return q;
}


//now we need a function to add a new appointment to the queue

void add_appointment(Queue* q,consultation* newconsultation){
    newconsultation->p=NULL;//we need to put NULL in the next pointer of the new appointment because it is the last appointment in the queue, however if it is not the last appointment we are going to link it with the correct appointment 
    if(q->head==NULL || q->head->priority < newconsultation->priority ){//if the queue is empty and the priority of the new appointment is higher than the priority of the head of the queue 
        newconsultation->p=q->head;//we need to put the head pointer in the next pointer of the new appointment so we will not loose the rest of the appointments in the queue
        q->head=newconsultation;//we need to put the new appointment in the head pointer 
        if(q->tail==NULL){//if the queue is empty we need to put the new appointment in the tail pointer
            q->tail=newconsultation;
    }
    return;//in order to exit the function after adding the new appointment to the queue
    } 

    consultation* temp = q->head;//we need a temporary pointer to point to the head of the queue because we need to loop through the queue to find the right place to put the new appointment , and it is not practical to use the head directly because we need to link the new appointment with the rest of the appointments in the queue

    while(temp->p!=NULL && temp->p->priority >= newconsultation->priority){
        temp=temp->p;//we need to move to the next appointment in the queue because we didnt find the right place to put the new appointment yet
    }

    newconsultation->p=temp->p;//we need to link the new appointment with the rest of the appointments in the queue at first so we will not loose the rest of the appointments in the queue 
    temp->p=newconsultation;//we need to put the new appointment in the right place in the queue

    if(newconsultation->p==NULL){
        q->tail=newconsultation;//if the new appointment is the last appointment in the queue we need to put it in the tail pointer 
    }

}




//now we need a function to read the consultations.txt file 
consultation* read_consultation_file(const char *consultationfile){
    FILE* file= fopen(consultationfile,"r");//withe this code we can open the file in read mode 
    if(file==NULL){
        printf("Error: could not open file\n");
        return NULL;
    }
     Queue* q = create_Queue();//we need to create a queue to store the consultations 
    while(!feof(file)){//we need a loop to read consultation file bu using feof it loop until the end of the file and line by liner 
        consultation* newconsultation = (consultation*)malloc(sizeof(consultation));
        if(newconsultation==NULL){
            printf("cannot allocate\n");
            return NULL;
        }
        //we need to read the consultation file and stores them in our struct 
        if(fscanf(file,"%[^;];%[^;];%[^;];%[^\n]",newconsultation->Employee_ID,newconsultation->Employee_Name,newconsultation->Consultation_Time,newconsultation->Consultation_Reason)!=4){
            free(newconsultation);//if reading the file failed free the memory 
            break;
        }

        //now we need to define the priority of the appointment 
        //we need to define the priority of the appointment based on the consultation reason 
        //so we need to define the priority of each consultation reason 

        if(strcmp(newconsultation->Consultation_Reason,"Work accident")==0){
            newconsultation->priority=4;
        }
        else if(strcmp(newconsultation->Consultation_Reason,"Occupational disease")==0){
            newconsultation->priority=3;
        }
        else if(strcmp(newconsultation->Consultation_Reason,"Return-to-work")==0){
            newconsultation->priority=2;
        }
        else if(strcmp(newconsultation->Consultation_Reason,"Pre-employment")==0){
            newconsultation->priority=2;
        }
        else if(strcmp(newconsultation->Consultation_Reason,"Periodic")==0){
            newconsultation->priority=1;
        }//now we had defined the priority of the appointment based on the consultation reason
        
        add_appointment(q,newconsultation);//we need to add the new consultation to the queue
        
    }

    fclose(file);//close the file 
    return q;//return the queue
}


//we need a function to initialize a priority to the new appointments 

int initialize_appointments_priority(char* consultation_reason){
    if(strcmp(consultation_reason,"Work accident")==0){
        return 4;
    }
    else if(strcmp(consultation_reason,"Occupational disease")==0){
        return 3;
    }
    else if(strcmp(consultation_reason,"Return-to-work")==0){
        return 2;
    }
    else if(strcmp(consultation_reason,"Pre-employment")==0){
        return 2;
    }
    else if(strcmp(consultation_reason,"Periodic")==0){
        return 1;
    }
    return 0;
}

   

   



//now we need a function to add new apppoinments on-demand

void adding_new_appointments(Queue* q,char* ID,char* Name,char* consultatio_reason,char* time){
    if(q->size>=max_appointments){
        printf("The queue is full\n");
        return;
    }

    consultation* newconsultation = (consultation*)malloc(sizeof(consultation));//we need to allocate memory for the new appointment

    strcpy(newconsultation->Employee_ID,ID);//we need to copy the id of the employee to the new appointment 
    strcpy(newconsultation->Employee_Name,Name);//we need to copy the name of the employee to the new appointment 
    strcpy(newconsultation->Consultation_Reason,consultatio_reason);//we need to copy the consultation reason of the employee to the new appointment 
    strcpy(newconsultation->Consultation_Time,time);//we need to copy the consultation time of the employee to the new appointment*
    newconsultation->priority=initialize_appointments_priority(consultatio_reason);//we need to define the priority of the new appointment base on the consultation reason
    add_appointment(q,newconsultation);//we need to add the new appointment to the queue
    q->size++;//we need to increment the size of the queue because we added a new appointment to the queue

}






















