#!/bin/bash

size=$1

cd Resource/

for directory in ./*; do
	echo $directory
	cd $directory/

	for file in ./*; do
		read width height < <(identify -format "%w %h" "$file")
		if [ $width != $size ] || [ $height != $size ]; then
			rm $file
		fi
	done

	cd ..
done
