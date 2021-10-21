#include <stdio.h>
#include "tests/threads/tests.h"
#include "threads/malloc.h"
#include "threads/synch.h"
#include "threads/thread.h"
#include "devices/timer.h"

struct semaphore logSem1,logSem2,logSem3,logSem4,logSem5;
char th_name[16];

void my_thread1(){

      printf("BEGIN 0.%d\n",thread_current()->tid);

      sema_up(&logSem1);
}

void my_thread2(){

   sema_init(&logSem1,0);

      snprintf(th_name, 16, "%s", "1");


      printf("BEGIN 1.%s\n",th_name);
      thread_create(th_name,PRI_DEFAULT, my_thread1, NULL);
      printf("END 1.%s\n",th_name);
      sema_down(&logSem1);

      sema_up(&logSem2);
  
}

void my_thread3(){

   sema_init(&logSem2,0);

   for(int i=1; i<=2; i++){

      snprintf(th_name, 16, "%d", i);

      printf("BEGIN 2.%s\n",th_name);
      thread_create(th_name,PRI_DEFAULT, my_thread2, NULL);
      printf("END 2.%s\n",th_name);

      sema_down(&logSem2);
 }

sema_up(&logSem3);
  
}

void my_thread4(){

   sema_init(&logSem3,0);

   for(int i=1; i<=3; i++){

      snprintf(th_name, 16, "%d", i);

      printf("BEGIN 3.%s\n",th_name);
      thread_create(th_name,PRI_DEFAULT, my_thread3, NULL);
      printf("END 3.%s\n",th_name);

      sema_down(&logSem3);
 }

sema_up(&logSem4);
  
}

void my_thread5(){

   sema_init(&logSem4,0);

   for(int i=1; i<=4; i++){

      snprintf(th_name, 16, "%d", i);

      printf("BEGIN 4.%s\n",th_name);
      thread_create(th_name,PRI_DEFAULT, my_thread4, NULL);
      printf("END 4.%s\n",th_name);

      sema_down(&logSem4);
 }

sema_up(&logSem5);
printf("END 5.%s\n",th_name);
  
}

void my_test_create_threads (void) 

{
  
  
  /* Am incercat sa fac sem_init cu 1 ca asa un thread ar avea voie sa intre 
      dar nu merge cum trebuie se mai calaresc 2 threaduri si am pus un down dupa init
      si asa a mers dar practic atunci am value 0 deci pot sa fac init direct cu 0
      dar nu imi dau exact seama de ce e bine asa */
  //sema_init(&logSem5,1);
  //sema_down(&logSem5);

  sema_init(&logSem5,0);

  for(int i=1; i<=5 ;i++){
   
   snprintf(th_name, 16, "%d", i);

   printf("BEGIN 5.%s\n",th_name);
   thread_create(th_name,PRI_DEFAULT, my_thread5, NULL);


   sema_down(&logSem5);
    
	}


}
