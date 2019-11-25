/*Дан файл типа BYTE размером не менее 256 Кбайт. Скопировать этот файл во внешнюю память 10 раз поблочно. 
Размер читаемого блока - 1024 байта, размер записываемого блока принять кратным размеру читаемого блока. 
Характеристика: коэффициент кратности (1:2, 1:4, 1:8, 1:16).*/
#include <iostream>
#include <windows.h>
#include <ctime>
using namespace std;

#define fileSize 256*1024                                   //размер файла
#define sizeReadBuff 1024                                   //размер читаемого блока

int main(){
srand(time(NULL));
byte *readBuff, *writeBuff;                                 //адреса буферов чтения и записи
HANDLE DIF, DOF;                                            //дескрипторы файлов
DWORD c;                                                    //число прочитанных файлов

DIF=CreateFile((LPCTSTR)"InFile.txt", GENERIC_READ|GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);   
DOF=CreateFile((LPCTSTR)"OutFile.txt", GENERIC_READ|GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
              
if(DIF==INVALID_HANDLE_VALUE || DOF==INVALID_HANDLE_VALUE){  //если файлы не открылись, выходим
    cout << "Ошибка" << GetLastError() << endl;
    cin.get();
    return 0;
	}
	
byte *data[fileSize];                                        //рандомный массив для заполнения входного файла
for(int i=0; i<fileSize; i++){
    data[i]=(byte*)rand();
    }
WriteFile(DIF,(LPVOID)data,fileSize,&c,NULL);                //заполняем файл
SetFilePointer(DOF,0,NULL,FILE_BEGIN);                       //установка файлового указателя в начала файла
readBuff=(byte*)GlobalAlloc(GMEM_FIXED,sizeReadBuff);        //выделение памяти под буферы чтения, записи, обмена
    
for(int sizeWriteBuff=sizeReadBuff/2; sizeWriteBuff>=sizeReadBuff/16; sizeWriteBuff/=2){ 
    float t=clock();
	cout<<"sizeWriteBuff="<<sizeWriteBuff<<endl;
	writeBuff=(byte*)GlobalAlloc(GMEM_FIXED,sizeWriteBuff);
	SetFilePointer(DIF,0,NULL,FILE_BEGIN);
    for(int i=0; i<fileSize/sizeReadBuff; i++){              //сколько блоков поместится в файле
   	ReadFile(DIF,readBuff,sizeReadBuff,&c,0);                //считываем блок
        for(int k=0; k<sizeReadBuff/sizeWriteBuff;k++){      //кратность буфера записи к буферу чтения
                  CopyMemory(writeBuff,readBuff+sizeWriteBuff*k,sizeWriteBuff); //записываем в буфер записи
                  WriteFile(DOF,writeBuff,sizeWriteBuff,&c,0); //блок записываем в файл
        }                    
    }
    t=(clock()-t)/CLOCKS_PER_SEC;
    cout<<" t = "<<t<<endl; 
    cout<<" kb/s = "<<500/t<<endl;                           //время
    cout<<"done for "<<sizeWriteBuff<<endl<<endl; 
    GlobalFree(writeBuff);                                   //освобождение памяти, занятой буфером
}
GlobalFree(readBuff);
CloseHandle(DIF);
CloseHandle(DOF);
return 0;
}


