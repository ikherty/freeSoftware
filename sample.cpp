#include <iostream>
#include <ctime>
#include <windows.h>
using namespace std;
 
#define ArraySize 256*1024           //размер файла
#define N 1024                       //размер блока для чтения 
#define M 10                        //сколько раз повторять для каждого размера блока
 
int main()
{
srand(time(NULL));
 
int i, j, k;
byte *p;
HANDLE data1, data2;                  //дескрипторы файлов
__int64 c1, c2, fr;           //переменные для тактов пр-ра, частоты
DWORD c;
float t,v;                    //время и скорость
 
BYTE A[ArraySize];
 for(int i=0;i<ArraySize;i++)
 {
 A[i]=0;
 };
 
data1=CreateFile((LPCTSTR)"data1.dat", GENERIC_READ|GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);   
data2=CreateFile((LPCTSTR)"data2.dat", GENERIC_READ|GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);                      
    //имя
    //открываем для чтения или записи
    //совместное использование файла запрещено
    //здесь либо дескриптор защиты либо нул
    //даже если существует такой файл - перезаписать его
    //обычный файл (не скрытый и не какой-нибудь еще)
    //то же здесь можно указывать флаг для некот. случаев
 
if (data1==INVALID_HANDLE_VALUE || data2==INVALID_HANDLE_VALUE) // если файлы не отркрылись, то выход
    {
        cout << "Ошибка" << GetLastError() << endl;
        cin.get();
        return 0;
    }
 
for (i=0; i<ArraySize/4; i++)
WriteFile(data1,(LPVOID)rand(),4,&c,0);
 
if(WriteFile==0)
 {
    cout<< "Ошибка" << GetLastError()<< endl;
    cin.get();
    return 0;
}
 
cout << "Size   |" << endl;
cout << "buf    | mb/s" <<endl;
cout << "change |" <<endl;
 
for (i=128; i<=1024; i*=2)                  // Для всех размеров буфера обмена
{
 t=0.0;
 p=(byte *)GlobalAlloc(GPTR,i);              //выделение памяти под буфер
for (j=0; j<M; j++)
{
 SetFilePointer(data1,0,NULL,FILE_BEGIN);     //установка файлового указателя в начало файла
 SetFilePointer(data2,0,NULL,FILE_BEGIN);
for (k=0; k<ArraySize/i; k++)                 //цикл столько раз, сколько блоков поместится в файле
 {
  QueryPerformanceCounter((LARGE_INTEGER *)&c1);   //функция возвращает некоторое кол-во тактов пр-ра на данный момент
  ReadFile(data1,p,i,&c,0);  //чтение в буфер
  WriteFile(data2,p,i,&c,0);
  QueryPerformanceCounter((LARGE_INTEGER *)&c2);
  QueryPerformanceFrequency((LARGE_INTEGER *)&fr); //чтение в буфер
  t=t+(c2-c1)/(float)fr;                           //время
 }
 
}
t=t/M;                                        // среднее время
v=ArraySize/(1024*1024*t);                     // скорость MB/s
cout << i << "    | " << v << endl;
GlobalFree(p);                                //освобождение памяти, занятой буфером
}
DeleteFile((LPCTSTR)"data1.dat");
DeleteFile((LPCTSTR)"data2.dat");
 
cin.get();
return 0;
}
