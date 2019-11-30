/*Организовать совместное использование мьютекса и события для защиты добавления элемента в очереди. Очередь произвольного формата. Событие сигнализирует чтение из очереди, а мьютекс - запись. Требуется снять статистику по времени использования объектов ядра*/
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <assert.h>
#include <queue> 
using namespace std;
//#include "stdafx.h"

// макрос, занимающий мютекс до конца области действия
#define SCOPE_LOCK_MUTEX(hMutex) CMutexLock _tmp_mtx_capt(hMutex);

class CAutoEvent
{
	HANDLE e_h_event;								// дескриптор создаваемого события
	CAutoEvent(const CAutoEvent&);					// запрет копирования
	CAutoEvent& operator=(const CAutoEvent&);
 public:
	CAutoEvent()
	{
		e_h_event = CreateEvent(NULL, TRUE, FALSE, NULL);		//создаем событие
		assert(e_h_event);								//заваливаем программу, если событие не создано
	}
	~CAutoEvent() { CloseHandle(e_h_event); }			//деструктор закрывает событие
	HANDLE get() { return e_h_event; }					//метод получения дескриптора события
};

class CAutoMutex{							// класс, создающий и удал€ющий мьютекс
  HANDLE m_h_mutex;							// дескриптор создаваемого мютекса
  CAutoMutex(const CAutoMutex&);				// запрет копировани€
  CAutoMutex& operator=(const CAutoMutex&);
 public:
  CAutoMutex(){
    m_h_mutex = CreateMutex(NULL, FALSE, NULL);		//создаем мьютекс
	assert(m_h_mutex);								//заваливаем программу, если мьютекс не создан
  }
  ~CAutoMutex() { CloseHandle(m_h_mutex); }			//деструктор закрывает мьютекс
  HANDLE get() { return m_h_mutex; }				//метод получени€ дескриптора мьютекса
};

class CMutexLock{									// класс, занимающий и освобождающий мютекс
  HANDLE m_mutex;
  CMutexLock(const CMutexLock&);					// запрещаем копирование
  CMutexLock& operator=(const CMutexLock&);
public:
  CMutexLock(HANDLE mutex): m_mutex(mutex){			// занимаем мютекс при конструировании объекта
    const DWORD res = WaitForSingleObject(m_mutex, INFINITE);		
    assert(res == WAIT_OBJECT_0);					//заваливаем программу, если мьютекс в сигнальном состоянии
  }
 ~CMutexLock(){										 // освобождаем мютекс при удалении объекта
    const BOOL res = ReleaseMutex(m_mutex);
    assert(res);									//проверка на успешность освобождения
  }
};


typedef struct _TList{
   int *arr;
   int size;
} TList;

static CAutoMutex g_mutex;				// автоматически создаваемый и удаляемый мютекс
static CAutoEvent f_event;				// автоматически создаваемое и удаляемое событие


DWORD WINAPI Writer(TList *param){				// запись в массив
    int i; // мютекс не занят
    Node * n = (param->arr)->first;
	for (i = 0; i < param->size; ++i){
		WaitForSingleObject(f_event.get(), INFINITE);		// дожидаемся события
		SCOPE_LOCK_MUTEX(g_mutex.get());		// занимаем мютекс
		n->data = i+1;					// изменяем общие данные
		n = n->next;
		Sleep(200);								// ждем
   }
		// здесь мютекс освобождается
		// мютекс не занят
	return 0;
}

DWORD WINAPI Reader(TList *param){				// чтение из массива		
   int i;// мютекс не занят		
   for (i = 0; i < param->size; ++i){
      int j = 0;
		SCOPE_LOCK_MUTEX(g_mutex.get());		// занимаем мютекс
		//while ((param->arr[j] != 0) && (j < param->size)){
			//printf("%d ", param->arr[j]);
			//j++;
		//}////////////////////
		//void Print(Queue* Q){
        Node * n = (param->arr)->first;
        while(n){
            cout << n->data << "  ";
            printf("%d "\n, n->data);
            n = n->next;
        }
        //cout << endl;
}/////////////////////////
		Sleep(100);							// ждем
		SetEvent(f_event.get());
		printf("\n");
   }
		// здесь мютекс освобождается
		// мютекс не занят
   return 0;
}

int main(){
	//int arr[] = {0,0,0,0,0,0,0,0,0,0};
	//int size = sizeof(arr) / sizeof(*arr);
    //TList lst = {arr, size};
    queue<int> myQueue;     // создаем пустую очередь типа  int
    // добавили в очередь несколько элементов
    for(int i=0;i<9;i++)
        myQueue.push(0);
    int size=sizeof(myQueue) / sizeof(*myQueue);
    TList lst = myQueue, size};
	
	CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(&Writer), &lst, 0, 0);		//поток записи
    CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(&Reader), &lst, 0, 0);		//поток чтения
	return 0;
}
