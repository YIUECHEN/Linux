#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(){
close(1);

int fd=open("myfile",O_WRONLY|O_CREAT,0644);

if(fd<0){
perror("open");
return 1;
}

printf("fd:%d\n",fd);
fflush(stdout);

close(fd);
exit(0);

}
