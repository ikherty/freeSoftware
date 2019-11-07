// ÑÏÎ¹2.cpp : Defines the entry point for the console application.
//

#include<iostream>
#include<windows.h> 
#include<conio.h>
using namespace std;

int main( void )
{
    
	int arraySize, maxSize, minSize;
	arraySize = 256*1024;
	maxSize = 512;
	minSize = 1;

	BYTE A[256*1024];
	LPCWSTR fileName = L"InFil.txt";

	BYTE *buffer;
	HANDLE fileHandler;
	LARGE_INTEGER tc1, tc2, tc3, tfr;
	LARGE_INTEGER *pc1 = &tc1;
	LARGE_INTEGER *pc2 = &tc2;
	LARGE_INTEGER *pfr = &tfr;
	DWORD *t = new DWORD ;

	int i;

	for(i=0; i<arraySize; i++)
	{
		A[i]=0;    
	}

	fileHandler = CreateFile(fileName,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);

	if(fileHandler == INVALID_HANDLE_VALUE){
		cout << "Error creating the file!";
		getch();
		return 1;
	}

	int currentSize = minSize;

	double time = 0;
	double speed,
		   transferTime,
		   totalTime = 0;
	printf(" ---------------------------------\n");
	printf("| Buffer (bytes) | Speed (kb/sec) |\n");
	printf(" ---------------------------------\n");
	while(currentSize <= maxSize){
		for (int j=0; j<10; j++){
			if( SetFilePointer(fileHandler, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER ){
				cout << "File navigate error!";
				return 3;
			}
			QueryPerformanceCounter(pc1);

			for(int n=0; n <arraySize/currentSize; n++)
			{
				buffer = (BYTE *)GlobalAlloc(GPTR, currentSize);
				CopyMemory(buffer, A+n*currentSize, currentSize);
				ReadFile(fileHandler, buffer, currentSize, t, NULL);
				if((int)t < currentSize) {
					cout << "Eror occured while allocating disk space...";
					return 2;
				}
				GlobalFree(buffer);
			}

			QueryPerformanceCounter(pc2);
			QueryPerformanceFrequency(pfr);

			time = (double)( tc2.QuadPart-tc1.QuadPart ) / tfr.QuadPart;
			totalTime += time;
		}
		double transferTime=totalTime / 10;

		speed = arraySize / ( 1024 * transferTime );
			printf("|%15d | %14d |\n", currentSize,(long int)speed);
		if(currentSize == maxSize)
		{
			printf(" _________________________________\n");
		}

		totalTime    = 0;
		time         = 0;
		currentSize *= 2;

	}
	getch();
	DeleteFile(fileName);
	GlobalFree(fileHandler);
	return 0;
}


