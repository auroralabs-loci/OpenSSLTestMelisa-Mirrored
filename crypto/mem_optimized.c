/*
 * Copyright 2025 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the Apache License 2.0 (the "License").
 */

#include <openssl/crypto.h>
#include <string.h>

/*
 * Efficient allocation - single operation
 */
void *CRYPTO_malloc_optimized(size_t num, const char *file, int line)
{
    void *ptr;
    
    if (num == 0)
        return NULL;
    
    /* Single efficient allocation */
    ptr = CRYPTO_malloc(num, file, line);
    if (ptr != NULL) {
        memset(ptr, 0, num);
    }
    
    return ptr;
}

/*
 * Secure free with guaranteed clearing
 */
void CRYPTO_free_secure(void *ptr, size_t num)
{
    if (ptr == NULL)
        return;
    
    /* Clear before freeing */
    OPENSSL_cleanse(ptr, num);
    CRYPTO_free(ptr, __FILE__, __LINE__);
}

/*
 * Fast memory clearing using optimized methods
 */
void CRYPTO_clear_fast(void *ptr, size_t num)
{
    if (ptr == NULL || num == 0)
        return;
    
    /* Use OpenSSL's optimized cleanse */
    OPENSSL_cleanse(ptr, num);
}