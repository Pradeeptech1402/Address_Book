#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include<ctype.h>
int name_is_invalid(const char *name){
    if(strlen(name)==0) return 1;
    for(int i=0;i<name[i]!='\0';i++){
        if(!isalpha(name) && name[i] != ' '){
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
    printf("Enter the Name: ");
    scanf(" %50[^\n]",name);
    printf("Enter the Phone Number: ");
    scanf(" %20[^\n]",phone);
    printf("Enter Email: ");
    scanf(" %50[^\n]",email);

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
