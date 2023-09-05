#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>	
#include <getopt.h>



/**
 * Only print out help message when it is not ever printed
 * Usage: isHelpMessagePrinted = printHelpMessage(argv[0], stderr, isHelpMessagePrinted);
*/
int printHelpMessage(char* argv0, FILE* stream, int isHelpMessagePrinted){
    if (!isHelpMessagePrinted) {
            fprintf(stream, 
            "Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file>\n"
            "Options:\n"
            "  -h         Print this help message.\n"
            "  -v         Optional verbose flag.\n"
            "  -s <num>   Number of set index bits.\n"
            "  -E <num>   Number of lines per set.\n"
            "  -b <num>   Number of block offset bits.\n"
            "  -t <file>  Trace file.\n"
            "\n"
            "Examples:\n"
            "  linux>  %s -s 4 -E 1 -b 4 -t traces/yi.trace\n"
            "  linux>  %s -v -s 8 -E 2 -b 4 -t traces/yi.trace\n", 
            argv0,
            argv0,
            argv0
            );
            return 1;
    }
    return 1;
}


void parseArguments(int argc, char* argv[], int *verbose, int *sets, int *associativity, int *blocks, char **traceFile){
    char c;
    int isHelpMessagePrinted = 0;
    while ((c = getopt(argc, argv, "hvs:E:b:t:")) != - 1){
        switch (c)
        {
        case 'h':
            isHelpMessagePrinted = printHelpMessage(argv[0], stdout, isHelpMessagePrinted);
            exit(EXIT_SUCCESS);
            break;
        case 'v':
            *verbose = 1;
            break;
        case 's':
             *sets = atoi(optarg);
             break;
        case 'E':
             *associativity = atoi(optarg);
             break;
        case 'b':
            *blocks = atoi(optarg);
            break;
        case 't':
            *traceFile = optarg;
            break;
        case '?':
            break;
        default:
            fprintf(stderr, "%s: %c is a wrong argument\n", argv[0], c);
            isHelpMessagePrinted = printHelpMessage(argv[0], stdout, isHelpMessagePrinted);
            exit(EXIT_FAILURE);
        }
    }
    // check for mandatory arguments
    if (*sets == 0 || *associativity == 0  || *blocks == 0 || *traceFile == NULL){
        fprintf(stderr, "%s: Missing required command line argument\n", argv[0]);
        isHelpMessagePrinted = printHelpMessage(argv[0], stderr, isHelpMessagePrinted);
        exit(EXIT_FAILURE);
    }
}

struct cacheLine {
    int valid; // 0 => not valid: no meaningful data is in the line; 1 => valid; 
    int tag; // tag => which line
};


void initCache(int numSets, int associativity, struct cacheLine cache[][associativity] ){
    for (int i = 0; i < numSets; i ++) {
        for (int j = 0; j < associativity; j ++){
            cache[i][j].valid = 0;
            cache[i][j].tag = j;
        }

    }
}

void scanTraceFile(FILE * traceFile, struct cacheLine** cache){

}


int main(int argc, char *argv[])
{
    int verbose = 0;
    int numSetIndexBits = 0;
    int associativity = 0;
    int numBlocksIndexBits = 0;
    char* traceFilePath=NULL;
    parseArguments(argc, argv, &verbose, &numSetIndexBits, &associativity, &numBlocksIndexBits, &traceFilePath);
    printf(
        "verborse: %d; sets: %d; associativity: %d; block: %d; traceFile: %s\n", 
        verbose,
        numSetIndexBits,
        associativity,
        numBlocksIndexBits,
        traceFilePath
        );
    

    int numSets = 1 << numSetIndexBits;
    struct cacheLine cache[numSets][associativity];
    initCache(numSets, associativity, cache);
        for (int i = 0; i < numSets; i ++) {
        for (int j = 0; j < associativity; j ++){
            printf("cache[%d][%d]: valid %d, tag %d\n", i, j, cache[i][j].valid, cache[i][j].tag);
        }

    }
    FILE *traceFile;
    if  (! (traceFile = fopen(traceFilePath, "r"))){
        fprintf(stderr, "%s: No such file or directory\n", traceFilePath);
        exit(EXIT_FAILURE);
    }

    return 0;
}
