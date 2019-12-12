/*Вариант 6
Напишите программу выводящую некоторое сообщение через равные промежутки времени в течение определенного интервала времени. 
Использовать функции alarm и pause.
*/
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <iostream>
#include <stdlib.h>


void alarm(int signal){
  printf("Alarm!\n");
}

int main(int argc, char **argv){
signal(SIGALRM, alarm);
alarm(1);
for(volatile unsigned long i=0; i!=~0; i++){
      printf("\ra");
      fflush(stdout);
}
pause();
printf("Finish\n");
}
