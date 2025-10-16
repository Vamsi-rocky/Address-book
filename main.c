#include <stdio.h>        // Standard I/O for printf, scanf
#include "contact.h"      // Header for contact-related structures and functions
#include "file.h"         // Header for file save/load functions

int main() {
    AddressBook addressBook;  // Create an AddressBook variable
    initialize(&addressBook); // Initialize the address book (contactCount = 0)

    // Load existing contacts from a file (if any)
    loadContactsFromFile(&addressBook);

    int choice;  // Variable to store user's menu choice
    do {
        // Display menu options
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Save contacts\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);  // Read user input

        // Execute action based on user's choice
        switch (choice) {
            case 1: createContact(&addressBook); break;      // Add new contact
            case 2: searchContact(&addressBook); break;      // Search for a contact
            case 3: editContact(&addressBook); break;        // Edit existing contact
            case 4: deleteContact(&addressBook); break;      // Delete a contact
            case 5: listContacts(&addressBook); break;       // List all contacts
            case 6: saveContactsToFile(&addressBook); break; // Save contacts to file
            case 7: printf("Exiting...\n"); break;          // Exit the program
            default: printf("Invalid choice! Please Try again.\n"); // Handle invalid input
        }
    } while (choice != 7); // Repeat until user chooses to exit

    return 0; // Program ends
}
