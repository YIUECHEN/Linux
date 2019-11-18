#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<unistd.h>

#define key 0x12345665
#define size 4096

int main()
{       //创建共享内存
	int shmid=shmget(key,size,IPC_CREAT|0664);

	if(shmid<0){
		perror("shmget error");
		return -1;
	}

	//映射到虚拟地址
	void *shm_start=shmat(shmid,NULL,0);

	if(shm_start==(void*)-1){
		perror("shmat error");
		return -1;
	}

	int i=0;
	while(1){
		sprintf(shm_start,"%s-%d\n","you are beautiful!",i++);//sprintf格式化一个字符串放到一个buf里
		sleep(1);	
	}
	//解除映射关系
	shmdt(shm_start);//shmat返回的指针
	//控制共享内存	
	shmctl(shmid,IPC_RMID,NULL);
	return 0;

}
