#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define employeeRE "EmpRecords.txt"
#define COnsultationS "Consultations.txt "



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
    char Employee_IDC[ID];//we need to define the id of the employee and i write IDC just to make the difference between the ID in the employee record and this one  
    char Employee_Name[full_name];//we need to define the name of the employee 
    char Consultation_Time[date2];//we need to define the consultation time of the employee 
    char Consultation_Reason[500];//we need to define the consultation reason of the employee 
    struct consultation *p; 
    int priority;//we need to define the priority of the appointment

}consultation;//we need to define a struct that holds the consultation information 

typedef struct Queue_appointments{
    consultation* head;
    consultation* tail;
    int size;//we need to define the size of the queue to know how many appointments in the queue so we dont exceed the maximum number of appointments in the queue  which is 10
}Queue_appointments;//we need to define a struct that holds the head and the tail of the queue

Queue_appointments* create_Queue(){
    Queue_appointments* q = (Queue_appointments*)malloc(sizeof(Queue_appointments));//we need to allocate memory for the queue
    q->head=NULL;
    q->tail=NULL;
    q->size=0;//we need to put the size of the queue to 0 because the queue is empty at first 
    return q;
}


//now we need a function to add a new appointment to the queue

void add_appointment(Queue_appointments* q,consultation* newconsultation){
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
     Queue_appointments* q = create_Queue();//we need to create a queue to store the consultations 
    while(!feof(file)){//we need a loop to read consultation file bu using feof it loop until the end of the file and line by liner 
        consultation* newconsultation = (consultation*)malloc(sizeof(consultation));
        if(newconsultation==NULL){
            printf("cannot allocate\n");
            return NULL;
        }
        //we need to read the consultation file and stores them in our struct 
        if(fscanf(file,"%[^;];%[^;];%[^;];%[^\n]",newconsultation->Employee_IDC,newconsultation->Employee_Name,newconsultation->Consultation_Time,newconsultation->Consultation_Reason)!=4){
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
//but if the reason is return to work it will be not accepted 

void adding_new_appointments(Queue_appointments* q,char* ID,char* Name,char* consultatio_reason,char* time){
    if(q->size>=max_appointments){
        printf("The queue is full\n");
        printf("rscheduling the appointment for the next day\n");
        rescheduling_for_nextday(q);//if the queue is full we need to reschedule the appointment for the next day
        return;
    }

    if(strcmp(consultatio_reason,"Return-to-work")==0){
        printf("The reason is return to work so the appointment will not be accepted\n");
        return;
    }

    consultation* newconsultation = (consultation*)malloc(sizeof(consultation));//we need to allocate memory for the new appointment
    

    strcpy(newconsultation->Employee_IDC,ID);//we need to copy the id of the employee to the new appointment 
    strcpy(newconsultation->Employee_Name,Name);//we need to copy the name of the employee to the new appointment 
    strcpy(newconsultation->Consultation_Reason,consultatio_reason);//we need to copy the consultation reason of the employee to the new appointment 
    strcpy(newconsultation->Consultation_Time,time);//we need to copy the consultation time of the employee to the new appointment*
    newconsultation->priority=initialize_appointments_priority(consultatio_reason);//we need to define the priority of the new appointment base on the consultation reason
    add_appointment(q,newconsultation);//we need to add the new appointment to the queue
    q->size++;//we need to increment the size of the queue because we added a new appointment to the queue

}



void rescheduling_for_nextday(Queue_appointments* q){
    if(q->size==0){
        printf("The queue is empty\n");
        return;
    }
    consultation* temp = q->head;//we need a temporary pointer to point to the head of the queue because we need to loop through the queue to reschedule the appointments for the next day 


    //we will loop through the queue until we reach the last appointment in the queue knowing that the last appointment in the queue has the lowest priority (it could be all of them has the highest priority but we will assume that the last appointment has the lowest priority)

    while(temp!=NULL){
        temp = temp->p;
    }
    if(temp->priority == 1){//if the last appointment in the queue has the highest priority we cannot reschedule
        printf("Cannot reschedule the appointment due to the highest priority\n");
        return;
    }
    //if the condition abouve is not satisfied we can reschedule the appointment for the next day

    strcpy(temp->Consultation_Time,"Next day");//we need to reschedule the appointment for the next day 
    printf("The appointment rescheduled successfully for the employye ID = %s  \n",temp->Employee_IDC);
}

//now we move to the cancelling or closing function(once the consultation is finished)

void closing(Queue_appointments* q,ptr *employees_records_head){
    if(q->size==0){
        printf("The queue is empty no appointment to close\n");
        return;
    }

    consultation* finished = q->head;
    q->head=q->head->p;//we need to move to the next appointment in the queue because we are going to close the first appointment in the queue , because it it  obviously that is the appointment in the head it will be the first finished due to the his highest priority
    q->size--;

    //now we are going to update our empoyyes's records 

    Employerecords* updated = *employees_records_head;
    while(updated!=NULL && strcmp(updated->Employee_ID,finished->Employee_IDC)!=0){//we need to loop through the employees records to find the employee we want to update 
        updated=updated->p;//we need to move to the next employee in the list because we didnt find the employee we want to update yet
    }

    char consultationdate[date];
    printf("Enter the consultation date . Please ensurte that you enter it in the following format!\n");
    printf("Date format : DD/MM/YYYY\n");
    printf("consultation_Date : ");
    scanf("%10s",consultationdate);


    if(updated!=NULL){//it means that we found the id of the employement 
        strcpy(updated->Last_consultation_Date,consultationdate); 
        printf("Employee recored have been updated for %s\n",updated->Employee_ID);
       
    }else if (strcmp(finished->Consultation_Reason,"Pre-employment")==0){
        //if the reason is pre-employment we gotta add a new employee to the record list 
        Employerecords* newemployee =(Employerecords*)malloc(sizeof(Employerecords));
        if(newemployee==NULL){
            printf("Failed to create the newemployee record!!!!");
            return;
        }
        strcpy(newemployee->Employee_ID,finished->Employee_IDC);//we need to copy the id and put it in the record
        strcpy(newemployee->Full_Name,finished->Employee_Name);//we need to copy the name of the employee
        strcpy(newemployee->Last_consultation_Date,consultationdate);
        newemployee->Total_Number_of_consultations=1;
        newemployee->p=*employees_records_head;
        *employees_records_head = newemployee;
        printf("A new employee have been added to the list!!");
        printf("Employee_ID : %s",newemployee->Employee_ID);
        printf("Employee Full Name : %s",newemployee->Full_Name) ;   
    }

    //after completing the consutlation or the appointment we have to delete it 

    free(finished);
     
}

//this function we only use it in scheduling next appointment for the next day for return to work visit
void add_appointment_for_nextday(Queue_appointments* q,char* ID,char* Name,char* reason,char* time){
    consultation* newone = (consultation*)malloc(sizeof(
        consultation ));
    strcpy(newone->Employee_IDC,ID);
    strcpy(newone->Employee_Name,Name);
    strcpy(newone->Consultation_Reason,reason);
    strcpy(newone->Consultation_Time,time);

    if (strcmp(reason, "Return-to-work") == 0) {
        newone->priority = 2;
    }
    newone->p = NULL;

    if(q->head==NULL || q->head->priority <newone->priority){
        newone->p=q->head;
        q->head=newone;
        if(q->tail==NULL) q->tail=newone;
    }else{
        consultation* temp = q->head;
        while(temp->p != NULL && temp->p->priority >= newone->priority){
            temp=temp->p;
        }
        newone->p = temp->p;
        temp->p=newone;
        if(newone->p==NULL) q->tail = newone;

    }
    q->size++;

}



void Scheduling_appointments_of_the_next_day(Queue_appointments* q,Employerecords* head_record,char* nextday){
    if(q->size>=max_appointments){
        printf("The appointments have reached the maximum!!");
        return;
    }

    char currenttime[6];//we need it to stor the cuurent appointment time(XXhXX)

    printf("Enter the first appointment time (HHhMM,eg : 08h30) : ");
    scanf("%s",currenttime);
    //now we need to cover the time into integers for time calculation 

    int hour=(currenttime[0] - '0')*10 + (currenttime[1] - '0');
    int minute=(currenttime[3] - '0')*10 +(currenttime[4] - '0');


    Employerecords* employee = head_record;
    while(employee!=NULL && q->size < max_appointments) {
        if(strcmp(employee->Retrurn_to_wrok_Date,nextday)==0){
            add_appointment_for_nextday(q,employee->Employee_ID,employee->Full_Name,"Return-to-work",currenttime);
        }
        else if(strcmp(employee->Last_consultation_Date,"")!=0){
            char lastyears[5]={employee->Last_consultation_Date[6],employee->Last_consultation_Date[7], employee->Last_consultation_Date[8],employee->Last_consultation_Date[9] , '\0'};
            char nextyears[5]={nextday[6],nextday[7],nextday[8],nextday[9]};
            //now we need to convert these year into integers (for better manipulation)and im going to use atoi function that convert any string into integer 
            int lastyear = atoi(lastyears);
            int nextyear = atoi(nextyears);

            if(lastyear - nextyear <= 1 ){
                adding_new_appointments(q,employee->Employee_ID,employee->Full_Name,"Periodic examination",currenttime);
            }

        }
        employee=employee->p;//move to the next employeee

        //now we need an algorithm to compute the time
        minute=minute+45;
        if(minute>=60){
            hour=hour+1;
            minute=minute - 60;
        }
        //i used '0' because it's ascii value is 48 and when we add for example 48 to 5(5hours) it will return 53 and 53 is the ascii value of the charachter '5'
        currenttime[0] = (hour / 10) +'0';
        currenttime[1] = (hour%10)+'0';
        currenttime[2] = 'h';
        currenttime[3] = (minute/10)+ '0';
        currenttime[4]= (minute %10) + '0';
    } 

    printf("Scheduling appointments of the next day successfully.\n");

}



// TASK 4 : Updating the records and consultations Files


// now we need a procedure that let us update the records and consultaions files 


void update_record_consultation_files(Queue_appointments* q,Employerecords* records){
    //we need to open the EmpRecords.txt file in write mode because we are going to edit the file so we need to overwrite the olddata and replace it with new data 
    FILE* employee_file = fopen("EmpRecords.txt","w");
    //we need to open the Consultations.txt file in append mode  because we just need to add new data to the end of the file without erasing existing content 
    FILE* consultation_file = fopen("Consultations.txt","a");
    if(!employee_file || !consultation_file){
        printf("Error!!! ""cannot open the files for the update.\n");
        return;
    }

    //now we are going to update the employee records file 

    Employerecords* employee = records;
    while(employee){
        fprintf(employee_file,"%s;%s;%s;%s\n",employee->Employee_ID,employee->Full_Name,employee->Last_consultation_Date,employee->Retrurn_to_wrok_Date);
        employee=employee->p;
    }

    //now we are going to update the consultations fime 

    consultation* cons = q->head;
    while(cons){
        Employerecords* emp = records;
        while(emp){
            if(strcmp(emp->Employee_ID,cons->Employee_IDC)==0){
                fprintf(consultation_file,"%s;%s;%s;%s\n",cons->Employee_IDC,emp->Full_Name,cons->Consultation_Time,cons->Consultation_Reason);
                break;//we need to break once we found the employee
            }
            emp=emp->p;
        }
        cons=cons->p;
    }
}

void display_employees(Employerecords* head){
    Employerecords* temp = head;
    while(temp!=NULL){
        printf("%s;%s;%d;%s;%s;%s",temp->Employee_ID,temp->Full_Name,temp->Total_Number_of_consultations,temp->Last_consultation_Date,temp->Retrurn_to_wrok_Date,temp->history);
        printf("\n");
        temp=temp->p;
}
}

void display_appointments(Queue_appointments* q){
    if(q->size == 0){
        printf("No appointments to display \n");
        return;
    }
    consultation* temp = q->head;
    while(temp!=NULL){
        printf("%s;%s;%s;%s\n",temp->Employee_IDC,temp->Employee_Name,temp->Consultation_Time,temp->Consultation_Reason);
        temp=temp->p;
    }
}




int main(){
    Queue_appointments queue = {NULL,NULL,0};//initialize the queue
    Employerecords* head = NULL;//initialize the list
    consultation* cons = NULL;

   head =  read_emprecord_file("EmpRecords.txt");
   cons = read_consultation_file("Consultations.txt");
   



    int choice;
    do{
        printf("\nOccupational Health Management System\n");
        printf("1.Managing employees’ records\n");
        printf("2.Managing appointments\n");
        printf("3.Update Files\n");
        printf("4.Exit\n");
        printf("Enter your choice : ");
        scanf("%d",&choice);
        getchar();
        switch (choice){
            case 1 :{ 
            int choice1;
            do{
            printf("\nEmployee Management\n");
            printf("1.Add Employee\n");
            printf("2.Update Employee\n");
            printf("3.Delete Employee\n");
            printf("4.Display Employee\n");
            printf("5.Back to main menu\n");
            printf("Enter your choice : ");
            scanf("%d",&choice1);
            getchar();
            switch (choice1){
                case 1:{
                    Employerecords newEmp;

                    printf("Enter Employee ID : ");
                    scanf("%s",newEmp.Employee_ID);
                    getchar();
                    

                    printf("Enter Full Name : ");
                    scanf("%[^\n]",newEmp.Full_Name);


                    printf("Enter Last Consultation Date (DD/MM/YYYY ) : ");
                    scanf("%s",newEmp.Last_consultation_Date);

                    printf("Enter the total number of consultations : ");
                    scanf("%d",&newEmp.Total_Number_of_consultations);

                    printf("Enter Return to work date :  ");
                    scanf("%s",newEmp.Retrurn_to_wrok_Date);

                    printf("Enter the history of reasons : ");
                    scanf("%[^\n]",newEmp.history);

                    add(&head,newEmp);
                    printf("Employee added successfully\n");
                    break;
                }
                case 2 : {
                    Employerecords updateemp;
                    char id[ID];
                    printf("Enter the ID :");
                    scanf("%s",id);
                    getchar();

                    printf("Enter new Full Name : ");
                    scanf("%[^\n]",updateemp.Full_Name);
                    getchar();

                    printf("Enter New last consultation Date DD/MM/YYYY : ");
                    scanf("%s",updateemp.Last_consultation_Date);
                    getchar();

                    printf("Enter New Total number of consultations : ");
                    scanf("%d",&updateemp.Total_Number_of_consultations);
                    getchar();

                    printf("Enter New return to work date : ");
                    scanf("%s",updateemp.Retrurn_to_wrok_Date);
                    getchar();

                    printf("Enter the new History reasons : ");
                    scanf("%[^\n]",updateemp.history);
                    getchar();

                    update(head,updateemp,id);
                    break;
                }

                case 3:{
                    char id[ID];
                    printf("Enter Employee ID to delete : ");
                    scanf("%s",id);
                    getchar();

                    delete(&head,id);
                    break;
                }

                case 4:
                display_employees(head);
                break;

                case 5 :
                printf("Retruning to main menu.....\n");
                break;

                default:
                printf("Invalid choice !!!\n");
                
            }  
        } while(choice1!=5);
        break;
    }  

    case 2: {
        int choice2;
        do{
            printf("\nAPPOINTMENT Management\n");
            printf("1.Add New Appointment\n");
            printf("2.closing Appointment\n");
            printf("3.Scheduling Appointment\n");
            printf("4.Display Appointment\n");
            printf("5.Back to Main Menu\n");
            printf("Enter your choice");
            scanf("%d",&choice2);
            getchar();
            
            switch(choice2){
                case 1:{
                char id[ID];
                char name[full_name];
                char reason[100];
                char time[date2];

                printf("Enter Employee ID : ");
                scanf("%s",id);
                getchar();

                printf("Enter Employee Full name : ");
                scanf("%[^\n]",name);
                getchar();

                printf("Enter Reason for consulation : ");
                scanf("%[^\n]",reason);
                getchar();

                printf("Enter Appointment time (eg 08h30) : ");
                scanf("%s",time);
                getchar();

                adding_new_appointments(&queue,id,name,reason,time);
                printf("Appointment added successfully\n");

                break;
            }

            case 2 : {
                char id[ID];
                printf("Enter the ID of employee to close appointment : ");
                scanf("%s",id);
                getchar();
                
                closing(&queue,&head);
                break;
            }

            case 3 :{
                char nextday[date];
                printf("Enter The date of the next day DD/MM/YYYY : ");
                scanf("%s",nextday);
                getchar();

                Scheduling_appointments_of_the_next_day(&queue,&head,nextday);
                break ;
            }

            case 4:{
            display_appointments(&queue);
            break;
            }

            case 5 :
            printf("Retruning to main menu.....\n");
            break;

            default:
            printf("Invalid choice !!!\n");
        }
        }while(choice2!=5);
        break;
    }

    case 3 : {
        update_record_consultation_files(&queue,&head);
        break;
    }

    case 4 : {
        printf("Exiting the system...\n");
        break;
    }
    
    default : 
    printf("Invalid choice!!!\n");
     }
    
    }while(choice!=4);


  return 0;
}






 



























