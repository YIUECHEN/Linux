#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{

char buf[1024];

ssize_t s=read(0,buf,strlen(buf));

if(s>0){
buf[s]=0;
write(1,buf,strlen(buf));
write(2,buf,strlen(buf));

}
return 0;
}

