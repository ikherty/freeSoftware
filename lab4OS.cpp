// Реализовать следующую схему испытаний: испытывающий процесс, который
// замеряет время, запускает процесс с условно предсказуемы временем выполнения.
// Требуется выполнить измерения времени выполнения для 10, 20 и 30 последовательно
// запущенных однотипных процесса с предсказуемым временем выполнения. Провести
// статистический анализ измерений.

#include <cstdlib>
#include <windows.h>
//#include <ctime>
#include <iostream>

int main(){
	LARGE_INTEGER was, now, fr;
    double time; 
    bool bp;
    STARTUPINFO cif;
    PROCESS_INFORMATION pi;
    for(int i=0; i<3; i++){
        QueryPerformanceCounter(&was); 
		for(int j=0; j<(i+1)*10; j++){
                ZeroMemory(&cif,sizeof(STARTUPINFO));
				bp=CreateProcess("slep.exe",NULL,NULL,NULL,FALSE,CREATE_NEW_CONSOLE,NULL,NULL,&cif,&pi); 
				if(bp) 
					WaitForSingleObject(pi.hProcess, INFINITE);
        }
        QueryPerformanceCounter(&now);  
		QueryPerformanceFrequency(&fr);                
        time=(double)(now.QuadPart-was.QuadPart)/(double)fr.QuadPart;                             
		std::cout<<"\nTime for "<<(i+1)*10<<" = "<<time;  
    }
    return 0;
}
