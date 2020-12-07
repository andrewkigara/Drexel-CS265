/* inventory.c 
* The program reads the contents of the inventory database file called inv.dat
* It then requests the user for a command to update the quantity of the items in the inventory
*
*
* Andrew Kigara
*
* December 2020
*
* Linux version 
*
* EDITOR: Tabstops=4, Columns=120
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct itemNode itemNode;
struct itemNode
{
    char id[16];
    unsigned short qty;
    char desc[31];
    itemNode *next;
};
itemNode itemList[100];

int main()
{
    char dataFilename[] = "inv.dat";
    FILE *dataFile = fopen(dataFilename, "r+");
    char line[1000];
    int lineSection = 0, lineNum = 0, inventNums;

    /* ----- PARSING THROUGH THE FILE ----- */
    while (fgets(line, sizeof line, dataFile) != NULL)
    {
        char *token = strtok(line, ":");
        while (token != NULL)
        {
            if (lineSection == 0)
            {
                strcpy(itemList[lineNum].id, token);
            }
            else if (lineSection == 1)
            {
                itemList[lineNum].qty = atoi(token);
            }
            else if (lineSection == 2)
            {
                strcpy(itemList[lineNum].desc, token);
            }
            token = strtok(NULL, ":");
            ++lineSection;
            if (lineSection == 3)
            {
                lineSection = 0;
            }
        } // line sections
        ++lineNum;
    } // while loop for lines
    /* ----- FILE PARSED ----- */

    /* ----- STDIN Commands and instructions ----- */
    printf("%% ");
    char *stdEntry = NULL; // stdin entry
    size_t len = 0;        //
    ssize_t cmdLine = 0;   //

    char *lineSect; // line section
    int tester = 0;

    char space[] = " "; // strtok separators
    char colon[] = ":";

    char cmd[100];         // command section
    char cmdInstruct[100]; //instruction section (id : qty)

    cmdLine = getline(&stdEntry, &len, stdin);

    // check format
    for (int x = 0; x < cmdLine; x++)
    {
        if (stdEntry[x] == ' ')
        {
            tester++;
        }
    }
    // to catch one word commands line QUIT and PRINT
    if (tester == 1)
    {
        lineSect = strtok(stdEntry, space);
        strcpy(cmd, lineSect);
        lineSect = strtok(NULL, space);
        strcpy(cmdInstruct, lineSect);
    }
    else if (tester < 1)
    {
        char *jay = "j";
        stdEntry[strcspn(stdEntry, "\n")] = ' ';
        strcat(stdEntry, jay);
        lineSect = strtok(stdEntry, space);
        strcpy(cmd, lineSect);
    }

    char addX[100] = "add";
    char printX[100] = "print";
    char quitX[100] = "quit";
    char removeX[100] = "remove";

    /* ------ PROCESSING THE INPUTS ------ */
    while (strcmp(cmd, quitX) != 0)
    {
        char *adder;
        char *remover;

        char instID[100]; // ID section (id : qty)
        int instQty;      // QTY section

        int addCheck = 0; // checking syntax
        int remCheck = 0;

        int addItem = 0; // check if ID is correct
        int remItem = 0;

        int instLen = strlen(cmdInstruct);

        /* ----- ADD COMMAND ----- */
        if (strcmp(cmd, addX) == 0)
        {
            // check for ":", none = incorrect syntax
            for (int x = 0; x <= instLen; x++)
            {
                if (cmdInstruct[x] == ':')
                {
                    addCheck++;
                }
            }
            if (addCheck == 0)
            {
                printf("NAK Incorrect Syntax\n");
            }
            else if (addCheck == 1)
            {
                adder = strtok(cmdInstruct, colon);
                strcpy(instID, adder);
                adder = strtok(NULL, colon);
                instQty = atoi(adder);
                for (int x = 0; x <= lineNum; x++)
                {
                    if (strcmp(instID, itemList[x].id) == 0)
                    {
                        itemList[x].qty = itemList[x].qty + instQty;
                        addItem = 1;
                        printf("ACK\n");
                    }
                }
                if (addItem == 0)
                {
                    printf("NAK Unknown Item\n");
                }
            }
        }
        /* ----- REMOVE COMMAND ----- */
        else if (strcmp(cmd, removeX) == 0)
        {
            // check for ":", none = incorrect syntax
            for (int x = 0; x <= instLen; x++)
            {
                if (cmdInstruct[x] == ':')
                {
                    remCheck++;
                }
            }
            if (remCheck == 0)
            {
                printf("NAK Incorrect syntax\n");
            }
            else if (remCheck == 1)
            {
                remover = strtok(cmdInstruct, colon);
                strcpy(instID, remover);
                remover = strtok(NULL, colon);
                instQty = atoi(remover);
                //printf("Correct Syntax\n\n");
                for (int x = 0; x <= lineNum; x++)
                {
                    if (strcmp(instID, itemList[x].id) == 0)
                    {
                        if (itemList[x].qty >= instQty)
                        {
                            itemList[x].qty = itemList[x].qty - instQty;
                            remItem = 1;
                            printf("ACK\n");
                        }
                        else
                        {
                            remItem = 1;
                            printf("NAK Insufficient Quantity\n");
                        }
                    }
                }
            }
            if ((remCheck == 1) && (remItem == 0))
            {
                printf("NAK Unknown Item\n");
            }
        }

        /* ----- PRINT COMMAND ----- */
        else if (strcmp(cmd, printX) == 0)
        {
            printf("            DESC                    QTY            ID        \n");
            printf("______________________________    _______    ________________\n");
            for (int x = 0; x < lineNum; x++)
            {
                itemList[x].desc[strcspn(itemList[x].desc, "\n")] = ' ';
                printf("%31s %8d       %s\n", itemList[x].desc, itemList[x].qty, itemList[x].id);
            }
        }

        /* ----- QUIT COMMAND ----- */
        // else if (strcmp(cmd, quitX) == 0)
        // {
        //     break;
        // }

        /* ----- UNRECOGNISED COMMAND ----- */
        else
        {
            printf("NAK Unrecognised Command\n");
        }

        // Takes new inputs and contines the while loop
        printf("%% ");
        char *stdEntry = NULL; // stdin entry
        size_t len = 0;        //
        ssize_t cmdLine = 0;   //
        char *lineSect;        // line section
        int tester = 0;
        cmdLine = getline(&stdEntry, &len, stdin);
        strcpy(cmd, ""); // command section
        strcpy(cmd, ""); //instruction section (id : qty)

        // check format
        for (int x = 0; x < cmdLine; x++)
        {
            if (stdEntry[x] == ' ')
            {
                tester++;
            }
        }
        // to catch one word commands line QUIT and PRINT
        if (tester == 1)
        {
            lineSect = strtok(stdEntry, space);
            strcpy(cmd, lineSect);
            lineSect = strtok(NULL, space);
            strcpy(cmdInstruct, lineSect);
        }
        else if (tester < 1)
        {
            char *jay = "j";
            stdEntry[strcspn(stdEntry, "\n")] = ' ';
            strcat(stdEntry, jay);
            lineSect = strtok(stdEntry, space);
            strcpy(cmd, lineSect);
        }
        free(stdEntry);
    }

    // Making a temp file incase original file gets corrupted
    static char *temppath = "/tmp/temp777777";
    int tempmake = mkstemp(temppath);
    char colone[50];
    char coltwo[10];
    char colthree[50];
    char add[10];

    FILE *tempfile;
    tempfile = fopen(temppath, "w");
    char col[3] = ":";
    for (int x = 0; x < lineNum; x++)
    {
        strcpy(colone, itemList[x].id);
        sprintf(add, "%d", itemList[x].qty);
        strcpy(coltwo, add);
        strcpy(colthree, itemList[x].desc);
        fprintf(tempfile, "%s:%s:%s\n", colone, coltwo, colthree);
    }
    fclose(tempfile);
    return 0;
}
