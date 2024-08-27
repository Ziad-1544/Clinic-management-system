#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Pre-poccesor phase:
#define start()  printf("               ------------------------------------------\n                Welcome to the Clinic Management System\n               ------------------------------------------\n ")
#define users()  printf("------------------\n 1.Admin user \n 2.Secretary user \n 3.Patient user \n 4.Exit\n------------------\nPlease choose the user mode: ")
#define admin_options()  printf("  1.Add Secretary \n  2.Add Patient \nPlease choose option: ")
#define secretary_options1()  printf("  1.Accept all requests\n  2.clear all Requests\nPlease choose option: ")
#define secretary_options2()  printf("  1.Show today's reservation attached with user ID\n  2.Search for specific patient record\n  3.Edit slot status\n  4.Add patient history\n  5.Delete patient profile \n  6.View all patients profiles \nPlease choose option: ")
#define patient_options()  printf("    1.Log in\n    2.Sign up\nPlease choose option: ")
#define post_login_options()  printf("    1.View history\n    2.Request a visit\nPlease choose an option: ");
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Structs:
typedef struct patient_data{
    char name[30];
    u16 age;
    u8 gender;
    u16 id;
    struct patient_data *next;
}pat_data;
pat_data *head_pat = NULL;

typedef struct patient_history{
    u16 id;
    u8 history[1000];
    struct patient_history *next;
}history;
history *head_his=NULL;

