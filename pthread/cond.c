#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#define MAX_THR 4
int noodle=0;
pthread_mutex_t mutex;
pthread_cond_t cond_foodie;
pthread_cond_t cond_chef;
void *foodie(void *argv){
	while(1){
		pthread_mutex_lock(&mutex);
		while(noodle==0){
			pthread_cond_wait(&cond_foodie,&mutex);
		}
		printf("%p:the noodles are delicious~\n",pthread_self());
		noodle--;

		pthread_mutex_unlock(&mutex);
		pthread_cond_signal(&cond_chef);
	}
	return NULL;
}

void *chef(void *argv){
	while(1){
		pthread_mutex_lock(&mutex);
		while(noodle==1){
			pthread_cond_wait(&cond_chef,&mutex);
		}
		printf("make a bowl of noodle~\n");
		noodle++;
		pthread_mutex_unlock(&mutex);
		pthread_cond_signal(&cond_foodie);
		sleep(1);
	}
	return NULL;
}

int main(){
	pthread_t foodietid[MAX_THR],cheftid;
	int ret,i;
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&cond_foodie,NULL);
	pthread_cond_init(&cond_chef,NULL);
	for(i=0;i<MAX_THR;i++){
		ret=pthread_create(&foodietid[i],NULL,foodie,NULL);
		if(ret!=0){
			perror("pthread create error");
		}
	}
	ret=pthread_create(&cheftid,NULL,chef,NULL);
	if(ret!=0){
		perror("pthread create error");
	}
	for(i=0;i<MAX_THR;i++){
		pthread_join(foodietid[i],NULL);
	}
	pthread_join(cheftid,NULL);
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond_foodie);
	pthread_cond_destroy(&cond_chef);
	return 0;
}
