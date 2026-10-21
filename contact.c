#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

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
