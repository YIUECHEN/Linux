#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
int main()
{
int fd=open("myfile",O_RDONLY);
if(fd<0){
perror("open");
return 1;
}

printf("FD:%d\n",fd);

close(fd);
return 0;
}
