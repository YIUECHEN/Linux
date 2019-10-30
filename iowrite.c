#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

int main()
{
umask(0);
int fd=open("file1",O_WRONLY|O_CREAT,0644);
if(fd<0){
perror("open error");
return 0;
}

int count=5;
const char *msg="hello world\n";
int len=strlen(msg);
while(count--){
write(fd,msg,len);
}
close(fd);
return 0;
}

