#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
int main ()
{

  int ret;
  FILE *fp = NULL;
  fp = fopen ("./tmp.txt", "r+");
  if (fp == NULL)
    {
      perror ("fopen error");
      return -1;
    }
  fseek (fp, 10, SEEK_END);

  char *ptr = "空山新雨后!\n";
  ret = fwrite (ptr, strlen (ptr), 1, fp);
  printf ("write item:%d\n", ret);
  fseek (fp, 0, SEEK_SET);

  char buf[1024] = { 0 };
  ret = fread (buf, 1023, 1, fp);
  perror ("fread error");
  printf ("read buf:[%s]-ret:[%d]\n", buf, ret);

  fclose ("fp");

}
