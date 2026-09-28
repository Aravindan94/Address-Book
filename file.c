#include <stdio.h>
#include "file.h"

/* -------------------------------------------------- */
/* Save all contacts into CSV file                    */
/* -------------------------------------------------- */
void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contacts.csv", "w");

    /* If file cannot be opened */
    if (fp == NULL)
    {
        printf("Error: Unable to open contacts.csv for writing.\n");
        return;
    }

    /* Write each contact in CSV format */
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fp);
}

/* -------------------------------------------------- */
/* Load contacts from CSV file                        */
/* -------------------------------------------------- */
void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contacts.csv", "r");

    /* If file does not exist, no contacts to load */
    if (fp == NULL)
    {
        return;
    }

    /* Read each line from CSV and store in structure */
    while (fscanf(fp, "%[^,],%[^,],%[^\n]\n",
                  addressBook->contacts[addressBook->contactCount].name,
                  addressBook->contacts[addressBook->contactCount].phone,
                  addressBook->contacts[addressBook->contactCount].email) == 3)
    {
        addressBook->contactCount++;
    }

    fclose(fp);
}
