#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
void *thr_start(){
        while(1)
        {   
                printf("child thread---\n");
                sleep (1);
        }   
        return;
} 
              
int main()
{
        pthread_t tid;
        int ret = pthread_create(&tid, NULL, thr_start, NULL);
        if (ret != 0)
        { 
                perror("pthread create error");
                return -1; 
    
        } 
        while(1)
        { 
                printf (("main thread---%p\n",tid);
                sleep (1);
        }
        return 0;
}


