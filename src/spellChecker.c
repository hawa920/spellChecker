// spellChecker version 1.0, with only one filter
// any tips on base selection ?
// one layer bloom filter implementation

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define getHashval(key, base, filterSize)   \
({                                          \
    int keylen = strlen(key), i;            \
    long long hv = 0, mod = filterSize - 1; \
    for(i = 0; i < keylen; i++)             \
    {                                       \
        hv = (hv * base + key[i]) & mod;    \
    }                                       \
    hv;                                     \
})


typedef long long lld;

int getWordCount(char *dictPath)
{
    int ret = 0;
    char buff[1024];
    FILE *fptr = fopen(dictPath, "r");
    assert(fptr != NULL);
    while(fscanf(fptr, "%s", buff) != EOF)
    {
        ret++;
    }
    fclose(fptr);
    return ret;
}

char *initFilter(char *dictPath, lld base, lld filterSize)
{
    // init
    assert( ((lld)((size_t) filterSize)) - filterSize == 0); // prevent overflow
    char *rptr = (char *) malloc(sizeof(char) * (filterSize + 1));
    assert(rptr != NULL);
    memset(rptr, 48, sizeof(char) * filterSize);
    rptr[filterSize] = '\0';
    // import dict
    int keylen, i;
    lld hashval, mod = filterSize - 1;
    char key[1 << 10];
    FILE *fptr = fopen(dictPath, "r");
    assert(fptr != NULL);
    while(fscanf(fptr, "%s", key) != EOF)
    {
        hashval = getHashval(key, base, filterSize);
        rptr[hashval] = '1';
    }
    fclose(fptr);
    return rptr;
}

int spellCheck(char *dictPath, char *filterPtr, lld base, lld filterSize)
{
    int keylen, i, err = 0;
    lld mod = filterSize - 1LL, hashval;
    char key[1024];
    FILE *fptr = fopen(dictPath, "r");
    assert(fptr != NULL);
    while(fscanf(fptr, "%s", key) != EOF)
    {
        hashval = getHashval(key, base, filterSize);
        if(filterPtr[hashval] == '0')
        {
            err++;
            printf(KRED"%s "KWHT, key);
        }
        else
        {
            printf("%s "KWHT, key);
        }
    }
    fclose(fptr);
    return err;
}

int main(int argc, char**argv)
{
    int wordcnt = getWordCount("../dictionary/words.txt");
    int shiftSize = (int) ceil(log2(wordcnt));
    lld filterSize = 1LL << (shiftSize + 1), base = 33;
    char *filterPtr = initFilter("../dictionary/words.txt", base, filterSize);
    int numErr = spellCheck("../articles/article.txt", filterPtr, base, filterSize);
    printf("\nNumber of errors detected: %d\n", numErr);
    return 0;
}