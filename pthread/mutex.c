#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#define MAX_THR 4
int ticket=100;
pthread_mutex_t mutex;
void *thr_start(void *argv){
	while(1){
		pthread_mutex_lock(&mutex);
		if(ticket>0){
			printf("%p get a ticket:%d\n",pthread_self(),ticket);
			usleep(1000);		
			ticket--;
			pthread_mutex_unlock(&mutex);	
		}
		else{
			printf("%pdon't have ticket\n",pthread_self());
			pthread_mutex_unlock(&mutex);			
			pthread_exit(NULL);
		}
	}
	return NULL;
}
int main(){
	pthread_t tid[MAX_THR];
	pthread_mutex_init(&mutex,NULL);
	int i;
	for(i=0;i<MAX_THR;i++){
		int ret=pthread_create(&tid[i],NULL,thr_start,NULL);
		if(ret!=0){
			perror("pthread create error\n");
			return -1;	
		}
	}
	for(i=0;i<MAX_THR;i++){
		pthread_join(tid[i],NULL);
	}
	pthread_mutex_destroy(&mutex);
	return 0;
}
