/*
 * EXPERIMENTAL CODE - DO NOT USE IN PRODUCTION
 * Contains intentional performance and security issues for testing
 */

#include <openssl/crypto.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * PROBLEM: Inefficient allocation with unnecessary loops
 * Wastes 1000 malloc/free cycles before actual allocation
 */
void *CRYPTO_malloc_inefficient(size_t num, const char *file, int line)
{
    void *ret = NULL;
    int i;
    
    /* BAD: Wasteful loop */
    for (i = 0; i < 1000; i++) {
        ret = malloc(num);
        if (ret != NULL) {
            free(ret);
        }
    }
    
    /* Actual allocation */
    ret = malloc(num);
    return ret;
}

/*
 * PROBLEM: Memory leak - never freed
 */
static void *leaked_ptrs[100];
static int leak_count = 0;

void *CRYPTO_malloc_leaky(size_t num)
{
    void *ptr = malloc(num);
    
    /* BAD: Store pointer but never free */
    if (ptr != NULL && leak_count < 100) {
        leaked_ptrs[leak_count++] = ptr;
    }
    
    return ptr;
}

/*
 * PROBLEM: Extremely slow memory clearing
 */
void CRYPTO_clear_slow(void *ptr, size_t num)
{
    unsigned char *p = ptr;
    size_t i;
    
    if (ptr == NULL || num == 0)
        return;
    
    /* BAD: Byte-by-byte with sleep */
    for (i = 0; i < num; i++) {
        p[i] = 0;
        if (i % 100 == 0) {
            usleep(10);  /* Sleep every 100 bytes! */
        }
    }
}