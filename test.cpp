#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<iostream>
#include<stdio.h>

using std::cin;
using std::cout;
void fake(int x){
    printf("status param %d\n",x);
    exit(x);
}

int main(){
    int stat;
    pid_t pid;
    int s1;
    printf("Enter exit status\n");
    cin>>stat;
    switch(pid = fork()){
        case -1:
        perror("fork");
        return -1;

        case 0  :
            //printf("Child\n");
            fake(stat);
            //printf("Error\n");
    }

    wait(& s1); //передаем указатель на инт для статуса
    printf("status is %d\n",s1); //печатаем статус
    printf("evaluation of the status low-order 8 bits %d\n",WEXITSTATUS(s1)); //печатаем младшие 8 бит статуса

    return 1;
}
