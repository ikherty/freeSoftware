/*Дан файл типа BYTE размером не менее 256 Кбайт. Скопировать этот файл во внешнюю память 10 раз поблочно. 
Размер читаемого блока - 1024 байта, размер записываемого блока принять кратным размеру читаемого блока. 
Характеристика: коэффициент кратности (1:2, 1:4, 1:8, 1:16).*/
#include <iostream>
#include <ctime>
#include <windows.h>
using namespace std;

#define FileSize 256*1024           //размер файла
#define block 1024

int main(){
srand(time(NULL));

byte *read_b, *write_b;       //адреса буферов чтения и записи
HANDLE DIF, DOF;              //дескрипторы файлов
__int64 c1, c2, fr;           //переменные для тактов пр-ра, частоты
DWORD c;
float averageTime,speed;                    //время и скорость

DIF=CreateFile((LPCTSTR)"InFil.txt", GENERIC_READ|GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);   
DOF=CreateFile((LPCTSTR)"OutFil.txt", GENERIC_READ|GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);                      
	//имя
	//открываем для чтения или записи
	//совместное использование файла запрещено
	//здесь либо дескриптор защиты либо нул
	//даже если существует такой файл - перезаписать его
	//обычный файл (не скрытый и не какой-нибудь еще)
	//то же здесь можно указывать флаг для некот. случаев

if(DIF==INVALID_HANDLE_VALUE || DOF==INVALID_HANDLE_VALUE){ // если файлы не открылись, выходим
    cout << "Ошибка" << GetLastError() << endl;
    cin.get();
    return 0;
	}
	
byte *data[FileSize]; //рандомный массив для заполнения файла
for(int i=0; i<FileSize; i++){
    data[i]=(byte*)rand();
    }
WriteFile(DIF,(LPVOID)data,FileSize,&c,NULL); //заполняем файл

for(int sz_buf=512; sz_buf>=64; sz_buf/=2){                  // Изменение размера буфера в 2 раза
    read_b=(byte*)GlobalAlloc(GMEM_FIXED,1024);              // Выделение памяти под буферы чтения, записи, обмена
    write_b=(byte*)GlobalAlloc(GMEM_FIXED,sz_buf);
    SetFilePointer(DIF,0,NULL,FILE_BEGIN);	                  //установка файловых указателей в начала файлов
    SetFilePointer(DOF,0,NULL,FILE_BEGIN);  

         for(int k=0; k<FileSize/block;){			//цикл столько раз, сколько блоков поместится в файле
              if(block > sz_buf) {  //если размер буфера меньше размера блока чтения
                  ReadFile(DIF,read_b,block,&c,0); //считываем блок
                  k++;
                  for (int n=0; n<block/sz_buf; n++) { //делим блок чтения на несколько мелких, размер которых равен размеру буфера записи
                      CopyMemory(write_b,read_b,sz_buf); //записываем в буфер записи
                  }
                  WriteFile(DOF,write_b,block,&c,0); //блок записываем в файл
              }
        }
/*!!      float t=clock();
!!        cout<<sz_buf<<" байт: ";
!!        t=(clock()-t)/CLOCKS_PER_SEC;//для счета времени
!!        cout<<" t = "<<t<<endl; 
!!        cout<<"Кбайт/с = "<<500/t<<endl<<endl;*/ 
        GlobalFree(read_b);// Освобождение памяти, занятой буферами
        GlobalFree(write_b);
    }
/*
for(int i=0; i<FileSize/4; i++)
	WriteFile(DIF,(LPVOID)rand(),4,&c,0);

if(WriteFile==0){
    cout<< "Ошибка" << GetLastError()<< endl;
    cin.get();
    return 0;
}

cout << "Size   |" << endl;
cout << "buf    | mb/s" <<endl;
cout << "change |" <<endl;

for(int i=128; i<=1024; i*=2){                  // Для всех размеров буфера обмена
 averageTime=0.0;
 p=(byte *)GlobalAlloc(GPTR,i);              //выделение памяти под буфер
 for(int j=0; j<M; j++){
 	SetFilePointer(DIF,0,NULL,FILE_BEGIN);     //установка файлового указателя в начало файла
 	SetFilePointer(DOF,0,NULL,FILE_BEGIN);
	for(int k=0; k<FileSize/i; k++){                 //цикл столько раз, сколько блоков поместится в файле
  		QueryPerformanceCounter((LARGE_INTEGER *)&c1);   //функция возвращает некоторое кол-во тактов пр-ра на данный момент
  		ReadFile(DIF,p,i,&c,0);  //чтение в буфер
  		WriteFile(DOF,p,i,&c,0);
  		QueryPerformanceCounter((LARGE_INTEGER *)&c2);
  		QueryPerformanceFrequency((LARGE_INTEGER *)&fr); //чтение в буфер
  		averageTime=averageTime+(c2-c1)/(float)fr;                           //время
 	}
}

averageTime=averageTime/M;                                  // среднее время
speed=FileSize/(1024*1024*averageTime);                     // скорость MB/s
cout<<i<<"    | "<<speed<<endl;
GlobalFree(p);                                				//освобождение памяти, занятой буфером
}*/


    CloseHandle(DIF);
    CloseHandle(DOF);
//DeleteFile((LPCTSTR)"InFil.txt");
//DeleteFile((LPCTSTR)"OutFil.txt");

cin.get();
return 0;
}


