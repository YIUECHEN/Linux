#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
void sigcb(signo){
	printf("get a signal:%d\n",signo);
}
int main(){

	//signal(2,SIG_IGN);//将2号信号SIGINT处理为忽略
	//struct sigaction act,old;

	//act.sa_handler=SIG_IGN;
	//sigemptyset(&act.sa_mask); //清空此信号集
	//act.sa_flags=0;

	//sigaction(2,&act,&old);//将2号信号替换为处理

	signal(2,sigcb);
	while(1){
		printf("-----------------\n");
		sleep(3);
		//getchar();
		//sigaction(SIGINT, &old, NULL); //恢复成原始状态
	}
	return 0;
}

