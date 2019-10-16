 
//////////////////////////////////////////////////////////////////////
//     Функция чтения записи байт из (в) virgRDWRBuff[]
//                           или  из (в) vchrgRDWRBuf[]
//     int virgRDWRBuff[n]; и char vchrgRDWRBuf[n]; должны быть объявлены
//                                                  вне функции
// Функция принимает:         
//      имя директории                vasFileDir
//      имя файла                     vasFileName
//      режим чтения записи           viRegime 0 - чтение 1 - запись
//      смещение  в элементах int     viSeek  
//      число байт для записи/чтения  viNumber
//      что пишем                     viType   0 - целое 1 - char
/////////////////////////////////////////////////////////////////////
int        __fastcall
TForm1::iRDWR(AnsiString &vasFileDir,AnsiString vasFileName,
              int viRegime,int viSeek,int viNumber,int viType)
{
 HFILE       hFile;
 AnsiString  vasFileName=vasFileDir+"\\"+vasFileName;
 DWORD       dwCounter;
 OFSTRUCT    tOfStr;
 tOfStr.cBytes = sizeof tOfStr;
 // Открыть файл
 hFile = OpenFile(vasFileName.c_str(),&tOfStr,OF_READWRITE);
 if(hFile == HFILE_ERROR)
 {
  CloseHandle(HANDLE(hFile));
  //Сообщение об ошибке
  return 1;
 }
 BY_HANDLE_FILE_INFORMATION bhFileInformation;
 GetFileInformationByHandle
 (
  HANDLE(hFile), // Дескриптор файла
  // Адрес структуры, в которой сохраняется информация
  &bhFileInformation    
 );
 viRazmer=bhFileInformation.nFileSizeLow;
 //сдвинуться
 switch(viType)
 {
  case 0:
   if(_llseek(hFile,viSeek*sizeof(int),0) != (long)(viSeek*sizeof(int)))
   {
    CloseHandle(HANDLE(hFile));
    //Сообщение об ошибке
   return 1;
   }
   break;
  case 1:
   if(_llseek(hFile,viSeek*sizeof(char),0) != (long)(viSeek*sizeof(char)))
   {
    CloseHandle(HANDLE(hFile));
    //Сообщение об ошибке
   return 1;
   }
  break;
 }
 // считать (записать)данные из (в) файл
 switch(viRegime)
 {
  case 1:
   if(viType == 0)
   {
    if(!WriteFile(HANDLE(hFile),virgRDWRBuff,
                  (DWORD)(viNumber*sizeof(int)),&dwCounter,0))
    {
     //Сообщение об ошибке
     CloseHandle(HANDLE(hFile));
    return 1;
    }
   }else
   {
    if(!WriteFile(HANDLE(hFile),(char far*) vchrgRDWRBuf,
               (DWORD)(viNumber*sizeof(char)),&dwCounter,0))
    {
     //Сообщение об ошибке
     CloseHandle(HANDLE(hFile));
     return 1;
    }
   }//if(viType == 0)
  break;
  case 0:
   if(viType == 0)
   {
    if(!ReadFile(HANDLE(hFile),virgRDWRBuff,
                (DWORD)(viNumber*sizeof(int)),&dwCounter,0))
    {
     //Сообщение об ошибке
     CloseHandle(HANDLE(hFile));
     return 1;
    }
   }else
   {
    if(!ReadFile(HANDLE(hFile),(char far*) vchrgRDWRBuf,
               (DWORD)(viNumber*sizeof(char)),&dwCounter,0))
    {
     //Сообщение об ошибке
     CloseHandle(HANDLE(hFile));
     return 1;
    }
   }//if(viType == 0)
  break;
 }//switch(viRegime)
 CloseHandle(HANDLE(hFile));
return 0;
}
