#include <stdio.h>
#include "tests/threads/tests.h"
#include "threads/malloc.h"
#include "threads/synch.h"
#include "threads/thread.h"
#include "devices/timer.h"


//PART 2. ??? nici asta nu cred ca merge bine 1. Create a new function which displays thread information for all the threads. Call this function every time a thread is created in my_test_create_threads.
//nu imi dau seama cum ar trebui folosit foreach-ul ala sau ce face sau in ce combinatie
void myFunction1(void *param){

  struct thread *threadPointer=thread_current();
  
  //printf("Thread %s tid = %d is %s and it was created by tid = %d\n",threadPointer->name,threadPointer->tid,get_thread_status_as_string(threadPointer->status),threadPointer->parent_tid);
  

}

void my_test_create_threads (void) 
{
  char thread_name[16]={0};
  for(int i=0; i<5 ;i++){

    snprintf(thread_name, 16, "my_thread_%d", i);
    thread_create(thread_name,PRI_DEFAULT, myFunction1, NULL);
    
	}

  thread_exit();

}
