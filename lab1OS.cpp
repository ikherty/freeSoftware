/*��� ���� ���� BYTE �������� �� ����� 256 �����. ����������� ���� ���� �� ������� ������ 10 ��� ��������. 
������ ��������� ����� - 1024 �����, ������ ������������� ����� ������� ������� ������� ��������� �����. 
��������������: ����������� ��������� (1:2, 1:4, 1:8, 1:16).*/
#include <iostream>
#include <ctime>
#include <windows.h>
using namespace std;

#define FileSize 256*1024           //������ �����
#define block 1024

int main(){
srand(time(NULL));

byte *read_b, *write_b;       //������ ������� ������ � ������
HANDLE DIF, DOF;              //����������� ������
__int64 c1, c2, fr;           //���������� ��� ������ ��-��, �������
DWORD c;
float averageTime,speed;                    //����� � ��������

DIF=CreateFile((LPCTSTR)"InFil.txt", GENERIC_READ|GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);   
DOF=CreateFile((LPCTSTR)"OutFil.txt", GENERIC_READ|GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);                      
	//���
	//��������� ��� ������ ��� ������
	//���������� ������������� ����� ���������
	//����� ���� ���������� ������ ���� ���
	//���� ���� ���������� ����� ���� - ������������ ���
	//������� ���� (�� ������� � �� �����-������ ���)
	//�� �� ����� ����� ��������� ���� ��� �����. �������

if(DIF==INVALID_HANDLE_VALUE || DOF==INVALID_HANDLE_VALUE){ // ���� ����� �� ���������, �������
    cout << "������" << GetLastError() << endl;
    cin.get();
    return 0;
	}
	
byte *data[FileSize]; //��������� ������ ��� ���������� �����
for(int i=0; i<FileSize; i++){
    data[i]=(byte*)rand();
    }
WriteFile(DIF,(LPVOID)data,FileSize,&c,NULL); //��������� ����

for(int sz_buf=512; sz_buf>=64; sz_buf/=2){                  // ��������� ������� ������ � 2 ����
    read_b=(byte*)GlobalAlloc(GMEM_FIXED,1024);              // ��������� ������ ��� ������ ������, ������, ������
    write_b=(byte*)GlobalAlloc(GMEM_FIXED,sz_buf);
    SetFilePointer(DIF,0,NULL,FILE_BEGIN);	                  //��������� �������� ���������� � ������ ������
    SetFilePointer(DOF,0,NULL,FILE_BEGIN);  

         for(int k=0; k<FileSize/block;){			//���� ������� ���, ������� ������ ���������� � �����
              if(block > sz_buf) {  //���� ������ ������ ������ ������� ����� ������
                  ReadFile(DIF,read_b,block,&c,0); //��������� ����
                  k++;
                  for (int n=0; n<block/sz_buf; n++) { //����� ���� ������ �� ��������� ������, ������ ������� ����� ������� ������ ������
                      CopyMemory(write_b,read_b,sz_buf); //���������� � ����� ������
                  }
                  WriteFile(DOF,write_b,block,&c,0); //���� ���������� � ����
              }
        }
/*!!      float t=clock();
!!        cout<<sz_buf<<" ����: ";
!!        t=(clock()-t)/CLOCKS_PER_SEC;//��� ����� �������
!!        cout<<" t = "<<t<<endl; 
!!        cout<<"�����/� = "<<500/t<<endl<<endl;*/ 
        GlobalFree(read_b);// ������������ ������, ������� ��������
        GlobalFree(write_b);
    }
/*
for(int i=0; i<FileSize/4; i++)
	WriteFile(DIF,(LPVOID)rand(),4,&c,0);

if(WriteFile==0){
    cout<< "������" << GetLastError()<< endl;
    cin.get();
    return 0;
}

cout << "Size   |" << endl;
cout << "buf    | mb/s" <<endl;
cout << "change |" <<endl;

for(int i=128; i<=1024; i*=2){                  // ��� ���� �������� ������ ������
 averageTime=0.0;
 p=(byte *)GlobalAlloc(GPTR,i);              //��������� ������ ��� �����
 for(int j=0; j<M; j++){
 	SetFilePointer(DIF,0,NULL,FILE_BEGIN);     //��������� ��������� ��������� � ������ �����
 	SetFilePointer(DOF,0,NULL,FILE_BEGIN);
	for(int k=0; k<FileSize/i; k++){                 //���� ������� ���, ������� ������ ���������� � �����
  		QueryPerformanceCounter((LARGE_INTEGER *)&c1);   //������� ���������� ��������� ���-�� ������ ��-�� �� ������ ������
  		ReadFile(DIF,p,i,&c,0);  //������ � �����
  		WriteFile(DOF,p,i,&c,0);
  		QueryPerformanceCounter((LARGE_INTEGER *)&c2);
  		QueryPerformanceFrequency((LARGE_INTEGER *)&fr); //������ � �����
  		averageTime=averageTime+(c2-c1)/(float)fr;                           //�����
 	}
}

averageTime=averageTime/M;                                  // ������� �����
speed=FileSize/(1024*1024*averageTime);                     // �������� MB/s
cout<<i<<"    | "<<speed<<endl;
GlobalFree(p);                                				//������������ ������, ������� �������
}*/


    CloseHandle(DIF);
    CloseHandle(DOF);
//DeleteFile((LPCTSTR)"InFil.txt");
//DeleteFile((LPCTSTR)"OutFil.txt");

cin.get();
return 0;
}


