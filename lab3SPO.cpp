/*Организовать совместное использование мьютекса и события для защиты добавления элемента в очереди. Очередь произвольного формата. Событие сигнализирует чтение из очереди, а мьютекс - запись.*/
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <queue>
using namespace std;
HANDLE hMutex, event;

DWORD WINAPI Writer(queue <int> qw){ 				       // запись в очередь
	for(int i=0; i<5; i++){
		WaitForSingleObject(hMutex, INFINITE);
		Sleep(10);	
		qw.push(qw.back()+1);					            
		printf("\ntw=%d \n",i);
		Sleep(100);	
		ReleaseMutex(hMutex);							            // освобождаем мьютекс
		SetEvent(event);                                              //сигналим событие
	}
	return 0;
}

DWORD WINAPI Reader(queue <int>qw){ 				// чтение из очереди
	while(!qw.empty()){				
		WaitForSingleObject(event, INFINITE);		// дожидаемся события	
		printf("%d",qw.front());
		qw.pop();
		Sleep(100);							        
		ResetEvent(event);                        //делаем несигнальное состояние события
		printf("\n");
	}
	return 0;
}

int main(){
	queue <int> Q;
	Q.push(0);
	HANDLE fd, sd, td;
	hMutex = CreateMutex(NULL, FALSE, NULL);
	event=CreateEvent(NULL, TRUE, FALSE, NULL);
	 fd=CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(&Writer), &Q, 0, 0);		        //поток записи
	 sd=CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(&Reader), &Q, 0, 0);		        //поток чтения
	 td=CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(&Writer), &Q, 0, 0);		        //поток записи
	WaitForSingleObject(fd, INFINITE);
	WaitForSingleObject(sd, INFINITE);
	WaitForSingleObject(td, INFINITE);
	CloseHandle(fd);
    CloseHandle(sd);
    CloseHandle(td);
    return 0;
}
