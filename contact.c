#include <stdio.h>      // For printf, scanf
#include <stdlib.h>     // For general utilities (malloc, free, exit)
#include <string.h>     // For string functions like strlen, strcmp
#include "contact.h"    // Custom header for Contact struct
#include "file.h"       // Custom header for file operations
#include <ctype.h>      // For isalpha, isdigit functions

// Validate a name (only letters and spaces, at least 3 characters)
int validateName(const char *name)
{
    if (strlen(name) < 3) return 0;           // Name too short
    for (int i = 0; name[i]; i++)            // Loop through each character
        if (!isalpha(name[i]) && name[i] != ' ') // Check letters & spaces
            return 0;                         // Invalid character
    return 1;                                 // Name is valid
}

// Validate a phone number (10 digits, starts with 6/7/8/9)
int validatePhone(const char *phone)
{
    if (strlen(phone) != 10) return 0;       // Must be 10 digits
    if (phone[0] < '6' || phone[0] > '9') return 0; // Check first digit
    for (int i = 0; phone[i]; i++)           // Loop through each digit
        if (!isdigit(phone[i]))              // Must be a number
            return 0;                         // Invalid character
    return 1;                                 // Phone is valid
}

// Validate an email 

// Function to validate Gmail only
int validateEmail(const char *email)
{
    const char *at = strchr(email, '@');     // Find '@' in email
    const char *dot = strrchr(email, '.');  // Find last '.' in email
    if (!at || !dot) return 0;               // Both must exist
    if (at > dot) return 0;                  // '@' must come before last '.'
    if (strchr(email, ' ')) return 0;        // No spaces allowed
    if (strlen(email) < 6) return 0;         // Minimum length check
    // Check for allowed domains
    if (strcmp(dot, ".com") != 0 &&
        strcmp(dot, ".org") != 0 &&
        strcmp(dot, ".net") != 0 &&
        strcmp(dot, ".in") != 0)
        return 0;  // Invalid domain
    return 1;   
 }                         // Email is valid
// Initialize address book
void initialize(AddressBook *addressBook)
{
    
    addressBook->contactCount = 0;           // Start with 0 contacts
}

// List all contacts
void listContacts(AddressBook *addressBook) 
{
    if (addressBook->contactCount == 0)      // No contacts check
    {
        printf("\nNo contacts found!\n");
        return;
    }
    printf("\n--- Contact List ---\n");
    for (int i = 0; i < addressBook->contactCount; i++) // Loop all contacts
    {
        printf("Contact %d:\n", i + 1);
        printf("  Name : %s\n", addressBook->contacts[i].name);
        printf("  Phone: %s\n", addressBook->contacts[i].phone);
        printf("  Email: %s\n", addressBook->contacts[i].email);
        printf("-------------------------\n");
    }
    printf("Total contacts: %d\n", addressBook->contactCount);
}

// Add a new contact
void createContact(AddressBook *addressBook)
{
    if (addressBook->contactCount >= MAX_CONTACTS) // Full check
    {
        printf("Address book is full!\n");
        return;
    }

    Contact newContact; // Temporary contact variable

    // Input Name
    do
    {
        printf("Enter name (min 3 letters, only alphabets & spaces): ");
        scanf(" %[^\n]", newContact.name);        // Read string with spaces
        if (!validateName(newContact.name))
            printf("Invalid name. Try again.\n");
    } while (!validateName(newContact.name));

    // Input Phone
    do
    {
        printf("Enter phone (10 digits, start with 6/7/8/9): ");
        scanf("%s", newContact.phone);
        if (!validatePhone(newContact.phone))
            printf("Invalid phone. Try again.\n");
    } while (!validatePhone(newContact.phone));

    // Input Email
    do
    {
        printf("Enter email (must be valid format, e.g. abc@gmail.com): ");
        scanf("%s", newContact.email);
        if (!validateEmail(newContact.email))
            printf("Invalid email format. Try again.\n");
    } while (!validateEmail(newContact.email));

    // Check for duplicates
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, newContact.phone) == 0)
        {
            printf("Error: Phone number already exists!\n");
            return;
        }
        if (strcmp(addressBook->contacts[i].email, newContact.email) == 0)
        {
            printf("Error: Email already exists!\n");
            return;
        }
    }

    // Add contact to list
    addressBook->contacts[addressBook->contactCount++] = newContact;
    printf("Contact added successfully!\n");
}

