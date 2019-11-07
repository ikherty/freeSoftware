/*Дан файл типа BYTE размером не менее 256 Кбайт. Скопировать этот файл во внешнюю память 10 раз поблочно. 
Размер читаемого блока - 1024 байта, размер записываемого блока принять кратным размеру читаемого блока. 
Характеристика: коэффициент кратности (1:2, 1:4, 1:8, 1:16).*/
#include <iostream>
#include <ctime>
#include <windows.h>
using namespace std;

#define FileSize 256*1024           //размер файла
#define N 1024                       //размеры блоков для чтения 
#define NN 1024						// и записи
#define M 20                        //сколько раз повторять для каждого размера блока

int main(){
srand(time(NULL));

byte *p;                    //адрес буфера
HANDLE DIF, DOF;              //дескрипторы файлов
__int64 c1, c2, fr;           //переменные для тактов пр-ра, частоты
DWORD c;
float averageTime,v;                    //время и скорость

IF=CreateFile((LPCTSTR)"InFil.txt", GENERIC_READ|GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);   
OF=CreateFile((LPCTSTR)"OutFil.txt", GENERIC_READ|GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);                      
	//имя
	//открываем для чтения или записи
	//совместное использование файла запрещено
	//здесь либо дескриптор защиты либо нул
	//даже если существует такой файл - перезаписать его
	//обычный файл (не скрытый и не какой-нибудь еще)
	//то же здесь можно указывать флаг для некот. случаев

if (IF==INVALID_HANDLE_VALUE || OF==INVALID_HANDLE_VALUE){ // если файлы не откррылись, то выход
		cout << "Ошибка" << GetLastError() << endl;
		cin.get();
		return 0;
	}

for (int i=0; i<FileSize/4; i++)
WriteFile(DIF,(LPVOID)rand(),4,&c,0);

if(WriteFile==0){
    cout<< "Ошибка" << GetLastError()<< endl;
    cin.get();
    return 0;
}

cout << "Size   |" << endl;
cout << "buf    | mb/s" <<endl;
cout << "change |" <<endl;

for (int i=128; i<=1024; i*=2){                  // Для всех размеров буфера обмена
 t=0.0;
 p=(byte *)GlobalAlloc(GPTR,i);              //выделение памяти под буфер
 for (int j=0; j<M; j++){
 	SetFilePointer(IF,0,NULL,FILE_BEGIN);     //установка файлового указателя в начало файла
 	SetFilePointer(OF,0,NULL,FILE_BEGIN);
	for (int k=0; k<FileSize/i; k++){                 //цикл столько раз, сколько блоков поместится в файле
  		QueryPerformanceCounter((LARGE_INTEGER *)&c1);   //функция возвращает некоторое кол-во тактов пр-ра на данный момент
  		ReadFile(DIF,p,i,&c,0);  //чтение в буфер
  		WriteFile(DOF,p,i,&c,0);
  		QueryPerformanceCounter((LARGE_INTEGER *)&c2);
  		QueryPerformanceFrequency((LARGE_INTEGER *)&fr); //чтение в буфер
  		t=t+(c2-c1)/(float)fr;                           //время
 	}
}

averageTime=averageTime/M;                                        // среднее время
v=FileSize/(1024*1024*t);                     // скорость MB/s
cout << i << "    | " << v << endl;
GlobalFree(p);                                //освобождение памяти, занятой буфером
}
//DeleteFile((LPCTSTR)"InFil.txt");
//DeleteFile((LPCTSTR)"OutFil.txt");

cin.get();
return 0;
}


