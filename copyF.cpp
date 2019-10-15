#include <fstream>
#include <iostream>
#include <windows.h>
#include <string>
#include <winbase.h>
#include <winuser.h>
//#include <atlstr.h>
using namespace std;

int readTXTfile() //read txt file
{
	ofstream outfile("OutFile.txt");
	HANDLE hFile;//дескриптор, т.е. число, с помощью которого можно идентифицировать ресурс
	if(INVALID_HANDLE_VALUE==(hFile=CreateFile("InFile.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL)))
		cout<<"Can't open file\n";
	DWORD dwBytes=0, BufSize=0;
	BufSize = GetFileSize(hFile, NULL);
	char *Buffer = new char[BufSize/sizeof(char)];
	ReadFile(hFile,Buffer,BufSize,&dwBytes,NULL);
	Buffer[BufSize/sizeof(char)]='\0';
	//cout<<Buffer<<endl;
	outfile<<Buffer;
	CloseHandle(hFile);
	outfile.close();
}

int readWrite(){
	string source; //в эту переменную нужно записать текст, который в дальнейшем поместится в буфер обмена
//запись текста в буфер обмена
	//if(OpenClipboard()) 
	{ //открываем буфер обмена
		HGLOBAL hgBuffer;
		char* chBuffer;
		EmptyClipboard(); //очищаем буфер
		hgBuffer= GlobalAlloc(GMEM_DDESHARE, source.length()+1);//выделяем память
		chBuffer= (char*)GlobalLock(hgBuffer); //блокируем память
		strcpy(chBuffer, LPCSTR(source));
		GlobalUnlock(hgBuffer);//разблокируем память
		SetClipboardData(CF_TEXT, hgBuffer);//помещаем текст в буфер обмена
		CloseClipboard(); //закрываем буфер обмена
	}
//чтение текста из буфера обмена
	String fromClipboard;//в эту переменную сохраним текст из буфера обмена
	if ( OpenClipboard() ) { //открываем буфер обмена
		HANDLE hData = GetClipboardData(CF_TEXT);//извлекаем текст из буфера обмена
		char* chBuffer= (char*)GlobalLock(hData);//блокируем память
		fromClipboard = chBuffer;
		GlobalUnlock(hData);//разблокируем память
		CloseClipboard();//закрываем буфер обмена
	}
}

void toClipboard(const std::wstring &s){
OpenClipboard(0);
EmptyClipboard();
HGLOBAL hg=GlobalAlloc(GMEM_MOVEABLE,s.size()*sizeof(wchar_t));
if (!hg){
CloseClipboard();
return;
}
memcpy(GlobalLock(hg),s.c_str(),s.size()*sizeof(wchar_t));
GlobalUnlock(hg);
SetClipboardData(CF_UNICODETEXT,hg);
CloseClipboard();
GlobalFree(hg);
}

void fromClipboard(std::wstring &s){
if( OpenClipboard( hwnd )){
HGLOBAL hg = GetClipboardData( CF_UNICODETEXT );
if( hg ){
unsigned int sz = GlobalSize( hg );
void* memory = GlobalLock( hg );
const wchar_t* text = reinterpret_cast(memory);
unsigned int cc = static_cast(wcsnlen(text, sz / sizeof(wchar_t)));
if( memory ){
s = text;
for( unsigned int i = 0; i < s.size(); ++i ){
if( s[i] == 0xA ){
if( i > 0 ){
if( s[i-1] != L'\r' ){
s.insert( s.begin()+i, L'\r' );
++i;
}
}else{
s.insert( s.begin(), L'\r' );
++i;
}
}
}
GlobalUnlock( hg );
}
}
CloseClipboard();
}
}

void CopyText(HWND hWnd)
{
    if(hWnd == NULL) return;
    if(!OpenClipboard(hWnd)) return;
    EmptyClipboard();
    
    DWORD dwSelStart, dwSelEnd;
    SendMessage(hWnd, EM_GETSEL, (WPARAM)&dwSelStart, (LPARAM)&dwSelEnd);
    if(dwSelStart == dwSelEnd) // zero length selection
    {
        CloseClipboard();
        return;
    } // if(dwSelStart == dwSelEnd)
    
    DWORD dwStart, dwEnd;
    if(dwSelStart < dwSelEnd)
    {
        dwStart = dwSelStart;
        dwEnd = dwSelEnd;
    }
    else
    {
        dwStart = dwSelEnd;
        dwEnd = dwSelStart;
    } // if(dwStart < dwEnd)
    
    // length selection
    int nLength = dwEnd - dwStart;
    
    TCHAR buff[MAXCHAR];
    GetWindowText(hWnd, buff, sizeof(buff));
    
    HGLOBAL hglbCopy = GlobalAlloc(GMEM_MOVEABLE, (nLength + 1) * sizeof(TCHAR));
    if(hglbCopy == NULL)
    {
        CloseClipboard();
        return;
    } // if(hglbCopy == NULL)
    
    LPTSTR lptstrCopy = (TCHAR*)GlobalLock(hglbCopy);
    memcpy(lptstrCopy, &buff[dwStart], nLength * sizeof(TCHAR));
    lptstrCopy[nLength] = _T('\0');
    GlobalUnlock(hglbCopy);
    #ifdef UNICODE
    SetClipboardData(CF_UNICODETEXT, hglbCopy);
    #else
    SetClipboardData(CF_TEXT, hglbCopy);
    #endif
    CloseClipboard();
    
    GlobalFree(hglbCopy);
    GlobalFree(lptstrCopy);
}

int sampleWOwinAPI() //coping file without winApi
{
	char * buffer;
	buffer = new char;
	ifstream infile("InFile.txt", ios::binary);
	ofstream outfile("OutFile.txt", ios::binary);
	if(!infile||!outfile) {
		cout << "Oops...\n";
		return 1;
	}
	infile.read(buffer, sizeof(char));
	while (!infile.eof()) {
		outfile.write(buffer, sizeof(char));
		infile.read(buffer, sizeof(char));
	}
	infile.close();
	outfile.close();
	delete buffer;
}

int main()
{
	//readTXTfile();
	return 0;
}
