#include <stdio.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

#include <stdlib.h>
#include <signal.h>


#include "lpthread.h"
#ifndef LPTHREAD

#endif



void *print_message_function( void *ptr );

int main()
{
     lpthread_t thread1, thread2;
     char *message1 = "Thread 1";
     char *message2 = "Thread 2";
     int  iret1, iret2;

    /* Create independent threads each of which will execute function */

     
     iret2 = lpthread_create( &thread2, NULL, print_message_function, (void*) message2);
     iret1 = lpthread_create( &thread1, NULL, print_message_function, (void*) message1);

     /* Wait till threads are complete before main continues. Unless we  */
     /* wait we run the risk of executing an exit which will terminate   */
     /* the process and all threads before the threads have completed.   */


    
     lpthread_join( thread1, NULL);
     lpthread_join( thread2, NULL); 

     printf("Thread 1 returns: %d\n",iret1);
     printf("Thread 2 returns: %d\n",iret2);
     exit(0);
}

void *print_message_function( void *ptr )
{
     char *message;
     message = (char *) ptr;
     printf("%s \n", message);
     sleep(5);
}