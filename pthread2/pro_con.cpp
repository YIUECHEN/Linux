#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<queue>
#include<pthread.h>
#include<unistd.h>
using namespace std;

#define MAX_QUE 10
#define MAX_THR 4

class BlockQueue{
	private:
		queue<int> _queue;
		int _capacity;
		pthread_cond_t _cond_pro;
		pthread_cond_t _cond_con;
		pthread_mutex_t _mutex;
	public:
		BlockQueue(int que_num=MAX_QUE):_capacity(que_num){
			pthread_mutex_init(&_mutex,NULL);
			pthread_cond_init(&_cond_pro,NULL);
			pthread_cond_init(&_cond_con,NULL);
		}
		~BlockQueue(){
			pthread_mutex_destroy(&_mutex);
			pthread_cond_destroy(&_cond_pro);
			pthread_cond_destroy(&_cond_con);
		}
		bool QueuePush(int &data){
			pthread_mutex_lock(&_mutex);
			while(_queue.size()==_capacity){
				pthread_cond_wait(&_cond_pro,&_mutex);
			}
			_queue.push(data);
			pthread_mutex_unlock(&_mutex);
			pthread_cond_signal(&_cond_con);
			return true;
		}
		bool QueuePop(int &data){
			pthread_mutex_lock(&_mutex);
			while(_queue.size()==0){
				pthread_cond_wait(&_cond_con,&_mutex);
			}
			data=_queue.front();
			_queue.pop();
			pthread_mutex_unlock(&_mutex);
			pthread_cond_signal(&_cond_pro);
			return true;
		}
};
void *consumer(void *arg){
	BlockQueue *queue=(BlockQueue*)arg;	
	while(1){
		int data;
		queue->QueuePop(data);
		printf("%p..get a data:%d\n",pthread_self(),data);
	}
	return NULL;
}
void *product(void *arg){
	int data=0;
	BlockQueue *queue=(BlockQueue*)arg;	

	while(1){
		queue->QueuePush(data);
		printf("%p__put a data:%d\n",pthread_self(),data++);
                sleep(1);
	}
	return NULL;
}
int main(){
	BlockQueue bq;
	pthread_t ptid[MAX_THR],ctid[MAX_THR];

	int ret;
	for(int i=0;i<MAX_THR;i++){
		ret=pthread_create(&ptid[i],NULL,product,(void*)&bq);
		if(ret!=0){
			cerr<<"pthread create error"<<endl;
			return -1;	
		}
	}
	for(int i=0;i<MAX_THR;i++){
		ret=pthread_create(&ctid[i],NULL,consumer,(void*)&bq);
		if(ret!=0){
			cerr<<"pthread create error\n"<<endl;
			return -1;	
		}
	}

	for(int i=0;i<MAX_THR;i++){
		pthread_join(ptid[i],NULL);
		pthread_join(ctid[i],NULL);
	}
	return 0;
}






