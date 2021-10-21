#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "a2_helper.h"
#include <time.h>
#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>

sem_t logSem;
sem_t logSem4;

void *thread5(void *arg)
{

    int i = (int)(size_t)arg;

    sem_wait(&logSem);
    //printf("I=%d\n", i);
    info(BEGIN, 5, i);
    info(END, 5, i);

    sem_post(&logSem);
    return NULL;
}

void *thread4(void *arg)
{

    int i = (int)(size_t)arg;

    sem_wait(&logSem4);
    info(BEGIN, 4, i);
    info(END, 4, i);
    sem_post(&logSem4);

    return NULL;
}

void *thread6(void *arg)
{

    int i = (int)(size_t)arg;

    sem_wait(&logSem);
    info(BEGIN, 6, i);
    info(END, 6, i);
    sem_post(&logSem);

    return NULL;
}

int main()
{
    init();

    pid_t pid[10];
    pthread_t th5[5], th4[40], th6[6];

    if (sem_init(&logSem, 0, 1) != 0)
    {
        perror("Could not init the semaphore");
        return -1;
    }

    if (sem_init(&logSem4, 0, 5) != 0)
    {
        perror("Could not init the semaphore");
        return -1;
    }

    //p1
    info(BEGIN, 1, 0);
    pid[1] = fork();
    if (pid[1] == 0)
    {
        //p2
        info(BEGIN, 2, 0);
        pid[2] = fork();
        if (pid[2] == 0)
        {
            //p3
            info(BEGIN, 3, 0);
            pid[3] = fork();
            if (pid[3] == 0)
            {
                //p7
                info(BEGIN, 7, 0);

                info(END, 7, 0);
            }
            else
            {
                //wait for p7
                wait(NULL);
                info(END, 3, 0);
            }
        }
        else
        {
            //wait for p3
            wait(NULL);

            //p5
            pid[5] = fork();
            if (pid[5] == 0)
            {
                info(BEGIN, 5, 0);

                for (int i = 0; i < 5; i++)
                {

                    pthread_create(&th5[i], NULL, &thread5, (void *)(size_t)(i + 1));
                }
                for (int i = 0; i < 5; i++)
                {
                    pthread_join(th5[i], NULL);
                }

                info(END, 5, 0);
            }
            else
            {
                //wait for p5
                wait(NULL);

                //p6
                pid[6] = fork();
                if (pid[6] == 0)
                {
                    info(BEGIN, 6, 0);

                    for (int i = 0; i < 6; i++)
                    {
                        pthread_create(&th6[i], NULL, &thread6, (void *)(size_t)(i + 1));
                    }
                    for (int i = 0; i < 6; i++)
                    {
                        pthread_join(th6[i], NULL);
                    }

                    info(END, 6, 0);
                }
                else
                {
                    //wait for p6
                    wait(NULL);
                    info(END, 2, 0);
                }
            }
        }
    }
    else
    {
        //wait for p2
        wait(NULL);

        //p4
        pid[4] = fork();
        if (pid[4] == 0)
        {
            info(BEGIN, 4, 0);

            for (int i = 0; i < 40; i++)
            {
                pthread_create(&th4[i], NULL, &thread4, (void *)(size_t)(i + 1));
            }
            for (int i = 0; i < 40; i++)
            {
                pthread_join(th4[i], NULL);
            }

            info(END, 4, 0);
        }
        else
        {
            //wait for p4
            wait(NULL);
            info(END, 1, 0);
        }
    }

    return 0;
}