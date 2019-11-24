/*Дан файл типа BYTE размером не менее 256 Кбайт. Скопировать этот файл во внешнюю память 10 раз поблочно. 
Размер читаемого блока - 1024 байта, размер записываемого блока принять кратным размеру читаемого блока. 
Характеристика: коэффициент кратности (1:2, 1:4, 1:8, 1:16).*/
#include <iostream>
#include <windows.h>
using namespace std;

#define fileSize 256*1024                                   //размер файла
#define sizeReadBuff 1024                                           //размер читаемого блока

int main(){
byte *readBuff, *writeBuff;                                     //адреса буферов чтения и записи
HANDLE DIF, DOF;                                            //дескрипторы файлов
DWORD c;

DIF=CreateFile((LPCTSTR)"InFile.txt", GENERIC_READ|GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);   
DOF=CreateFile((LPCTSTR)"OutFile.txt", GENERIC_READ|GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);                      

if(DIF==INVALID_HANDLE_VALUE || DOF==INVALID_HANDLE_VALUE){  // если файлы не открылись, выходим
    cout << "Ошибка" << GetLastError() << endl;
    cin.get();
    return 0;
	}
	
byte *data[fileSize];                                        //рандомный массив для заполнения входного файла
for(int i=0; i<fileSize; i++){
    data[i]=(byte*)rand();
    }
WriteFile(DIF,(LPVOID)data,fileSize,&c,NULL);                //заполняем файл
SetFilePointer(DIF,0,NULL,FILE_BEGIN);	                     //установка файловых указателей в начала файлов
SetFilePointer(DOF,0,NULL,FILE_BEGIN);
    
//for(int sizeWriteBuff=sizeReadBuff/2; sizeWriteBuff>=sizeReadBuff/16; sizeWriteBuff/=2)
int sizeWriteBuff=512;
{ 
	//SetFilePointer(DIF,0,NULL,FILE_BEGIN);	
    readBuff=(byte*)GlobalAlloc(GMEM_FIXED,sizeReadBuff);          // Выделение памяти под буферы чтения, записи, обмена
    writeBuff=(byte*)GlobalAlloc(GMEM_FIXED,sizeWriteBuff);
   for(int kolvo=0; kolvo<fileSize/sizeReadBuff; kolvo++){
   	ReadFile(DIF,readBuff,sizeReadBuff,&c,0);  //считываем блок
        for(int k=0; k<sizeReadBuff/sizeWriteBuff;k++){			         //цикл столько раз, сколько блоков поместится в файле
                  CopyMemory(writeBuff,readBuff,sizeWriteBuff);         //записываем в буфер записи
                  WriteFile(DOF,writeBuff,sizeWriteBuff,&c,0);        //блок записываем в файл
                  GlobalFree(writeBuff);
        }
        GlobalFree(readBuff);                                  // Освобождение памяти, занятой буферами
        //GlobalFree(writeBuff);
    }
    cout<<"done for "<<sizeWriteBuff<<endl; 
    //DeleteFile("OutFile.txt");
}
//}
    CloseHandle(DIF);
    CloseHandle(DOF);
return 0;
}


