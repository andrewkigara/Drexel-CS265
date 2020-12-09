// Finite State Machine assignment 2

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
bool foo(char msg[120]);
bool eep(char msg[120]);
bool op(char msg[120]);
bool ork(char msg[120]);
int main()
{
    char fname[30], lyne[120];

    FILE *filehandle;
    char *item;
    char rule[100], msg[120];
    printf("Enter the filename\n");
    scanf("%s", fname);
    filehandle = fopen(fname, "r");
    if (filehandle == NULL)
    {
        printf("Error Could not open\n");
        return 0;
    } else
    {
        while (fgets(lyne, 120, filehandle))
        {
            //printf("%s",lyne);
            item = strtok(lyne, ":");
            strcpy(rule, item);
            //printf("%s",rule);
            item = strtok(NULL, ":");
            strcpy(msg, item);
            if (strcmp(rule, "foo") == 0)
            {
                printf("\nMessage: %s", msg);
                if (foo(msg))
                {
                    printf("OK");
                }
                else
                {
                    printf("FAIL");
                }
            }
            if (strcmp(rule, "op") == 0)
            {
                printf("\nMessage: %s", msg);
                if (op(msg))
                {
                    printf("OK");
                }
                else
                {
                    printf("FAIL");
                }
            }
        }
    }
    return 0;
}



bool foo(char msg[120])
{
    int len;
    len = strlen(msg);
    int valid1 = 0, valid2 = 0;
    int i;
    // printf("%c last %c",msg[0],msg[(len-3)]);
    // printf("%d",len);
    // for(i=0;i<len;i++)
    // {
    // printf("%c",msg[i]);
    //}
    if (msg[0] == 'E' && msg[len - 3] == 'F') // please check the correct character position and take
    {
        valid1 = 1;
    }
    for (i = 1; i <= len - 4; i++)
    {
        if ((msg[i] == '0') || (msg[i] == '1') || (msg[i] == '2'))
        {
            valid2 = 1;
        }
        else
        {
            valid2 = 0;
        }
    }
    if ((valid1 == 1) && (valid2 == 1))
    {
        return true;
    }
    return false;
}



bool eep(char msg[120])
{
    bool v1 = false;
    if (msg[0] == 'P')
    {
        v1=true;
    }

    return false;
}




bool op(char msg[120])
{
    int l;
    bool v1 = false, v2 = false, v3 = true;
    int i;
    int c = 0;
    l = strlen(msg);
    // printf("%d",l);
    if (msg[0] == 'Q')
    {
        v1 = true;
    }
    for (int i = 1; i < l - 2; i++)
    {
        if ((msg[i] == '6') || (msg[i] == '7'))
        {
            v2 = true;
        }
        else
        {
            v2 = false;
        }
        if (msg[i] == '7')
        {
            c++;
        }
    }
    if (c % 2 == 1)
    {
        v3 = true;
    }
    if ((v1 = true) && (v2 == true) && (v3 == true))
    {
        return true;
    }

    return false;
}



bool ork(char msg[120])
{
    return false;
}