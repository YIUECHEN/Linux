#include<iostream>
#include<string>
#include<stdio.h>
#include<unistd.h>
#include<vector>
#include<semaphore.h>
#include<pthread.h>
using namespace std;
#define MAX_THR 4
#define MAX_QN 10
class RingQueue{
	private:
		vector<int> _queue;
		int _capacity;
		int _read;
		int _write;
		sem_t sem_lock;
		sem_t sem_con;
		sem_t sem_pro;
	public:
		RingQueue(int max_que=MAX_QN):_capacity(max_que),_queue(max_que),_write(0),_read(0){
			sem_init(&sem_lock,0,1);
			sem_init(&sem_con,0,0);
			sem_init(&sem_pro,0,max_que);

		}
		~RingQueue(){
			sem_destroy(&sem_lock);
			sem_destroy(&sem_pro);
			sem_destroy(&sem_con);
		}
		bool QueuePush(int &data){
			sem_wait(&sem_pro);
			sem_wait(&sem_lock);
			_queue[_write]=data;
			_write=(_write+1)%_capacity;
			sem_post(&sem_lock);
			sem_post(&sem_con);
			return true;
		}
		bool QueuePop(int &data){
			sem_wait(&sem_con);
			sem_wait(&sem_lock);
			data=_queue[_read];		        
			_read=(_read+1)%_capacity;
			sem_post(&sem_lock);
			sem_post(&sem_pro);
			return true;              
		}

};
void *consumer(void *arg){
	RingQueue *queue=(RingQueue*)arg;
	while(1){
		int data;
		queue->QueuePop(data);
		printf("%p***get a data:%d\n",pthread_self(),data);
	}
	return NULL;
}

void *productor(void *arg){
	RingQueue *queue=(RingQueue*)arg;
	int i=0;	
	while(1){
		queue->QueuePush(i);
		printf("%p---put a data:%d\n",pthread_self(),i++);
		sleep(1);	
	}
	return NULL;
}
int main(){
	RingQueue queue;
	pthread_t ctid[MAX_THR],ptid[MAX_THR];
	for(int i=0;i<MAX_THR;i++){
	      int ret=pthread_create(&ctid[i],NULL,consumer,(void*)&queue);
		if(ret!=0){
			printf("pthread create error\n");
			return -1;	
		}
	}
	for(int i=0;i<MAX_THR;i++){
	      int ret=pthread_create(&ptid[i],NULL,productor,(void*)&queue);
		if(ret!=0){
			printf("pthread create error\n");
			return -1;		
		}
	}

	for(int i=0;i<MAX_THR;i++){
		pthread_join(ctid[i],NULL);
		pthread_join(ptid[i],NULL);
	}
	return 0;
}
