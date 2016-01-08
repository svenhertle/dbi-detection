#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
    int verbose = argc == 2 && !strcmp(argv[1], "-v");

    // source: https://www.gnu.org/savannah-checkouts/gnu/libc/manual/html_node/Simple-Directory-Lister.html
    DIR *dp;
    struct dirent *ep;

    dp = opendir ("/proc/self/fd");
    if(dp != NULL)
    {
        int count = 0;
        while(ep = readdir(dp))
        {
            if(strlen(ep->d_name) > 0 && ep->d_name[0] != '.')
            {
                if(verbose)
                    printf("%s\n", ep->d_name);
                count++;
            }
        }

        closedir(dp);

        if(count != 4)
            printf("DBI\n");
        else
            printf("OS\n");
    }
    else
    {
        perror("Couldn't open the directory /proc/self/fd");
        return 1;
    }

    return 0;
}
