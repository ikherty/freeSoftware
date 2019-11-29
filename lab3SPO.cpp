/*Организовать совместное использование мьютекса и события для защиты добавления элемента в очереди. Очередь произвольного формата. Событие сигнализирует чтение из очереди, а мьютекс - запись. Требуется снять статистику по времени использования объектов ядра*/
#include <cstdlib>
#include <iostream>
#include <windows.h>
using namespace std;

// OS_Lab1_Mutex.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

// макрос, занимающий мютекс до конца области действия
#define SCOPE_LOCK_MUTEX(hMutex) CMutexLock _tmp_mtx_capt(hMutex);

typedef struct _TList
{
   int *arr;
   int size;
} TList;

static CAutoMutex g_mutex;				// автоматически создаваемый и удаляемый мютекс
static CAutoEvent f_event;				// автоматически создаваемое и удаляемое событие


DWORD WINAPI Writer(TList *param)				// запись в массив
{		// мютекс не занят
    int i;
	for (i = 0; i < param->size; ++i)			
	{
		WaitForSingleObject(f_event.get(), INFINITE);		// дожидаемся события
		SCOPE_LOCK_MUTEX(g_mutex.get());		// занимаем мютекс
		param->arr[i] = i+1;					// изменяем общие данные
		Sleep(200);								// ждем
   }
		// здесь мютекс освобождается
		// мютекс не занят
	return 0;
}

DWORD WINAPI Reader(TList *param)				// чтение из массива
{		// мютекс не занят		
   int i;
   for (i = 0; i < param->size; ++i)
   {
      int j = 0;
		SCOPE_LOCK_MUTEX(g_mutex.get());		// занимаем мютекс
		while ((param->arr[j] != 0) && (j < param->size))
		{
			printf("%d ", param->arr[j]);
			j++;
		}
		Sleep(100);							// ждем
		SetEvent(f_event.get());
		printf("\n");
   }
		// здесь мютекс освобождается
		// мютекс не занят
   return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int arr[] = {0,0,0,0,0,0,0,0,0,0};
	int size = sizeof(arr) / sizeof(*arr);
	TList lst = {arr, size};

	CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(&Writer), &lst, 0, 0);		//поток записи
    CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(&Reader), &lst, 0, 0);		//поток чтения

	getch();
	return 0;
}
