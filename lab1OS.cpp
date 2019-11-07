/*��� ���� ���� BYTE �������� �� ����� 256 �����. ����������� ���� ���� �� ������� ������ 10 ��� ��������. 
������ ��������� ����� - 1024 �����, ������ ������������� ����� ������� ������� ������� ��������� �����. 
��������������: ����������� ��������� (1:2, 1:4, 1:8, 1:16).*/
#include <iostream>
#include <ctime>
#include <windows.h>
using namespace std;

#define FileSize 256*1024           //������ �����
#define N 1024                       //������� ������ ��� ������ 
#define NN 1024						// � ������
#define M 20                        //������� ��� ��������� ��� ������� ������� �����

int main(){
srand(time(NULL));

byte *p;                    //����� ������
HANDLE DIF, DOF;              //����������� ������
__int64 c1, c2, fr;           //���������� ��� ������ ��-��, �������
DWORD c;
float averageTime,v;                    //����� � ��������

IF=CreateFile((LPCTSTR)"InFil.txt", GENERIC_READ|GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);   
OF=CreateFile((LPCTSTR)"OutFil.txt", GENERIC_READ|GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);                      
	//���
	//��������� ��� ������ ��� ������
	//���������� ������������� ����� ���������
	//����� ���� ���������� ������ ���� ���
	//���� ���� ���������� ����� ���� - ������������ ���
	//������� ���� (�� ������� � �� �����-������ ���)
	//�� �� ����� ����� ��������� ���� ��� �����. �������

if (IF==INVALID_HANDLE_VALUE || OF==INVALID_HANDLE_VALUE){ // ���� ����� �� ����������, �� �����
		cout << "������" << GetLastError() << endl;
		cin.get();
		return 0;
	}

for (int i=0; i<FileSize/4; i++)
WriteFile(DIF,(LPVOID)rand(),4,&c,0);

if(WriteFile==0){
    cout<< "������" << GetLastError()<< endl;
    cin.get();
    return 0;
}

cout << "Size   |" << endl;
cout << "buf    | mb/s" <<endl;
cout << "change |" <<endl;

for (int i=128; i<=1024; i*=2){                  // ��� ���� �������� ������ ������
 t=0.0;
 p=(byte *)GlobalAlloc(GPTR,i);              //��������� ������ ��� �����
 for (int j=0; j<M; j++){
 	SetFilePointer(IF,0,NULL,FILE_BEGIN);     //��������� ��������� ��������� � ������ �����
 	SetFilePointer(OF,0,NULL,FILE_BEGIN);
	for (int k=0; k<FileSize/i; k++){                 //���� ������� ���, ������� ������ ���������� � �����
  		QueryPerformanceCounter((LARGE_INTEGER *)&c1);   //������� ���������� ��������� ���-�� ������ ��-�� �� ������ ������
  		ReadFile(DIF,p,i,&c,0);  //������ � �����
  		WriteFile(DOF,p,i,&c,0);
  		QueryPerformanceCounter((LARGE_INTEGER *)&c2);
  		QueryPerformanceFrequency((LARGE_INTEGER *)&fr); //������ � �����
  		t=t+(c2-c1)/(float)fr;                           //�����
 	}
}

averageTime=averageTime/M;                                        // ������� �����
v=FileSize/(1024*1024*t);                     // �������� MB/s
cout << i << "    | " << v << endl;
GlobalFree(p);                                //������������ ������, ������� �������
}
//DeleteFile((LPCTSTR)"InFil.txt");
//DeleteFile((LPCTSTR)"OutFil.txt");

cin.get();
return 0;
}


