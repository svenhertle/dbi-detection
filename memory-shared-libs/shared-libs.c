#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <limits.h>

int main(int argc, char **argv)
{
    int verbose = argc == 2 && !strcmp(argv[1], "-v");

    FILE *fp = NULL;
    int found = 0;

    // open some file
    if((fp = fopen("/proc/self/maps", "r")) != NULL)
    {
        char *line = NULL;
        size_t len = 0;

        char perm[5], dev[6], mapname[PATH_MAX];
        unsigned long begin, end, size, inode, foo;

        while(getline(&line, &len, fp) != -1)
        {
            strcpy(mapname, "");

            // parsing from https://github.com/cbbrowne/pmap/blob/master/pmap.c
            sscanf(line, "%lx-%lx %4s %lx %5s %ld %[^\n]s", &begin, &end, perm, &foo, dev, &inode, mapname);

            if(strcmp(mapname, "") && mapname[0] != '[')
            {
                char *lib = basename(mapname);

                if(verbose)
                    printf("%s\n", lib);

                if(!found)
                {
                    if(!strcmp(lib, "pinbin"))
                    {
                        printf("DBI (PIN)\n");
                        found = 1;
                    }
                    else if(strstr(lib, "libdynamorio"))
                    {
                        printf("DBI (DynamoRIO)\n");
                        found = 1;
                    }
                    else if(strstr(lib, "vgpreload_core"))
                    {
                        printf("DBI (valgrind)\n");
                        found = 1;
                    }
                }
            }
        }

        free(line);
        fclose(fp);
    }
    else
    {
        perror("Couldn't open the file /proc/self/maps");
        return 1;
    }

    if(!found)
        printf("OS\n");

    return 0;
}
