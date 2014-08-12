#!/bin/sh

# Use the script in this file to bring life to your desktop!

~/Projects/Rechteckschoner/rechteckschoner -w 1366 -h 768 -d 12 -b 3 -c 3 -o ~/Projects/Rechteckschoner/ -i			#init call, generate .tmp
feh  --bg-scale '~/Projects/Rechteckschoner/rechteckschoner.png'

while true; do
	sleep 2s
	~/Projects/Rechteckschoner/rechteckschoner -w 1366 -h 768 -d 12 -b 3 -c 3 -r -t ~/Projects/Rechteckschoner/.tmp -o ~/Projects/Rechteckschoner/	#use generated tmp and change only parts
	feh  --bg-scale '~/Projects/Rechteckschoner/rechteckschoner.png'
	
	sleep 30s
	~/Projects/Rechteckschoner/rechteckschoner -w 1366 -h 768 -d 12 -b 3 -c 3 -i -t ~/Projects/Rechteckschoner/.tmp -o ~/Projects/Rechteckschoner/	
	feh  --bg-scale '~/Projects/Rechteckschoner/rechteckschoner.png'
done
