#include <stdio.h>
#include "tests/threads/tests.h"
#include "threads/malloc.h"
#include "threads/synch.h"
#include "threads/thread.h"
#include "devices/timer.h"

struct semaphore logSem1, logSem2, logSem3, logSem4, logSem5;

void my_thread1()
{
   int i = 0;

   printf("BEGIN 0.%d\n", i);

   print_thread_info_create(thread_current());

   printf("ENDIN 0.%d\n", i);

   sema_up(&logSem1);
}

void my_thread2()
{

   char th_name1[16] = {0};
   sema_init(&logSem1, 0);
   int i = 1;

   snprintf(th_name1, 16, "%d", i);

   printf("--BEGIN 1.%d\n", i);

   thread_create(th_name1, PRI_DEFAULT, my_thread1, NULL);
   sema_down(&logSem1);

   printf("--ENDIN 1.%d\n", i);

   sema_up(&logSem2);
}

void my_thread3()
{

   char th_name2[16] = {0};
   sema_init(&logSem2, 0);

   for (int i = 1; i <= 2; i++)
   {
      snprintf(th_name2, 16, "%d", i);

      printf("----BEGIN 2.%d\n", i);

      thread_create(th_name2, PRI_DEFAULT, my_thread2, NULL);
      sema_down(&logSem2);

      printf("----ENDIN 2.%d\n", i);
   }

   sema_up(&logSem3);
}

void my_thread4()
{

   char th_name3[16] = {0};
   sema_init(&logSem3, 0);

   for (int i = 1; i <= 3; i++)
   {
      snprintf(th_name3, 16, "%d", i);

      printf("------BEGIN 3.%d\n", i);

      thread_create(th_name3, PRI_DEFAULT, my_thread3, NULL);
      sema_down(&logSem3);

      printf("------ENDIN 3.%d\n", i);
   }

   sema_up(&logSem4);
}

void my_thread5()
{

   char th_name4[16] = {0};
   sema_init(&logSem4, 0);

   for (int i = 1; i <= 4; i++)
   {
      snprintf(th_name4, 16, "%d", i);

      printf("--------BEGIN 4.%d\n", i);

      thread_create(th_name4, PRI_DEFAULT, my_thread4, NULL);
      sema_down(&logSem4);

      printf("--------ENDIN 4.%d\n", i);
   }

   sema_up(&logSem5);
}

void my_test_create_threads(void)

{
   char th_name5[16] = {0};

   /* Am incercat sa fac sem_init cu 1 ca asa un thread ar avea voie sa intre
       dar nu merge cum trebuie se mai calaresc 2 threaduri si am pus un down dupa init
       si asa a mers dar practic atunci am value 0 deci pot sa fac init direct cu 0
       dar nu imi dau exact seama de ce e bine asa */
   // sema_init(&logSem5,1);
   // sema_down(&logSem5);

   sema_init(&logSem5, 0);

   for (int i = 1; i <= 5; i++)
   {

      snprintf(th_name5, 16, "%d", i);

      printf("----------BEGIN 5.%d\n", i);

      thread_create(th_name5, PRI_DEFAULT, my_thread5, NULL);
      // astept sa se creeze cele 4 threaduri
      sema_down(&logSem5);

      printf("----------ENDIN 5.%d\n", i);
   }
}
