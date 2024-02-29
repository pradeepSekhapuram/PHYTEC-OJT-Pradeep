/*
*  Proves that both the child and parent executes concurrently
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
   int cpid = fork();
   if (cpid == 0)
   {
   sleep(5);
      while(1) putchar('x');
      }
   else
   { 
   	sleep(10);
        while(1) putc('o', stdout);
      }
   return 0;
}

