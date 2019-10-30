#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
int main(){
umask(0);
int fd=open("file1",O_RDONLY);
if(fd<0){
perror("open error");
return 0;
}

const char *msg="hello world\n";
char buf[1024];
while(1){
int s= read(fd,buf,strlen(msg));
if(s>0){
printf("%s",buf);
}
else{
break;
}

}

close(fd);
return 0;
}
