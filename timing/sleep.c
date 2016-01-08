#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

unsigned int wallclocktime()
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return time.tv_sec*1000000 + time.tv_usec;
}

int main(int argc, char **argv)
{
    int verbose = argc == 2 && !strcmp(argv[1], "-v");

    int t1 = wallclocktime();
    sleep(1);
    int t2 = wallclocktime();

    int diff = t2-t1;

    if(verbose)
        printf("Diff: %d\n", diff);

    if(diff > 1000500)
        printf("DBI\n");
    else
        printf("OS\n");

    return 0;
}
