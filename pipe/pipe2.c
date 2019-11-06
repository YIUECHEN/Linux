#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

int main()
{
int fd[2]={0};


int ret=pipe(fd);
if(ret<0){
perror("pipe error");
return -1;
}

int pid1=fork();

if(pid1<0){
perror("fork1 error");
return -1;
}else if(pid1==0){ 
//进程1实现ps
close(fd[0]);
dup2(fd[1],1);
execlp("ps","ps","-ef",NULL);
exit(0);
}


int pid2=fork();

if(pid2<0){
perror("fork2 error");
return -1;
}else if(pid2==0){
//进程2实现grep
close(fd[1]);
dup2(fd[0],0);
execlp("grep","grep","ssh",NULL);
exit(0);
}
close(fd[0]);
close(fd[1]);
//waitpid(pid1,NULL,0);
//waitpid(pid2,NULL,0);
return 0;
}

