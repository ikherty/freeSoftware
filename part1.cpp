/*Вариант 6
Напишите программу fake, которая использует целочисленное значение первого аргумента в качестве статуса завершения.
Выполните программу fake, задавая различные значения аргументов, включая большие и отрицательные.
*/
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<iostream>
#include<stdio.h>

void fake(int status){
 printf("%d\n",status);
 exit(status);
}

int main(int argc, char **argv){
  int status=std::stoi(argv[1]);//преобразует первый аргумент в целочисленное значение
  pid_t pid; //определяет идентификатор процесса
  int s;
  printf("expected exit status = %d\n", status);
  switch(pid = fork()){
        case -1://возникла ошибка
            perror("fork");
            return -1;
        case 0://успешное создание дочернего процесса
            printf("fake exit status = ");
            fake(status);
   printf("Error\n");
  }

wait(& s);//приостанавливает выполнение текущего процесса до тех пор, пока дочерний процесс не завершится и возвращает статус
printf("status exit fake function = %d\n",s); 

}
