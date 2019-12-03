//信号量实现同步互斥
#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<unistd.h>
#include<pthread.h>

sem_t sem;
int t=100;
void *cattle(void *arv){
	while(1){
		sem_wait(&sem);
		if(t>0){
			sleep(1);
			printf("%pi get a ticket:%d\n",pthread_self(),t--);
			sem_post(&sem);
		}
		else{
			sem_post(&sem);
			pthread_exit(NULL);

		}
	}
	return NULL;
}
int main(){
	int ret;
	pthread_t tid1,tid2;
	sem_init(&sem,0,1);
	ret=pthread_create(&tid1,NULL,cattle,NULL);
	if(ret!=0){
		perror("pthead create error");
		return -1;
	}

	ret=pthread_create(&tid2,NULL,cattle,NULL);
	if(ret!=0){
		perror("pthead create error");
		return -1;
	}
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	sem_destroy(&sem);
	return 0;
}
