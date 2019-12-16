#!/bin/bash
#Объединить все файлы из указанного каталога с расширением ".txt" в один файл.  Имя каталога и файла вводится при выполнении сценария или задаётся в качестве параметра.
if [ -z $1 ]||[ -z $2 ]
then
echo "file name:"
read file
echo "Dir:"
read dir
elif [ !-d $2 ]
then 
exit 1
else
file=$1
dir=$2
fi

cd $dir
touch $file
cat `ls | grep.txt` > $file

exit 0
