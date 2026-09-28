#ifndef CONTACT_H
#define CONTACT_H

/* ---------- MACROS ---------- */
#define MAX_CONTACTS 100

/* ---------- STRUCTURES ---------- */

/* Structure to store individual contact details */
typedef struct
{
    char name[50];
    char phone[15];
    char email[50];
} Contact;

/* Structure to store address book */
typedef struct
{
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

/* ---------- FUNCTION PROTOTYPES ---------- */

/* Initialization */
void initialize(AddressBook *addressBook);

/* Contact operations */
void createContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);

/* Save and Exit */
void saveAndExit(AddressBook *addressBook);

#endif
