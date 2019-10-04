/*копирование входного файла в выходной*/
#include <fstream>
#include <iostream>
using namespace std;
 
int main(){
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
    return 0;
}
