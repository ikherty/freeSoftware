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
}

void create1Kfile(){//б)
    HANDLE DIF;
    DIF=CreateFile((LPCTSTR)"1KFile.txt", GENERIC_READ|GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);   
    byte *data[1024];                                        //рандомный массив для заполнения входного файла
    for(int i=0; i<1024; i++){
        data[i]=(byte*)rand();
    }
    WriteFile(DIF,(LPVOID)data,fileSize,&c,NULL); 
}

int main(){
    __int64 c1, c2, c3, c4, fr1,fr2;			//переменные для ф-лы счётчика
    double t1=0, t2=0;
    LPDWORD ID;
    HANDLE fThread[3000], sThread[3000], tThread[3000];			//дескрипторы потоков

    //cout << "Suspend_________|NOP_________\n";
    for (int i=0; i<10; i++)		//повторение 10 раз
    {
        QueryPerformanceCounter((LARGE_INTEGER *)&c1);				//начало отсчёта времени
        for (int j=0; j<3000; j++){
            fThread[j]=CreateThread(NULL,0, NULL, NULL, CREATE_SUSPENDED, (LPDWORD)&ID);
                  //Null-указатель на поток не может быть унаследованн
                  //0-размер стека будет установлен таким же как и для основного потока процесса
                  //начальный адрес потока
                  //m - это значение которое мы передаем в ThreadFunc в качестве параметра
                  //CREATE_SUSPENDED - создан приостановленным
                  //параметр, в котором будет возвращен идентификатор потока.
            CloseHandle(nThread[j]);										//завершение потока
        }
        //ResumeThread(sThread);    //функция приостанавливает 2й поток
        //ResumeThread(tThread);    //функция приостанавливает 3й поток
        QueryPerformanceCounter((LARGE_INTEGER *)&c2);					//конец отсчёта времени
        QueryPerformanceFrequency((LARGE_INTEGER *)&fr1);				//посчёт частоты
        t1=(int)(c2-c1)/(float)fr1;

        QueryPerformanceCounter((LARGE_INTEGER *)&c3);				//начало отсчёта времени
        for (int k=0; k<3000; k++)        {
            tThread[k]=CreateThread(NULL,0, (LPTHREAD_START_ROUTINE)create0Kfile, NULL, NULL, (LPDWORD)&ID);
                  //ThreadFuncNOP - функция, которую передаем потоку
            CloseHandle(hThread[k]);										//завершение потока
        }

        QueryPerformanceCounter((LARGE_INTEGER *)&c4);					//конец отсчёта времени
        QueryPerformanceFrequency((LARGE_INTEGER *)&fr2);				//посчёт частоты
        t2=(int)(c4-c3)/(float)fr2;
        cout << "t"<< i+1 << ":" << t1 << "     "<< "t"<< i+1 << ":" << t2<<endl;	//вывод времени
    }

    return 0;
}


/*Основой поток создает другой поток, передавая ему параметр. Параметр может принимать два значения: 0 или 1.
 * Если параметр равен 0, то поток организует задержку в 10 мс и завершает свое выполнение. 
 * Если параметр равен 1, то второй поток создает третий поток, который содержит единственную ассемблерную операцию NOP.
 * Измерить время исполнения  второго потока в обоих случаях. Измерения повторить 10 раз.*/

/*int main(){
    __int64 c1, c2, c3, c4, fr1,fr2;			//переменные для ф-лы счётчика
    double t1=0, t2=0;
    LPDWORD ID;
    HANDLE nThread[3000],hThread[3000];			//дескрипторы потоков

    cout << "Suspend_________|NOP_________\n";
    for (int i=0; i<10; i++)		//повторение 10 раз
    {
        QueryPerformanceCounter((LARGE_INTEGER *)&c1);				//начало отсчёта времени
        for (int j=0; j<3000; j++)
        {
            nThread[j]=CreateThread(NULL,0, NULL, NULL, CREATE_SUSPENDED, (LPDWORD)&ID);
                  //Null-указатель на поток не может быть унаследованн
                  //0-размер стека будет установлен таким же как и для основного потока процесса
                  //начальный адрес потока
                  //m - это значение которое мы передаем в ThreadFunc в качестве параметра
                  //CREATE_SUSPENDED - создан приостановленным
                  //параметр, в котором будет возвращен идентификатор потока.
            CloseHandle(nThread[j]);										//завершение потока
        }
        QueryPerformanceCounter((LARGE_INTEGER *)&c2);					//конец отсчёта времени
        QueryPerformanceFrequency((LARGE_INTEGER *)&fr1);				//посчёт частоты
        t1=(int)(c2-c1)/(float)fr1;

        QueryPerformanceCounter((LARGE_INTEGER *)&c3);				//начало отсчёта времени
        for (int k=0; k<3000; k++)
        {
            hThread[k]=CreateThread(NULL,0, (LPTHREAD_START_ROUTINE)ThreadFuncNOP, NULL, NULL, (LPDWORD)&ID);
                  //ThreadFuncNOP - функция, которую передаем потоку
            CloseHandle(hThread[k]);										//завершение потока
        }

        QueryPerformanceCounter((LARGE_INTEGER *)&c4);					//конец отсчёта времени
        QueryPerformanceFrequency((LARGE_INTEGER *)&fr2);				//посчёт частоты
        t2=(int)(c4-c3)/(float)fr2;
        cout << "t"<< i+1 << ":" << t1 << "     "<< "t"<< i+1 << ":" << t2<<endl;	//вывод времени
    }

    return 0;
}
*/
