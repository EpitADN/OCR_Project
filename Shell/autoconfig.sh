#!/bin/bash

size=$1
filename=_config.txt


echo $1 > $filename
echo $1 >> $filename
file=$(pwd)/$filename

cd Resource/

ls -AqU | wc -l >> $file

for directory in *; do
	echo -n $directory >> $file
done

echo >> $file

for directory in *; do
	cd $directory
	ls -U | wc -l >> $file
	cd ..
done

mv $file ./
