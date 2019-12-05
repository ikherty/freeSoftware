// Реализовать следующую схему испытаний: испытывающий процесс, который
// замеряет время, запускает процесс с условно предсказуемы временем выполнения.
// Требуется выполнить измерения времени выполнения для 10, 20 и 30 последовательно
// запущенных однотипных процесса с предсказуемым временем выполнения. Провести
// статистический анализ измерений.

program VAR2_3;
{$APPTYPE CONSOLE}
uses
  Windows;
const m=2048;
const q=3 ;
var

    was,now,fr,was10,now10 ,was20,now20,was30,now30   :Int64;
    t1,t10,t20,t30                                    :array[1..q]of real;
    timegone1,timegone10,timegone20,timegone30        :real;
    h1,h10,h20,h30                                    :hFile;
    cs,j ,i ,k,n ,w                                   :DWORD;
    ch                                                :byte;

begin

for w:=1 to q do
begin
writeln('*********************');
    QueryPerformanceCounter(was);
    h1 := Createfile('example.dat',Generic_write,0,nil,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
    for j:=1 to m do
       begin
       ch:=random(256);
       writefile(h1,ch,1,cs,nil);
       end;
  CloseHandle(h1);
  QueryPerformanceCounter(now);
  QueryPerformanceFrequency(fr);
  timegone1:=(now-was)/fr;        // время в с.
   writeln('Time for 1 ',timegone1);


   QueryPerformanceCounter(was10);
   for i:=1 to 10 do
   begin
    h10 := Createfile('example10.dat',Generic_write,0,nil,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
    for j:=1 to m do
       begin
       ch:=random(256);
       writefile(h10,ch,1,cs,nil);
       end;
   CloseHandle(h10);
  end;
  QueryPerformanceCounter(now10);
  QueryPerformanceFrequency(fr);
  timegone10:=(now10-was10)/fr;        // время в с.
   writeln('Time for 10 ',timegone10);


   QueryPerformanceCounter(was20);
   for n:=1 to 20 do
   begin
    h20 := Createfile('example20.dat',Generic_write,0,nil,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
    for j:=1 to m do
       begin
       ch:=random(256);
       writefile(h20,ch,1,cs,nil);
       end;
  CloseHandle(h20);
  end;
  QueryPerformanceCounter(now20);
  QueryPerformanceFrequency(fr);
  timegone20:=(now20-was20)/fr;        // время в с.
   writeln('Time for 20 ',timegone20);



   QueryPerformanceCounter(was30);
   for k:=1 to 30 do
   begin
    h30 := Createfile('example30.dat',Generic_write,0,nil,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
    for j:=1 to m do
       begin
       ch:=random(256);
       writefile(h30,ch,1,cs,nil);
       end;
  CloseHandle(h30);
  end;
  QueryPerformanceCounter(now30);
  QueryPerformanceFrequency(fr);
  timegone30:=(now30-was30)/fr;        // время в с.
   writeln('Time for 30 ',timegone30);

t1[w]:=timegone1;
t10[w]:=timegone10;
t20[w]:=timegone20;
t30[w]:=timegone30;

end;
writeln;

{for w:=1 to q do
begin
 writeln(t1[w]);
end; }

writeln;
write('For exit pres ENTER ');
  readln;
end.

http://www.cyberforum.ru/visual-cpp/thread1753022.html
