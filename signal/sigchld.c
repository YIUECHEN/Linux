#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

void sigcb(int signo){

	//waitpid(-1,NULL,0);//SIGCHILD是一个非可靠信号，容易造成信号丢失
	while(waitpid(-1,NULL,WNOHANG)>0);//不断等待子进程退出，直到等待出错
}

int main()
{
	signal(SIGCHLD,sigcb);//将sigchild信号的处理方式自定义为回调杉树
	int pid=fork();
	if(pid==0){
		printf("child\n");
		sleep(3);
		exit(0);
	}
	while(1){

		printf("father\n");
		sleep(1);
	}
	return 0;
}