typedef struct slots{
    u8 slot[20];
    u8 status; // 0 for free, 1 for pending, 2 for reserved
    u32 id;  // 0 if not reserved
}slots;

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Global varibales
u8 admin=0,secretary=0;
u16 sn_id=0,user_found=0,id_saved,secretary_acc=0;
char secreatry_name[30];

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Slots:
 slots arr[5] = {
    {"2pm to 2:30pm", 0, 0},
    {"2:30pm to 3pm", 0, 0},
    {"3pm to 3:30pm", 0, 0},
    {"4pm to 4:30pm", 0, 0},
    {"4:30pm to 5pm", 0, 0}
};

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Functions Prototypes:
void admin_acces();
void admin_acces_denied();
const char* gend(u8 type);
void set_patient(char *name, u16 age, u8 gender);
void sign_up_pat();
void logn_in_pat();
void view_patients_profile();
void post_login_pat();
void view_history(u16 id);
void request_slots();
void secretary_acces();
void secretary_acces_denied();
void requests_orders(u16 requests_order);
void show_today_slots();
void view_patient();
void add_pat_history();
void edit_slot();
void delete_pat();
void sign_up_secretary();

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main(){
    start();
    while(1){
         users();
        u8 user_mode;    scanf("%d",&user_mode);
        switch (user_mode)
        {
        case 1:
            admin=0;
            admin_acces();
            admin_acces_denied();
            u16 again;
            do{
            admin_options(); 
            u16 choice;
            scanf("%d",&choice);
            switch (choice)
            {
            case 1:
                sign_up_secretary();
                break;
            case 2:
                sign_up_pat();
                break;
            default:
                printf("Invalid choice\n");
                break;
            }
            printf("Do you want to leave this user?(0 to exit ,any num to continue): ");
            scanf("%d",&again);
            }while(again);
            break;
        case 2:
            u16 again1;
            do{
            if(secretary_acc){
            secretary=0;
            secretary_acces();
            secretary_acces_denied();
            u16 no_requests=0;
            for (size_t i = 0; i < 5; i++)
            {
               if(arr[i].status!=0 && arr[i].status!=2 ){
                no_requests=1;
               }
            }
            if(no_requests){
            secretary_options1();
            u16 requests_order;
            scanf("%d",&requests_order);
            requests_orders(requests_order);
            }else{
                printf("---------------------------------------------------------------\n");
                printf("No pending requests\n");
                printf("---------------------------------------------------------------\n");
            }
            secretary_options2();
            u16 secretary_option;
            scanf("%d",&secretary_option);
            switch (secretary_option)
            {
            /*case 0:
                break;*/
                
            case 1:
                show_today_slots();
                break;
            case 2:
                view_patient();
                break;
            case 3:
                edit_slot();
                break;
            case 4:
                add_pat_history();
                break;
            case 5:
                delete_pat();
                break;
            case 6:
                view_patients_profile();
                break;
            default:
                printf("Incorrect choice\n");
                break;
            }}else{
                printf("You don't have access to this feature\nAdmin should create a secretary account\n");
                printf("-----------------------------------------------\n");
            }
            printf("Do you want to leave this user?(0 to exit ,any num to continue): ");
            scanf("%d",&again1);
            }while(again1);
            break;
        case 3:
            u16 again2;
            do{
            patient_options();
            u16 patient_option;
            scanf("%d",&patient_option);

            switch (patient_option) {
            case 1:
                logn_in_pat();
                break;
            case 2:
                sign_up_pat();
                break;
            default:
                printf("Incorrect choice\n");
                break;
            }
            printf("Do you want to leave this user?(0 to exit ,any num to continue): ");
            scanf("%d",&again2);
            }while(again2);
            break;
        case 4:
            printf("Shutting Down");
            return 0;
        default:
            printf("Incorrect choice\n");
            break;
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Function bodies:
void admin_acces(){
    u16 default_pass=1234;
    u16 user_pass;
    for (size_t i = 0; i < 3; i++)
    {
        printf("Please enter the admin passcode: ");  scanf("%hu",&user_pass);
        if(user_pass==default_pass){
            printf("Welcome Back Ziad kassem\n");
            admin=1;
            break;
        }else{
            printf("Wrong password\n");
            printf("You have %d chances left\n",3-i-1);
        }
    }  
}
void admin_acces_denied(){
    if(!admin){
                printf("Access Denied\n");
                printf("Shutting Down");
                exit(0);
            }
}
const char* gend(u8 type){
    if(type==1){
        return "Male";
    }else if(type==2){
        return "Female"; 
    }else{
        return "Patient refused to specify";
    }
}
void view_patients_profile(){
    if(head_pat!=NULL){
        pat_data *ptr=head_pat;
        do{
            printf("-------------------------------------------------------\n");
            printf("Patient ID: %d\n",ptr->id);
            printf("    Name: %s\n",ptr->name);
            printf("    Age: %d\n",ptr->age);
            printf("    Gender: %s\n",gend(ptr->gender));
            printf("-------------------------------------------------------\n");
            ptr=ptr->next;
        }while(ptr!=NULL);

    }else{
        printf("No patients in the list\n");
    }
}

void set_patient(char *name, u16 age, u8 gender){
    sn_id++;
    pat_data *ptr=(pat_data*) malloc(sizeof(pat_data));
    strcpy(ptr->name, name); 
    ptr->age=age;
    ptr->id=1000+sn_id;
    ptr->gender=gender;
    ptr->next=head_pat;
    head_pat=ptr;
    printf("    Patient Profile created succesfuly\n    Patient ID:%i\n",ptr->id);
    printf("-------------------------------------------------------\n");
}
void sign_up_pat(){
            char name[30];
            printf("Enter patient name: ");
            u8 c;
            while ((c = getchar()) != '\n' && c != EOF);
            fgets(name,sizeof(name),stdin);
            u8 i=0;
            while (name[i] != '\n' && name[i] != '\0') { i++; }
            name[i] = '\0';

            u16 age;
            printf("Enter patient age: ");
            scanf("%hu", &age);

            u8 gender;
            printf("Enter patient gender (1 for male, 2 for female): ");
            scanf("%hhu", &gender);

            while ((c = getchar()) != '\n' && c != EOF);
            //printf("test\n");
            set_patient(name, age, gender);
            //printf("test\n");
}
void logn_in_pat(){
    u16 id;
    user_found=0;
    printf("Please enter your ID: ");
    scanf("%hu",&id);
    id_saved=id;

    pat_data *ptr=head_pat;
    for (size_t i = 0; i < sn_id; i++)
    {
       if(id==ptr->id){
        printf("Welcome %s\n",ptr->name);
        user_found=1;
        break;
       }
       ptr=ptr->next;
    }

    post_login_pat();
}
void post_login_pat(){
    if(user_found==1){
        u16 post_login_option;
        post_login_options();
        scanf("%d",&post_login_option);
        switch (post_login_option)
        {
        case 1:
            view_history(id_saved);
            break;
        case 2:
            request_slots();
            break;
        default:
            printf("Incorrect choice");
            post_login_pat();
            break;
        }
    }else{
        printf("Invalid ID\n");
        logn_in_pat();
    }
}
void view_history(u16 id){
    if(head_his!=NULL){
        history *ptr =head_his;
        for (size_t i = 0; i < sn_id; i++){
            if(id==ptr->id){
                printf("ID: %d\n",ptr->id);
                printf("-------------------------------------------------------\n");
                printf("history: %s\n",ptr->history);
                printf("-------------------------------------------------------\n");
                break;
            }
            ptr=ptr->next;
        }
    }else{
        printf("No history\n");
        printf("-----------------------------------------------\n");
    }
}
void request_slots(){
    printf("Avaible Slots: \n");
    for (size_t i = 0; i < 5; i++)
    {
        if(arr[i].status==0){
            printf("-------------------------------------------------------\n");
            printf("%d. Slot time: %s\n",i+1,arr[i].slot);
            printf("-------------------------------------------------------\n");        
        }
    }
    u16 slot;
    printf("Please choose your slot number: ");
    scanf("%hu",&slot);
    arr[slot-1].status=1;
    arr[slot-1].id=id_saved;
    printf("Slot requested succesfully\n");
    printf("-------------------------------------------------------\n");        
}
void secretary_acces(){
    u16 default_pass=1234;
    u16 user_pass;
    for (size_t i = 0; i < 3; i++)
    {
        printf("Please enter the secretary passcode: ");  scanf("%hu",&user_pass);
        if(user_pass==default_pass){
            printf("Welcome %s\n",secreatry_name);
            secretary=1;
            break;
        }else{
            printf("Wrong password\n");
            printf("You have %d chances left\n",3-i-1);
        }
    }  
}
void secretary_acces_denied(){
    if(!secretary){
                printf("Access Denied\n");
                printf("Shutting Down");
                exit(0);
            }
}
void requests_orders(u16 requests_order){
    if(requests_order==1){
        for (size_t i = 0; i < 5; i++)
        {
            if(arr[i].status==1) arr[i].status=2;
        }
        
    }else{
        for (size_t i = 0; i < 5; i++){
            if(arr[i].status==1) 
            {
                arr[i].status=0;
                arr[i].id=0;
            }
        }
    }
}
void show_today_slots(){
    u16 no_requests=0;
            for (size_t i = 0; i < 5; i++)
            {
               if(arr[i].status!=0 && arr[i].status!=1){
                no_requests=1;
               }
            }
            if(no_requests){
            for (size_t i = 0; i < 5; i++){
        if(arr[i].status==2) {
            printf("-----------------------------------------------\n");
            printf("Slot %d: %s is reserved by patient ID: %d\n",i+1,arr[i].slot,arr[i].id );
            printf("-----------------------------------------------\n");
            }
            }
            }else{
                printf("No Slots reserverd for today\n");
                printf("---------------------------------------------------------------\n");
            }
    
}
void view_patient(){
    u8 id_found=0;
    if(head_pat!=NULL){
        u16 pat_id;
                printf("Please enter the patient id: ");
                scanf("%d",&pat_id);
    pat_data *ptr=head_pat;
    for (size_t i = 0; i < sn_id; i++){
        if(ptr->id==pat_id){
            id_found=1;
            printf("-----------------------------------------------\n");
            printf("Patient name: %s\n",ptr->name);
            printf("Patient age: %d\n",ptr->age);
            printf("Patient gender: %s\n",gend(ptr->gender));
            view_history(pat_id);
            printf("-----------------------------------------------\n");
        }
        ptr=ptr->next;
    }
    }else{
        printf("No patients in the list\n");
        printf("-----------------------------------------------\n");
    }
    if(!id_found){
        printf("Patient ID is not found in the list\n");
        printf("-----------------------------------------------\n");
    }
}
void add_pat_history(){
    if(head_pat!=NULL){
        u16 pat_id;
                printf("Please enter the patient id: ");
                scanf("%d",&pat_id);
    history *ptr = head_his;
    while(ptr != NULL){
        if(ptr->id == pat_id){
            break;
        }
        ptr = ptr->next;
    }

    if(ptr == NULL){
        // No history found for the patient, create a new one
        history *new_history = (history*)malloc(sizeof(history));
        new_history->id = pat_id;
        printf("Enter patient new record: ");
        u8 c;
        while ((c = getchar()) != '\n' && c != EOF);
        fgets(new_history->history, sizeof(new_history->history), stdin);
        u8 i = 0;
        while (new_history->history[i] != '\n' && new_history->history[i] != '\0') { i++; }
        new_history->history[i] = '\0';
        new_history->next = head_his;
        head_his = new_history;
    }else{
        // History found for the patient, append the new record to the old history
        char new_record[1000];
        printf("Enter patient new record: ");
        u8 c;
        while ((c = getchar()) != '\n' && c != EOF);
        fgets(new_record, sizeof(new_record), stdin);
        u8 i = 0;
        while (new_record[i] != '\n' && new_record[i] != '\0') { i++; }
        new_record[i] = '\0';

        strcat(ptr->history, "\n");
        strcat(ptr->history, new_record);
    }
    printf("Record added succesfully\n ");
    printf("-----------------------------------------------\n");
    }else{
        printf("No patients in the list\n");
    }

}
void edit_slot(){
    if(head_pat != NULL) {
    printf("Enter the slot number you want to edit (1-5): ");
    u8 choice;
    scanf("%hhu", &choice); 
    printf("To change slot status to:\n  free enter 0\n  pending enter 1\n  reserved enter 2\nPlease enter your choice: ");
    u8 status;
    scanf("%hhu", &status); 

    arr[choice-1].status=status;
    if(status==0){
        arr[choice-1].id=0;
    }else if(status==1 || status==2){
        printf("Enter patient id: ");
        scanf("%hu", &arr[choice-1].id); 
    }
    printf("Status changed succesfully\n");
    printf("-------------------------------------------------------\n");
    }else{
        printf("No patients in the list\n");
        printf("-------------------------------------------------------\n");
    }
}
void delete_pat(){
    if(head_pat != NULL) {
        u16 pat_id;
        printf("Please enter the patient id: ");
        scanf("%hu",&pat_id);

        pat_data *ptr = head_pat;
        pat_data *prev = NULL;

        while(ptr != NULL) {
            if(ptr->id == pat_id) {
                if(prev == NULL) {
                    head_pat = ptr->next;
                } else {
                    prev->next = ptr->next;
                }
                free(ptr);
                sn_id--; 
                printf("Deleted succesfully\n");
                printf("-----------------------------------------------\n");
                return;
            }
            prev = ptr;
            ptr = ptr->next;
        }

        printf("No patient with ID: %d exist\n",pat_id);
        printf("-----------------------------------------------\n");
    } else {
        printf("No patients to delete\n");
        printf("-----------------------------------------------\n");
    }
}
void sign_up_secretary(){
            printf("Enter secretary name: ");
            u8 c;
            while ((c = getchar()) != '\n' && c != EOF);
            fgets(secreatry_name,sizeof(secreatry_name),stdin);
            u8 i=0;
            while (secreatry_name[i] != '\n' && secreatry_name[i] != '\0') { i++; }
            secreatry_name[i] = '\0';
            printf("Secretary id:9999 \n");
            printf("-----------------------------------------------\n");
            secretary_acc=1;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------