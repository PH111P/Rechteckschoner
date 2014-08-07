#!/bin/sh

# Use the script in this file to bring life to your desktop!

./rechteckschoner -w 1366 -h 768 -d 10 -b 8 -c 3 -o ./ 			#init call, generate .tmp
while true; do
	sleep 5s
	feh  --bg-scale './rechteckschoner.png'
	./rechteckschoner -w 1366 -h 768 -d 10 -b 8 -c 3 -t .tmp -o ./ 	#use generated tmp and change only parts
done