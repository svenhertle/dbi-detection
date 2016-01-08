#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define rdtsc(low,high) \
    __asm__ __volatile__ ("cpuid" : : "a" (0) : "bx", "cx", "dx"); \
    __asm__ __volatile__("rdtsc" : "=a" (low), "=d" (high))

typedef unsigned long long u64;

static inline u64 rdtsc_read(void)
{
    unsigned long high, low;
    rdtsc(low,high);
    return ((u64)high << 32) | low;
}

int main(int argc, char **argv)
{
    int verbose = argc == 2 && !strcmp(argv[1], "-v");

    char *buffer = malloc(100);

    u64 t1 = rdtsc_read();
    memset(buffer, 0, 100);
    u64 t2 = rdtsc_read();

    u64 diff = t2-t1;
    if(verbose)
        printf("Diff: %d\n", diff);

    if(diff > 10000)
        printf("DBI\n");
    else
        printf("OS\n");

    free(buffer);
}
