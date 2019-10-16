#include <iostream>
#include <windows.h>
//#include <string>
using namespace std;

int readTXTfile(){  //read txt file
	//ofstream outfile("OutFile.txt");
	HANDLE hFile=CreateFile("InFil.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL);
	//дескриптор, т.е. число, с помощью которого можно идентифицировать ресурс
	if(INVALID_HANDLE_VALUE==hFile)
		cout<<"Can't open file\n";
	DWORD dwBytes=0, BufSize=0;
	BufSize = GetFileSize(hFile, NULL);
	char *Buffer = new char[BufSize/sizeof(char)];
	ReadFile(hFile,Buffer,BufSize,&dwBytes,NULL);
	Buffer[BufSize/sizeof(char)]='\0';
	cout<<Buffer<<endl;
	CloseHandle(hFile);
}

int main(){
	readTXTfile();
	return 0;
}
