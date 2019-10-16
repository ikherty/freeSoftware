#include <iostream>
#include <windows.h>
//#include <string>
using namespace std;

int readTXTfile(){  //read txt file
	//ofstream outfile("OutFile.txt");
	HANDLE inFile=CreateFile("InFil.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL);
	//дескриптор, т.е. число, с помощью которого можно идентифицировать ресурс
	if(INVALID_HANDLE_VALUE==inFile)
		cout<<"Can't open file\n";
	DWORD dwBytes=0, BufSize=0;
	BufSize = GetFileSize(inFile, NULL);
	char *Buffer = new char[BufSize/sizeof(char)];
	ReadFile(inFile,Buffer,BufSize,&dwBytes,NULL);
	Buffer[BufSize/sizeof(char)]='\0';
	HANDLE outFile=CreateFile("InFil.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL,NULL);
	WriteFile
	cout<<Buffer<<endl;
	CloseHandle(inFile);
}

int main(){
	readTXTfile();
	return 0;
}
