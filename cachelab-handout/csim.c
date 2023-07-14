#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>	
#include <getopt.h>

void printHelpInfo(char* programName){
}

int main(int argc, char *argv[])
{
    // Parse arguments
    int opt;
    int isVerbose = 0;
    int setIndex, associativity, blockSize;
    char * traceFilePath;
    while((opt = getopt(argc, argv, "hvs:E:b:t:")) != -1){
        switch (opt)
        {
        case 'v':
            isVerbose = 1;
        case 's':
            setIndex = atoi(optarg);
            break;
        case 'h':
            fprintf(stdout, " -h: Optional help flag that prints usage info\n -v: Optional verbose flag that displays trace info\n -s <s>: Number of set index bits (S = 2s is the number of sets)\n -E <E>: Associativity (number of lines per set)\n -b <b>: Number of block bits (B = 2b is the block size)\n -t <tracefile>: Name of the valgrind trace to replay");
            break;
        default:
            fprintf(stderr, "Usage: %s -h -v -s [s] -E [E] -b [b] -t [tracefile]", argv[0]);
            exit(EXIT_FAILURE);
        }
    }


    printSummary(0, 0, 0);
    return 0;
}
