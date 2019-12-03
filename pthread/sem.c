//信号量实现同步互斥
#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<unistd.h>
#include<pthread.h>

sem_t sem;

void *eat(void *arv){
	while(1){
		sem_wait(&sem);
		printf("**eat a bool of noodle\n");

	}
	return NULL;
}
void *cook(void *arv){
	while(1){

		printf("$$cook a bool of noodle\n");
		sleep(1);	
		sem_post(&sem);
	}
	return NULL;
}
int main(){
	int ret,i;
	pthread_t tid1,tid2;
	sem_init(&sem,0,0);
	ret=pthread_create(&tid1,NULL,eat,NULL);
	if(ret!=0){
		perror("pthead create error");
		return -1;
	}

	ret=pthread_create(&tid2,NULL,cook,NULL);
	if(ret!=0){
		perror("pthead create error");
		return -1;
	}
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	sem_destroy(&sem);
	return 0;
}
