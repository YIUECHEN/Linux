#include<unistd.h>
#include<stdio.h>

int main(){

int buf[10]={0};

int i=0;
for(;i<10;i++){
 buf[i]='-';

printf("%s\n",buf);

  }

return 0;
}
