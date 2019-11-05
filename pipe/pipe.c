#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main()
{
int pid;
int fd[2];
if(pipe(fd)<0){
perror("pipe error");
return -1;
}
pid=fork();
if(pid==0){
//子进程向管道读取数据
char buf[1024];
if(read(fd[0],buf,1023)<0){
perror("read error\n");
return -1;
}
printf("child get data:[%s]\n",buf);
}

else{
//父进程向管道写入数据
char *ptr="hello world";

if(write(fd[1],ptr,strlen(ptr))<0){
perror("write error");
return -1;
}
}

}
