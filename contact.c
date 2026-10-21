#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include<ctype.h>
int name_is_invalid(const char *name){
    if(strlen(name)==0) return 1;
    // Check wether name consist of character other than alphabhet and space
    for(int i=0;i<name[i]!='\0';i++){
        if(!isalpha(name[i]) && name[i] != ' '){
            printf("Error: Invalid Name (name should consist only alphabhets and spaces)\n");
            return 1;
        }
    }
    return 0;
}
int phone_is_invalid(AddressBook* addressBook, const char* phone){
    // length of the phone number must me 10 digit
    if(strlen(phone) != 10){
        printf("Error: Phone number must be 10 digits.\n");
        return 1;
    }
    // phone number character should digit
    for(int i=0;phone[i] != '\0';i++){
        if(!isdigit(phone[i])){
            printf("Error: Phone number must contain only digits.\n");
            return 1;
        }
    }
    // check weather this phone number is already regestered in AddressBook
    for(int i=0;i< addressBook->contactCount;i++){
        if(strcmp(addressBook->contacts[i].phone,phone)==0){
            printf("Error: Phone number is already registered.\n");
            return 1;
        }
    }
    return 0;
}
int email_is_invalid(AddressBook* addressBook, char* email){
    if(strlen(email)==0)return 1;

    // check gmail characters consist of only 'a-z,A-Z' , '_' , '@' , '.' only
    for(int i=0;email[i]!='\0';i++){
        char ch=email[i];
        if(!(isalpha(ch)||ch=='.'||ch=='@'||ch=='_')){
            printf("Error: Email should consist only alpha characters,'@','.','_'\n");
            return 1;
        }
    }
    // check email should be in formate something@something.something
    char* at = strchr(email,'@');
    char* dot = strchr(email,'.');
    if(!(at&&dot&&at<=dot&&isalpha(*(at-1))&&isalpha(*(at+1))&&isalpha(*(dot+1)))){
        printf("Email should be in formate 'something@something.something'\n");
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
            printf("Error: This Email is already registered.\n");
            return 1;
        }
    }
    return 0;
}


void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    if(addressBook->contactCount==0){
        printf("NO contacts found.\n");
        return;
    }

    printf("\n----------------------------------------------------------------------\n");
    printf("|%-5s|%-20s|%-15s|%-25s|\n","S.NO","Name","Phone","Email");
    printf("----------------------------------------------------------------------\n");

    for(int i=0;i<addressBook->contactCount;i++){
        printf("|%-5d|%-20s|%-15s|%-25s|\n",
            i+1,
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
    }
    printf("-----------------------------------------------------------------------\n");
    printf("Total Contacts: %d\n",addressBook->contactCount);
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    if(addressBook->contactCount>=MAX_CONTACTS){
        printf("Contact Book is Full");
        return;
    }
    char name[50];
    char phone[20];
    char email[50];
    do{
        printf("Enter the Name: ");
        scanf(" %50[^\n]",name);
    }while(name_is_invalid(name));

    do{
        printf("Enter the Phone Number: ");
        scanf(" %20[^\n]",phone);
    }while(phone_is_invalid(addressBook,phone));
    
    do{
        printf("Enter Email: ");
        scanf(" %50[^\n]",email);
    }while(email_is_invalid(addressBook,email));

    strcpy(addressBook->contacts[addressBook->contactCount].name,name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email,email);
    addressBook->contactCount += 1;
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
   
}
