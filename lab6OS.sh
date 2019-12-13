#!/bin/bash

if [ -z «$1» ]
then
echo "Директория не задана"
dir=/home/valentina/docs/
exit 1
else
dir=$1
fi
ls . | egrep 'd' | xargs -i -t -r cp {} dir

exit 0
