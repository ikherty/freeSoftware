/*Вариант 6
Напишите программу выводящую некоторое сообщение через равные промежутки времени в течение определенного интервала времени. 
Использовать функции alarm и pause.
*/
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void printAlarm(int signal){
    printf(" Alarm!\n");
}

int main(){
    signal(SIGALRM, printAlarm);
    for(int i=0; i<5; i++){
        alarm(2);
        pause();
    }
    printf("Done.\n");
}
