#include <fstream>
#include <iostream>
#include <windows.h>
using namespace std;

int readTXTfile(){//read txt file
    HANDLE hFile;//дескриптор, т.е. число, с помощью которого можно идентифицировать ресурс
    if(INVALID_HANDLE_VALUE==(hFile=CreateFile("D:\\new\\list.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL)))
        cout<<"Can't open file\n";
    DWORD dwBytes=0, BufSize=0;
    BufSize = GetFileSize(hFile, NULL);
    char *Buffer = new char[BufSize/sizeof(char)];
    ReadFile(hFile,Buffer,BufSize,&dwBytes,NULL);
    Buffer[BufSize/sizeof(char)]='\0';
    cout<<Buffer<<endl;
    CloseHandle(hFile);
}
int readWrite(){
    CString source; //в эту переменную нужно записать текст, который в дальнейшем поместится в буфер обмена
//запись текста в буфер обмена
if(OpenClipboard())//открываем буфер обмена
{
   HGLOBAL hgBuffer;
   char* chBuffer;
   EmptyClipboard(); //очищаем буфер
   hgBuffer= GlobalAlloc(GMEM_DDESHARE, source.GetLength()+1);//выделяем память
   chBuffer= (char*)GlobalLock(hgBuffer); //блокируем память
   strcpy(chBuffer, LPCSTR(source));
   GlobalUnlock(hgBuffer);//разблокируем память
   SetClipboardData(CF_TEXT, hgBuffer);//помещаем текст в буфер обмена
   CloseClipboard(); //закрываем буфер обмена
}
 
//чтение текста из буфера обмена
CString fromClipboard;//в эту переменную сохраним текст из буфера обмена
if ( OpenClipboard() )//открываем буфер обмена
{
   HANDLE hData = GetClipboardData(CF_TEXT);//извлекаем текст из буфера обмена
   char* chBuffer= (char*)GlobalLock(hData);//блокируем память
   fromClipboard = chBuffer;
   GlobalUnlock(hData);//разблокируем память
   CloseClipboard();//закрываем буфер обмена
}
}


int sampleWOwinAPI(){//coping file without winApi
    char * buffer;
    buffer = new char;
    ifstream infile("InFile.txt", ios::binary);
    ofstream outfile("OutFile.txt", ios::binary);
    if(!infile||!outfile){
        cout << "Oops...\n";
        return 1;
    }
    infile.read(buffer, sizeof(char));
    while (!infile.eof()){
        outfile.write(buffer, sizeof(char));
        infile.read(buffer, sizeof(char));
    }
    infile.close();
    outfile.close();
    delete buffer;
}

int main(){
    return 0;
}
