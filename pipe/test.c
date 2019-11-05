#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h> 

int main()
{
int fd[2];
char buf[100];
int len;

if(pipe(fd)!=0){

perror("make pipe");
exit(-1);

}

//read from stdin
while(fgets(buf,100,stdin)){
len=strlen(buf);

//write into pipe
if(write(fd[1],buf,len)!=len){

perror("write to pipe");
break;
}

memset(buf,0x00,sizeof(buf));
 
//read from pipe
if(len=read(fd[0],buf,100)==-1){
perror("read from pipe");
break;
}

//write to stdout
if(write(1,buf,len)!=len){
perror("write from stdout");
break;
}
}

}
