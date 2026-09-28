#include <stdio.h>
#include "contact.h"

int main()
{
    AddressBook addressBook;
    int choice;

    /* Initialize address book and load CSV data */
    initialize(&addressBook);

    while (1)
    {
        printf("\n========== ADDRESS BOOK ==========\n");
        printf("1. Create Contact\n");
        printf("2. Search Contact\n");
        printf("3. Edit Contact\n");
        printf("4. Delete Contact\n");
        printf("5. List Contacts\n");
        printf("6. Save & Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');  // clear buffer
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
                saveAndExit(&addressBook);
                break;

            default:
                printf("Invalid choice. Please select between 1 and 6.\n");
        }
    }

    return 0;
}
