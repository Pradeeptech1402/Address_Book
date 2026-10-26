/*----DOCUMENTATION----
Name: Pradeep R.
Date: 26/10/2026.
Project: AdddresBook.
Discription: A modular, console-based contact management system developed in C. 
It features full CRUD operations—enabling users to create, 
search (by name, phone, or email),edit, delete, and list contacts. 
The project enforces comprehensive input validation and duplicate prevention,
 stores data persistently across sessions via file I/O, and 
presents a clean, minimalist terminal user interface.
*/

#include <stdio.h>
#include "contact.h"

int main() 
{
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do 
    {
        printf("\n  =====================================\n");
        printf("              ADDRESS BOOK             \n");
        printf("  =====================================\n");
        printf("    1. Create contact\n");
        printf("    2. Search contact\n");
        printf("    3. Edit contact\n");
        printf("    4. Delete contact\n");
        printf("    5. List all contacts\n");
        printf("    6. Save and Exit\n");       
        printf("  -------------------------------------\n");
        printf("  Select an option > ");
        
        if (scanf("%d", &choice) != 1) {
            printf("\n  [!] Invalid input. Please enter a valid number.\n");
            while (getchar() != '\n');
            continue;
        }
        
        switch (choice) 
        {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:          
                listContacts(&addressBook);
                break;
            case 6:
                printf("\n  [-] Saving contacts and exiting...\n\n");
                saveContactsToFile(&addressBook);
                break;
            default:
                printf("\n  [!] Invalid choice. Please select 1 through 6.\n");
        }
    } while (choice != 6);
    
    return 0;
}