#include<stdio.h>
#include<signal.h>
#include<stdlib.h>

int main(){

//kill(getpid(),SIGINT);//给任意进程发送任意信号
//raise(SIGTSTP);//给进程本身发送一个指定信号
//abort();给进程自身发送SIGABUT信号，引发进程非正常退出
//alarm(7);//在7秒后退出进程
while(1){
printf("--------------\n");
sleep(3);

}
return 0;
}
