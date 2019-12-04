/*Организовать совместное использование мьютекса и события для защиты добавления элемента в очереди. Очередь произвольного формата. Событие сигнализирует чтение из очереди, а мьютекс - запись.*/
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <Processthreadsapi.h>
#include <assert.h>
#include <queue>
#include <cstring>
using namespace std;
/*
// макрос, занимающий мютекс до конца области действия
//#define SCOPE_LOCK_MUTEX(hMutex) CMutexLock _tmp_mtx_capt(hMutex);

//class CAutoEvent{
//		HANDLE e_h_event;								     // дескриптор создаваемого события
//		CAutoEvent(const CAutoEvent&);					     // запрет копирования
//		CAutoEvent& operator=(const CAutoEvent&);
//	public:
//		CAutoEvent(){
//			e_h_event = CreateEvent(NULL, TRUE, FALSE, NULL);//создаем событие
//			assert(e_h_event);								 //завершаем программу, если событие не создано
//		}
//		~CAutoEvent(){
//			CloseHandle(e_h_event);                          //деструктор закрывает событие
////		}
////		HANDLE get(){
////			return e_h_event;                                //метод получения дескриптора события
////		}
////};
//
//class CAutoMutex{ 							                 // класс, создающий и удаляющий мьютекс
//		HANDLE m_h_mutex;							         // дескриптор создаваемого мютекса
//		CAutoMutex(const CAutoMutex&);				         // запрет копировани€
//		CAutoMutex& operator=(const CAutoMutex&);
//	public:
//		CAutoMutex(){
//			m_h_mutex = CreateMutex(NULL, FALSE, NULL);		//создаем мьютекс
//			assert(m_h_mutex);								//завершаем программу, если мьютекс не создан
//		}
//		~CAutoMutex(){
//			CloseHandle(m_h_mutex);                          //деструктор закрывает мьютекс
//		}
//		HANDLE get(){
//			return m_h_mutex;                                //метод получения дескриптора мьютекса
//		}
//};
//
//class CMutexLock{ 									         // класс, занимающий и освобождающий мютекс
//		HANDLE m_mutex;
//		CMutexLock(const CMutexLock&);					     // запрещаем копирование
//		CMutexLock& operator=(const CMutexLock&);
//	public:
//		CMutexLock(HANDLE mutex): m_mutex(mutex){			// занимаем мютекс при конструировании объекта
//			const DWORD res = WaitForSingleObject(m_mutex, INFINITE);
//			assert(res == WAIT_OBJECT_0);					//завершаем программу, если мьютекс в сигнальном состоянии
//		}
//		~CMutexLock(){										 // освобождаем мютекс при удалении объекта
//			const BOOL res = ReleaseMutex(m_mutex);
//			assert(res);									//проверка на успешность освобождения
//		}
//};

//static CAutoMutex g_mutex;				// автоматически создаваемый и удаляемый мютекс
//static CAutoEvent f_event;				// автоматически создаваемое и удаляемое событие
*/
HANDLE hMutex, event;
queue <int> Q;

DWORD WINAPI Writer(void* param){ 				       // запись в массив
	// мютекс не занят
	 int threadNum = (int)param;
     for(int i=0; i<10; i++){
		////WaitForSingleObject(f_event.get(), INFINITE);		// дожидаемся события
		WaitForSingleObject(hMutex, INFINITE);
		//SCOPE_LOCK_MUTEX(g_mutex.get());		            // занимаем мютекс
		printf("thread %d done\n", threadNum);
//		qw.push(qw.back()+i);					            // изменяем общие данные
Q.push(Q.back()+1);
//		SetEvent(f_event.get());
		SetEvent(event);
		ReleaseMutex(hMutex);	
		Sleep(100);								            // ждем
	}
	// здесь мютекс освобождается
	// мютекс не занят
	return 0;
}

DWORD WINAPI Reader(queue <int>qw){ 				// чтение из массива

	while(!qw.empty()){	
//		WaitForSingleObject(f_event.get(), INFINITE);		// дожидаемся события
WaitForSingleObject(event, INFINITE);
		if(true){
		////SCOPE_LOCK_MUTEX(g_mutex.get());		    // занимаем мютекс
		printf("%d\n",qw.front());
		qw.pop();
	}
		Sleep(100);							        // ждем
	}
	// здесь мютекс освобождается
	// мютекс не занят
	return 0;
}

int main(){
//	queue <int> Q;
//wrap up Q and a in struct and pass it to the thread
//make Q local (uncomment line 107)
//change a value for each thread
	Q.push(0);
	int a=1,b=2;
	hMutex = CreateMutex(NULL, FALSE, NULL);
	event = CreateEvent(NULL, TRUE, FALSE, NULL);
	HANDLE fd=CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(&Writer), (void*)a, 0, 0);		        //поток записи
	HANDLE sd=CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(&Reader), &Q, 0, 0);		        //поток чтения
	HANDLE td=CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(&Writer), (void*)b, 0, 0);		        //поток записи//

	WaitForSingleObject(fd, INFINITE);
	WaitForSingleObject(sd, INFINITE);
	WaitForSingleObject(td, INFINITE);
	CloseHandle(fd);
    CloseHandle(sd);
    CloseHandle(td);
    return 0;
}
