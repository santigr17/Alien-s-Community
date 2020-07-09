#include <stdio.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include "lpthread/lpthread.h"
#include <stdlib.h>
#include <signal.h>
#ifndef LPTHREAD

#endif

#define NTHREADS 10
void *thread_function(void *);
lpthread_mutex_t mutex1;
int  counter = 0;

main()
{
   lpthread_t thread_id[NTHREADS];
   int i, j;

   for(i=0; i < NTHREADS; i++)
   {
      lpthread_create( &thread_id[i], NULL, thread_function, NULL );
   }

   for(j=0; j < NTHREADS; j++)
   {
      lpthread_join( thread_id[j], NULL); 
   }
  
   /* Now that all threads are complete I can print the final result.     */
   /* Without the join I could be printing a value before all the threads */
   /* have been completed.                                                */

   printf("Final counter value: %d\n", counter);
}

void *thread_function(void *dummyPtr)
{
   printf("Thread number %d\n", lpthread_self());
   lpthread_mutex_lock( &mutex1 );
   counter++;
   lpthread_mutex_unlock( &mutex1 );
}