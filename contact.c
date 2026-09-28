/*
Name-S.Aravindan
Batch-25036A
Date-24-01-2026
Description:
The Address Book Management System is a menu-driven C application 
designed to store, manage, and maintain personal 
contact information such as name, phone number, and email address.
The project focuses on data validation, file handling, and modular programming to 
ensure data integrity and persistence.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"

//INTERNAL VALIDATION FUNCTIONS
static int validateName(const char *name)
{
        //check minimum length
    if (strlen(name) < 3)
    {
        printf("Error: Name must contain at least 3 characters.\n");
        return 0;
    }

    //check each character
    for (int i = 0; name[i]; i++)
    {
        //If not an alphabet, invalid name
        if (!isalpha(name[i]))
        {
            printf("Error: Name must contain only alphabets.\n");
            return 0;
        }
    }
    return 1;
}

static int validatePhone(const char *phone)
{
    //Check first digit 
    if (phone[0] < '6' || phone[0] > '9')
    {
        printf("Error: Phone number must start with digits between 6 and 9.\n");
        return 0;
    }
    //Check remaining digits
    for (int i = 0; phone[i]; i++)
    {
        //If any character is not a digit
        if (!isdigit(phone[i]))
        {
            printf("Error: Phone number must contain only digits.\n");
            return 0;
        }
    }
    // Phone number is valid
    return 1;
}
//Validate email ID based on given specifications
static int validateEmail(const char *email)
{
    int atPos = -1;//Position of '@' 
    int dotPos = -1;//Position of '.'
    int atCount = 0;//Count of '@' symbols

    //Traverse email character by character 
    for (int i = 0; email[i]; i++)
    {
        if (email[i] == '@')
        {
            atPos = i;
            atCount++;
        }
        else if (email[i] == '.')
        {
            dotPos = i;
        }
        //Only alphanumeric, @ and . allowed
        else if (!isalnum(email[i]))
        {
            printf("Error: Invalid symbol '%c'. Only '@' and '.' are allowed.\n", email[i]);
            return 0;
        }
    }
    //Double '@' not allowed 
    if (atCount != 1)
    {
        printf("Error: Email must contain exactly one '@'.\n");
        return 0;
    }
    //'.' must appear after '@'
    if (dotPos == -1 || dotPos < atPos)
    {
        printf("Error: '.' must appear after '@'.\n");
        return 0;
    }
    //Domain name must exist between '@' and '.'
    if (dotPos == atPos + 1)
    {
        printf("Error: Domain missing between '@' and '.'.\n");
        return 0;
    }
    // After '.' only alphabets allowed
    for (int i = dotPos + 1; email[i]; i++)
    {
        if (!isalpha(email[i]))
        {
            printf("Error: After '.', only alphabets are allowed.\n");
            return 0;
        }
    }
    //Email is valid
    return 1;
}

//INITIALIZATION 
//initialize addressbook
void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);
}

//LIST CONTACTS
//Display all contacts
void listContacts(AddressBook *addressBook)
{      
    //If no contacts exist
    if (addressBook->contactCount == 0)
    {
        printf("No contacts available.\n");
        return;
    }
    //printf each contact
    for (int i = 0; i < addressBook->contactCount; i++)
    {
       printf("%s,%s,%s\n",
       addressBook->contacts[i].name,
       addressBook->contacts[i].phone,
       addressBook->contacts[i].email);

    }
}

//CREATE CONTACT

void createContact(AddressBook *addressBook)
{
    Contact c;
    //Read and validate name
    printf("Enter Name: ");
    scanf(" %[^\n]", c.name);
    if (!validateName(c.name)) 
    return;
    //Read and validate phone number
    printf("Enter Phone: ");
    scanf(" %s", c.phone);
    if (!validatePhone(c.phone)) 
    return;

    printf("Enter Email: ");
    scanf(" %s", c.email);
    if (!validateEmail(c.email)) 
    return;

    //Store contact in address book
    addressBook->contacts[addressBook->contactCount++] = c;
    printf("Contact created successfully.\n");
}

//SEARCH CONTACT

void searchContact(AddressBook *addressBook)
{
    int choice, found = 0;
    char key[50];
    //Display and search options
    printf("\nSearch by:\n");
    printf("1. Name\n2. Email\n3. Phone\n4. Exit\n");
    scanf("%d", &choice);


    //Exit option
    if (choice == 4) return;

    //Read search key
    printf("Enter search value: ");
    scanf(" %s", key);
    
    //Search through all contacts
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if ((choice == 1 && strcmp(addressBook->contacts[i].name, key) == 0) ||
            (choice == 2 && strcmp(addressBook->contacts[i].email, key) == 0) ||
            (choice == 3 && strcmp(addressBook->contacts[i].phone, key) == 0))
        {
            printf("Found: %s | %s | %s\n",
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
            found = 1;
        }
    }
    //If no contact matched
    if (!found)
        printf("No matching contact found.\n");
}

//EDIT CONTACT

void editContact(AddressBook *addressBook)
{
    int choice;
    char key[50];

    printf("\nEdit by:\n");
    printf("1. Name\n2. Email\n3. Phone\n4. Exit\n");
    scanf("%d", &choice);
    
    //Exit option
    if (choice == 4) 
    return;

    //Read key to edit
    printf("Enter value to edit: ");
    scanf(" %s", key);


    //Search and edit
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if ((choice == 1 && strcmp(addressBook->contacts[i].name, key) == 0) ||
            (choice == 2 && strcmp(addressBook->contacts[i].email, key) == 0) ||
            (choice == 3 && strcmp(addressBook->contacts[i].phone, key) == 0))
        {
            //Re-enter and validate all fields
            printf("Enter new Name: ");
            scanf(" %[^\n]", addressBook->contacts[i].name);
            if (!validateName(addressBook->contacts[i].name)) return;

            printf("Enter new Phone: ");
            scanf(" %s", addressBook->contacts[i].phone);
            if (!validatePhone(addressBook->contacts[i].phone)) return;

            printf("Enter new Email: ");
            scanf(" %s", addressBook->contacts[i].email);
            if (!validateEmail(addressBook->contacts[i].email)) return;

            printf("Contact updated successfully.\n");
            return;
        }
    }

    printf("No matching contact found.\n");
}

//DELETE CONTACT

void deleteContact(AddressBook *addressBook)
{
    int choice;
    char key[50];


    //Display delete options
    printf("\nDelete by:\n");
    printf("1. Name\n2. Email\n3. Phone\n4. Exit\n");
    scanf("%d", &choice);

    //Exit option
    if (choice == 4) 
    return;

    //Read key to delete
    printf("Enter value to delete: ");
    scanf(" %s", key);

    //Search and delete contact
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if ((choice == 1 && strcmp(addressBook->contacts[i].name, key) == 0) ||
            (choice == 2 && strcmp(addressBook->contacts[i].email, key) == 0) ||
            (choice == 3 && strcmp(addressBook->contacts[i].phone, key) == 0))
        {   
            //Shift remaining contacts
            for (int j = i; j < addressBook->contactCount - 1; j++)
            {
                addressBook->contacts[j] = addressBook->contacts[j + 1];
            }
            addressBook->contactCount--;
            printf("Contact deleted successfully.\n");
            return;
        }
    }

    printf("No matching contact found.\n");
}


//SAVE & EXIT
void saveAndExit(AddressBook *addressBook)
{
    //Save all contacts into csv file
    saveContactsToFile(addressBook);
    //Exit the program
    exit(EXIT_SUCCESS);
}
