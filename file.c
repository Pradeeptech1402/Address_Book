#include <stdio.h>
#include "file.h"
// Save data to the database (Address_data.txt)
void saveContactsToFile(AddressBook *addressBook) {
  FILE* fp = fopen("Address_data.txt","w");
  if(fp==NULL){
    printf("Unable to Open Data File.\n");
    return;
  }
  fprintf(fp,"#%d#\n",addressBook->contactCount);
  for(int i=0;i<addressBook->contactCount;i++){
    fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
  }
  fclose(fp);
}
// while start of program. load the data from Address_data.txt to memory
void loadContactsFromFile(AddressBook *addressBook) {
    FILE* fp = fopen("Address_data.txt","r");
    if(fp==NULL){
        printf("Unable to open Data File.\n");
        return;
    }
    fscanf(fp,"#%d#\n",&addressBook->contactCount);
    for(int i=0; i<addressBook->contactCount;i++){
        fscanf(fp,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fp);
}
