/*Организовать совместное использование мьютекса и события для защиты добавления элемента в очереди. Очередь произвольного формата. Событие сигнализирует чтение из очереди, а мьютекс - запись. Требуется снять статистику по времени использования объектов ядра*/
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <assert.h>
#include <queue>
using namespace std;

// макрос, занимающий мютекс до конца области действия
#define SCOPE_LOCK_MUTEX(hMutex) CMutexLock _tmp_mtx_capt(hMutex);

class CAutoEvent{
		HANDLE e_h_event;								     // дескриптор создаваемого события
		CAutoEvent(const CAutoEvent&);					     // запрет копирования
		CAutoEvent& operator=(const CAutoEvent&);
	public:
		CAutoEvent(){
			e_h_event = CreateEvent(NULL, TRUE, FALSE, NULL);//создаем событие
			assert(e_h_event);								 //завершаем программу, если событие не создано
		}
		~CAutoEvent(){
			CloseHandle(e_h_event);                          //деструктор закрывает событие
		}
		HANDLE get(){
			return e_h_event;                                //метод получения дескриптора события
		}
};

class CAutoMutex{ 							                 // класс, создающий и удаляющий мьютекс
		HANDLE m_h_mutex;							         // дескриптор создаваемого мютекса
		CAutoMutex(const CAutoMutex&);				         // запрет копировани€
		CAutoMutex& operator=(const CAutoMutex&);
	public:
		CAutoMutex(){
			m_h_mutex = CreateMutex(NULL, FALSE, NULL);		//создаем мьютекс
			assert(m_h_mutex);								//завершаем программу, если мьютекс не создан
		}
		~CAutoMutex(){
			CloseHandle(m_h_mutex);                          //деструктор закрывает мьютекс
		}
		HANDLE get(){
			return m_h_mutex;                                //метод получения дескриптора мьютекса
		}
};

class CMutexLock{ 									         // класс, занимающий и освобождающий мютекс
		HANDLE m_mutex;
		CMutexLock(const CMutexLock&);					     // запрещаем копирование
		CMutexLock& operator=(const CMutexLock&);
	public:
		CMutexLock(HANDLE mutex): m_mutex(mutex){			// занимаем мютекс при конструировании объекта
			const DWORD res = WaitForSingleObject(m_mutex, INFINITE);
			assert(res == WAIT_OBJECT_0);					//завершаем программу, если мьютекс в сигнальном состоянии
		}
		~CMutexLock(){										 // освобождаем мютекс при удалении объекта
			const BOOL res = ReleaseMutex(m_mutex);
			assert(res);									//проверка на успешность освобождения
		}
};

static CAutoMutex g_mutex;				// автоматически создаваемый и удаляемый мютекс
static CAutoEvent f_event;				// автоматически создаваемое и удаляемое событие


DWORD WINAPI Writer(queue <int> qw){ 				       // запись в массив
	// мютекс не занят
	for(int i=0; i<10; i++){
		WaitForSingleObject(f_event.get(), INFINITE);		// дожидаемся события
		SCOPE_LOCK_MUTEX(g_mutex.get());		            // занимаем мютекс
		qw.push(qw.back()+1);					            // изменяем общие данные
		Sleep(100);								            // ждем
	}
	// здесь мютекс освобождается
	// мютекс не занят
	return 0;
}

DWORD WINAPI Reader(queue <int>qw){ 				// чтение из массива
	while(!qw.empty()){
		//SCOPE_LOCK_MUTEX(g_mutex.get());		    // занимаем мютекс
		printf("%d",qw.front());
		qw.pop();
		Sleep(100);							        // ждем
		SetEvent(f_event.get());
		printf("\n");
	}
	// здесь мютекс освобождается
	// мютекс не занят
	return 0;
}

int main(){
	queue <int> Q;
	Q.push(0);
	Q.push(1);
	Q.push(2);
	CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(&Writer), &Q, 0, 0);		        //поток записи
	HANDLE dd=CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(&Reader), &Q, 0, 0);		//поток чтения
	CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(&Writer), &Q, 0, 0);		        //поток записи
	WaitForSingleObject(dd, INFINITE);
	return 0;
}
