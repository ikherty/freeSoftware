#!/bin/bash
#Напишите программу, запускающую указанную команду, и чтобы она возвращала статус вызова exit выполняемой команды. Что должно происходить, если вызов wait возвращает значение -1?

if [ -z $1 ]
then
echo "Command didnt write. Write command:"
read command
else
command=$1
fi
function myfunc{
`$1`
exit()
}
#`$command`
result=$(myfunc command)
echo "The value is $result"
echo $?
exit 0
