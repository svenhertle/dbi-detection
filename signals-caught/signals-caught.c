#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    int verbose = argc == 2 && !strcmp(argv[1], "-v");

    FILE *fp;

    // get caught signals from /proc/self/status
    char mask[64];
    if((fp = fopen("/proc/self/status", "r")) != NULL)
    {
        char *line = NULL;
        size_t len = 0;
        while(getline(&line, &len, fp) != -1)
        {
            if(strstr(line, "SigCgt:"))
            {
                strcpy(mask, &line[8]);  // get mask
                mask[strlen(mask)-1] = 0;  // remove newline

                if(verbose)
                    printf("Caught signals: %s\n", mask);
            }
        }

        free(line);
        fclose(fp);
    }
    else
    {
        perror("Couldn't open the file /proc/self/stat");
        return 1;
    }

    // evaluate
    if(!strcmp(mask, "0000000000000000"))
        printf("OS\n");
    else if(!strcmp(mask, "fffffffff7b8feff"))
        printf("DBI (valgrind)\n");
    else if(!strcmp(mask, "fffffffff780feff"))
        printf("DBI (PIN)\n");
    else if(!strcmp(mask, "ffffffffffc1feff"))
        printf("DBI (DynamoRIO)\n");
    else
        printf("DBI\n");

    return 0;
}
