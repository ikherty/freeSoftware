// OS_Lab1_Mutex.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"

// ������, ���������� ������ �� ����� ������� ��������
#define SCOPE_LOCK_MUTEX(hMutex) CMutexLock _tmp_mtx_capt(hMutex);

typedef struct _TList
{
   int *arr;
   int size;
} TList;

static CAutoMutex g_mutex;				// ������������� ����������� � ��������� ������
static CAutoEvent f_event;				// ������������� ����������� � ��������� �������


DWORD WINAPI Writer(TList *param)				// ������ � ������
{		// ������ �� �����
    int i;
	for (i = 0; i < param->size; ++i)			
	{
		WaitForSingleObject(f_event.get(), INFINITE);		// ���������� �������
		SCOPE_LOCK_MUTEX(g_mutex.get());		// �������� ������
		param->arr[i] = i+1;					// �������� ����� ������
		Sleep(200);								// ����
   }
		// ����� ������ �������������
		// ������ �� �����
	return 0;
}

DWORD WINAPI Reader(TList *param)				// ������ �� �������
{		// ������ �� �����		
   int i;
   for (i = 0; i < param->size; ++i)
   {
      int j = 0;
		SCOPE_LOCK_MUTEX(g_mutex.get());		// �������� ������
		while ((param->arr[j] != 0) && (j < param->size))
		{
			printf("%d ", param->arr[j]);
			j++;
		}
		Sleep(100);							// ����
		SetEvent(f_event.get());
		printf("\n");
   }
		// ����� ������ �������������
		// ������ �� �����
   return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int arr[] = {0,0,0,0,0,0,0,0,0,0};
	int size = sizeof(arr) / sizeof(*arr);
	TList lst = {arr, size};

	CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(&Writer), &lst, 0, 0);		//����� ������
    CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(&Reader), &lst, 0, 0);		//����� ������

	getch();
	return 0;
}