// Search for a contact
void searchContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0) // Empty check
    {
        printf("\nNo contacts available to search!\n");
        return;
    }

    int choice;
    char query[50];

    printf("\nSearch by:\n1. Name\n2. Phone\n3. Email\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1: // Name search
        printf("Enter name to search: ");
        scanf(" %[^\n]", query);
        for (int i = 0; i < addressBook->contactCount; i++)
            if (strcasecmp(addressBook->contacts[i].name, query) == 0)
            {
                printf("\nContact Found:\n");
                printf("  Name : %s\n", addressBook->contacts[i].name);
                printf("  Phone: %s\n", addressBook->contacts[i].phone);
                printf("  Email: %s\n", addressBook->contacts[i].email);
                return;
            }
        printf("No contact found with that name.\n");
        break;

    case 2: // Phone search
        printf("Enter phone to search: ");
        scanf("%s", query);
        for (int i = 0; i < addressBook->contactCount; i++)
            if (strcmp(addressBook->contacts[i].phone, query) == 0)
            {
                printf("\nContact Found:\n");
                printf("  Name : %s\n", addressBook->contacts[i].name);
                printf("  Phone: %s\n", addressBook->contacts[i].phone);
                printf("  Email: %s\n", addressBook->contacts[i].email);
                return;
            }
        printf("No contact found with that phone number.\n");
        break;

    case 3: // Email search
        printf("Enter email to search: ");
        scanf("%s", query);
        for (int i = 0; i < addressBook->contactCount; i++)
            if (strcmp(addressBook->contacts[i].email, query) == 0)
            {
                printf("\nContact Found:\n");
                printf("  Name : %s\n", addressBook->contacts[i].name);
                printf("  Phone: %s\n", addressBook->contacts[i].phone);
                printf("  Email: %s\n", addressBook->contacts[i].email);
                return;
            }
        printf("No contact found with that email.\n");
        break;

    default:
        printf("Invalid choice.\n");
    }
}

// Edit an existing contact
void editContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0) // Empty check
    {
        printf("\nNo contacts available to edit!\n");
        return;
    }

    char search[50];
    printf("Enter phone number of the contact you want to edit: ");
    scanf("%s", search);

    for (int i = 0; i < addressBook->contactCount; i++)
        if (strcmp(addressBook->contacts[i].phone, search) == 0)
        {
            int choice;
            printf("\nContact Found:\n");
            printf("  Name : %s\n", addressBook->contacts[i].name);
            printf("  Phone: %s\n", addressBook->contacts[i].phone);
            printf("  Email: %s\n", addressBook->contacts[i].email);

            printf("\nWhat do you want to edit?\n1. Name\n2. Phone\n3. Email\nEnter your choice: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1: // Edit name
                do
                {
                    printf("Enter new name: ");
                    scanf(" %[^\n]", addressBook->contacts[i].name);
                    if (!validateName(addressBook->contacts[i].name))
                        printf("Invalid name. Try again.\n");
                } while (!validateName(addressBook->contacts[i].name));
                break;

            case 2: // Edit phone
                do
                {
                    printf("Enter new phone: ");
                    scanf("%s", addressBook->contacts[i].phone);
                    if (!validatePhone(addressBook->contacts[i].phone))
                        printf("Invalid phone. Try again.\n");
                } while (!validatePhone(addressBook->contacts[i].phone));
                break;

            case 3: // Edit email
                do
                {
                    printf("Enter new email: ");
                    scanf("%s", addressBook->contacts[i].email);
                    if (!validateEmail(addressBook->contacts[i].email))
                        printf("Invalid email. Try again.\n");
                } while (!validateEmail(addressBook->contacts[i].email));
                break;

            default:
                printf("Invalid choice.\n");
                return;
            }

            printf("Contact updated successfully!\n");
            return;
        }

    printf("No contact found with that phone number.\n");
}

// Delete a contact
void deleteContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0) // Empty check
    {
        printf("\nNo contacts available to delete!\n");
        return;
    }

    char phone[20];
    printf("Enter phone number of the contact to delete: ");
    scanf("%s", phone);

    for (int i = 0; i < addressBook->contactCount; i++)
        if (strcmp(addressBook->contacts[i].phone, phone) == 0)
        {
            printf("\nContact Found:\n");
            printf("  Name : %s\n", addressBook->contacts[i].name);
            printf("  Phone: %s\n", addressBook->contacts[i].phone);
            printf("  Email: %s\n", addressBook->contacts[i].email);

            char confirm;
            printf("\nAre you sure you want to delete this contact? (y/n): ");
            scanf(" %c", &confirm);

            if (confirm == 'y' || confirm == 'Y')
            {
                for (int j = i; j < addressBook->contactCount - 1; j++)
                    addressBook->contacts[j] = addressBook->contacts[j + 1]; // Shift left
                addressBook->contactCount--; // Decrease count
                printf("Contact deleted successfully!\n");
            }
            else
            {
                printf("Deletion cancelled.\n"); // Cancelled
            }
            return;
        }

    printf("No contact found with that phone number.\n"); // Not found
}
