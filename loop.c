#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<stdint.h>

int main(){
int i=0;
for(i=0;i<256;++i){

printf("errormeg:[%s]\n",strerror(i));

  }
}

