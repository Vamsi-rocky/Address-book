#ifndef CONTACT_H
#define CONTACT_H
// Include guard to prevent multiple inclusions of this header file

#define MAX_CONTACTS 100
// Maximum number of contacts allowed in the address book

// Structure to store individual contact details
typedef struct
{
    char name[50];   // Name of the contact (max 49 chars + null terminator)
    char phone[20];  // Phone number of the contact (max 19 chars + null terminator)
    char email[50];  // Email of the contact (max 49 chars + null terminator)
} Contact;

// Structure to store the entire address book
typedef struct
{
    int contactCount;              // Number of contacts currently stored
    Contact contacts[MAX_CONTACTS];// Array of Contact structures
} AddressBook;

// Main functions for managing contacts

void initialize(AddressBook *addressBook);
// Initialize the address book (set contactCount to 0)

void createContact(AddressBook *addressBook);
// Add a new contact to the address book

void searchContact(AddressBook *addressBook);
// Search for a contact by name, phone, or email

void editContact(AddressBook *addressBook);
// Edit an existing contact's details

void deleteContact(AddressBook *addressBook);
// Delete a contact from the address book

void listContacts(AddressBook *addressBook);
// Display all contacts in the address book

void saveContactsToFile(AddressBook *addressBook);
// Save all contacts to a file for persistence

// Validation functions to ensure correct input formats

int validate_name(const char *name);
// Check if the name is valid (only letters and spaces, minimum length)

int validate_phone(const char *phone);
// Check if the phone number is valid (10 digits, starts with 6-9)

int validate_email(const char *email);
// Check if the email is valid (contains '@' and a proper domain)

#endif // CONTACT_H
// End of include guard
