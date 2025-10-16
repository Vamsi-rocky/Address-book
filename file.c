#include <stdio.h>       // For file I/O functions like fopen, fprintf, fscanf, fclose
#include <string.h>      // For string functions
#include "file.h"        // Header file where AddressBook struct and prototypes are declared

// Function to save all contacts into "contacts.csv"
void saveContactsToFile(AddressBook *addressBook)
{
    // Open file in write mode ("w" overwrites existing data)
    FILE *fp = fopen("contacts.csv", "w");
    if (fp == NULL)   // If file could not be opened
    {
        printf("Error: Unable to open file for saving!\n");
        return;  // Exit function
    }

    // Write each contact into the file in CSV format (name,phone,email)
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s,%s,%s\n",
                addressBook->contacts[i].name,   // Contact Name
                addressBook->contacts[i].phone,  // Contact Phone
                addressBook->contacts[i].email); // Contact Email
    }

    fclose(fp);  // Close the file after writing
    printf("Contacts saved successfully into contacts.csv!\n");
}

// Function to load contacts from "contacts.csv"
void loadContactsFromFile(AddressBook *addressBook)
{
    // Open file in read mode ("r")
    FILE *fp = fopen("contacts.csv", "r");
    if (fp == NULL)   // If file not found (first run)
    {
        addressBook->contactCount = 0;   // Start with empty list
        return;
    }

    addressBook->contactCount = 0;  // Reset count before loading

    // Read contacts line by line using fscanf
    while (fscanf(fp, "%49[^,],%19[^,],%49[^\n]\n",
                  addressBook->contacts[addressBook->contactCount].name,   // Read name until ','
                  addressBook->contacts[addressBook->contactCount].phone,  // Read phone until ','
                  addressBook->contacts[addressBook->contactCount].email)  // Read email until '\n'
           == 3)  // fscanf returns 3 if all three fields are read successfully
    {
        addressBook->contactCount++;   // Increase contact count

        // Stop if maximum contacts reached
        if (addressBook->contactCount >= MAX_CONTACTS)
            break;
    }

    fclose(fp);  // Close file after reading
    printf("%d contacts loaded from contacts.csv\n", addressBook->contactCount);
}
