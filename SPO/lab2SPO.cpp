/*Основной поток создает 2 потока приостановленными. Затем запускает один из созданных потоков, который в свою очередь запускает другой поток. Измерить интервал времени от запуска первого потока до завершения второго в двух случаях:
а) Второй поток создает файл нулевой длины и завершает работу
б) Второй поток создает файл длиной 1К и завершает работу*/
#include <cstdlib>
#include <iostream>
#include <windows.h>
using namespace std;

void create0Kfile(){//a)
    HANDLE DIF;
    DIF=CreateFile((LPCTSTR)"0KFile.txt", GENERIC_READ|GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);  
	CloseHandle(DIF); 
}

void create1Kfile(){//б)
    HANDLE DIF;
    DWORD c;    
    DIF=CreateFile((LPCTSTR)"1KFile.txt", GENERIC_READ|GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);   
    byte *data[1024];                                        //рандомный массив для заполнения входного файла
    for(int i=0; i<1024; i++){
        data[i]=(byte*)rand();
    }
    WriteFile(DIF,(LPVOID)data,1024,&c,NULL);
	CloseHandle(DIF);  
}

void resumeTread(LPVOID lpParam){
    HANDLE myThread;
    myThread = (HANDLE)lpParam;
    ResumeThread(myThread);
    WaitForSingleObject(myThread, INFINITE);
}
int main(){
    __int64 c1, c2,fr1;			          //переменные для счётчика
    double t1=0, t2=0;
    LPDWORD ID;
    HANDLE sThread, fThread;			//дескрипторы потоков
	for (int i=0; i<10; i++){		    //повторение 10 раз
        fThread=CreateThread(NULL,0, (LPTHREAD_START_ROUTINE)resumeTread, sThread, CREATE_SUSPENDED, (LPDWORD)&ID);
                  //Null-указатель на поток не может быть унаследованн
                  //0-размер стека будет установлен таким же как и для основного потока процесса
                  //resumeTread-функция потока
                  //sThread - это значение которое мы передаем в функцию в качестве параметра
                  //CREATE_SUSPENDED - создан приостановленным
                  //параметр, в котором будет возвращен идентификатор потока.
            //CloseHandle(tThread);										//завершение потока
        sThread=CreateThread(NULL,0, (LPTHREAD_START_ROUTINE)create0Kfile, NULL, CREATE_SUSPENDED, (LPDWORD)&ID);
        QueryPerformanceCounter((LARGE_INTEGER *)&c1);				//начало отсчёта времени
        ResumeThread(fThread);                                      //функция запускает 1й поток
        WaitForSingleObject(fThread, INFINITE);
        QueryPerformanceCounter((LARGE_INTEGER *)&c2);					//конец отсчёта времени
        QueryPerformanceFrequency((LARGE_INTEGER *)&fr1);				//посчёт частоты
        t1=(int)(c2-c1)/(float)fr1;
        cout << "t"<< i << ": " << t1 <<endl;	//вывод времени
    }
    CloseHandle(fThread);	
    CloseHandle(sThread);
    return 0;
}

