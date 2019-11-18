#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<ctype.h>
#include<sys/wait.h>

int main(){

while(1){
printf("[test@local]#");
fflush(stdout);
char buf[1024];
fgets(buf,1023,stdin);
buf[strlen(buf)-1]='\0';
printf("cmd:[%s]\n",buf);

char *ptr=buf;
int argc=0;
char *argv[32]={NULL};

while(*ptr!='\0'){
 if(!isspace(*ptr)){
   argv[argc]=ptr;
   argc++;
     while(!isspace(*ptr)&& *ptr!='\0'){
             *ptr++;
  }
  *ptr='\0'; 
}

  ptr++;
}
argv[argc]=NULL;

int i=0;
for(i=0;i<argc;i++){
    printf("[%s]\n",argv[i]);
 }

int pid=fork();
if(pid==(0)){
  execvp(argv[0],argv);
  exit(0);
  }
 waitpid(-1,NULL,0);
}
return 0;

}
