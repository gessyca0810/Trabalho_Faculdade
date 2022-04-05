/*
 *  primes module
 *  Primary module providing control flow for the primes program
 * 
 *  University of Washington, Tacoma
 *  TCSS 422 - Operating Systems
 *  Spring 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>
#include "counter.h"
#include "primes.h"
#define OUTPUT 1

counter_t primessearch;
counter_t primescnt;
int genprimes = 1000;

bool findPrime(int threadid)
{
  int n = inc_counter(&primessearch);
  int halfOfn = n / 2;
  for (int i=2; i<=halfOfn; i++)
    if (n % i == 0)
    {
      return false;
    }

#if OUTPUT

      switch (threadid)
      {
        case 1:
          printf("\033[0;31m%d,",n);
          break;
        case 2:
          printf("\033[0;32m%d,",n);
          break;
        case 3:
          printf("\033[0;33m%d,",n);
          break;
        case 4:
          printf("\033[0;34m%d,",n);
          break;
        case 5:
          printf("\033[0;35m%d,",n);
          break;
        case 6:
          printf("\033[0;36m%d,",n);
          break;
        case 7:
          printf("\033[1;32m%d,",n);
          break;
        case 8:
          printf("\033[1;34m%d,",n);
      }

#endif
  inc_counter(&primescnt);
  return true;
}
