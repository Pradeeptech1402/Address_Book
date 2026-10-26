#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include <ctype.h>
// validation function to check the name is valid
int name_is_invalid(const char *name){
    if(strlen(name)==0) return 1;
    // Check wether name consist of character other than alphabhet and space
    for(int i=0;i<name[i]!='\0';i++){
        if(!isalpha(name[i]) && name[i] != ' '){
            printf("  [!] Error: Name should contain only alphabets and spaces.\n");
            return 1;
        }
    }
    return 0;
}
// validation function to check the phone number is valid
int phone_is_invalid(AddressBook* addressBook, const char* phone){
    // length of the phone number must me 10 digit
    if(strlen(phone) != 10){
        printf("  [!] Error: Phone number must be exactly 10 digits.\n");
        return 1;
    }
    // phone number character should digit
    for(int i=0;phone[i] != '\0';i++){
        if(!isdigit(phone[i])){
            printf("  [!] Error: Phone number must contain only digits.\n");
            return 1;
        }
    }
    // check weather this phone number is already regestered in AddressBook
    for(int i=0;i< addressBook->contactCount;i++){
        if(strcmp(addressBook->contacts[i].phone,phone)==0){
            printf("  [!] Error: Phone number is already registered.\n");
            return 1;
        }
    }
    return 0;
}
// validation function to check the email is valid
int email_is_invalid(AddressBook* addressBook, char* email){
    if(strlen(email)==0)return 1;

    // check gmail characters consist of only 'a-z,A-Z' , '_' , '@' , '.' only
    for(int i=0;email[i]!='\0';i++){
        char ch=email[i];
        if(!(isalpha(ch)||ch=='.'||ch=='@'||ch=='_')){
            printf("  [!] Error: Email can only contain letters, '@', '.', and '_'.\n");
            return 1;
        }
    }
    // check email should be in formate something@something.something
    char* at = strchr(email,'@');
    char* dot = strchr(email,'.');
    if(!(at&&dot&&at<=dot&&isalpha(*(at-1))&&isalpha(*(at+1))&&isalpha(*(dot+1)))){
        printf("  [!] Error: Format must be 'user@domain.ext'\n");
        return 1;
    }

    //  convert the email alpha characters to lowercase;
    for(int i=0;email[i]!='\0';i++){
        if(email[i]>='A' && email[i]<='Z'){
            email[i] = (email[i]-'A')+'a';
        }
    }

    // check wether this email is already regestered
    for(int i=0;i<addressBook->contactCount;i++){
        if(strcmp(addressBook->contacts[i].email,email)==0){
            printf("  [!] Error: Email is already registered.\n");
            return 1;
        }
    }
    return 0;
}
// validation function to check the phone number is valid 
int search_phone_is_invalid(const char* phone){
    // length of the phone number must me 10 digit
    if(strlen(phone) != 10){
        printf("  [!] Error: Phone number must be exactly 10 digits.\n");
        return 1;
    }
    // phone number character should digit
    for(int i=0;phone[i] != '\0';i++){
        if(!isdigit(phone[i])){
            printf("  [!] Error: Phone number must contain only digits.\n");
            return 1;
        }
    }
    return 0;
}
// validation function to check the email is valid
int search_email_is_invalid(char* email){
    if(strlen(email)==0)return 1;

    // check gmail characters consist of only 'a-z,A-Z' , '_' , '@' , '.' only
    for(int i=0;email[i]!='\0';i++){
        char ch=email[i];
        if(!(isalpha(ch)||ch=='.'||ch=='@'||ch=='_')){
            printf("  [!] Error: Email can only contain letters, '@', '.', and '_'.\n");
            return 1;
        }
    }
    // check email should be in formate something@something.something
    char* at = strchr(email,'@');
    char* dot = strchr(email,'.');
    if(!(at&&dot&&at<=dot&&isalpha(*(at-1))&&isalpha(*(at+1))&&isalpha(*(dot+1)))){
        printf("  [!] Error: Format must be 'user@domain.ext'\n");
        return 1;
    }

    //  convert the email alpha characters to lowercase;
    for(int i=0;email[i]!='\0';i++){
        if(email[i]>='A' && email[i]<='Z'){
            email[i] = (email[i]-'A')+'a';
        }
    }
    return 0;
}
// printformat to print the single contact after search
void print_contact(AddressBook* addressBook,int contact_num){
    if(contact_num < 0){
        return;
    }
    printf("\n  ---------------- Contact Details ----------------\n");
    printf("  Index : %d\n", contact_num);
    printf("  Name  : %s\n", addressBook->contacts[contact_num].name);
    printf("  Phone : %s\n", addressBook->contacts[contact_num].phone);
    printf("  Email : %s\n", addressBook->contacts[contact_num].email);
    printf("  -------------------------------------------------\n\n");
}
// to search the contact by name,phone,emeil
int search(AddressBook* addressBook,char* data,int option){
    int count;
    int i=-1;
    switch(option){
        case 1:
            count=0;
            for(int j=0;j<addressBook->contactCount;j++){
                if(strcmp(data,addressBook->contacts[j].name)==0){
                    i=j;
                    count++;
                }
            }
            if(count==0){
                printf("\n  [-] No matching contact found with that name.\n");
                return i;
            };
            if(count > 1){
                printf("\n  [-] Multiple matches found. Please search by Phone or Email.\n");
                return i;
            }
            if(count==1){
                return i;
            }
            break;
        case 2:
            for(int j=0;j<addressBook->contactCount;j++){
                if(strcmp(data,addressBook->contacts[j].phone)==0){
                    return j;
                }
            }
            printf("\n  [-] Phone number not found.\n");
            return i;
            break;
        case 3:
            for(int j=0;j<addressBook->contactCount;j++){
                if(strcmp(data,addressBook->contacts[j].email)==0){
                    return j;
                }
            }
            printf("\n  [-] Email not found.\n");
            return i;
            break;
        default:
            printf("\n  [-] Invalid search option selected.\n");
            break; 
    }
    return i;
}

