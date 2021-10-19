/* Tests timer_sleep(-100).  Only requirement is that it not crash. 

#include <stdio.h>
#include "tests/threads/tests.h"
#include "threads/malloc.h"
#include "threads/synch.h"
#include "threads/thread.h"
#include "devices/timer.h"

void
test_alarm_negative (void) 
{
  timer_sleep (-100);
  pass ();
}
*/

//cum se creaza thereaduri
/*
#include <stdio.h>
#include "tests/threads/tests.h"
#include "threads/malloc.h"
#include "threads/synch.h"
#include "threads/thread.h"
#include "devices/timer.h"

void myFunction(void *param){

  struct thread *threadPointer=thread_current();
  printf("%s",threadPointer->name);

}

void
test_alarm_negative (void) 
{

  tid_t t=thread_create("Ana are mere",PRI_DEFAULT, myFunction, NULL);

}*/

#include <stdio.h>
#include "tests/threads/tests.h"
#include "threads/malloc.h"
#include "threads/synch.h"
#include "threads/thread.h"
#include "devices/timer.h"
#include <string.h>

void myFunction(void *param){

  struct thread *threadPointer=thread_current();
  printf("Thread %s_%d was created\n",threadPointer->name,threadPointer->tid);


}

void
test_alarm_negative (void) 
{
  //char s[12];
  for(int i=0; i<5 ;i++){

    //snprintf(s, 12, "my_thread_%d\n", i);
    thread_create("my_thread",PRI_DEFAULT, myFunction, NULL);

  }

}