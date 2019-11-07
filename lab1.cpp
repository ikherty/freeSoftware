#include <iostream>
#include <windows.h>
#include <cstring>
using namespace std;

int readfromFile(){
HFILE              hFile;
//Имя читаемого файла
string vasFileName="InFile.txt";
DWORD              vwCounter;
int                *virgRDWRBuff;
BY_HANDLE_FILE_INFORMATION bhFileInformation;
OFSTRUCT tOfStr;
tOfStr.cBytes = sizeof tOfStr;

//Открываем файл и заполняем информацией tOfStr
    hFile = OpenFile(
    vasFileName.c_str(), // имя файла, преобразуемое к типу char*
    &tOfStr,             //указатель на буфер  с информацией о файле
    OF_READWRITE);       // файл открыт для чтения и записи
    if(hFile == HFILE_ERROR){
 //Здесь может быть сообщение об ощибке
        CloseHandle(HANDLE(hFile));
        return 0;
    }
//Теперь можно получить информацию о файле
    GetFileInformationByHandle(
    HANDLE(hFile),     // дескриптор файла
    &bhFileInformation //адрес структуры, в которой сохраняется информация
    );
//Резервируем память для всего файла обычно размер файла
//не больше  размера nFileSizeLow объявленного как DWORD
    int viSize=bhFileInformation.nFileSizeLow/sizeof(int);
    virgRDWRBuff = (int*) new int[viSize];
//Сдвигаем указатель на нужный байт - сдесь на начало
    if(_llseek(hFile,0*sizeof(int),0) != (long)(0*sizeof(int))){
        CloseHandle(HANDLE(hFile));
 //Здесь может быть сообщение об ошибке
        return 0;
    }
//Считать данные из файла
    if(!ReadFile(HANDLE(hFile),virgRDWRBuff,(DWORD)viSize*sizeof(int),&vwCounter,NULL)){
 //Здесь может быть сообщение об ошибке
    }
    else{
        if(vwCounter == (DWORD)viSize*sizeof(int)){
  //Используем информацию
            int viRez=virgRDWRBuff[99];
        }else{
  //Здесь может быть сообщение об ошибке
        }
    }
    CloseHandle(HANDLE(hFile));
    delete[] virgRDWRBuff;
/*В тексте объявляются две структуры. Первая, BY_HANDLE_FILE_INFORMATION, нужна для хранения полезной информации о файле. Вторая, OFSTRUCT требуется для работы функции API OpenFile(). Далее идет инициализация поля размера этой структуры.

Далее - создание буфера, в который будут скопированы данные, считанные из файла. Можно проделать расчет, основанный на размере файла, но можно поступить проще: задать размер принудительно, например 64 Кбайт. Для создания такого буфера можно использовать задание типа new char[0xfffe], выделяющей блок памяти подходящего размера. В конце обработчика необходимо освободить блок памяти операцией delete[].

Само чтение происходит в несколько этапапов: открытие файла, получение его размера, сдвиг на нужную позицию и собственно чтение.

Полученный дескриптор функцией OpenFile() открытого файла необходимо передать в качестве параметра для другой функции API - GetFileInformationByHandle(), которая заполняет структуру bhFileInformation типа BY_HANDLE_FILE_INFORMATION, переданную в качестве второго параметра, данными об открытом файле. В этой структуре имеются два поля, хранящие старшие и младшие четыре байта размера файла. Для малого файла хватает и младших четырех байтов.

Первые два параметра - это дескриптор читаемого файла и адрес буфера, в который будут считаны данные. Четвертый параметр функции - счетчик байтов, в который ReadFile() записывает количество байтов, считанных из файла.

Пятый параметр игнорируется.

Обратим внимание на то, что для правильной работы дескриптор файла надо преобразовывать к типу HANDLE.

При работе в переменной появятся данные из файла.*/
}

int main(){
	readfromFile();
	return 0;
}

int writetoFile(){
    HFILE              hFile;
string vasFileName="InFil.txt";
DWORD              vwCounter;
int                *virgRDWRBuff;
BY_HANDLE_FILE_INFORMATION bhFileInformation;
OFSTRUCT tOfStr;
tOfStr.cBytes = sizeof tOfStr;
//Открываем файл и заполняем информацией tOfStr
hFile = OpenFile(
 vasFileName.c_str(), // имя файла, преобразуемое к типу char*
 &tOfStr,             //указатель на буфер  с информацией о файле
 OF_READWRITE);       // файл открыт для чтения и записи
if(hFile == HFILE_ERROR){
 //Здесь может быть сообщение об ощибке
 CloseHandle(HANDLE(hFile));
return 0;
}
//Теперь можно получить информацию о файле, но понадобиться она 
//может только для того, чтобы не записать за пределы файла, хотя и 
//это не страшно, файл просто увеличится в размере
GetFileInformationByHandle
(
 HANDLE(hFile),     // дескриптор файла
 &bhFileInformation //адрес структуры, в которой сохраняется информация
);
//Резервировать память для всего файла обычно при записи нет необходимости
//так как известно сколько будем писать, например 100 чисел
int viSize=100;
virgRDWRBuff = (int*) new int[viSize];
//Сдвигаем указатель на нужный байт - сдесь на начало
if(_llseek(hFile,0*sizeof(int),0) != (long)(0*sizeof(int))){
 CloseHandle(HANDLE(hFile));
 //Здесь может быть сообщение об ошибке
 return 0;
}
//Пишем данные в буфер
for(int i=0; i < 100; i++) virgRDWRBuff[99-i]=i;
//Переносим содержимое буфера в файл
if(!WriteFile(HANDLE(hFile),virgRDWRBuff,(DWORD)viSize*sizeof(int),&vwCounter,NULL)){
 //Здесь может быть сообщение об ошибке
}
else{
 if(vwCounter == (DWORD)viSize*sizeof(int)){
  //Запись прошла успешно

 }else{
  //Здесь может быть сообщение об ошибке
 }
}
CloseHandle(HANDLE(hFile));
delete[] virgRDWRBuff;
}

int main(){
    readfromFile();
	//writetoFile();
	return 0;
}
