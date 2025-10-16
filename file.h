#ifndef FILE_H
#define FILE_H
// Include guard to prevent multiple inclusions of this header file

#include "contact.h"
// Include the contact header to use AddressBook and Contact structures

// Function to save all contacts to a file
// Typically writes the AddressBook contents into a file like "contacts.txt" or "contacts.csv"
void saveContactsToFile(AddressBook *addressBook);

// Function to load all contacts from a file
// Reads contacts from a file into the AddressBook structure
void loadContactsFromFile(AddressBook *addressBook);

#endif
// End of include guard
