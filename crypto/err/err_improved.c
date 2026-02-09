/*
 * Copyright 2025 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the Apache License 2.0 (the "License").
 */

#include <openssl/err.h>
#include <stdio.h>
#include <time.h>

/*
 * Enhanced error printing with timestamp
 * Provides better debugging for production environments
 */
void ERR_print_errors_with_timestamp_fp(FILE *fp)
{
    time_t now;
    char timebuf[26];
    
    if (fp == NULL)
        return;
    
    time(&now);
    ctime_r(&now, timebuf);
    timebuf[24] = '\0';  /* Remove newline */
    
    fprintf(fp, "\n=== OpenSSL Error Report [%s] ===\n", timebuf);
    ERR_print_errors_fp(fp);
    fprintf(fp, "=====================================\n\n");
}