// Main Functions-----
// Print all the contacts in terminal
void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    if(addressBook->contactCount==0){
        printf("\n  [-] No contacts available to display.\n");
        return;
    }

    printf("\n  ------------------------------------------------------------------------------\n");
    printf("  | %-4s | %-20s | %-15s | %-26s |\n", "No.", "Name", "Phone", "Email");
    printf("  |------|----------------------|-----------------|----------------------------|\n");

    for(int i=0;i<addressBook->contactCount;i++){
        printf("  | %-4d | %-20s | %-15s | %-26s |\n",
            i+1,
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
    }
    printf("  ------------------------------------------------------------------------------\n");
    printf("  Total Contacts: %d\n\n", addressBook->contactCount);
}
// At the start of the program. load all the student data to memory
void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    // populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}
// After modifying or creating user data Need to save before exit
void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}
// Create or Add a New contact to existing contact book
void createContact(AddressBook *addressBook)
{
    /* Define the logic to create a Contacts */
    if(addressBook->contactCount>=MAX_CONTACTS){
        printf("\n  [!] Contact list is full. Cannot add more contacts.\n");
        return;
    }
    // initial variaples to store data before updating it to memory
    char name[50];
    char phone[20];
    char email[50];
// take input for name and veryfy the name consist of only alpha and space characters
    printf("\n  --- New Contact ---\n");
    do{
        printf("  Enter Name         : ");
        scanf(" %50[^\n]",name);
    }while(name_is_invalid(name));
// Take input for phone number and validate it consist of only
// (digits and length of number is 10 and no number exist befor in database)
    do{
        printf("  Enter Phone Number : ");
        scanf(" %20[^\n]",phone);
    }while(phone_is_invalid(addressBook,phone));
    // Take input for Email address and validate wether it is in right formate
    // (something@something.something and no email is regersterd same email in database)
    do{
        printf("  Enter Email        : ");
        scanf(" %50[^\n]",email);
    }while(email_is_invalid(addressBook,email));
// If the input is taken and validate eligible criterya then save that data to memory
    strcpy(addressBook->contacts[addressBook->contactCount].name,name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email,email);
    addressBook->contactCount += 1;
    printf("\n  [-] Contact '%s' added successfully.\n\n", addressBook->contacts[addressBook->contactCount-1].name);
}
// Search the contacts and print the details of that project
int searchContact(AddressBook *addressBook) 
{
    int exit=0;
    while(!exit){
        int id=0;
        int option=0;
        /* Define the logic for search */
        printf("\n  --- Search Contact ---\n");
        printf("  1. By Name\n");
        printf("  2. By Phone Number\n");
        printf("  3. By Email\n");
        printf("  4. Back\n");
        printf("  ----------------------\n");
        printf("  Select option > ");
        if(scanf(" %d",&option)!=1){
            printf("  [!] Invalid input. Please enter a valid number.\n");
            while(getchar() != '\n');
            continue;
        }
        char name[50];
        char phone[20];
        char email[50];

        switch(option){
            case 1:
            // search by name
                do{
                    printf("  Enter Name: ");
                    scanf(" %49[^\n]",name);
                }while(name_is_invalid(name));
                print_contact(addressBook,id=search(addressBook,name,option));
                if(id<0)continue;
                return id;
            case 2:
            // search by phone number
                do{
                    printf("  Enter Phone Number: ");
                    scanf(" %19[^\n]",phone);
                }while(search_phone_is_invalid(phone));
                print_contact(addressBook,id=search(addressBook,phone,option));
                if(id<0)continue;
                return id; 
            case 3:
            // search by email
                do{
                    printf("  Enter Email: ");
                    scanf(" %49[^\n]",email);
                }while(search_email_is_invalid(email));
                print_contact(addressBook,id=search(addressBook,email,option));
                if(id<0)continue;
                return id; 
            case 4:
            // if no need to search exit
                exit = 1;
                return -1;
                break;
            default:
            // if option is not any one from menue print
                printf("  [!] Invalid option. Please choose between 1 and 4.\n");
                break;
        }
    }
}
// Edit Contacts and update the New data
void editContact(AddressBook *addressBook)
{
    /* Define the logic for Editcontact */

    int exit = 0;
    while(!exit){
        // Search the contact that to be edit
        printf("\n  --- Edit: Select Contact ---");
        int id = searchContact(addressBook);
        if(id<0){
            return;
        }
        int option=0;
        printf("  --- Edit Options ---\n");
        printf("  1. Edit Name\n");
        printf("  2. Edit Phone Number\n");
        printf("  3. Edit Email\n");
        printf("  4. Back\n");
        printf("  --------------------\n");
        printf("  Select option > ");
        if(scanf(" %d",&option)!=1){
            printf("  [!] Invalid input. Please enter a valid number.\n");
            while(getchar() != '\n');
            continue;
        }
        char name[50];
        char phone[20];
        char email[50];

        switch(option){
            case 1:
            // Modify the name
                do{
                    printf("  Enter New Name: ");
                    scanf(" %49[^\n]",name);
                }while(name_is_invalid(name));
                strcpy(addressBook->contacts[id].name,name);
                printf("\n  [-] Name updated to '%s'.\n", addressBook->contacts[id].name);
                break;
            case 2:
            // Modify the phone number
                do{
                    printf("  Enter New Phone Number: ");
                    scanf(" %19[^\n]",phone);
                }while(phone_is_invalid(addressBook,phone));
                strcpy(addressBook->contacts[id].phone,phone);
                printf("\n  [-] Phone number updated to '%s'.\n", addressBook->contacts[id].phone);
                break;
            case 3:
            // Modify the Email
                do{
                    printf("  Enter New Email: ");
                    scanf(" %49[^\n]",email);
                }while(email_is_invalid(addressBook,email));
                strcpy(addressBook->contacts[id].email,email);
                printf("\n  [-] Email updated to '%s'.\n", addressBook->contacts[id].email);
                break;
            case 4:
            // Exit if you dont want to modify
                exit=1;
                break;
            default:
                printf("  [!] Invalid option. Please choose between 1 and 4.\n");
                break;
        }
    }
}
// Delete contact from the address book
void deleteContact(AddressBook *addressBook)
{
    /* Define the logic for deletecontact */
    printf("\n  --- Delete: Select Contact ---");
    // search the contact that need's to be deleted
    int id = searchContact(addressBook);
    if(id<0)return;
    // delete the index where searched contact present
    printf("\n  [-] Contact '%s' removed.\n", addressBook->contacts[id].name);
    int new_index=0;
    for(int i=0;i<addressBook->contactCount;i++){
        if(i != id){
            addressBook->contacts[new_index]=addressBook->contacts[i];
            new_index++;
        }
    }
    addressBook->contactCount=new_index;
}