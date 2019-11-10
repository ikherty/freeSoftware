/*создание тестового файла типа BYTE размером 256 Кбайт*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <windows.h>
#include <stdint.h>
using namespace std;

int main(){
    ofstream outfile("InFile.txt");
    byte arr[262180];
    for(int i=0;i<262180;i++){
        arr[i]=rand();
        outfile<<arr[i];
    }
    outfile.close();
    return 0;
}
