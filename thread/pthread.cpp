#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define THR_NUM 3

using namespace std;

pthread_mutex_t mutex;


void *thr_fun(void *num)
{
    pthread_mutex_lock(&mutex); //上锁 
    long number = (long)num;
    cout << "thread num is :" << number << endl;
    switch (number)
    {
        case 1:
            sleep(5);
            break;
        case 2:
            sleep(3);
            break;
        default:
            sleep(8);
            break;
    }
    cout << "Thread finished :" << number <<endl;
    pthread_exit(NULL);
}



int main ()
{
    void * thrd_ret;
    pthread_t pthd[THR_NUM];
    int ret;

    pthread_mutex_init(&mutex, NULL);   //互斥锁初始化
    for(int i = 0; i < THR_NUM; i++)
    {
        ret = pthread_create(&pthd[i], NULL, thr_fun, (void *)(i+1)); 
       if (ret != 0)
       {
           perror("pth_create");
           exit(ret);
       }
    }
     //pthread_join : 主线程挂起，等待监视的线程结束后做处理（同步线程）
    printf("Create treads success\nWaiting for threads to finish...\n");
    for (int no = 0; no < THR_NUM; no++) {
        /* 等待线程结束 */
        ret = pthread_join(pthd[no], &thrd_ret);    
        if (!ret) {
            printf("Thread %d joined\n", no+1);
        } else {
            printf("Thread %d join failed\n", no+1);
        }
        pthread_mutex_unlock(&mutex);

    }
    sleep(10);
    pthread_mutex_destroy(&mutex);
    return 0;

}